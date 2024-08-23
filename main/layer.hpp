#ifndef __LAYER_H__
#define __LAYER_H__
#pragma once

#include <stdint.h>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include "perceptron.hpp"
#include "matrix.hpp"

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
            for (auto i = 0; i < n; i++) {
                perceptrons.push_back(mlp_create(init_random));
            }
        }

        // Copy constructor declaration
        Layer(const Layer &other);


        ~Layer()
        {
            printf("~Layer()\n");
            // delete perceptrons
        }
    
        template <class T>
        int copy_vector(const vector<T> &src, vector<T> &dst);
        int copy_vector(const vector<float> &src, vector<mlp_t *> &dst);
        float compute_layer();
        float grad_descent();
        void print_layer(const string content);
        string get_name();
        uint32_t get_n();
        uint32_t get_num_edges();

};


#endif /* __LAYER_H__ */
