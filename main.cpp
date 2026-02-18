// Alejandro Mateus
// Controls program flow
// Calls all major functions

#include <iostream>
#include "Circuit.h"
#include "Matrix.h"

int main() {

    Circuit circuit;
    circuit.readNetlist("netlist.txt");

    std::cout << "Branches: " << circuit.getNumBranches() << std::endl;
    std::cout << "Nodes (excluding ground): " << circuit.getNumNodes() << std::endl;
    std::cout << "Voltage Sources: " << circuit.getNumVoltageSources() << std::endl;
    std::cout << "System size: " << circuit.getSystemSize() << std::endl;

    // Create conductance matrix
    int N = circuit.getNumNodes();
    Matrix G(N, N);

    circuit.buildConductanceMatrix(G);

    std::cout << "\nConductance Matrix (G):\n";
    for (int i = 0; i < G.getRows(); i++) {
        for (int j = 0; j < G.getCols(); j++) {
            std::cout << G(i, j) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
