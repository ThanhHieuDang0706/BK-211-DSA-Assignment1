#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"
struct symbol {
    string variable_name;
    string type;
    int scope; //0: global, 1, 2, 3, 4
    symbol* next;
    void operator=(const symbol &sym)
    {
        this->variable_name = sym.variable_name;
        this->type = sym.type;
        this->scope = sym.scope;
        this->next = sym.next;
    }
    
};
// insert, assign, begin/end, lookup, print, rprint
class SymbolTable {
public:
    symbol* symbols;

    
    SymbolTable() {
        symbols = nullptr;
    }
    void run(string filename);

private:
    bool process(string);
    bool insert_process(smatch s);
    bool assign_process(smatch s);
    bool lookup_process(smatch s);
    bool begin_process(smatch s);
    bool end_process(smatch s);
    bool print_process(smatch s);
    bool rprint_process(smatch s);
    

    bool verify_identifer_name(string name);
    bool identifier_name_declared(string);
    string getType(string value, string instruction);
    symbol findSymbol(string name);
    void assigning(string idName, string valueType, string instruction);
    void push_back(symbol newSymbol);
};
#endif