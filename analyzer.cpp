#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

stack<char> helperStack;

void stackPrinter()
{
    for (stack<char> dump = helperStack; !dump.empty(); dump.pop())
        cout << dump.top();

    cout << endl;
};

int main()
{

    // Test string
    string testInput = "a+b$";

    // Initialize about the stack
    helperStack.push('$');
    helperStack.push('E');

    int inputIndex = 0;

    while (helperStack.size() > 1)
    {
        if (helperStack.top() == testInput[inputIndex])
        {
            stackPrinter();
            cout << "Matched with " << helperStack.top() << endl;

            if (testInput[inputIndex + 1] != '\0')
                inputIndex++;

            helperStack.pop();
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
        }
    }

    stackPrinter();
    return 0;
}