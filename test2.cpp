#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

stack<string> helperStack;

enum COLUMN
{
    ID,
    PLUS,
    TIME,
    LEFT_PAR,
    RIGHT_PAR,
    MONEY,
    E,
    T,
    F,
    ERROR
};

enum STATE
{
    EXCEPTION,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    S4,
    S5,
    S6,
    S7,
    S11,
    N1,
    N2,
    N3,
    N8,
    N9,
    N10,
    ACCT,
    EMPTY
};

int stateTable[12][9] = {
    {S5, EMPTY, EMPTY, S4, EMPTY, EMPTY, N1, N2, N3},
    {EMPTY, S6, EMPTY, EMPTY, EMPTY, ACCT, EMPTY, EMPTY, EMPTY},
    {EMPTY, R2, S7, EMPTY, R2, R2, EMPTY, EMPTY, EMPTY},
    {EMPTY, R4, R4, EMPTY, R4, R4, EMPTY, EMPTY, EMPTY},
    {S5, EMPTY, EMPTY, S4, EMPTY, EMPTY, N8, N2, N3},
    {EMPTY, R6, R6, EMPTY, R6, R6, EMPTY, EMPTY, EMPTY},
    {S5, EMPTY, EMPTY, S4, EMPTY, EMPTY, EMPTY, N9, N3},
    {S5, EMPTY, EMPTY, S4, EMPTY, EMPTY, EMPTY, EMPTY, N10},
    {EMPTY, S6, EMPTY, EMPTY, S11, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, R1, S7, EMPTY, R1, R1, EMPTY, EMPTY, EMPTY},
    {EMPTY, R3, R3, EMPTY, R3, R3, EMPTY, EMPTY, EMPTY},
    {EMPTY, R5, R5, EMPTY, R5, R5, EMPTY, EMPTY, EMPTY},
};

void stackPrinter()
{
    for (stack<string> dump = helperStack; !dump.empty(); dump.pop())
        cout << dump.top();

    cout << endl;
};

string getString(char x)
{
    string s(1, x);
    return s;
}

void popStack(int num)
{
    while (num > 0)
    {
        helperStack.pop();
        num--;
    }
}

COLUMN charParser(char value)
{
    switch (value)
    {
    case '+':
        return PLUS;
    case '*':
        return TIME;
    case '(':
        return LEFT_PAR;
    case ')':
        return RIGHT_PAR;
    case '$':
        return MONEY;
    default:
        if (isalpha(value))
            return ID;
        return ERROR;
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
    case N8:
        helperStack.push("8");
        return 8;
    case N9:
        helperStack.push("9");
        return 9;
    case N10:
        helperStack.push("10");
        return 10;
    default:
        return 0;
    }
    return 0;
}

int main()
{

    // Test string
    string testInput = "a+b$";

    // Initialize about the stack
    helperStack.push("$");
    helperStack.push("0");

    int inputIndex = 0;
    int currentState = 0;

    bool isLoop = true;

    cout << "Stack ";
    stackPrinter();

    cout << "Input " << testInput << endl;

    while (isLoop)
    {
        int parseResult = charParser(testInput[inputIndex]);
        int x = stateTable[currentState][parseResult];
        int Qj, Qk;
        switch (x)
        {
        case S4:
            helperStack.push(getString(testInput[inputIndex]));
            helperStack.push("4");
            currentState = 4;
            inputIndex++;
            break;
        case S5:
            helperStack.push(getString(testInput[inputIndex]));
            helperStack.push("5");
            currentState = 5;
            inputIndex++;
            break;
        case S6:
            helperStack.push(getString(testInput[inputIndex]));
            helperStack.push("6");
            currentState = 6;
            inputIndex++;
            break;
        case S7:
            helperStack.push(getString(testInput[inputIndex]));
            helperStack.push("7");
            currentState = 7;
            inputIndex++;
            break;
        case S11:
            helperStack.push(getString(testInput[inputIndex]));
            helperStack.push("11");
            currentState = 11;
            inputIndex++;
            break;
        case R1:
            popStack(6);
            Qj = stoi(helperStack.top());
            helperStack.push("E");
            Qk = stateTable[Qj][E];
            currentState = pushGoTo(Qk);
            break;
        case R2:
            popStack(2);
            Qj = stoi(helperStack.top());
            helperStack.push("E");
            Qk = stateTable[Qj][E];
            currentState = pushGoTo(Qk);
            break;
        case R3:
            popStack(6);
            Qj = stoi(helperStack.top());
            helperStack.push("T");
            Qk = stateTable[Qj][T];
            currentState = pushGoTo(Qk);
            break;
        case R4:
            popStack(2);
            Qj = stoi(helperStack.top());
            helperStack.push("T");
            Qk = stateTable[Qj][T];
            currentState = pushGoTo(Qk);
            break;
        case R5:
            popStack(6);
            Qj = stoi(helperStack.top());
            helperStack.push("F");
            Qk = stateTable[Qj][F];
            currentState = pushGoTo(Qk);
            break;
        case R6:
            popStack(2);
            Qj = stoi(helperStack.top());
            helperStack.push("F");
            Qk = stateTable[Qj][F];
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
        stackPrinter();
        cout << "Input " << testInput.substr(inputIndex, testInput.length()) << endl;
    }

    return 0;
}