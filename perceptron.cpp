#include <cstdlib>
#include <ctime>
#include "list.h"
#include "perceptron.hpp"
#include <vector>


struct perceptron {
    list_t *next_layer_perc; // Pointers to next layer perceptrons
    float w;                 // Weights vector
    float b;                 // Bias
    float x;                 // Input
    float y;                 // y = activation_func(wx + b)
};


// Define appropriate equality callback for handling list of next layer perceptrons.
// Compares the addresses of 2 given perceptrons
// If equal return 1, otherwise return 0
int perc_eq (const void *p1, const void *p2)
{
    return ((perceptron_t *)p1 == (perceptron_t *)p2) ? 1: 0;
}


perceptron_t *perc_create(bool init_random)
{
    perceptron_t *p;

    // basic initialization
    p = (perceptron_t *)malloc(sizeof(*p));
   
    // create and initialize the next layer list
    list_flags_t lflags = LIST_NONE;
    list_cbs_t cbs = {
        perc_eq,
        (list_copy_cb)memcpy,
        free
    };
    p->next_layer_perc = list_create(&cbs, lflags);

    // use current time to seed for random generator
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
