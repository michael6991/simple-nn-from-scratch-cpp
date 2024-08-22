#ifndef __LAYER_H__
#define __LAYER_H__
#pragma once

#include <string>
#include "perceptron.hpp"

using namespace std;


// layer flags
typedef enum {
    LAYER_NONE            = 0,
    LAYER_FULLY_CONNECTED = 1 << 0
} layer_flags_t;


class Layer
{
    private:
        uint32_t n = 0;              // total number of perceptrons
        uint32_t edges = 0;          // toatl number of edges between this layer and the next
        vector<mlp_t *> perceptrons; // multi-layer perceptrons vector of this layer
        string name = "0";           // name of the layer

    public:
        Layer(uint32_t num_of_perc, bool init_random=true, string layer_name="0"):
                                                                                n(num_of_perc),
                                                                                name(layer_name)
        {
            // initialize the layer with perceptrons
            for (uint32_t i = 0; i < n; i++) {
                perceptrons.push_back(mlp_create(init_random));
            }

            if (layer_name == "0") {
                // if default take the name of the previous layer and add 1
            }
        }


        ~Layer()
        {
            printf("~Layer()\n");
        }
    
        template <class T>
        void copy_vector(const vector<T> &src, vector<T> &dst);
        int copy_vector(const vector<float> &src, vector<mlp_t *> &dst);
        float compute_layer();
        float grad_descent();

};


#endif /* __LAYER_H__ */
