#include "SymbolTable.h"

using namespace std;

void test(string filename)
{
    SymbolTable *st = new SymbolTable();
    try
    {
        st->run(filename);
    }
    catch (exception &e)
    {
        cout << e.what();
    }
    delete st;
}

int main()
{
    string filename = "E:\\BK\\HL211\\CTDLGT\\assignment1\\testcase\\test1.txt";
    test(filename);
    return 0;
}