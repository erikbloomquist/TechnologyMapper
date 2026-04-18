#include "mapper.h"

//set up the mapper with an existing NAND-NOT tree
Mapper::Mapper(const vector<NandNode>& treeNodes) : nodes(treeNodes) {
    dp.assign(nodes.size(), -1);
}

//check whether a node is NAND and return its children
bool Mapper::isNand(int i, int& l, int& r) const {
    if (i < 0 || i >= (int)nodes.size() || nodes[i].kind != NAND_NODE) {
        return false;
    }

    l = nodes[i].left;
    r = nodes[i].right;
    return true;
}

//check whether a node is NOT and return its child
bool Mapper::isNot(int i, int& c) const {
    if (i < 0 || i >= (int)nodes.size() || nodes[i].kind != NOT_NODE) {
        return false;
    }

    c = nodes[i].left;
    return true;
}

//compute the minimum cost for implementing a subtree
int Mapper::cost(int i) {
    if (i < 0 || i >= (int)dp.size()) {
        return 0;
    }

    if (dp[i] != -1) {
        return dp[i];
    }

    NandNode nd = nodes[i];

    if (nd.kind == INPUT_NODE) {
        dp[i] = 0;
        return dp[i];
    }

    int best = INF;

    if (nd.kind == NAND_NODE) {
        int l = nd.left;
        int r = nd.right;

        //AND implementation
        best = smaller(best, COST_NAND2 + cost(l) + cost(r));//update best cost

        //OR implementation
        int ca, cb;
        if (isNot(l, ca) && isNot(r, cb)) {
            best = smaller(best, COST_OR2 + cost(ca) + cost(cb));//update best cost
        }
    }

    if (nd.kind == NOT_NODE) {
        int c2 = nd.left;

        //NOT implementation
        best = smaller(best, COST_NOT + cost(c2));//update best cost

        int nl, nr;
        if (isNand(c2, nl, nr)) {
            //AND pattern NOT(NAND(a, b))
            best = smaller(best, COST_AND2 + cost(nl) + cost(nr));//update best cost

            //NOR pattern NOT(NAND(NOT(a), NOT(b)))
            int ca, cb;
            if (isNot(nl, ca) && isNot(nr, cb)) {
                best = smaller(best, COST_NOR2 + cost(ca) + cost(cb));//update best cost
            }

            //and-or-invert 2-1 pattern
            int p, q;
            if (isNand(nl, p, q)) {
                best = smaller(best, COST_AOI21 + cost(nr) + cost(p) + cost(q));//update best cost
            }
            if (isNand(nr, p, q)) {
                best = smaller(best, COST_AOI21 + cost(nl) + cost(p) + cost(q));//update best cost
            }

            //and-or-invert 2-2 pattern
            int p2, q2;
            if (isNand(nl, p, q) && isNand(nr, p2, q2)) {
                best = smaller(best, COST_AOI22 + cost(p) + cost(q) + cost(p2) + cost(q2)); //update best cost
            }
        }
    }

    dp[i] = best;
    return dp[i]; //return best cost
}

//return the minimum cost for the WHOLE tree, starting from the root
int Mapper::solve(int root) {
    return cost(root);
}