#include <iostream>
#include <array>
#include <cmath>

#define T float
#define DIM 5

struct LayerNormParameter {
    std::array<float, DIM> weights;
    std::array<float, DIM> bias;

    long long count() {
        return DIM * 2;
    }
};

class LayerNorm {
public:
    static void forward(std::array<T, DIM> &input, std::array<T, DIM> &output, LayerNormParameter&p) {
        T sum = 0;
        T sum2 = 0;
        for (int i = 0; i < DIM; ++i) {
            sum += input[i];
            sum2 += input[i] * input[i];
        }
        T avg = sum / DIM; //mean of the input array
        T avg2 = sum2 / DIM;
        T var = avg2 - avg * avg; //Var(x) = E[X^2] - E[X]^2
        T sq_var = sqrt(var + 1e-5); //square root of the variance of the input
        for (int i = 0; i < DIM; ++i) {
            output[i] = (input[i] - avg) / sq_var * p.weights[i] + p.bias[i];
        }
    }
};

int main() {
    // Sample input data
    std::array<float, DIM> input = {1.0, 2.0, 3.0, 4.0, 5.0};

    // Sample LayerNormParameter
    LayerNormParameter params;
    params.weights = {0.5, 1.0, 0.5, 1.0, 0.5};
    params.bias = {-1.0, 0.0, 1.0, 2.0, 3.0};

    // Output array to store the result
    std::array<float, DIM> output;

    // Call LayerNorm::forward
    LayerNorm::forward(input, output, params);

    // Display the result
    std::cout << "Input: ";
    for (const auto& value : input) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Output: ";
    for (const auto& value : output) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}