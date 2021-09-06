#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;


regex ins("^(INSERT)\\s([a-zA-Z]\\w*)\\s(\\w+)");



int main () {
    string filename = "testfile.txt";
    string test;

    fstream input (filename);
    getline(input, test);


// string s = "foo bar  baz";
// regex e("\\s+");
// regex_token_iterator<string::iterator> i(s.begin(), s.end(), e, -1);
// regex_token_iterator<string::iterator> end;
// while (i != end)
//    cout << " [" << *i++ << "]";

    string s = "INSERT 2x number";
    // not done
    // ^(ASSIGN)\s\w+\s(\d+|'.*')
    regex valid_identifier_name ("[a-zA-Z]\\w*");
    smatch match;
    cout << regex_match(s, match, ins) << endl;
 
    
    //[0]: The whole match
    //[1]: the first item
    // ...
    return 0;

}