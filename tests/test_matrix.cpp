#include <cstdio>
#include <vector>
#include <iostream>
#include "../main/matrix.hpp"

using namespace std;


int main(void) 
{
    // Example transpose
    matrix_f32_t matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    matrix_f32_t transposed(3, vector<float>(3));
    print_mat(matrix, "Original matrix");

    // Transpose the matrix
    transpose_mat(matrix, transposed);
    print_mat(transposed, "Transposed matrix");


    // Example multiplication
    matrix_f32_t matrixA = {
        {1, 2, 3},
        {4, 5, 6}
    };

    matrix_f32_t matrixB = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    matrix_f32_t matrixC(2, vector<float>(2));

    print_mat(matrixA, "Matrix A");
    print_mat(matrixB, "Matrix B");
    print_mat(matrixC, "Matrix C");

    // Multiply the matrices
    matmul(matrixA, matrixB, matrixC);
    cout << "Result matrix after multiplication:" << endl;
    print_mat(matrixC, "Result matrix");

    return 0;
}
