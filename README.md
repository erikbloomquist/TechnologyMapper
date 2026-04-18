# Technology Mapper Project  
**Written By: Gerald Bissell & Erik Bloomquist**

## Overview
This program is a technology mapping tool that reads a Boolean netlist from an input text file, builds a NAND-NOT logic tree, and then computes the minimum implementation cost using the given technology library. The final cost is written to `output.txt`.

## File Breakdown

### **1. `common.h`**
This file stores the shared definitions used throughout the project. It includes the following:
- The `NandNode` structure used to represent nodes in the NAND-NOT tree
- The `Net` structure used to store parsed netlist entries
- The `NodeKind` enum used to identify input, NOT, and NAND nodes
- Technology library cost constants
- A small helper function used in cost comparisons

### **2. `parser.h` / `parser.cpp`**
These files are responsible for reading the input netlist and storing the circuit description. It also checks for simple input errors such as a missing input file or a missing output declaration.

### **3. `nandTree.h` / `nandTree.cpp`**
These files build the NAND-NOT tree from the parsed netlist.

The following transformations are used according to De Morgan’s Laws:
- `AND(a, b) -> NOT(NAND(a, b))`
- `OR(a, b) -> NAND(NOT(a), NOT(b))`
- `NOT(a) -> NOT(a)`

These files also handle direct wire connections and input nodes while constructing the final tree.

### **4. `mapper.h` / `mapper.cpp`**
These files compute the minimum cost of the NAND-NOT tree. The mapper works in a bottom-up manner using dynamic programming. For each subtree, it determines the minimum cost implementation using the available gates in the technology library. The final cost is returned at the root node.

The cost library implemented:
- `NOT = 2`
- `NAND2 = 3`
- `AND2 = 4`
- `NOR2 = 6`
- `OR2 = 4`
- `AOI21 = 7`
- `AOI22 = 7`

### **5. `main.cpp`**
This is the driver file for the program. First, it calls the parser to read the input file. Then, it builds the NAND-NOT tree and calls the mapper to compute the minimum cost. It then writes the result to `output.txt`.

## How to Compile
Compile all source files together using `g++`.  
First, `cd` into the directory containing all files, including a valid netlist named `input.txt`  
Then, run the following commands to compile and run the executable

Example:
```bash
g++ *.cpp -o ex1
./ex1
```
