#include "layer.hpp"
#include "perceptron.hpp"
#include <stdint.h>
#include <vector>
#include <algorithm>


class Layer
{
    private:
        uint32_t n = 0;                          // total number of perceptrons
        uint32_t edges = 0;                      // toatl number of edges between this layer and the next
        std::vector<perceptron_t *> perceptrons; // perceptrons vector of this layer
    public:
        Layer(uint32_t num_of_perc, bool init_random) : n(num_of_perc)
        {
            // initialize the layer with perceptrons
            for (uint32_t i = 0; i < n; i++) {
                perceptrons.push_back(perc_create(init_random));
            }
        }

};


// Return the sigmoid result of x.
// x can be positive or negative float.
// The result is bound to be between [0, 1].
// I'll refer to it as sigma.
float sigmoid(float x)
{
    return 1 / (1 + exp(-x));
}

// Return the rectified linear unit of x.
// This is a sort of activation function that is easier to compute.
float relu(float x)
{
    return std::max(0, x);
}

float compute_layer () {
    // Organize all the inputs in a column vector.
    // Organize all the weights in a matrix, where each row in this matrix
    // corresponds to the connections between one layer and a particular neuron
    // in the next layer.

    //     { w00 w01 ... w0n }          [x0]         [b0]
    //     { w10 w11 ... w1n }          [x1]         [b1]
    //     {  .   .  .    .  }          [. ]         [. ]
    // W = {  .   .   .   .  }      x = [. ]     b = [. ]
    //     {  .   .    .  .  }          [. ]         [. ]
    //     { wk0 wk1 ... wkn }          [xn]         [bn]

    // Do a matrix - vector product and add vector of biasses to the product.
    // Calculate the activation function on each of the elements in the final product vector:
    // y = sigma(Wx + b)

}



