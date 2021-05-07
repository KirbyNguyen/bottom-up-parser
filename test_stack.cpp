#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>

using namespace std;

enum ASSEMBLY
{
    NONE = 0,
    POPM,
    PUSHI,
    PUSHM,
    STDOUT,
    STDIN,
    ADD,
    SUB,
    MUL,
    DIV,
    GRT,
    LES,
    EQU,
    NEQ,
    GEQ,
    LEQ,
    JUMPZ,
    JUMP,
    LABEL

};

struct Symbol
{
    int addr;
    string instr;
    string iden;
    int memloc;
    string type;
    int value;
};


stack<char> helperStack;
stack<int> assemblyStack;
vector<Symbol> instructions;
vector<Symbol> symbols;
vector<string> identifiers;
unordered_set<string> idset;
int globalMemLoc = 2000;
int globalMax = 2000;
string spacing = "                        ";
string spacing2 = "            ";
pair<string, string> current;

void stackPrinter()
{
    for (stack<char> dump = helperStack; !dump.empty(); dump.pop())
        cout << dump.top();

    cout << endl;
};

int getMemAddr(string var)
{

    return 0;
}

void symbolTablePrinter()
{
    cout << "Symbol Table\nIdentifier          " << "     Memory Location     "<< "         Type          " << endl;
    for (auto S : symbols)
    {
        cout << S.iden << spacing << S.memloc << spacing << S.type << endl;
    }
}

void assemblyPrinter()
{
    for (auto S : instructions)
    {
        cout << S.addr << spacing2 << S.instr << spacing2 << S.value << endl;
    }
}

int gen_instr(int op, int oper)
{
    Symbol S;
    if (op < 0) { return -1; }
    switch(op)
    {
        case POPM:
            //assemblyStack.pop();
            S.addr = instructions.size() + 1;
            S.iden = current.first;
            S.instr = "POPM ";
            S.memloc = globalMemLoc;
            S.type = current.second;
            S.value = S.memloc;
            instructions.push_back(S);
            break;
        case PUSHI:
            S.addr = instructions.size() + 1;
            S.iden = current.first;
            S.instr = "PUSHI";
            if (!idset.count(current.first))
            {
                idset.insert(current.first);
                globalMax++;
                S.memloc = globalMax;
            }
            else
            {
                S.memloc = globalMemLoc;                
            }
            S.type = current.second;
            S.value = 0;
            instructions.push_back(S);
            //assemblyStack.push(S.value);
            return S.value;
            break;
        case PUSHM:
            S.addr = instructions.size() + 1;
            S.iden = current.first;
            S.instr = "PUSHM";
            S.memloc = globalMemLoc;
            S.type = current.second;
            S.value = S.memloc;
            instructions.push_back(S);
            //assemblyStack.push(S.value);
            return S.value;
            break;
        case STDOUT:
            break;
        case STDIN:
            break;
        case ADD:
            break;
        case SUB:
            break;
        case MUL:
            break;
        case DIV:
            break;
        case GRT:
            break;
        case LES:
            break;
        case EQU:
            break;
        case NEQ:
            break;
        case GEQ:
            break;
        case LEQ:
            break;
        case JUMPZ:
            break;
        case JUMP:
            break;
        case LABEL:
            break;
        default:
            break;
    }
    return 0;
}

int main()
{

    // Test string
    string testInput = "a+b-c$";

    //instructions.push_back(Symbol());
    gen_instr(PUSHI, globalMemLoc);
    gen_instr(POPM, globalMemLoc);
    gen_instr(PUSHI, globalMemLoc);
    gen_instr(POPM, globalMemLoc);
    gen_instr(PUSHI, globalMemLoc);
    gen_instr(POPM, globalMemLoc);
    gen_instr(PUSHI, globalMemLoc);
    gen_instr(POPM, globalMemLoc);
    gen_instr(PUSHI, globalMemLoc);
    gen_instr(PUSHI, globalMemLoc);
    gen_instr(EQU, globalMemLoc);
    gen_instr(JUMPZ, globalMemLoc);
    gen_instr(PUSHM, globalMemLoc);
    gen_instr(POPM, globalMemLoc);
    gen_instr(PUSHM, globalMemLoc);
    gen_instr(POPM, globalMemLoc);
    assemblyPrinter();
    symbolTablePrinter();

    // Initialize about the stack
    helperStack.push('$');
    helperStack.push('E');

    int inputIndex = 0;

    while (inputIndex < testInput.size() && helperStack.size() > 1)
    {
        if (helperStack.top() == testInput[inputIndex])
        {
            stackPrinter();
            cout << "Matched with " << helperStack.top() << endl;

            if (testInput[inputIndex + 1] != '\0')
                inputIndex++;
                
            helperStack.pop();
            
            if (testInput[inputIndex] == '$')
            {
                while(!helperStack.empty())
                {
                    stackPrinter();
                    helperStack.pop();
                }
                stackPrinter();
                cout << "done" << endl;
                exit(0);
            }
        }
        else if (helperStack.top() == 'E' && testInput[inputIndex] == '(')
        {
            stackPrinter();
            cout << testInput[inputIndex] << endl;
            cout << "Rule no. 1" << endl;

            helperStack.pop();
            helperStack.push('Q');
            helperStack.push('T');
        }
        else if (helperStack.top() == 'E' && isalpha(testInput[inputIndex]))
        {
            stackPrinter();
            cout << testInput[inputIndex] << endl;
            cout << "Rule no. 1" << endl;

            helperStack.pop();
            helperStack.push('Q');
            helperStack.push('T');
        }
        else if (helperStack.top() == 'Q' && testInput[inputIndex] == '+')
        {
            cout << "Rule no. 2" << endl;

            helperStack.pop();
            helperStack.push('Q');
            helperStack.push('T');
            helperStack.push('+');
        }
        else if (helperStack.top() == 'Q' && testInput[inputIndex] == '-')
        {
            cout << "Rule no. 3" << endl;

            helperStack.pop();
            helperStack.push('Q');
            helperStack.push('T');
            helperStack.push('-');
        }
        else if (helperStack.top() == 'Q' && testInput[inputIndex] == '$')
        {
            cout << "Rule no. 4" << endl;

            helperStack.pop();
        }
        else if (helperStack.top() == 'T' && testInput[inputIndex] == '(')
        {
            stackPrinter();
            cout << testInput[inputIndex] << endl;
            cout << "Rule no. 5" << endl;

            helperStack.pop();
            helperStack.push('R');
            helperStack.push('F');
        }
        else if (helperStack.top() == 'T' && isalpha(testInput[inputIndex]))
        {
            stackPrinter();
            cout << testInput[inputIndex] << endl;
            cout << "Rule no. 5" << endl;

            helperStack.pop();
            helperStack.push('R');
            helperStack.push('F');
        }
        else if (helperStack.top() == 'R' && (testInput[inputIndex] == '+' ||
                                              testInput[inputIndex] == '-' ||
                                              testInput[inputIndex] == ')' ||
                                              testInput[inputIndex] == '#' ))
        {
            cout << "Rule no. 8" << endl;

            helperStack.pop();
        }
        else if (helperStack.top() == 'R' && testInput[inputIndex] == '*')
        {
            cout << "Rule no. 6" << endl;

            helperStack.pop();
            helperStack.push('R');
            helperStack.push('F');
            helperStack.push('*');
        }
        else if (helperStack.top() == 'F' && testInput[inputIndex] == '(')
        {
            cout << "Rule no. 9" << endl;

            helperStack.pop();
            helperStack.push(')');
            helperStack.push('E');
            helperStack.push('(');
        }
        else if (helperStack.top() == 'F' && isalpha(testInput[inputIndex]))
        {
            stackPrinter();
            cout << testInput[inputIndex] << endl;
            cout << "Rule no. 10" << endl;

            helperStack.pop();
            helperStack.push('I');
        }
        else if (helperStack.top() == 'I' && isalpha(testInput[inputIndex]))
        {
            stackPrinter();
            cout << testInput[inputIndex] << endl;
            cout << "Rule no. 11" << endl;

            helperStack.pop();
            helperStack.push(testInput[inputIndex]);

            stackPrinter();
            cout << testInput[inputIndex] << endl;

            current.first = testInput[inputIndex];
            current.second = ((isalpha(testInput[inputIndex])) ? "integer" : "nil" );

            if (find(identifiers.begin(), identifiers.end(), current.first) != identifiers.end())
            {
                identifiers.push_back(current.first);
            }
            else 
            {
                globalMemLoc++;                
            }
        }
    }

    stackPrinter();
    return 0;
    exit(0);
}