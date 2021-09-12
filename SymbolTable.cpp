#include "SymbolTable.h"


extern regex ins("^(INSERT)\\s([a-zA-Z]\\w*)\\s(number|string)");
extern regex assign("^(ASSIGN)\\s([a-zA-Z]\\w*)\\s(\\d+|'.*'|[a-zA-Z]\\w*)");
extern regex beg("^(BEGIN)");
extern regex en("^(END)");
extern regex lookup("^(LOOKUP)\\s([a-zA-Z]\\w*)");
extern regex print("^(PRINT)");
extern regex rprint("^(RPRINT)");
extern regex cons_num("\\d+");
extern regex literal_char("'.*'");
extern regex identifier_name("[a-zA-Z]\\w*");

extern const string success = "success\n";
extern int current_scope = 0;




void symbol::initialize(string name, string type, int scope)
{
    this->variable_name = name;
    this->type = type;
    this->scope = scope;
    this->next = nullptr;
    this->prev = nullptr;
}


void push_back(SymbolTable* symbolTable, symbol newSymbol)
{
    // there is no symbol in the table yet
    if (symbolTable->head == nullptr)
    {
        symbol* newHead = new symbol;
        *newHead = newSymbol;
        // update head and tail
        symbolTable->head = newHead;
        symbolTable->tail = newHead;
    }    
    else 
    {
        symbol* newSym = new symbol;
        *newSym = newSymbol;
        newSym->prev = symbolTable->tail;
        newSym->next = nullptr;
        symbolTable->tail->next = newSym;
        symbolTable->tail = newSym;
    }
}

// find only within scope
bool identifier_name_declared_insert(SymbolTable* symbolTable, string name)
{

    // search in the current scope (table)
    symbol* temp = symbolTable->tail;
    while (temp != nullptr)
    {
        if (temp->variable_name == name)
        {
            return true;
        }
        else
        {
            temp = temp->prev;
        }
    }

    // not found within the scope
    return false;

}


// similar to lookup, but we dive into that later, find from child to PARENT (ALL OF IT)
bool identifier_name_declared(SymbolTable* symbolTable, string name)
{
    
    // base case: traverse all the tables from child -> parent
    if (symbolTable == nullptr)
    {
        return false;
    }
    else
    {
        // search in the current table
        symbol* temp = symbolTable->tail;
        while (temp != nullptr)
        {
            if (temp->variable_name == name) 
            {
                return true;
            }
            else
            {
                temp = temp->prev;
            }
        }

        // search the parent
        return identifier_name_declared(symbolTable->parent, name);
    }
}

bool insert_process(SymbolTable* symbolTable, smatch s)
{
    if (identifier_name_declared_insert(symbolTable, s[2]))
    {
        throw Redeclared(s[0]).what();
        return 0;
    }
    else
    {
        symbol newSymbol;
        newSymbol.initialize(s[2], s[3], current_scope);
        push_back(symbolTable, newSymbol);
        cout << success;
        return true;    
    }
}

/*ASSIGN*/
// s[1]=ASSIGN; s[2] = (identifierName) ; s[3] = newval
bool assign_process(SymbolTable* symbolTable, smatch s)
{
    if (!identifier_name_declared(symbolTable, s[2]))
    {
        throw Undeclared(s[0]).what();
        return false;
    }

    // getType() get the type of the new value and assert its correctness
    string idType = getType(s[3], s[0], symbolTable);

    symbol* assignedSymbol = findSymbol(s[2], symbolTable);

    if (idType != assignedSymbol->type)
    {
        throw TypeMismatch(s[0]).what();
        return false;
    }
    else
    {
        cout << success;
        return true;
    }
}



/* GET TYPE OF THE NEW VAL (ASSIGN)*/
string getType(string value, string instruction, SymbolTable* symbolTable)
{
    if (regex_match(value, cons_num))
        return "number";
    else if (regex_match(value, literal_char))
        return "string";
    else if (regex_match(value, identifier_name))
    {
        if (!identifier_name_declared(symbolTable, value))
            throw Undeclared(instruction).what();

        return findSymbol(value, symbolTable)->type;
    }
}

void assigning(string idName, string valueType, string instruction, SymbolTable* symbolTable)
{
    return;
}

symbol* findSymbol(string name, SymbolTable* symbolTable)
{
    SymbolTable* tempTable = symbolTable;
    // not found
    if (symbolTable == nullptr)
    {
        return nullptr;
    }
    symbol* temp = tempTable->head;
    while(temp != nullptr)
    {
        if (temp->variable_name == name)
        {
            return temp;
        }
        temp = temp->next;
    }
    return findSymbol(name, symbolTable->parent);
}

/* LOOKUP */
bool lookup_process(smatch s)
{
    return true;
}
/*BEGIN*/
bool begin_process(SymbolTable** symbolTable)
{
    ++current_scope;
    if ((*symbolTable)->child == nullptr)
    {
        SymbolTable* temp = *symbolTable;
        // create a new table for the child
        SymbolTable* newChild = new SymbolTable;
        // set the parent of new child
        newChild->parent = *symbolTable;
        // set the  new child
        temp->child = newChild;
        *symbolTable = (*symbolTable)->child;
        return true;
    }
    // the program must never reach here.
    return false;
}
/*END*/
void deleteSymbolTable(SymbolTable* symbolTable)
{
    symbol* temp = symbolTable->head;

    while (temp->next != nullptr)
    {
        // delete the node and move temp to next
        symbol* deleted = temp;
        temp = temp->next;
        temp->prev = nullptr;
        deleted->next = nullptr;
        delete deleted;
        deleted = nullptr;
        
    }
    // temp is at tail
    delete temp;
    temp = nullptr;
    symbolTable->tail = nullptr;
    symbolTable->head = nullptr;

    delete symbolTable;
    symbolTable = nullptr;
}

bool end_process(SymbolTable* symbolTable)
{
    /* delete the current and get back to the parent node */
    --current_scope;
    if (current_scope < 0)
    {
        throw UnknownBlock().what();
        return false;
    }

    SymbolTable* temp = symbolTable;

    symbolTable = symbolTable->parent;
    symbolTable->child = nullptr;
    deleteSymbolTable(temp);
}
/* PRINT */
bool print_process(smatch s)
{
    return true;
}
/* RPRINT */
bool rprint_process(smatch s)
{
    return true;
}

bool verify_identifer_name(string name)
{
    return true;
}






bool process(SymbolTable* &symbolTable, string line)
{

    smatch match;

    // check if the instruction is invalid
    if (!regex_match(line, match, ins) && !regex_match(line, match, assign) 
    && !regex_match(line, match, beg) && !regex_match(line, match, en)
    && !regex_match(line, match, lookup) && !regex_match(line, match, print)
    && !regex_match(line, match, rprint))
    {
        cout << regex_match(line, match, ins) << endl;
        throw (InvalidInstruction(line).what());
    }
        
    else 
    {
        if (match[1] == "INSERT") 
        {
            return insert_process(symbolTable, match);
        }
        else if (match[1] == "ASSIGN") 
        {
            return assign_process(symbolTable, match);
        }
        else if (match[1] == "LOOKUP") 
        {
            return lookup_process(match);
        }
        else if (match[1] == "BEGIN")
        {
            return begin_process(&symbolTable);
        }
        else if (match[1] == "END")
        {
            return end_process(symbolTable);
        }
        else if (match[1] == "PRINT")
        {
            return print_process(match);
        }
        else if (match[1] == "RPRINT")
        {
            return rprint_process(match);
        }
    }
    // the program should never reach here
    cout << "Out of control" << endl;
    return true;
}

void SymbolTable::run(string filename) {
    ifstream file(filename);

    string line;

    SymbolTable* temp = this;

    while (getline(file, line, '\n'))
    {
        process(temp, line);
    }
    
    if (current_scope != 0)
    {
        throw UnclosedBlock(current_scope).what();
    }
    
}