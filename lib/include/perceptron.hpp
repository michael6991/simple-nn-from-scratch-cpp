#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__
#pragma once

#include <vector>

typedef struct perceptron mlp_t;  // multi-layer perceptron

struct perceptron {
    std::vector<mlp_t *> next_layer_perc;  // Pointers to next layer perceptrons
    float w;                               // Weight
    float b;                               // Bias
    float a;                               // Input
    float y;                               // y_result = activation_func(w•a + b)
};


// Function declarations
mlp_t * mlp_create(bool init_random);
int perc_eq (const void *p1, const void *p2);

#endif /* __PERCEPTRON_H__ */
