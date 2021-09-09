#include "SymbolTable.h"


regex ins("^(INSERT)\\s([a-zA-Z]\\w*)\\s(number|string)");
regex assign("^(ASSIGN)\\s([a-zA-Z]\\w*)\\s(\\d+|'.*'|[a-zA-Z]\\w*)");
regex beg ("^(BEGIN)");
regex en ("^(END)");
regex lookup ("^(LOOKUP)\\s([a-zA-Z]\\w*)");
regex print("^(PRINT)");
regex rprint("^(RPRINT)");

regex cons_num("\\d+");
regex literal_char("'.*'");
regex identifier_name("[a-zA-Z]\\w*");

const string success = "success\n";

int current_scope = 0;

void SymbolTable::push_back(symbol newSym)
{
    // The table is empty
    if (this->symbols == nullptr)
    {
        this->symbols = new symbol;
        *(this->symbols) = newSym;
    }

    symbol* last = this->symbols;
    while (last->next != nullptr) 
    {
        last = last->next;
    }
    symbol *newSymbol = new symbol;
    *newSymbol = newSym;
}

bool SymbolTable::insert_process(smatch s) // s[1]=INSERT; s[2] = (identifierName) ; s[3] = (type)
{
    if (!verify_identifer_name(s[2])) 
    {
        throw Redeclared(s[0]).what();
    }
    else 
    {
        // add a new symbol
        symbol newSymbol;
        newSymbol.variable_name = s[2];
        newSymbol.type = s[3];
        newSymbol.scope = current_scope;
        newSymbol.next = nullptr;
        this->push_back(newSymbol);
        cout << success;
        return true;
    }

}

// helper function
string SymbolTable::getType(string value, string instruction) {
    if (regex_match(value, cons_num)) 
        return "number";
    else if (regex_match(value, literal_char))
        return "string";
    else if (regex_match(value, identifier_name))
    {
        if (!identifier_name_declared(value)) 
            throw Undeclared(instruction).what();
        
        return findSymbol(value).type;
    }
}

// problem: do assign relate to scope? For now: we ignore scope
// jus the name is concerned
void SymbolTable::assigning(string idName, string idType, string instruction) 
{
    symbol* temp_sym = this->symbols;
    while (temp_sym != nullptr) 
    {
        if (temp_sym->variable_name == idName)
        {
            if (temp_sym->type != idType)
            {
                throw TypeMismatch(instruction).what();
            }
            else 
            {
                // output here
                cout << success;
                return;
            }
        }
    }
}

// s[1]=ASSIGN; s[2] = (identifierName) ; s[3] = (type)
bool SymbolTable::assign_process(smatch s) 
{
    if (!identifier_name_declared(s[2])) 
    {
        throw Undeclared(s[0]).what();
    }
    
    string idtype = getType(s[2], s[0]);

    this->assigning(s[2], idtype, s[0]);

    return true;
}


bool SymbolTable::process(string line) {
    // slice the string in words
    // process each word 1 by 1
    // insert regex
    // assign regex
    smatch match;

    // check if the instruction is invalid
    if (!regex_match(line, match, ins) || !regex_match(line, match, assign) 
    || !regex_match(line, match, beg) || !regex_match(line, match, en)
    || !regex_match(line, match, lookup) || !regex_match(line, match, print)
    || !regex_match(line, match, rprint))
    {
        throw (InvalidInstruction(line).what());
    }
        
    else 
    {
        if (match[1] == "INSERT") 
        {
            return insert_process(match);
        }
        else if (match[1] == "ASSIGN") 
        {
            return assign_process(match);
        }
        else if (match[1] == "LOOKUP") 
        {
            return lookup_process(match);
        }
        else if (match[1] == "BEGIN")
        {
            return begin_process(match);
        }
        else if (match[1] == "END")
        {
            return end_process(match);
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


}

void SymbolTable::run(string filename) {
    ifstream file(filename);

    string line;

    while (getline(file, line)) 
    {
        if (process(line));
            
    }
    

    
}