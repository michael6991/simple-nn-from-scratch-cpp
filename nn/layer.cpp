#include "layer.hpp"
#include "../utils/matrix.hpp"

using namespace std;


// Return the sigmoid result of x.
// x can be positive or negative float.
// The result is bound to be between [0, 1].
float sigmoid(float x)
{
    return 1 / (1 + exp(-x));
}

// Return the rectified linear unit of x. (ReLU)
// This is a sort of activation function that is easier to compute
// than the sigmoid.
float relu(float x)
{
    return max(float(0), x);
}


template <class T>
int Layer::copy_vector(const vector<T> &src, vector<T> &dst)
{
    // TODO: check type equality

    // that's actually a deep copy. New memory is allocated for dst vector
    dst = src;
}


// Copy float src input to destination input (perceptrons)
int Layer::copy_vector(const vector<float> &src, vector<mlp_t *> &dst)
{
    if (dst.size() == 0 || src.size() == 0) {
        printf("size of src or dst vector is 0\n");
        return -1;
    }
    if (dst.size() != src.size()) {
        printf("sizes of vectors don't  match\n");
        return -1;
    }

    for (auto i = 0; i < src.size(); i++) {
        ((mlp_t *)(dst[i]))->a = src[i];
    }

    return 0;
}

void Layer::print_layer(const string content)
{
    printf("%s w•a+b: ", content.c_str());
    for (auto p : perceptrons) {
        printf(" %f•%f+%f ",p->w, p->a, p->b);
    }
    printf("\n");
}

// Compute the a single forward propagation from current layer to the next layer.
// 
// 1) Organize all the inputs in a column vector.
//    (inputs can be activations from previous layer or just new data feed from outside).
// 2) Organize all the weights in a matrix, where each row in this matrix
//    corresponds to the connections between one layer and a particular neuron
//    in the next layer.
// 
//     { w00 w01 ... w0n }          [x0]         [b0]
//     { w10 w11 ... w1n }          [x1]         [b1]
//     {  .   .  .    .  }          [. ]         [. ]
// W = {  .   .   .   .  }      x = [. ]     b = [. ]
//     {  .   .    .  .  }          [. ]         [. ]
//     { wk0 wk1 ... wkn }          [xn]         [bn]
// 
// 3) Transpose the weights matrix (T notation).
// 4) Do a matrix - vector product and add vector of biases to the product.
// 5) Calculate the activation function on each one of the elements in the final product vector:
//    y = sigma(WTx + b)
// 
float Layer::compute_layer()
{
    // vector<float> * x;





    return 0;
}


float Layer::grad_descent()
{
    return 0;
}
