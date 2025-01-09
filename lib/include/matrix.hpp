#ifndef __MATRIX_H__
#define __MATRIX_H__
#pragma once

#include <vector>
#include <cstdio>

using std::vector;

typedef vector<float> col_vecs;
typedef vector<col_vecs> matrix_f32_t; 

// Function declarations
int matmul(const matrix_f32_t& A, const matrix_f32_t& B, matrix_f32_t& C);
int transpose_mat(const matrix_f32_t& matrix, matrix_f32_t& out);
void print_mat(const matrix_f32_t& matrix, const std::string content);

#endif