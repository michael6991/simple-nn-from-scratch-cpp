#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;


// elements can be float/double/int
template <class T>
vector <vector<T> > matmul(vector<vector<T> > &A, vector<vector<T> > &B)
{
    if (A.empty() || B.empty() || A[0].size() != B.size()) {
        throw invalid_argument("Invalid matrices dimensions for multiplication.");
    }

    const int rowsA = A.size();
    const int colsA = A[0].size();
    const int colsB = B[0].size();

    // Create the resulting matrix with dimensions rowsA x colsB
    vector<vector<T> > C(rowsA, vector<int>(colsB, 0));

    // Perform matrix multiplication
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}


// Function to transpose a matrix
// This function takes a constant reference to a 2D vector matrix
// and returns a new 2D vector which is the transposed version of the input matrix.
template <class T>
vector<vector<T> > transpose_mat(const vector<vector<T> >& matrix)
{
    if (matrix.empty()) {
        cout << "Error: empty matrix" << endl;
        return {};
    }

    int rows = matrix.size();
    int cols = matrix[0].size();

    // Create a new matrix with dimensions cols x rows
    vector<vector<T> > transposed_mat(cols, vector<T>(rows));

    // Fill the transposed matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed_mat[j][i] = matrix[i][j];
        }
    }

    return transposed_mat;
}

// Helper function to print a matrix
template <class T>
void print_mat(const vector<vector<T> >& matrix, const string name)
{
    cout << "Printing Matrix: " << name << endl;

    for (const auto& row : matrix) {
        for (auto element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}
