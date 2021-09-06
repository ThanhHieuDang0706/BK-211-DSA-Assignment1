#include "SymbolTable.h"


regex ins("^(INSERT)\\s([a-zA-Z]\\w*)\\s(\\w+)");
regex assign("^(ASSIGN)\\s([a-zA-Z]\\w*)\\s(\\d+|'.*')");
regex beg ("^(BEGIN)");
regex en ("^(END)");
regex lookup ("^(LOOKUP)\\s([a-zA-Z]\\w*)");
regex print("^(PRINT)");
regex rprint("^(RPRINT)");


bool SymbolTable::insert_process(smatch s) // s[1]=INSERT; s[2] = (identifierName) ; s[3] = (type)
{
    



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
            insert_process(match);
        }
    }


}

void SymbolTable::run(string filename) {
    ifstream file(filename);

    string line;

    while (getline(file, line)) 
    {
        if (process(line))
            cout << "success";
    }
    

    
}