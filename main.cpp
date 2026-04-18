#include <fstream>
#include <iostream>
#include "parser.h"
#include "nandTree.h"
#include "mapper.h"

int main(int argc, char* argv[]) {
    string inFile = (argc >= 2) ? argv[1] : "input.txt";
    string outFile = (argc >= 3) ? argv[2] : "output.txt";

    unordered_map<string, Net> netlist;
    string outName;

    if (!parseNetlist(inFile, netlist, outName)) {
        ofstream f(outFile);
        f << -1 << endl;
        return 1;
    }

    NandTree tree;
    int root = tree.build(outName, netlist);

    Mapper mapper(tree.getNodes());
    int result = mapper.solve(root);

    ofstream f(outFile);
    if (!f) {
        cerr << "Error: cannot write to file output.txt" ;
        return 1;
    }

    f << result << "\n";
    cout << "Minimum cost: " << result << endl;

    return 0;
}