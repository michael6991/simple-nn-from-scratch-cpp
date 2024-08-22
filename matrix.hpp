#ifndef __MATRIX_H__
#define __MATRIX_H__
#pragma once

#include <vector>
#include <cstdio>

using namespace std;

// Function declarations
int matmul(vector<vector<float> > &A, vector<vector<float> > &B, vector<vector<float> > &C);
int transpose_mat(const vector<vector<float> > &matrix, vector<vector<float> > &out);
void print_mat(const vector<vector<float> >& matrix, const string content);

#endif /* __MATRIX_H__ */
