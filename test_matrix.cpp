#include "../matrix.hpp"
#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;



int main() {
    // Example transpose
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "Original matrix:" << endl;
    print_mat(matrix);

    // Transpose the matrix
    vector<vector<int>> transposed_mat = transpose_mat(matrix);

    cout << "Transposed matrix:" << endl;
    print_mat(transposed_mat);


    // Example multiplication
    vector<vector<int>> matrixA = {
        {1, 2, 3},
        {4, 5, 6}
    };

    vector<vector<int>> matrixB = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    cout << "Matrix A:" << endl;
    print_mat(matrixA);

    cout << "Matrix B:" << endl;
    print_mat(matrixB);

    try {
        // Multiply the matrices
        vector<vector<int>> resultMatrix = matmul(matrixA, matrixB);

        cout << "Resultant matrix after multiplication:" << endl;
        print_mat(resultMatrix);
    } catch (const std::invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
