#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    vector<vector<double>> data;

public:
    Matrix(int r, int c);

    double& operator()(int r, int c);

    int getRows() const;
    int getCols() const;
    
    vector<double> solve(const vector<double>& b);
};

#endif
