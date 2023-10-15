# Generate code usage

### Step1 產生參數txt
- 首先在GPU工作站的EMO dir底下創建一個```stageX_parameters.txt``` 
- 到```printParameters.py```內找到註解```store parameters value to stageX_parameters.txt```
- 解開該段code的註解，並將code內的```stage1```更改成所需的stage
- 檢查```stageX_parameters.txt```內是否有正確產生出參數
- 將```stageX_parameters.txt```下載並複製到該work station的所需資料夾底下

### Step2 生成parametersName
- 根據```count_depth.py```將data和parameters分開
- 新增一個變數為```parametersName=[]```
- 使用GPU工作站內的```printParameters.py```，並找到裡面註解```generate parameters name for count_depth.py```
- 將該段code解除註解，並將code內```stage1```更改成所需的stage
- 執行後將output複製放入```parametersName```的```[]```內

### Step3 生成testbench參數初始化code
- 先將以下的code複製在testbench裡，並根據stageX更改`TODO`
    ```c++
    // init parameters value
        ifstream file("./stage1_parameters.txt"); // TODO: modify stageX
        if (!file.is_open())
            cerr << "Failed to open the parameter file." << std::endl;
        
        unordered_map<string, vector<float>> parameterData;
        string line;
        string current_key;
        while (std::getline(file, line))
        {
            if (!line.empty())
            {
                if (line[0] == 's'){ // key
                    current_key = line;
                    cout << "HOST-INFO: loading " << current_key << " value..." << endl;
                } 
                else
                {
                    istringstream iss(line);
                    float value;
                    while (iss >> value)
                    {
                        parameterData[current_key].push_back(value);
                    }
                }
            }
        }
    ```
- 使用```count_depth.py```內註解部份```generate code for testbench init parameters value```
- 執行後將output複製放在testbench裡（注意不要放在迴圈內，因為已經給定idx了）

### Step4 生成stageX_validate.py的參數初始化code
- 使用GPU工作站內的```printParameters.py```，並找到裡面註解```generate init code in stagex_validate```
- 將該段code解開註解，並將code內```stage1```更改成所需的stage
- 執行後將output複製放入```stageX_validate.py```內做參數初始化