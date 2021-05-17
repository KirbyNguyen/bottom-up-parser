#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

#include "constants.cpp"

using namespace std;

// A vector to hold the tokens
vector<Token> tokens;
// Stack for syntax analyzer
stack<string> helperStack;

void stackPrinter(stack<string> dump)
{
    if (dump.empty())
        return;

    string TOS = dump.top();

    dump.pop();

    stackPrinter(dump);

    cout << TOS;

    dump.push(TOS);
};

void popStack(int num)
{
    while (num > 0)
    {
        helperStack.pop();
        num--;
    }
}

int pushGoTo(int Qk)
{
    switch (Qk)
    {
    case N1:
        helperStack.push("1");
        return 1;
    case N2:
        helperStack.push("2");
        return 2;
    case N3:
        helperStack.push("3");
        return 3;
    case N10:
        helperStack.push("10");
        return 10;
    case N11:
        helperStack.push("11");
        return 11;
    case N12:
        helperStack.push("12");
        return 12;
    case N13:
        helperStack.push("13");
        return 13;
    case N14:
        helperStack.push("14");
        return 14;
    default:
        return 0;
    }
    return 0;
}

void printToken(int index)
{
    for (int i = index; i < tokens.size(); i++)
    {
        cout << tokens[i].lexeme;
    }
}
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

    int inputIndex = 0;
    int currentState = 0;

    bool isLoop = true;
    while (isLoop)
    {
        int parseResult = tokenParser(tokens[inputIndex]);
        int x = stateTable[currentState][parseResult];
        int Qj, Qk;
        switch (x)
        {
        case S4:
            helperStack.push(tokens[inputIndex].lexeme);
            helperStack.push("4");
            currentState = 4;
            inputIndex++;
            break;
        case S5:
            helperStack.push(tokens[inputIndex].lexeme);
            helperStack.push("5");
            currentState = 5;
            inputIndex++;
            break;
        case S6:
            helperStack.push(tokens[inputIndex].lexeme);
            helperStack.push("6");
            currentState = 6;
            inputIndex++;
            break;
        case S7:
            helperStack.push(tokens[inputIndex].lexeme);
            helperStack.push("7");
            currentState = 7;
            inputIndex++;
            break;
        case S8:
            helperStack.push(tokens[inputIndex].lexeme);
            helperStack.push("8");
            currentState = 8;
            inputIndex++;
            break;
        case S9:
            helperStack.push(tokens[inputIndex].lexeme);
            helperStack.push("9");
            currentState = 9;
            inputIndex++;
            break;
        case S15:
            helperStack.push(tokens[inputIndex].lexeme);
            helperStack.push("15");
            currentState = 15;
            inputIndex++;
            break;
        case R1:
            popStack(6);
            Qj = stoi(helperStack.top());
            helperStack.push("E");
            Qk = stateTable[Qj][E_STATE];
            currentState = pushGoTo(Qk);
            break;
        case R2:
            popStack(6);
            Qj = stoi(helperStack.top());
            helperStack.push("E");
            Qk = stateTable[Qj][E_STATE];
            currentState = pushGoTo(Qk);
            break;
        case R3:
            popStack(2);
            Qj = stoi(helperStack.top());
            helperStack.push("E");
            Qk = stateTable[Qj][E_STATE];
            currentState = pushGoTo(Qk);
            break;
        case R4:
            popStack(6);
            Qj = stoi(helperStack.top());
            helperStack.push("T");
            Qk = stateTable[Qj][T_STATE];
            currentState = pushGoTo(Qk);
            break;
        case R5:
            popStack(6);
            Qj = stoi(helperStack.top());
            helperStack.push("T");
            Qk = stateTable[Qj][T_STATE];
            currentState = pushGoTo(Qk);
            break;
        case R6:
            popStack(2);
            Qj = stoi(helperStack.top());
            helperStack.push("T");
            Qk = stateTable[Qj][T_STATE];
            currentState = pushGoTo(Qk);
            break;
        case R7:
            popStack(6);
            Qj = stoi(helperStack.top());
            helperStack.push("F");
            Qk = stateTable[Qj][F_STATE];
            currentState = pushGoTo(Qk);
            break;
        case R8:
            popStack(2);
            Qj = stoi(helperStack.top());
            helperStack.push("F");
            Qk = stateTable[Qj][F_STATE];
            currentState = pushGoTo(Qk);
            break;
        case ACCT:
            cout << "Parsing is complete" << endl;
            isLoop = false;
            break;
        default:
            cout << "Error" << endl;
            isLoop = false;
            break;
        }
        cout << "Stack ";
        stackPrinter(helperStack);
        cout << endl;

        cout << "Input ";
        printToken(inputIndex);
        cout << endl;
    }

    return 0;

    return 0;
}