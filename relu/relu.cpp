//
// Created by dianhsu on 2021/03/10.
//

#include <cmath>
#include <iostream>

#define DIM 512
// #define DEP 20

// class Relu {
// public:
//     static void forward(float (&input)[DIM], float (&output)[DIM]) {
//         for (int i = 0; i < DIM; ++i) {
//             if (input[i] < 0) {
//                 output[i] = 0;
//             } else {
//                 output[i] = input[i];
//             }
//         }
//     }
// };

void forward(float (&input)[DIM], float (&output)[DIM]) {
    for (int i = 0; i < DIM; ++i) {
        if (input[i] < 0) {
            output[i] = 0;
        } else {
            output[i] = input[i];
        }
    }
}


int main(){
    float inp[DIM];
    for(int i = 0; i < DIM; i++){
        inp[i] = i * pow(-1, i);
        std::cout << inp[i] << ' ';
    }

    std::cout << "Initialized input in interspersed positive/negatives\n";
    float out[DIM];
    // std::cout << "Zero initialize output\n";
    
    // Relu::forward(inp, out);
    forward(inp, out);

    float sum = 0, max = 0;
    for(int i = 0; i < DIM; i++){
        sum += out[i];
        if(out[i] > max) max = out[i];
    }
    std::cout << "Verify sum, max of vector: " << sum << ", " << max << "\n";

    return 0;
}