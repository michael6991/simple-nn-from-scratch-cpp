#ifndef __LAYER_H__
#define __LAYER_H__
#pragma once

#include <stdint.h>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include "perceptron.hpp"

using namespace std;

class Layer
{
    private:
        uint32_t n = 0;              // total number of perceptrons
        uint32_t edges = 0;          // total number of edges between this layer and the next
        uint32_t layer_n = 0;        // index of this layer within the whole network
        vector<mlp_t *> perceptrons; // multi-layer perceptrons vector of this layer
        string name = "";            // name of the layer

    public:
        Layer(uint32_t num_of_perc, bool init_random=true, uint32_t layer_num=0, string layer_name="default"):
                                                                                            n(num_of_perc),
                                                                                            layer_n(layer_num),
                                                                                            name(layer_name)
        {
            // Initialize the layer with new perceptrons
            printf("Creating mlp units for layer: %s", name.c_str());
            for (uint32_t i = 0; i < n; i++) {
                perceptrons.push_back(mlp_create(init_random));
            }
        }


        ~Layer()
        {
            printf("~Layer()\n");
        }
    
        template <class T>
        int copy_vector(const vector<T> &src, vector<T> &dst);
        int copy_vector(const vector<float> &src, vector<mlp_t *> &dst);
        float compute_layer();
        float grad_descent();
        void print_layer(const string content);

};


#endif /* __LAYER_H__ */
