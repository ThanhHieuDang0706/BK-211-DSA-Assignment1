#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main () {
    string filename = "testfile.txt";
    string test;

    fstream input (filename);
    getline(input, test);
  
    cout << test;
    string word;
    test >> word;
    cout << word;
    return 0;
}