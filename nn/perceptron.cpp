#include <cstdlib>
#include <ctime>
#include "list.h"
#include "perceptron.hpp"
#include <string>


struct perceptron {
    list_t *next_layer_perc; // Pointers to next layer perceptrons
    float w;                 // Weight
    float b;                 // Bias
    float a;                 // Input
    float y;                 // y_result = activation_func(w•a + b)
};

// Define appropriate equality callback for handling list of next layer perceptrons.
// Compares the addresses of 2 given perceptrons
// If equal return 1, otherwise return 0
int perc_eq (const void *p1, const void *p2)
{
    return ((mlp_t *)p1 == (mlp_t *)p2) ? 1: 0;
}


mlp_t *perc_create(bool init_random)
{
    mlp_t *p;

    // basic initialization
    p = (mlp_t *)malloc(sizeof(*p));
   
    // create and initialize the list of output perceptrons in the next layer
    list_flags_t lflags = LIST_NONE;
    list_cbs_t cbs = {
        perc_eq,
        (list_copy_cb)memcpy,
        free
    };
    p->next_layer_perc = list_create(&cbs, lflags);

    p->a = 0;
    p->y = 0;

    // use current time as seed for random generator
    std::srand(std::time(nullptr));
    // initialize perceptron weight and bias accordingly
    if (init_random) {
        p->w = static_cast<float>(std::rand());
        p->b = static_cast<float>(std::rand());
    } else {
        p->w = 0;
        p->b = 0;
    }
    return p;
}
