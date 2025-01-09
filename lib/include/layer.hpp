#ifndef __LAYER_H__
#define __LAYER_H__
#pragma once

#include <stdint.h>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include "matrix.hpp"
#include "perceptron.hpp"

using std::vector;
using std::string;

class Layer
{
    private:
        uint32_t n = 0;              // total number of perceptrons
        uint32_t edges = 0;          // total number of edges between this layer and the next
        uint32_t layer_n = 0;        // index of this layer within the whole network
        string name = "";            // name of the layer

        vector<float> x;             // Inputs
        vector<float> w;             // Weights
        vector<float> b;             // Biases
        vector<float> y;             // output: activation_func(w•a + b)

    public:
        Layer(uint32_t n, bool init_random=true, uint32_t layer_n=0, string name="default"):
                                                                                            n(n),
                                                                                            layer_n(layer_n),
                                                                                            name(name)
        {
            // TODO: take out the random number generator. it should be an input from the hihgher level NN.

            // Create a random device to seed the generator
            std::random_device rd;
            // Create a Mersenne Twister random number engine
            std::mt19937 gen(rd());
            // Create a uniform distribution between 0 and 1
            std::uniform_real_distribution<float> dist(0.0, 1.0);

            // Vector is resized to 'n' elements, all initialized to 0
            x.resize(n);
            w.resize(n);
            b.resize(n);
            y.resize(n);

            if (init_random) {
                printf("Creating mlp units with random weights for layer: %s\n", name.c_str());
                for (auto i = 0; i < n; i++)
                    w[i] = dist(gen);
            } else {
                printf("Created mlp units with weights initialize to 0 for layer: %s\n", name.c_str());
            }
        }

        // Copy constructor declaration
        Layer(const Layer &other);


        ~Layer()
        {
            printf("~Layer()\n");
            // Requests the removal of unused capacity.
            // Basically de-allocates all memory that was allocated to the vector
            x.resize(0);
            x.shrink_to_fit();
            w.resize(0);
            w.shrink_to_fit();
            b.resize(0);
            b.shrink_to_fit();
            y.resize(0);
            y.shrink_to_fit();

            // delete the connections to next layer's perceptrons
        }
    
        template <class T>
        int copy_vector(const vector<T>& src, vector<T>& dst);
        int copy_vector(const vector<float>& src, vector<mlp_t* >& dst);
        float compute_layer();
        float grad_descent();
        void print_layer(const string content);
        string get_name();
        uint32_t get_n();
        uint32_t get_num_edges();

};


#endif
