#include <cstdio>
#include <vector>
#include <iostream>
#include "../lib/include/matrix.hpp"

using namespace std;


int main(void) 
{
    int rows = 5, cols = 10;
    matrix_f32_t M(rows, col_vecs(cols, 0));
    print_mat(M, "Example of initialization of (5 x 10) matrix");


    printf("Testing Transpose Operation:");
    matrix_f32_t matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    matrix_f32_t transposed(3, vector<float>(3));
    print_mat(matrix, "Original matrix");
    transpose_mat(matrix, transposed);
    print_mat(transposed, "Transposed matrix");


    printf("Testing Multiplication Operation:");
    matrix_f32_t matrixA = {
        {1, 2, 3},
        {4, 5, 6}
    };

    matrix_f32_t matrixB = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    matrix_f32_t matrixC(2, col_vecs(2, 0));

    print_mat(matrixA, "Matrix A");
    print_mat(matrixB, "Matrix B");
    print_mat(matrixC, "Matrix C");
    matmul(matrixA, matrixB, matrixC);
    cout << "Result matrix after multiplication:" << endl;
    print_mat(matrixC, "Matrix C");

    return 0;
}
