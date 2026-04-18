#include "parser.h"
#include <fstream>
#include <iostream>
#include <sstream>

//read the input netlist file into the netlist map
bool parseNetlist(const string& fname, unordered_map<string, Net>& netlist, string& outName) {
    ifstream fin(fname);

    if (!fin) {
        cerr << "Error: cannot open file: " << fname;
        return false;
    }

    string line;

    while (getline(fin, line)) {
        if (line.empty()) {
            continue;
        }

        istringstream ss(line);
        string a, b;

        if (!(ss >> a >> b)) {
            continue;
        }

        if (b == "INPUT") {
            netlist[a] = {"INPUT", "", ""};
            continue;
        }

        if (b == "OUTPUT") {
            outName = a;
            if (!netlist.count(a)) {
                netlist[a] = {"OUTPUT", "", ""};
            }
            continue;
        }

        if (b != "=") {
            continue;
        }

        string op;
        if (!(ss >> op)) {
            continue;
        }

        if (op == "NOT") {
            string x;
            ss >> x;
            netlist[a] = {"NOT", x, ""};
        }
        else if (op == "AND" || op == "OR") {
            string x, y;
            ss >> x >> y;
            netlist[a] = {op, x, y};
        }
        else {
            netlist[a] = {"WIRE", op, ""};
        }
    }

    if (outName.empty()) {
        cerr << "Error- no output node found";
        return false;
    }

    return true;
}