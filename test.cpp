#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;
regex cons_num("\\d+");

regex ins("^(INSERT)\\s([a-zA-Z]\\w*)\\s(\\w+)");
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

void symbol::initialize(string name, string type, int scope)
{
    this->variable_name = name;
    this->type = type;
    this->scope = scope;
    this->next = nullptr;
    this->prev = nullptr;
}

void push_back(symbol** sym, symbol val)
{
    if (*sym == nullptr)
    {
        symbol* newSym = new symbol;
        *newSym = val;
        *sym = newSym;
        return;
    }
    else 
    {
        symbol* temp = (*sym);
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        symbol* newSym = new symbol;
        *newSym = val;
        newSym->prev = temp;
        temp->next = newSym;

    }
}

int main () {
    // string filename = "testfile.txt";
    // string test;

    // fstream input (filename);
    // getline(input, test);


// string s = "foo bar  baz";
// regex e("\\s+");
// regex_token_iterator<string::iterator> i(s.begin(), s.end(), e, -1);
// regex_token_iterator<string::iterator> end;
// while (i != end)
//    cout << " [" << *i++ << "]";

    // string s = "2";
    // not done
    // ^(ASSIGN)\s\w+\s(\d+|'.*')
    // regex valid_identifier_name ("[a-zA-Z]\\w*");
    // smatch match;
    // cout << regex_match(s, cons_num) << endl;
 
    
    //[0]: The whole match
    //[1]: the first item
    // ...

    symbol* temp = nullptr;
    symbol a,b ;
    a.initialize("a", "b", 2);
    b.initialize("b", "b", 2);
    push_back(&temp, a);
    push_back(&temp, b);

    cout << temp->next->variable_name;
    symbol* n = temp->next;
    delete temp;
    cout << n->variable_name;
    return 0;

}