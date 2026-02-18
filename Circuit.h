#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <string>
#include <vector>
#include <map>

using namespace std;

struct Branch {
    string label;
    int src;
    int dest;
    double value;
    bool isVoltageSource;
};

class Matrix;

class Circuit {
private:
    vector<Branch> branches;
    map<int, int> nodeMap;

public:
    void readNetlist(const string& filename);
    int getNumBranches() const;
    int getNumNodes() const;
    int getNumVoltageSources() const;
    int getSystemSize() const;
    void buildConductanceMatrix(Matrix& G) const;
};

#endif
