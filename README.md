# Circuit Analysis Tool (MNA)

A C++ circuit analysis program that reads a circuit netlist and computes:

- **Node Potentials**
- **Branch Voltages**
- **Branch Currents**

The program uses **Modified Nodal Analysis (MNA)** and solves the resulting system using a dense matrix Gaussian elimination solver.

---

## Features

- Parses circuit netlist input
- Constructs the MNA system of equations
- Solves linear equations using Gaussian elimination
- Outputs results in required format (single line, 3 decimal precision)
- Compatible with automated grading format

---

## Compilation (Windows PowerShell)

```powershell
g++ main.cpp Circuit.cpp Matrix.cpp -o ex1
```

This compiles:
- `main.cpp`
- `Circuit.cpp`
- `Matrix.cpp`

and generates an executable named `ex1.exe`.

---

## Running the Program

```powershell
./ex1
```

This executes the compiled program and prints the computed node potentials, branch voltages, and branch currents to standard output.

---

## Output Format

The program outputs:

- All values on **one single line**
- Separated by **one space**
- Rounded to **three decimal places**
- Ordered as:
  1. Node potentials
  2. Branch voltages
  3. Branch currents

Example output:

```
5.000 3.333 5.000 1.667 3.333 -0.167 0.167 0.167
```

---

## Implementation Details

- Method: Modified Nodal Analysis (MNA)
- Matrix Type: Dense matrix representation
- Solver: Gaussian elimination

---

## Bonus

Sparse matrix implementation: Implemented.

The MNA matrix is stored using a vector of unordered_maps,
so only nonzero elements are stored in memory.

---

## Author

Alejandro Mateus  
University of Florida  
EEL4837