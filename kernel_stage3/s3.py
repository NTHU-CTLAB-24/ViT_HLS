from einops import rearrange, reduce
from timm.models.layers.activations import *
from timm.models.layers import DropPath, trunc_normal_, create_attn
from timm.models.efficientnet_blocks import num_groups, SqueezeExcite as SE
from model.basic_modules import get_norm, get_act, ConvNormAct, LayerScale2D, MSPatchEmb
import numpy as np
from model import MODEL

inplace = True

class iRMB(nn.Module):

    def __init__(self, dim_in, dim_out, norm_in=True, has_skip=True, exp_ratio=1.0, norm_layer='bn_2d',
                 act_layer='silu', v_proj=True, dw_ks=3, stride=1, dilation=1, se_ratio=0.0, dim_head=64, window_size=7,
                 attn_s=True, qkv_bias=False, attn_drop=0., drop=0., drop_path=0., v_group=False, attn_pre=False):
        super().__init__()
        # get_norm回傳的是一個norm layer的instance，而(dim_in)則為其建構參數
        self.norm = get_norm(norm_layer)(dim_in).eval() if norm_in else nn.Identity()
        dim_mid = int(dim_in * exp_ratio)  # pointwise升維後的維度
        self.has_skip = (dim_in == dim_out and stride ==1) and has_skip  # 維度相同才可以有short cut connect
        self.attn_s = attn_s
        if self.attn_s:  # 使用attention
            assert dim_in % dim_head == 0, 'dim should be divisible by num_heads'
            self.dim_head = dim_head
            self.window_size = window_size
            self.num_head = dim_in // dim_head  # 輸入維度需要可以整除attention head的維度，數量才可以是整數
            self.scale = self.dim_head ** -0.5
            self.attn_pre = attn_pre
            # 此處做kernel_size為1的conv，目的是將輸入做線性變換，以便後續捕捉feature之間的相關性(pointwise conv)
            # qk是將key和query組合在一起的tensor，在文中X=Q=K，因此具有兩倍於input的feature維度
            self.qk = ConvNormAct(dim_in, int(
                dim_in * 2), kernel_size=1, bias=qkv_bias, norm_layer='none', act_layer='none')
            # v是x經過pointwise conv進行升維(channels擴充)後的feature map
            self.v = ConvNormAct(dim_in, dim_mid, kernel_size=1, groups=self.num_head if v_group else 1,
                                 bias=qkv_bias, norm_layer='none', act_layer=act_layer, inplace=inplace)
            
            self.attn_drop = nn.Dropout(attn_drop)
        else:
            if v_proj:
                self.v = ConvNormAct(dim_in, dim_mid, kernel_size=1, bias=qkv_bias,
                                     norm_layer='none', act_layer='gelu', inplace=inplace)
            else:
                self.v = nn.Identity()
        # DW-Conv: conv_local先做一次DepthWise-Conv萃取局部特徵，之後再應用SE模塊對通道的重要程度加權，以增強特徵
        self.conv_local = ConvNormAct(dim_mid, dim_mid, kernel_size=dw_ks, stride=stride,
                                      dilation=dilation, groups=dim_mid, norm_layer='bn_2d', act_layer='silu', inplace=inplace)
        self.se = SE(dim_mid, rd_ratio=se_ratio, act_layer=get_act(
            act_layer)) if se_ratio > 0.0 else nn.Identity()

        # pointwise的降維，將DW-Conv的結果降維成與進入iRMB之前的維度相同(即dim_out=dim_in)
        self.proj_drop = nn.Dropout(drop)
        self.proj = ConvNormAct(dim_mid, dim_out, kernel_size=1,
                                norm_layer='none', act_layer='none', inplace=inplace)
        self.drop_path = DropPath(drop_path) if drop_path else nn.Identity()

    def forward(self, x):
        shortcut = x  # 保留原始訊息
        #print(x[0][0][0][0].item())
        x = self.norm(x)  # 先做一次normalize
        #print(x[0][0][0][0])
        #print(x[0][0][0][0].item())
        #print(x[0])
        B, C, H, W = x.shape
        #print("B C H W :",B, C, H, W)
        #for i in range(B):
        #    for j in range(C):
        ##        for k in range(H):
        #            for l in range(W):
        #                print(x[i][j][k][l].item(),end=" ")
        #            print("")
        #        print("")
        #    print("")
        #print(x,"1234564")
        #print("   ",x[0])
        #print(self.attn_s)
        
        if self.attn_s:
            # padding
            #print(self.window_size,"999999999999")
            if self.window_size <= 0:
                window_size_W, window_size_H = W, H
            else:
                window_size_W, window_size_H = self.window_size, self.window_size
            #print("window_size_W, window_size_H : ", window_size_W, window_size_H);
            pad_l, pad_t = 0, 0
            pad_r = (window_size_W - W % window_size_W) % window_size_W
            pad_b = (window_size_H - H % window_size_H) % window_size_H
            #print("pad_l pad_t pad_r pad_b : ",pad_l, pad_t, pad_r, pad_b)
            # 根據window_size做padding，之後切割
            
            x = F.pad(x, (pad_l, pad_r, pad_t, pad_b, 0, 0,))
            #print("   ",x[0][0][0][0].item())
            #print("afterPad x : ",x.shape)
            #print("afterPad x : ",x)
            #print(x[0][0])
            n1, n2 = (H + pad_b) // window_size_H, (W +
                                                    pad_r) // window_size_W  # n1, n2分別為高度和寬度會有多少個patch
            #print("n1 n2 : ",n1,n2)
            x = rearrange(
                x, 'b c (h1 n1) (w1 n2) -> (b n1 n2) c h1 w1', n1=n1, n2=n2).contiguous()
            #print("rearrangex : ",x.shape)
            #print("   ",x[0][0])
            #print(x[0])
            # rearrange將維度轉換為(b * n1 * n2)個patch，每一個Patch的維度為c * h1 * w1
            # attention
            b, c, h, w = x.shape
            qk = self.qk(x)
            #print("   ",qk[0][0])
            # q和k分別有batch * heads個vector，每個vector的維度為h * w * dim_head
            #print("rearrangex : ",qk.shape)
            qk = rearrange(qk, 'b (qk heads dim_head) h w -> qk b heads (h w) dim_head',
                           qk=2, heads=self.num_head, dim_head=self.dim_head).contiguous()
            #print("in_qk : ",qk.shape)
            #print("   ",qk[0][0][0][0])
            q, k = qk[0], qk[1]  # 分別取得q和k，兩者維度相同
            #print(q.shape)
            ##print(k.shape)
            #print("0000000000000000000000000000000000000000000000000000000000000000000000")
            #print(q[0])
            #print(k[0])
            #print(q[0][0])
            # 計算注意力，@為矩陣乘法操作
            # k.transpose(-2, -1)將k的形狀從(batch_size, num_heads, h*w, dim_head)轉換為(batch_size, num_heads, dim_head, h*w)
            # (q * k.T)=>得到一個(batch_size, num_heads, dim_head, h*w, h*w)的矩陣？ h*w和h*w抱有疑惑
            # self.scale = self.dim_head ** -0.5(即為1 / sqrt(dim_head))，用於縮放注意力分數
            #print("scale : ", self.scale)
            attn_spa = (q @ k.transpose(-2, -1)) * self.scale
            #print("   ",attn_spa[0][0][0])
            #print(attn_spa)
            #print(attn_spa.shape)
            attn_spa = attn_spa.softmax(dim=-1)
            
            #print(attn_spa.shape)
            #print(attn_spa)
            #print("   ",attn_spa[0][0][0])

            attn_spa = self.attn_drop(attn_spa)  # 做attention drop可以提高泛化
            # 如果做attention預處理，則將x(原始訊息)做形狀轉換，與注意力矩陣相乘，最後做pointwise conv(self.V)得到feature map
            if self.attn_pre:
                #print("##########################################")
                #print("heads=self.num_head : ", self.num_head)
                x = rearrange(
                    x, 'b (heads dim_head) h w -> b heads (h w) dim_head', heads=self.num_head).contiguous()
                #print("afterRearrangeX2 : ",x.shape)
                #print("   ",x[0][0][0][0].item())

                x_spa = attn_spa @ x
                #print("afterQKXMultiplication : ",x_spa.shape)
                
                
                #print(x_spa)
                #print("   ",x_spa[0][0][0])
                x_spa = rearrange(x_spa, 'b heads (h w) dim_head -> b (heads dim_head) h w',
                                  heads=self.num_head, h=h, w=w).contiguous()
                #for i in range(40):
                #print(x_spa[0][0])
                #print()
                #print("afterRearrangeQKX : ",x_spa.shape)
                #print(x_spa)
                x_spa = self.v(x_spa)
                #print("   ",x_spa[0][0][0][0].item())
                #print("QKV : ",x_spa.shape)
                #print(x_spa)
            # 若沒有attn_pre，即為正常的self-attention，在將x做pointwise升維後，將qk的結果與v(加權分數)相乘，得到x_spa(注意力分數)=>同為feature map
            else:
                v = self.v(x)
                v = rearrange(
                    v, 'b (heads dim_head) h w -> b heads (h w) dim_head', heads=self.num_head).contiguous()
                x_spa = attn_spa @ v
                x_spa = rearrange(x_spa, 'b heads (h w) dim_head -> b (heads dim_head) h w',
                                  heads=self.num_head, h=h, w=w).contiguous()
            # unpadding
            # 確保feature map和x的維度是相同的，因為在後續需要做shortcut
            #print(x_spa)
            x = rearrange(
                x_spa, '(b n1 n2) c h1 w1 -> b c (h1 n1) (w1 n2)', n1=n1, n2=n2).contiguous()
            #print("rearrange : ", x.shape)
            #print("   ",x[0][0][0][0].item())
            #print(x)
            if pad_r > 0 or pad_b > 0:
                # :H, :W代表只有取到原本維度，後面多出來的(padding)就丟掉
                x = x[:, :, :H, :W].contiguous()
            
            #print("   ",x[0][0][0][0].item())
            #print(x)
            #for i in range(14):
            #    for j in range(14):
            #        print(x[0][0][i][j])
            #    print()
            #print("rearrange : ", x.shape,"\n\nbreak******************************\n\n\n")
        else:  # 如果沒有要做self-attion，就只有將x做Pointwise升維成v，再接續DW-conv（可參考架構圖）
            x = self.v(x)
        # 根據是否有shortcut決定是否要加上x(原始訊息)
        x = x + self.se(self.conv_local(x)) if self.has_skip else self.se(self.conv_local(x))
        # 做完DW-conv後，再做pointwise降維，變回原本的channels數，即為將高維度萃取特徵完後的feature map嵌入到低維度
        x = self.proj_drop(x)
        x = self.proj(x)
        # 加上shortcut的x(原始訊息)
        x = (shortcut + self.drop_path(x)) if self.has_skip else x
        return x


# input parameters
BATCH_SIZE = 1
CHANNEL_IN = 48
HEIGHT_IN = 28
WIDTH_IN = 28

# EMO parameters
depths = 8
dim_in = 48
dim_out = 80
norm_in = True
has_skip = False
exp_ratio = 3
norm_layer = 'ln_2d'
act_layer = 'gelu'
v_proj = True
dw_ks = 5
stride = 1
dilation = 1
se_ratio = 0
dim_head = 20
window_size = 7
attn_s = True
qkv_bias = True
attn_drop = 0
drop = 0
drop_path = 0
v_group = False
attn_pre = True

state_dict = torch.load('./resources/EMO_1M/net.pth',
                        map_location=torch.device('cpu'))


def main():
    # init module
    emb_dim_pre = dim_in # previous stage dim_out
    emb_dim_out = dim_out # this stage dim_out
    layers = []
    for idx in range(depths): # 決定每一個stage有幾個iRMB
        if idx == 0:
            stride, has_skip, attn_s, exp_ratio = 2, False, False, 6
        else:
            stride, has_skip, attn_s, exp_ratio = 1, True, True, 3
        # iRMB constructor
        print(idx)
        layers.append(iRMB(
            emb_dim_pre, emb_dim_out, norm_in=True, has_skip=has_skip, exp_ratio=exp_ratio,
            norm_layer=norm_layer, act_layer=act_layer, v_proj=True, dw_ks=dw_ks,
            stride=stride, dilation=1, se_ratio=se_ratio,
            dim_head=dim_head, window_size=window_size, attn_s=attn_s,
            qkv_bias=qkv_bias, attn_drop=attn_drop, drop=drop, drop_path=drop_path, v_group=v_group,
            attn_pre=attn_pre
        ))
        emb_dim_pre = emb_dim_out


    # init input
    x = torch.zeros(BATCH_SIZE, CHANNEL_IN, HEIGHT_IN, WIDTH_IN)
    for n in range(BATCH_SIZE):
        for c in range(CHANNEL_IN):
            for h in range(HEIGHT_IN):
                for w in range(WIDTH_IN):
                    x[n, c, h, w] = (n+c+h+w) % 25
    #print(x.shape)
    #print()
    #load parameter
    layers[0].norm.norm.weight.data = state_dict["stage3.0.norm.norm.weight"]
    layers[0].norm.norm.bias.data = state_dict["stage3.0.norm.norm.bias"]
    layers[0].v.conv.weight.data = state_dict["stage3.0.v.conv.weight"]
    layers[0].v.conv.bias.data = state_dict["stage3.0.v.conv.bias"]
    layers[0].conv_local.conv.weight.data = state_dict["stage3.0.conv_local.conv.weight"]
    layers[0].conv_local.norm.weight.data = state_dict["stage3.0.conv_local.norm.weight"]
    layers[0].conv_local.norm.bias.data = state_dict["stage3.0.conv_local.norm.bias"]
    layers[0].conv_local.norm.running_mean = state_dict["stage3.0.conv_local.norm.running_mean"]
    layers[0].conv_local.norm.running_var = state_dict["stage3.0.conv_local.norm.running_var"]
    layers[0].proj.conv.weight.data = state_dict["stage3.0.proj.conv.weight"]
    layers[1].norm.norm.weight.data = state_dict["stage3.1.norm.norm.weight"]
    layers[1].norm.norm.bias.data = state_dict["stage3.1.norm.norm.bias"]
    layers[1].qk.conv.weight.data = state_dict["stage3.1.qk.conv.weight"]
    layers[1].qk.conv.bias.data = state_dict["stage3.1.qk.conv.bias"]
    layers[1].v.conv.weight.data = state_dict["stage3.1.v.conv.weight"]
    layers[1].v.conv.bias.data = state_dict["stage3.1.v.conv.bias"]
    layers[1].conv_local.conv.weight.data = state_dict["stage3.1.conv_local.conv.weight"]
    layers[1].conv_local.norm.weight.data = state_dict["stage3.1.conv_local.norm.weight"]
    layers[1].conv_local.norm.bias.data = state_dict["stage3.1.conv_local.norm.bias"]
    layers[1].conv_local.norm.running_mean = state_dict["stage3.1.conv_local.norm.running_mean"]
    layers[1].conv_local.norm.running_var = state_dict["stage3.1.conv_local.norm.running_var"]
    layers[1].proj.conv.weight.data = state_dict["stage3.1.proj.conv.weight"]
    
    layers[2].norm.norm.weight.data = state_dict["stage3.2.norm.norm.weight"]
    layers[2].norm.norm.bias.data = state_dict["stage3.2.norm.norm.bias"]
    layers[2].qk.conv.weight.data = state_dict["stage3.2.qk.conv.weight"]
    layers[2].qk.conv.bias.data = state_dict["stage3.2.qk.conv.bias"]
    layers[2].v.conv.weight.data = state_dict["stage3.2.v.conv.weight"]
    layers[2].v.conv.bias.data = state_dict["stage3.2.v.conv.bias"]
    layers[2].conv_local.conv.weight.data = state_dict["stage3.2.conv_local.conv.weight"]
    layers[2].conv_local.norm.weight.data = state_dict["stage3.2.conv_local.norm.weight"]
    layers[2].conv_local.norm.bias.data = state_dict["stage3.2.conv_local.norm.bias"]
    layers[2].conv_local.norm.running_mean = state_dict["stage3.2.conv_local.norm.running_mean"]
    layers[2].conv_local.norm.running_var = state_dict["stage3.2.conv_local.norm.running_var"]
    layers[2].proj.conv.weight.data = state_dict["stage3.2.proj.conv.weight"]
    layers[3].norm.norm.weight.data = state_dict["stage3.3.norm.norm.weight"]
    layers[3].norm.norm.bias.data = state_dict["stage3.3.norm.norm.bias"]
    layers[3].qk.conv.weight.data = state_dict["stage3.3.qk.conv.weight"]
    layers[3].qk.conv.bias.data = state_dict["stage3.3.qk.conv.bias"]
    layers[3].v.conv.weight.data = state_dict["stage3.3.v.conv.weight"]
    layers[3].v.conv.bias.data = state_dict["stage3.3.v.conv.bias"]
    layers[3].conv_local.conv.weight.data = state_dict["stage3.3.conv_local.conv.weight"]
    layers[3].conv_local.norm.weight.data = state_dict["stage3.3.conv_local.norm.weight"]
    layers[3].conv_local.norm.bias.data = state_dict["stage3.3.conv_local.norm.bias"]
    layers[3].conv_local.norm.running_mean = state_dict["stage3.3.conv_local.norm.running_mean"]
    layers[3].conv_local.norm.running_var = state_dict["stage3.3.conv_local.norm.running_var"]
    layers[3].proj.conv.weight.data = state_dict["stage3.3.proj.conv.weight"]
    layers[4].norm.norm.weight.data = state_dict["stage3.4.norm.norm.weight"]
    layers[4].norm.norm.bias.data = state_dict["stage3.4.norm.norm.bias"]
    layers[4].qk.conv.weight.data = state_dict["stage3.4.qk.conv.weight"]
    layers[4].qk.conv.bias.data = state_dict["stage3.4.qk.conv.bias"]
    layers[4].v.conv.weight.data = state_dict["stage3.4.v.conv.weight"]
    layers[4].v.conv.bias.data = state_dict["stage3.4.v.conv.bias"]
    layers[4].conv_local.conv.weight.data = state_dict["stage3.4.conv_local.conv.weight"]
    layers[4].conv_local.norm.weight.data = state_dict["stage3.4.conv_local.norm.weight"]
    layers[4].conv_local.norm.bias.data = state_dict["stage3.4.conv_local.norm.bias"]
    layers[4].conv_local.norm.running_mean = state_dict["stage3.4.conv_local.norm.running_mean"]
    layers[4].conv_local.norm.running_var = state_dict["stage3.4.conv_local.norm.running_var"]
    layers[4].proj.conv.weight.data = state_dict["stage3.4.proj.conv.weight"]
    layers[5].norm.norm.weight.data = state_dict["stage3.5.norm.norm.weight"]
    layers[5].norm.norm.bias.data = state_dict["stage3.5.norm.norm.bias"]
    layers[5].qk.conv.weight.data = state_dict["stage3.5.qk.conv.weight"]   
    layers[5].qk.conv.bias.data = state_dict["stage3.5.qk.conv.bias"]
    layers[5].v.conv.weight.data = state_dict["stage3.5.v.conv.weight"]
    layers[5].v.conv.bias.data = state_dict["stage3.5.v.conv.bias"]
    layers[5].conv_local.conv.weight.data = state_dict["stage3.5.conv_local.conv.weight"]
    layers[5].conv_local.norm.weight.data = state_dict["stage3.5.conv_local.norm.weight"]
    layers[5].conv_local.norm.bias.data = state_dict["stage3.5.conv_local.norm.bias"]
    layers[5].conv_local.norm.running_mean = state_dict["stage3.5.conv_local.norm.running_mean"]
    layers[5].conv_local.norm.running_var = state_dict["stage3.5.conv_local.norm.running_var"]
    layers[5].proj.conv.weight.data = state_dict["stage3.5.proj.conv.weight"]
    layers[6].norm.norm.weight.data = state_dict["stage3.6.norm.norm.weight"]
    layers[6].norm.norm.bias.data = state_dict["stage3.6.norm.norm.bias"]
    layers[6].qk.conv.weight.data = state_dict["stage3.6.qk.conv.weight"]
    layers[6].qk.conv.bias.data = state_dict["stage3.6.qk.conv.bias"]
    layers[6].v.conv.weight.data = state_dict["stage3.6.v.conv.weight"] 
    layers[6].v.conv.bias.data = state_dict["stage3.6.v.conv.bias"]
    layers[6].conv_local.conv.weight.data = state_dict["stage3.6.conv_local.conv.weight"]
    layers[6].conv_local.norm.weight.data = state_dict["stage3.6.conv_local.norm.weight"]
    layers[6].conv_local.norm.bias.data = state_dict["stage3.6.conv_local.norm.bias"]
    layers[6].conv_local.norm.running_mean = state_dict["stage3.6.conv_local.norm.running_mean"]
    layers[6].conv_local.norm.running_var = state_dict["stage3.6.conv_local.norm.running_var"]
    layers[6].proj.conv.weight.data = state_dict["stage3.6.proj.conv.weight"]
    layers[7].norm.norm.weight.data = state_dict["stage3.7.norm.norm.weight"]
    layers[7].norm.norm.bias.data = state_dict["stage3.7.norm.norm.bias"]
    layers[7].qk.conv.weight.data = state_dict["stage3.7.qk.conv.weight"]
    layers[7].qk.conv.bias.data = state_dict["stage3.7.qk.conv.bias"]
    layers[7].v.conv.weight.data = state_dict["stage3.7.v.conv.weight"]
    layers[7].v.conv.bias.data = state_dict["stage3.7.v.conv.bias"]
    layers[7].conv_local.conv.weight.data = state_dict["stage3.7.conv_local.conv.weight"]
    layers[7].conv_local.norm.weight.data = state_dict["stage3.7.conv_local.norm.weight"]
    layers[7].conv_local.norm.bias.data = state_dict["stage3.7.conv_local.norm.bias"]
    layers[7].conv_local.norm.running_mean = state_dict["stage3.7.conv_local.norm.running_mean"]
    layers[7].conv_local.norm.running_var = state_dict["stage3.7.conv_local.norm.running_var"]
    layers[7].proj.conv.weight.data = state_dict["stage3.7.proj.conv.weight"]

    # forward
    idx = 0
    for layer in layers:
            
            
        
        x = layer(x)
        print()
        if(idx == 0):
            print()
            print("In iRMB depth: ", idx)
            # print(x.shape)
            print("x[0, 0, :7, :7]")
            print(x[0, 0, :7, :7])
            print("x[0, 79, 7:14, 7:14]")
            print(x[0, 79, 7:14, 7:14])
    
        '''
        state_dict = layers[idx].qk.state_dict()
        weights_data = state_dict['conv.weight'].numpy()
        biases_data = state_dict['conv.bias'].numpy()

        print("Weight data:")
        print(weights_data.shape)

        print("Bias data:")
        print(biases_data)
        print()'''
        idx += 1
    print(x)
if __name__ == '__main__':
    main()
