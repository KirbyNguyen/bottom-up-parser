#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <iomanip>
#include <cstdio>
#include <ctime>

#include "lexer.cpp"

using namespace std;

bool checkStatement();
bool checkAssign();
bool checkDeclarative();

bool checkExpression();
bool checkExpressionPrime();
bool checkTerm();
bool checkTermPrime();
bool checkFactor();

bool checkIdentifier();
bool checkType();

clock_t t;
double duration;

// Acknowledge if this is a statement or not
// DEFAULT: false
bool duringStatement = false;
bool duringExpression = false;

// A vector to hold the tokens
vector<Token> tokens;
// Token token;
int token_ptr;

int main()
{
    // Declare variables for reading file
    ifstream infile;
    string fileName = "";
    string line = "";

    // Money sign to mark the end of the file
    Token moneySign;
    moneySign.lexemeNum = 4;
    moneySign.lexeme = "$";
    moneySign.lexemeName = "SEPERATOR";
    // Fake null char (line break)
    Token nullchar;
    nullchar.lexemeNum = 3;
    nullchar.lexeme = "\0";
    nullchar.lexemeName = "SEPERATOR";

    // Read the file
    cout << "\nPlease enter the name of the file (ignore file extensions): ";
    getline(cin, fileName);

    // Open the file
    fileName += ".txt";
    infile.open(fileName.c_str());

    // Error shooting if the file cannot be opened
    if (infile.fail())
    {
        cout << "\n** ERROR - the file \"" << fileName << "\" cannot be found!\n\n";
        exit(1);
    }

    token_ptr = 0;

    // Determine each token in the line
    // Forces a null char delimiter after each line without a natural semicolon, to ensure a boundary exists between sentences
    vector<vector<Token>> tokensList;
    int k = 1;
    while (getline(infile, line))
    {
        vector<Token> temp = lexer(line, k);
        
        if (!temp.empty() && (temp.front().lexeme != "!" && temp.back().lexeme != "!") && temp.back().lexeme != ";")
        {            
            temp.push_back(nullchar);
        }
        if ( !temp.empty() && (temp.front().lexeme != "!" && temp.back().lexeme != "!") )
        {            
            //tokens.insert(tokens.end(), temp.begin(), temp.end());
            tokensList.push_back(temp);
        }
        ++k;
    }

    //tokens.push_back(moneySign);

    // Close the file
    infile.close();
    infile.clear();
    /*
    // Parse the file one sentence (line) at a time
    // ParseExpr is a helper class to determine syntax using tabular method
    */
    ParseExpr expr;
    string tempstring, prev;
    t = clock();

    /*for (Token tk : tokens)
    {
        tempstring = tk.lexeme;
        expr.str2 += tempstring;
        expr.token = tk;
        prev = tk.lexeme;
        if (tk.lexeme == ";")
        {
            if (tk.artificial)
            {
                expr.setArtificial(true);
            }
            expr.interpret();
            expr.str2 = "";
            expr.token.lexeme = "";
            expr.setArtificial(false);
        }
        else if (tk.lexeme.length() < 1)
        {
            expr.interpret();
        }
        expr.prev = tempstring;

    }*/
    for (auto tkl: tokensList)
    {
        string sline = "";
        for (auto s : tkl)
        {
            sline = sline + " "+ s.lexeme;
            //cout << s.lexemeName + "       " << s.lexeme << endl;
        }
        cout << "\n\n   ::::::::::::::::: New Line :::::::::::::::::   " << sline << "\n\n\n";
        expr.interpret(tkl);
        tokens.insert(tokens.end(), tkl.begin(), tkl.end());
        /*for (auto tk: tkl)
        {
            expr.interpret(tk);
        }*/
    }
    moneySign.scope = expr.getScope();
    tokens.push_back(moneySign);
    Token lastToken = tokens.back();
    if (lastToken.scope != 0)
    {
        cout << "\n**ERROR : scope value is not 0 at the end of file**\n"
        " actual scope = " << lastToken.scope << "\n**Now Exiting....**";
    }
    duration = ( clock() - t ) / (double) CLOCKS_PER_SEC;
    cout << "\nParsing concluded successfully in " << duration << " seconds! \n\n";
    printST(symbolTable(tokens));
    duration = ( clock() - t ) / (double) CLOCKS_PER_SEC - duration;
    cout << "\nSymbol table constructed in " << duration << " seconds! \n\n";

    return 0;
}
