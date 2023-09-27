from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

out_height = 24
out_width = 24
path = 'C:\\Users\\justi\\Documents\\CT_lab\\ViT_HLS\\read_in\\source_test.jpg'

pic = Image.open(path)
target_size = min(pic.size)
# print(target_size)

left = int(pic.size[0] - target_size)/2
top = int(pic.size[1] - target_size)/2
right = int(pic.size[0] + target_size)/2
bottom = int(pic.size[1] + target_size)/2
pic = pic.crop((left, top, right, bottom)).rotate(90).resize((out_width, out_height))
rgb_split = Image.Image.split(pic)

# print(*list(rgb_split[0].getdata()) + list(rgb_split[1].getdata()) + list(rgb_split[2].getdata()))
out = open("test.txt", "w")
print(*list(rgb_split[0].getdata()) + list(rgb_split[1].getdata()) + list(rgb_split[2].getdata()), file=out)
out.close()