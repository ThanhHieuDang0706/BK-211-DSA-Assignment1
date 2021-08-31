#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"
class symbol {
private:
    string variable_name;
    string type;
    int scope; //0: global, 1, 2, 3, 4
    string value;
    symbol *nextSymbol;
public:
    void insert ();
};
// insert, assign, begin/end, lookup, print, rprint
class SymbolTable {
public:
    symbol* symbols;
    SymbolTable() {}
    void run(string filename);

private:
    void process(string line);
};
#endif