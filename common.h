#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <unordered_map>
#include <vector>
#include <limits>

using namespace std;

inline int smaller(int a, int b) {
    return (a < b) ? a : b;
}

//gate library costs
const int COST_NOT = 2;
const int COST_NAND2 = 3;
const int COST_AND2 = 4;
const int COST_NOR2 = 6;
const int COST_OR2 = 4;
const int COST_AOI21 = 7;
const int COST_AOI22 = 7;
const int INF = 999999;

//types of nodes in a NAND/NOT tree (input, nand, not)
enum NodeKind {
    INPUT_NODE,
    NOT_NODE,
    NAND_NODE
};

//a single node in the NAND/NOT tree
struct NandNode {
    NodeKind kind;
    int left;
    int right;
};

//structure to store one parsed entry from the input netlist
struct Net {
    string op;
    string in1;
    string in2;
};

#endif