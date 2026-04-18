#ifndef NAND_TREE_H
#define NAND_TREE_H

#include "common.h"

class NandTree {
private:
    vector<NandNode> nodes;
    unordered_map<string, int> memo;

public:
    int createInput();
    int createNot(int child);
    int createNand(int leftChild, int rightChild);
    int build(const string& name, const unordered_map<string, Net>& netlist);
    const vector<NandNode>& getNodes() const;
};

#endif