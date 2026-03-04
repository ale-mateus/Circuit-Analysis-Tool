// Alejandro Mateus
// Main driver for Circuit Analysis Tool
// EEL4837 – Excursion 1

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "Circuit.h"
#include "Matrix.h"

int main() {

    Circuit circuit;

    // Read netlist
    circuit.readNetlist("netlist.txt");

    int systemSize = circuit.getSystemSize();
    int N = circuit.getNumNodes();
    int M = circuit.getNumVoltageSources();

    // Build MNA matrix
    Matrix A(systemSize, systemSize);
    circuit.buildMNAMatrix(A);

    // Build RHS vector
    std::vector<double> z(systemSize, 0.0);
    circuit.buildRHS(z);

    // Solve Ax = z
    std::vector<double> solution = A.solve(z);

    // Open output file
    std::ofstream outFile("output.txt");
    if (!outFile) {
        std::cerr << "Error opening output.txt\n";
        return 1;
    }

    outFile << std::fixed << std::setprecision(3);

    // --------------------------------------------------
    // 1) Node potentials (e1 e2 ... en)
    // --------------------------------------------------
    for (int i = 0; i < N; i++) {
        outFile << solution[i] << " ";
    }

    // --------------------------------------------------
    // 2) Branch voltages (v1 v2 ... vn)
    // --------------------------------------------------
    const auto& branches = circuit.getBranches();

    for (const auto& b : branches) {

        double vSrc = 0.0;
        double vDest = 0.0;

        if (b.src != 0)
            vSrc = solution[circuit.getNodeIndex(b.src)];

        if (b.dest != 0)
            vDest = solution[circuit.getNodeIndex(b.dest)];

        double voltageDrop = vSrc - vDest;
        outFile << voltageDrop << " ";
    }

    // --------------------------------------------------
    // 3) Branch currents (i1 i2 ... in)
    // --------------------------------------------------
    for (int k = 0; k < branches.size(); k++) {

        const auto& b = branches[k];
        double current = 0.0;

        if (b.isVoltageSource) {
            int idx = circuit.getVoltageSourceIndex(k);
            current = solution[N + idx];
        }
        else {
            double vSrc = 0.0;
            double vDest = 0.0;

            if (b.src != 0)
                vSrc = solution[circuit.getNodeIndex(b.src)];

            if (b.dest != 0)
                vDest = solution[circuit.getNodeIndex(b.dest)];

            current = (vSrc - vDest) / b.value;
        }

        outFile << current;
        if (k != branches.size() - 1)
            outFile << " ";
    }

    outFile.close();
    return 0;
}