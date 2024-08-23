#include <cstdio>
#include <vector>
#include <iostream>
#include "matrix.hpp"

using namespace std;


int main(void) 
{
    // Example transpose
    vector<vector<float> > matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    vector<vector<float> > transposed(3, vector<float>(3));
    print_mat(matrix, "Original matrix");

    // Transpose the matrix
    transpose_mat(matrix, transposed);
    print_mat(transposed, "Transposed matrix");


    // Example multiplication
    vector<vector<float> > matrixA = {
        {1, 2, 3},
        {4, 5, 6}
    };

    vector<vector<float> > matrixB = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    vector<vector<float> > matrixC(2, vector<float>(2));

    print_mat(matrixA, "Matrix A");
    print_mat(matrixB, "Matrix B");
    print_mat(matrixC, "Matrix C");

    // Multiply the matrices
    matmul(matrixA, matrixB, matrixC);
    cout << "Result matrix after multiplication:" << endl;
    print_mat(matrixC, "Result matrix");

    return 0;
}
