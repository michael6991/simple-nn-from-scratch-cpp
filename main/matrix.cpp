#include "matrix.hpp"
#include <iostream>

using namespace std;


// Function Defenitions

// Elements can be float/double/int
int matmul(vector<vector<float> > &A, vector<vector<float> > &B, vector<vector<float> > &C)
{
    if (A.empty() || B.empty() || C.empty()) {
        cout << "Error: empty matrices given" << endl;
        return -1;
    }

    int rowsA = A.size();
    int rowsB = B.size();
    int rowsC = C.size();
    int colsA = A[0].size();
    int colsB = B[0].size();
    int colsC = C[0].size();

    // Input matrices A,B should have correct dimensions.
    // Resulting matrix C should have dimensions rowsA x colsB
    if (colsA != rowsB || rowsC != rowsA || colsC != colsB) {
        cout << "Invalid matrices dimensions for multiplication operation" << endl;
        return -1;
    }

    // Perform matrix multiplication
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return 0;
}


// Function to transpose a matrix
int transpose_mat(const vector<vector<float> > &matrix, vector<vector<float> > &out)
{
    if (matrix.empty()) {
        cout << "Error: empty input matrix" << endl;
        return -1;
    }
    if (out.empty()) {
        cout << "Error: empty output matrix" << endl;
        return -1;
    }

    int rows = matrix.size();
    int cols = matrix[0].size();

    // Output matrix should have dimensions: (input cols) x (input rows)
    if (out[0].size() != rows || out.size() != cols) {
        cout << "Invalid output matrix dimensions for transpose operation" << endl;
        return -1;
    }

    // Fill the transposed matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            out[j][i] = matrix[i][j];
        }
    }
    return 0;
}

// Helper function to print a matrix
void print_mat(const vector<vector<float> >& matrix, const string content)
{
    cout << content << endl;

    for (const auto& row : matrix) {
        for (auto element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}
