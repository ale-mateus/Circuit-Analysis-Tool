#include "Matrix.h"

Matrix::Matrix(int r, int c) {
    rows = r;
    cols = c;
    data.resize(r, std::vector<double>(c, 0.0));
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
