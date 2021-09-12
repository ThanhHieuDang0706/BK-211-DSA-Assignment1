#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"



struct symbol {
    string variable_name;
    string type;
    int scope; //0: global, 1, 2, 3, 4
    symbol* next;
    symbol* prev;

    

    void operator=(const symbol &sym)
    {
        this->variable_name = sym.variable_name;
        this->type = sym.type;
        this->scope = sym.scope;
        this->next = sym.next;
        this->prev = sym.prev;
    }
    void initialize(string name, string type, int scope);  
};


// insert, assign, begin/end, lookup, print, rprint
class SymbolTable {
public:
    symbol* head; //head
    symbol* tail;
    
    SymbolTable* parent;
    SymbolTable* child;
    
    SymbolTable() {
        head = nullptr;
        tail = nullptr;
        parent = nullptr;
        child = nullptr;
    }
    void run(string filename);

};

bool process(SymbolTable*& ,string);
bool insert_process(SymbolTable*, smatch);
bool assign_process(SymbolTable*, smatch);
bool lookup_process(smatch s);
bool begin_process(SymbolTable*);
bool end_process();
bool print_process(smatch s);
bool rprint_process(smatch s);


bool verify_identifer_name(string name);
bool identifier_name_declared(SymbolTable*, string);
string getType(string value, string instruction, SymbolTable*);
symbol* findSymbol(string name, SymbolTable*);
void assigning(string idName, string valueType, string instruction);
void push_back(SymbolTable*, symbol);
bool identifier_name_declared_insert(SymbolTable* symbolTable, string name);
void deleteSymbolTable(SymbolTable*);

#endif