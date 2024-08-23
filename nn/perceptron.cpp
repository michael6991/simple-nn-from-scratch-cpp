#include <cstdlib>
#include <ctime>
#include <string>
#include "perceptron.hpp"


// Definition of appropriate equality callback between 2 given mlp.
// That's for handling list of next layer perceptrons.
// Compares the addresses of 2 given perceptrons.
// If equal return 1, otherwise return 0.
int perc_eq (const void *p1, const void *p2)
{
    if (p1 == nullptr || p2 == nullptr) {
        return -1;
    }
    return ((mlp_t *)p1 == (mlp_t *)p2) ? 1: 0;
}


// Create a single perceptron unit and intialize it
mlp_t * mlp_create(bool init_random)
{
    // Basic initialization
    mlp_t *p;
    p = (mlp_t *)malloc(sizeof(*p));

    if (p == nullptr) {
        printf("Error creating mlp with malloc\n");
        return p;
    }

    // Initialize Input and result parameters
    p->a = 0;
    p->y = 0;

    // Use current time as seed for random generator
    std::srand(std::time(nullptr));
    // Initialize perceptron weight and bias accordingly
    // Should be normalized values
    if (init_random) {
        p->w = static_cast<float>(std::rand());
        p->b = static_cast<float>(std::rand());
    } else {
        p->w = 0;
        p->b = 0;
    }
    return p;
}
