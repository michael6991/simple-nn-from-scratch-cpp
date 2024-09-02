#ifndef __MATRIX_H__
#define __MATRIX_H__
#pragma once

#include <vector>
#include <cstdio>

using namespace std;

typedef vector<vector<float> > matrix_f32_t;

// Function declarations
void some(const matrix_f32_t &A);
int matmul(const matrix_f32_t &A, const matrix_f32_t &B, matrix_f32_t &C);
int transpose_mat(const matrix_f32_t &matrix, matrix_f32_t &out);
void print_mat(const matrix_f32_t &matrix, const string content);

#endif /* __MATRIX_H__ */
