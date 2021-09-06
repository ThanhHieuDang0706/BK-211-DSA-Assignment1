#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"
class symbol {
private:
    string variable_name;
    string type;
    int scope; //0: global, 1, 2, 3, 4
    string value;
};
// insert, assign, begin/end, lookup, print, rprint
class SymbolTable {
public:
    vector<symbol> symbols;

    
    SymbolTable() {}
    void run(string filename);

private:
    bool process(string);
    bool insert_process(smatch s);
};
#endif