#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
private:
    int rows;
    int cols;
    std::vector<std::vector<double>> data;

public:
    Matrix(int r, int c);

    double& operator()(int r, int c);

    int getRows() const;
    int getCols() const;
};

#endif
