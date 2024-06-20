#ifndef __MATRIX_H__
#define __MATRIX_H__
#pragma once

#include <vector>
#include <cstdio>

using namespace std;

template <class T>
vector <vector<T>> matmul(vector<vector<T>> &A, vector<vector<T>> &B);
template <class T>
std::vector<std::vector<T>> transpose_mat(const std::vector<std::vector<T>>& matrix);
template <class T>
void print_mat(const std::vector<std::vector<T>>& matrix);

#endif /* __MATRIX_H__ */
