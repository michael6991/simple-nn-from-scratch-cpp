#include <cstdio>
#include <vector>
#include <iostream>
#include "../nn/nn.hpp"


using namespace std;


int main()
{
    FullyConnectedNetwork * nn = new FullyConnectedNetwork();

    nn->add_layer(4, false, 0, "input");
    nn->add_layer(3, true,  1, "hidden-1");
    nn->add_layer(2, true,  2, "hidden-2");
    nn->add_layer(2, true,  3, "output");

    delete nn;

    return 0;
}