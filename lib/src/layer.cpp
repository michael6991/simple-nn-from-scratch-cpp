#include "../include/layer.hpp"

using namespace std;


// Return the sigmoid result of x.
// x can be positive or negative float.
// The result is bound to be between [0, 1].
float sigmoid(float x){
    return 1 / (1 + exp(-x));
}

// Return the rectified linear unit of x. (ReLU)
// This is a sort of activation function that is easier to compute
// than the sigmoid.
/**
 *            |       .
 *            |     .
 *            |   .
 *            | .
 * _._._._._._.___________
 *            
 *  ReLU(x) = {x if x > 0, else 0 if x<= 0}
 */
float relu(float x){
    return max(float(0), x);
}

string Layer::get_name(){
    return this->name;
}


uint32_t Layer::get_n(){
    return this->n;
}


uint32_t Layer::get_num_edges(){
    return this->edges;
}


// Copy constructor implementation
Layer::Layer(const Layer &other)
{
    // Copy each member of other to this
    this->n = other.n;
    this->edges = other.edges;
    this->layer_n = other.layer_n;
    this->name = other.name;

    // TODO: ensure this:
    // that's actually a deep copy. New memory is allocated for dst vector
    this->x = other.x;
    this->w = other.w;
    this->b = other.b;
    this->y = other.y;
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
        printf("sizes of vectors don't match\n");
        return -1;
    }
    for (auto i = 0; i < src.size(); i++)
    for (auto i = 0; i < src.size(); i++)
        ((mlp_t *)(dst[i]))->a = src[i];
    return 0;
}

void Layer::print_layer(const string content)
{
    printf("\n%s: w•x+b = y \n\n", content.c_str());
    printf("w      x      b      y\n");
    printf("-------------------------\n");
    for (auto i = 0; i < this->n; i++)
        printf("%.2f • %.2f + %.2f = %.2f\n", this->w[i], this->x[i], this->b[i], this->y[i]);

    printf("\n");
}

// Compute the a single forward propagation from current layer to the next layer.
// 
// 1) Organize all the inputs in a column vector.
//    (inputs can be activations from previous layer or just new data feed from outside).
// 2) Organize all the weights in a matrix, where each row in this matrix
//    corresponds to the connections between one layer and a particular perceptron
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
// 4) Do a matrix - vector product and add a vector of biases to the product.
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
