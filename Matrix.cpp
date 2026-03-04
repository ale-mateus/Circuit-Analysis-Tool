#include "Matrix.h"
#include <cmath>
#include <algorithm>

Matrix::Matrix(int r, int c) {
    rows = r;
    cols = c;
    data.resize(r);
}

double& Matrix::operator()(int r, int c) {
    return data[r][c];  // creates entry if it doesn't exist
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getCols() const {
    return cols;
}

vector<double> Matrix::solve(const vector<double>& b) {

    int n = rows;
    Matrix A = *this;   // copy matrix
    vector<double> x = b;

    // Forward elimination with partial pivoting
    for (int k = 0; k < n; k++) {

        // ---- PARTIAL PIVOTING ----
        int maxRow = k;
        double maxVal = fabs(A(k, k));

        for (int i = k + 1; i < n; i++) {
            double val = fabs(A(i, k));
            if (val > maxVal) {
                maxVal = val;
                maxRow = i;
            }
        }

        // Swap rows if needed
        if (maxRow != k) {
            swap(A.data[k], A.data[maxRow]);
            swap(x[k], x[maxRow]);
        }
        // ---------------------------

        double pivot = A(k, k);

        // Normalize pivot row
        if (pivot != 0.0) {
            for (auto& entry : A.data[k]) {
                entry.second /= pivot;
            }
            x[k] /= pivot;
        }

        // Eliminate below
        for (int i = k + 1; i < n; i++) {

            double factor = A(i, k);
            if (factor == 0.0) continue;

            for (auto& entry : A.data[k]) {
                int col = entry.first;
                double value = entry.second;

                A(i, col) -= factor * value;

                // Remove near-zero entries to keep sparse
                if (fabs(A(i, col)) < 1e-12) {
                    A.data[i].erase(col);
                }
            }

            x[i] -= factor * x[k];
        }
    }

    // Back substitution
    for (int i = n - 1; i >= 0; i--) {

        for (auto& entry : A.data[i]) {
            int j = entry.first;
            if (j > i) {
                x[i] -= entry.second * x[j];
            }
        }
    }

    return x;
}