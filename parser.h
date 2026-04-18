#ifndef PARSER_H
#define PARSER_H

#include "common.h"

bool parseNetlist(const string& fname, unordered_map<string, Net>& netlist, string& outName);

#endif