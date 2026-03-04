#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <unordered_map>

using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    vector<std::unordered_map<int, double>> data;

public:
    Matrix(int r, int c);

    double& operator()(int r, int c);

    int getRows() const;
    int getCols() const;
    
    vector<double> solve(const vector<double>& b);
};

#endif
