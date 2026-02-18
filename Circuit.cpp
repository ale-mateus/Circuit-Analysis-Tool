#include "Circuit.h"
#include "Matrix.h"
#include <fstream>
#include <iostream>
#include <set>

void Circuit::readNetlist(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening netlist file." << std::endl;
        return;
    }

    std::string label;
    int src, dest;
    double value;

    while (file >> label >> src >> dest >> value) {
        Branch b;
        b.label = label;
        b.src = src;
        b.dest = dest;
        b.value = value;
        b.isVoltageSource = (label[0] == 'V');

        branches.push_back(b);
    }

    file.close();

    // Build node mapping
    std::set<int> nodes;

    for (const auto& b : branches) {
        if (b.src != 0)
            nodes.insert(b.src);
        if (b.dest != 0)
            nodes.insert(b.dest);
    }

    int index = 0;
    for (int node : nodes) {
        nodeMap[node] = index++;
    }

    int vIndex = 0;

    for (int i = 0; i < branches.size(); i++) {
        if (branches[i].isVoltageSource) {
            voltageSourceMap[i] = vIndex++;
        }
    }

}

int Circuit::getNumBranches() const {
    return branches.size();
}

int Circuit::getNumNodes() const {
    std::set<int> nodes;

    for (const auto& b : branches) {
        if (b.src != 0)
            nodes.insert(b.src);
        if (b.dest != 0)
            nodes.insert(b.dest);
    }

    return nodes.size();
}

int Circuit::getNumVoltageSources() const {
    int count = 0;

    for (const auto& b : branches) {
        if (b.isVoltageSource)
            count++;
    }

    return count;
}

int Circuit::getSystemSize() const {
    return getNumNodes() + getNumVoltageSources();
}

void Circuit::buildConductanceMatrix(Matrix& G) const {
    int N = getNumNodes();

    for (const auto& b : branches) {

        if (!b.isVoltageSource) {  // only resistors

            double g = 1.0 / b.value;

            int a = b.src;
            int c = b.dest;

            bool aIsGround = (a == 0);
            bool cIsGround = (c == 0);

            if (!aIsGround) {
                int i = nodeMap.at(a);
                G(i, i) += g;
            }

            if (!cIsGround) {
                int j = nodeMap.at(c);
                G(j, j) += g;
            }

            if (!aIsGround && !cIsGround) {
                int i = nodeMap.at(a);
                int j = nodeMap.at(c);

                G(i, j) -= g;
                G(j, i) -= g;
            }
        }
    }
}

void Circuit::buildMNAMatrix(Matrix& A) const {

    int N = getNumNodes();
    int M = getNumVoltageSources();

    // First build G portion
    buildConductanceMatrix(A);

    // Now build B and C
    for (int k = 0; k < branches.size(); k++) {

        if (branches[k].isVoltageSource) {

            int vIdx = voltageSourceMap.at(k);

            int row = N + vIdx;  // bottom rows
            int col = N + vIdx;  // bottom-right block (stays zero)

            int a = branches[k].src;
            int b = branches[k].dest;

            if (a != 0) {
                int i = nodeMap.at(a);
                A(i, N + vIdx) = 1;      // B block
                A(N + vIdx, i) = 1;      // C block
            }

            if (b != 0) {
                int j = nodeMap.at(b);
                A(j, N + vIdx) = -1;     // B block
                A(N + vIdx, j) = -1;     // C block
            }
        }
    }
}

void Circuit::buildRHS(std::vector<double>& z) const {

    int N = getNumNodes();

    for (int k = 0; k < branches.size(); k++) {

        if (branches[k].isVoltageSource) {

            int vIdx = voltageSourceMap.at(k);
            z[N + vIdx] = branches[k].value;
        }
    }
}
