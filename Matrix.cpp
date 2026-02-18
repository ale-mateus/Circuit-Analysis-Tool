#include "Matrix.h"

Matrix::Matrix(int r, int c) {
    rows = r;
    cols = c;
    data.resize(r, vector<double>(c, 0.0));
}

double& Matrix::operator()(int r, int c) {
    return data[r][c];
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getCols() const {
    return cols;
}

vector<double> Matrix::solve(const vector<double>& b) {

    int n = rows;
    Matrix A = *this;  // copy matrix
    vector<double> x = b;

    // Forward elimination
    for (int k = 0; k < n; k++) {

        // Pivot
        double pivot = A(k, k);

        for (int j = k; j < n; j++)
            A(k, j) /= pivot;

        x[k] /= pivot;

        // Eliminate below
        for (int i = k + 1; i < n; i++) {

            double factor = A(i, k);

            for (int j = k; j < n; j++)
                A(i, j) -= factor * A(k, j);

            x[i] -= factor * x[k];
        }
    }

    // Back substitution
    for (int i = n - 1; i >= 0; i--) {

        for (int j = i + 1; j < n; j++)
            x[i] -= A(i, j) * x[j];
    }

    return x;
}
