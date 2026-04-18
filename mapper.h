#ifndef MAPPER_H
#define MAPPER_H

#include "common.h"

class Mapper {
private:
    const vector<NandNode>& nodes;
    vector<int> dp;

    bool isNand(int i, int& l, int& r) const;
    bool isNot(int i, int& c) const;
    int cost(int i);

public:
    Mapper(const vector<NandNode>& treeNodes);
    int solve(int root);
};

#endif