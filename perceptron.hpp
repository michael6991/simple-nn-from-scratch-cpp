#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__


struct perceptron;
typedef struct perceptron perceptron_t;


perceptron_t *perc_create(bool init_random);

#endif /* __PERCEPTRON_H__ */
