#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__
#pragma once

struct perceptron;
typedef struct perceptron mlp_t;  // multi-layer perceptron


mlp_t *mlp_create(bool init_random);

#endif /* __PERCEPTRON_H__ */
