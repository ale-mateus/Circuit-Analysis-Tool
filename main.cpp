// Alejandro Mateus
// Main driver for Circuit Analysis Tool

#include <iostream>
#include <fstream>
#include <vector>
#include "Circuit.h"
#include "Matrix.h"

int main() {

    Circuit circuit;

    // Read netlist
    circuit.readNetlist("netlist.txt");

    int size = circuit.getSystemSize();

    // Build MNA matrix
    Matrix A(size, size);
    circuit.buildMNAMatrix(A);

    // Build RHS vector
    std::vector<double> z(size, 0.0);
    circuit.buildRHS(z);

    // Solve system
    std::vector<double> solution = A.solve(z);

    // Open output file
    std::ofstream outFile("output.txt");

    if (!outFile) {
        std::cerr << "Error opening output file.\n";
        return 1;
    }

    int N = circuit.getNumNodes();
    int M = circuit.getNumVoltageSources();

    // Write node voltages
    outFile << "Node Voltages:\n";
    for (int i = 0; i < N; i++) {
        outFile << "V(" << i + 1 << ") = " << solution[i] << "\n";
    }

    outFile << "\nVoltage Source Currents:\n";
    for (int i = 0; i < M; i++) {
        outFile << "I(V" << i + 1 << ") = " << solution[N + i] << "\n";
    }

    outFile.close();

    return 0;
}
