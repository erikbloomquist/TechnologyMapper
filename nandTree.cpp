#include "nandTree.h"

//create an input node
int NandTree::createInput() {
    nodes.push_back({INPUT_NODE, -1, -1});
    return (int)nodes.size() - 1;
}

//create a NOT node
int NandTree::createNot(int child) {
    nodes.push_back({NOT_NODE, child, -1});
    return (int)nodes.size() - 1;
}

//create a NAND node
int NandTree::createNand(int leftChild, int rightChild) {
    nodes.push_back({NAND_NODE, leftChild, rightChild});
    return (int)nodes.size() - 1;
}

//building the NAND/NOT tree

int NandTree::build(const string& name, const unordered_map<string, Net>& netlist) {
    unordered_map<string, int>::iterator memoIt = memo.find(name);
    if (memoIt != memo.end()) {
        return memoIt->second;
    }

    unordered_map<string, Net>::const_iterator netIt = netlist.find(name);
    if (netIt == netlist.end()) {
        memo[name] = createInput();
        return memo[name];
    }

    Net n = netIt->second;
    int idx;

    if (n.op == "INPUT") {
        idx = createInput();
    }
    else if (n.op == "WIRE" || n.op == "OUTPUT") {
        if (n.in1.empty()) {
            idx = createInput();
        }
        else {
            idx = build(n.in1, netlist);
        }
    }
    else if (n.op == "NOT") {
        idx = createNot(build(n.in1, netlist));
    }
    else if (n.op == "AND") {
        idx = createNot(createNand(build(n.in1, netlist), build(n.in2, netlist)));
    }
    else if (n.op == "OR") {
        idx = createNand(createNot(build(n.in1, netlist)), createNot(build(n.in2, netlist)));
    }
    else {
        idx = createInput();
    }

    memo[name] = idx;
    return idx;
}

//Return the full tree
const vector<NandNode>& NandTree::getNodes() const {
    return nodes;
}