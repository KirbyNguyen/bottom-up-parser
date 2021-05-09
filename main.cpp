#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

#include "lexer.cpp"

using namespace std;

// A vector to hold the tokens
vector<Token> tokens;
// Stack for syntax analyzer
stack<string> helperStack;

int main()
{
    // Declare variables for reading file
    ifstream infile;
    string fileName = "";
    string line = "";

    // Read the file
    cout << "\nPlease enter the name of the file: ";
    getline(cin, fileName);

    // Open the file
    infile.open(fileName.c_str());

    // Error shooting if the file cannot be opened
    if (infile.fail())
    {
        cout << "\n** ERROR - the file \"" << fileName << "\" cannot be found!\n\n";
        exit(1);
    }

    // Determine each token in the line
    while (getline(infile, line))
    {
        vector<Token> temp = lexer(line);
        tokens.insert(tokens.end(), temp.begin(), temp.end());
    }

    tokens.push_back(Token(4, "$", "SEPERATOR"));


    return 0;
}