#include "nn.hpp"


// Calculate the loss function over all the outputs from a single training epoch run.
// The loss function is sometimes refered to as the "cost function".
// It is the softmax function.
// 
// L( y_predicted, y_true)
// 
float FullyConnectedNetwork::loss()
{
    float loss = 0;
    return loss;
}


// Requirements:
// network depth, l
// W_(i) , i belongs {1,..., l} the weight matrices of the model
// b_(i) , i belongs {1,..., l} the bias parameters of the model
// x input vector to process
// y target output vector to evaluate
//
// l = depth
// h_(0) = x
//
// iterate over layers and feed forward the results of each layer
//
//  for k = 1, ..., l do
//     a_(k) = b_(k) + W_(k) • h_(k-1)
//     h_(k) = ƒ(a_(k))
// end for
// 
// y_result = h_(l)
// J = Loss(y_result, y) + q•U(ß)   plus and optional regularization term
// 
// 
int FullyConnectedNetwork::forward_propagation(vector<float> x, vector<float> y)
{
    if (this->layers.size() == 0) {
        printf("Network depth is 0\n");
        return -1;
    }

    // assign input x into first layer
    
    


    for (auto &layer : this->layers)
    {
        layer->compute_layer();
    }

    Layer * y_result = out;
    return 0;
}


Layer * FullyConnectedNetwork::add_layer(uint32_t n, bool init_random, string layer_name)
{
    if (n == 0) {
        printf("cannot add new layer with 0 perceptrons\n");
        return nullptr;
    }
    return new Layer(n, init_random, layer_name);
}


int main()
{
    FullyConnectedNetwork * nn = new FullyConnectedNetwork();

    nn->add_layer(4, false, "input");
    nn->add_layer(3, true, "hidden-1");
    nn->add_layer(2, true, "hidden-2");
    nn->add_layer(2, true, "output");


    delete nn;

    return 0;
}