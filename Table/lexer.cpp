/**********

Lexical Analyzer

Group Members: Duc Nguyen (887323301), Wayne Lin (887280121)

**********/

/**************
Instructions
1) Run the .exe
2) Enter name of text file when prompted
3) View results
**************/

#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <stack>

using namespace std;

/*
    Enumerator to get lexeme name and to transist the FSM
*/
#ifndef _MY_HEADER_H_
#define _MY_HEADER_H_

enum TOKEN_TYPES
{
	REJECT = 0,
	INTEGER,
	REAL,
	SEPERATOR,
	OPERATOR,
	STRING,
	IGNORE,
	UNKNOWN,
	SPACE,
	KEYWORD,
	IDENTIFIER
};
enum EXPR_TYPES
{
	INVALID = -1,
	Te,
	PLUSTe,
	MINUSTe,
	Ft,
	STARFt,
	SLASHFt,
	id,
	EPSILON,
	E_WITH_PARENTHESES,
    STAT,
    ASSIGN,
	NOTHNG
};

//#endif /* _MY_HEADER_H_ */
#endif /* _MY_HEADER_H_ */

// State table for transvering through the lexeme
// A string can either be a KEYWORD or an IDENTIFIER
int stateTable[][9] = {
	/* PLACE HOLDER STATE */ {0, INTEGER, REAL, SEPERATOR, OPERATOR, STRING, IGNORE, UNKNOWN, SPACE},
	/* INTEGER STATE */ {INTEGER, INTEGER, REAL, REJECT, REJECT, REJECT, REJECT, REJECT, REJECT},
	/* REAL STATE */ {REAL, REAL, UNKNOWN, REJECT, REJECT, REJECT, REJECT, REJECT, REJECT},
	/* SEPERATOR STATE */ {SEPERATOR, REJECT, REJECT, REJECT, REJECT, REJECT, REJECT, REJECT, REJECT},
	/* OPERATOR STATE */ {OPERATOR, REJECT, REJECT, REJECT, OPERATOR, REJECT, REJECT, REJECT, REJECT},
	/* STRING STATE */ {STRING, STRING, STRING, REJECT, REJECT, STRING, STRING, STRING, REJECT},
	/* IGNORE STATE */ {IGNORE, IGNORE, IGNORE, IGNORE, IGNORE, IGNORE, REJECT, IGNORE, IGNORE},
	/* UNKNOWN STATE */ {UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN},
	/* REJECT STATE */ {SPACE, REJECT, REJECT, REJECT, REJECT, REJECT, REJECT, REJECT, REJECT}};

/*
    A struct to hold a token information
*/
struct Token
{
	int lexemeNum;
	string lexeme;
	string lexemeName;
	string productionRules;
	bool artificial = false;	// set true for fake semicolons ONLY
};

// Set to hold seperators
static const unordered_set<char> SEPERATORS({'{', '}', '[', ']', '(', ')', ',', '.', ';', ':'});
// Set to hold operators
static const unordered_set<char> OPERATORS({'+', '-', '*', '/', '=', '<', '>', '%'});
// Set to hold special characters
static const unordered_set<char> SPECIALS({'!', '_'});
// Set to hold keywords
static const unordered_set<string> KEYWORDS({"int", "float", "bool", "True", "False",
											 "if", "else", "then", "endif", "endelse", "while", "whileend", "do",
											 "enddo", "for", "endfor", "STDinput", "STDoutput", "and", "or", "not"});

/* PROTOTYPES FOR THE FUNCTIONS */
vector<Token> lexer(string expression);
int getCharState(char currentChar, char prevState);
string getLexemeName(int lexemeNum, string token);

/**
*	FUNCTION: lexer
*	USE: go through the string to return a list of tokens.
*	@param expression - the code line
*	@return tokens - a list of tokens
*/
vector<Token> lexer(string expression)
{
	// Variable for the state machine
	Token access;
	vector<Token> tokens;
	char currentChar = ' ';
	int charState = REJECT;
	int currentState = REJECT;
	int prevState = REJECT;
	string currentToken = "";

	// Go through each character
	for (unsigned x = 0; x < expression.length();)
	{

		// Check the current state of the character
		currentChar = expression[x];
		charState = getCharState(currentChar, prevState);

		// Get the current state
		currentState = stateTable[currentState][charState];

		// If the current state is REJECT, we have started a new parse,
		// and the old one is succesfull.
		// If not, continue finding a token
		if (currentState == REJECT)
		{
			if (prevState != SPACE) // we dont care about whitespace
			{
				access.lexeme = currentToken;
				access.lexemeNum = prevState;
				access.lexemeName = getLexemeName(access.lexemeNum, access.lexeme);

				// Extra step for the KEYWORD and IDENTIFIER
				if (access.lexemeName.compare("KEYWORD") == 0)
					access.lexemeNum = KEYWORD;
				else if (access.lexemeName.compare("IDENTIFIER") == 0)
					access.lexemeNum = IDENTIFIER;

				tokens.push_back(access);
			}
			currentToken = "";
		}
		else
		{
			currentToken += currentChar;
			++x;
		}
		prevState = currentState;
	}

	// Include the last character
	if (currentState != SPACE && currentToken != "")
	{
		access.lexeme = currentToken;
		access.lexemeNum = currentState;
		access.lexemeName = getLexemeName(access.lexemeNum, access.lexeme);

		// Extra step for the KEYWORD and IDENTIFIER
		if (access.lexemeName.compare("KEYWORD") == 0)
			access.lexemeNum = KEYWORD;
		else if (access.lexemeName.compare("IDENTIFIER") == 0)
			access.lexemeNum = IDENTIFIER;

		tokens.push_back(access);
	}
	return tokens;
} // end of Lexer

/**
* FUNCTION: getCharState
* USE: get the corresponding state based on the current character
* @param currentChar - the current char
* @return int - the current state of the character
*/
int getCharState(char currentChar, char prevState)
{
	// Check for whitespace
	if (isspace(currentChar))
	{
		return SPACE;
	}

	// Check for integer numbers
	else if (isdigit(currentChar))
	{
		return INTEGER;
	}

	// Check for real numbers or period
	else if (currentChar == '.')
	{
		return (prevState == INTEGER ? REAL : SEPERATOR);
	}

	// Check for characters
	else if (isalpha(currentChar))
	{
		return STRING;
	}

	// Check for comment
	else if (currentChar == '!')
	{
		return IGNORE;
	}

	// Check for seperators
	else if (SEPERATORS.find(currentChar) != SEPERATORS.end())
	{
		return SEPERATOR;
	}

	// Check for operators
	else if (OPERATORS.find(currentChar) != OPERATORS.end())
	{
		return OPERATOR;
	}

	return UNKNOWN;
}

/**
* FUNCTION: getLexemeName
* USE: takes a number and return the corresponding string to the token type.
* @param lexemeNum - integer that corresponds to the state
* @return - a string of the state
*/
string getLexemeName(int lexemeNum, string lexeme)
{
	switch (lexemeNum)
	{
	case INTEGER:
		return "INTEGER";
		break;
	case REAL:
		return "REAL";
		break;
	case SEPERATOR:
		return "SEPERATOR";
		break;
	case OPERATOR:
		return "OPERATOR";
		break;
	case STRING:
		return (KEYWORDS.find(lexeme) != KEYWORDS.end() ? "KEYWORD" : "IDENTIFIER");
		break;
	case IGNORE:
		return "COMMENT";
		break;
	case UNKNOWN:
		return "UNKNOWN";
		break;
	case SPACE:
		return "SPACE";
		break;
	default:
		return "ERROR";
		break;
	};
};

static int globalMemLoc = 2000;

struct Symbol
{
    string iden;
    int memloc;
    string type;

    Symbol ()
    {

    }
    Symbol(string i, int loc, string t)
    {
        iden = i;
        memloc = loc;
        type = t;
    }
};

string format(string type)
{
    if (type == "int")
    {
        return "integer";
    }
    if (type == "bool")
    {
        return "boolean";
    }
    if (type == "float")
    {
        return "floating point";
    }
    if (type == "real")
    {
        return "real number";
    }
    return "other";
}

vector<Symbol> symbolTable (vector<Token> tkns)
{  
    vector<Symbol> symbols;
    Token prev;
    int k = 0;
    for (auto tk: tkns)
    {
        if (tk.lexemeNum == 10 && prev.lexemeNum == 9)
        {
            Symbol S = Symbol (tk.lexeme, globalMemLoc + k, format(prev.lexeme));
            symbols.push_back(S);
            ++k;
        }
        if (tk.lexemeNum != 10 && tk.lexeme != ",")
        {
            prev = tk;
        }
    }
    return symbols;
}

template<typename T> void print(T t, const int& width)
{
    const char space = ' ';
    cout << left << setw(width) << setfill(space) << t;
}

void printST (vector<Symbol> ST)
{
    cout << endl << "Symbol Table" << endl;
    const char width0 = 25;
    const char width1 = 25;
    const char width2 = 25;
    print("Identifier", width0);
    print("Memory Location", width0);
    print("Type", width0);
    cout << endl;
    for (auto S : ST)
    {
        print(S.iden, width1);
        print(S.memloc, width1);
        print(S.type, width1);
        cout << endl;
    }
}

class Expr 
{
    public:
    stack<string> stk;                  // stack for pushing and popping table elements (shorthand production tokens)
    deque<string> fullstack;            // deque stores the whole stack contents for parse tree (only reset after statement or on new sentence)
    Token token;
    string str2;                        // holds each sentence passed into the interpret()
    unordered_set<string> expansion;    // holds production rules from the stack in the proper order to be expanded and prevents duplicates
    vector<string> expanded;            // holds expanded production rules
    string prev;                        // holds previous lexeme, used for syntax checks
    int curr = 0;                       // current string ptr
    bool assigned = false;              // false if an assignment-statement is needed (before EQUALS sign)
    bool once = true;                   // prevent printing assignment-statement multiple times
    bool artificial;                    // don't print production details for fake semicolons
    pair<string,string> prodRules;      // experimental

    bool isTerminal(string S) 
    {
        return  S == "*" || S == "/" || 
                S == "+" || S == "-" ||
                S == "i" || S == "#" || 
                S == "(" || S == ")";

    }
    // Expression production rules starting with E -> T E'
    string RULES[5][12] = {
    //        id      +     -      *         /       (       )       $       ;        =     num      ,
            {"Te",  "nil", "nil",  "nil",  "nil",  "Te",   "nil",  "nil",   "",    "skip",  "Te",   ""},    //     E  ->  T E'                  in the table : e = E'
            {"nil", "+Te", "-Te",  "nil",  "nil",  "nil",   "",    "",      "",    "skip",  "nil",  ""},    //     E' ->  +- T E' | epsilon     in the table : e = E' , "" = epsilon
            {"Ft",  "nil", "nil",  "nil",  "nil",  "Ft",   "nil",  "nil",   "",    "skip",  "Ft",   ""},    //     T  ->  F T'                  in the table : t = T'
            {"nil",   "",    "",   "*Ft",  "/Ft",  "nil",   "",     "",     "",    "skip",  "nil",  ""},    //     T' ->  */ F T' | epsilon     in the table : t = T' , "" = epsilon
            {"i",   "nil", "nil",  "nil",  "nil",  "(E)",  "nil",  "nil",  "nil",  "skip",  "i",    ""}     //     F  ->  ( E )   | id          in the table : i stands for id
    };

    // experimental
    int newRULES[5][10] = {
    //        id          +          -          *         /             (                   )          $          ;         =
            {Te,       INVALID,   INVALID,   INVALID,   INVALID,     Te,                 INVALID,   INVALID,   EPSILON,   NOTHNG},    // E
            {INVALID,  PLUSTe,    MINUSTe,   INVALID,   INVALID,     INVALID,            EPSILON,   EPSILON,   EPSILON,   NOTHNG},    // E’
            {Ft,       INVALID,   INVALID,   INVALID,   INVALID,     Ft,                 INVALID,   INVALID,   EPSILON,   NOTHNG},    // T
            {INVALID,  EPSILON,   EPSILON,   STARFt,    SLASHFt,     INVALID,            EPSILON,   EPSILON,   EPSILON,   NOTHNG},    // T’
            {id,       INVALID,   INVALID,   INVALID,   INVALID,     E_WITH_PARENTHESES, INVALID,   INVALID,   EPSILON,   NOTHNG}     // F
    };

    //  retrieves the appropriate production rule from RULES to be analyzed and (if applicable) pushed onto the stack
    string getTable(string X, string a)
    {
        int col, row = -1;
        //  set any alphanumeric token to follow the rules for id
        if (isalpha(a[0]))
        {
            a = "i";
        }
        else if (isdigit(a[0]))
        {
            a = "n";
        }
        //  get row of the table that corresponds to the token type
        switch (a[0]) 
        {
            case 'i' : col=0; break;
            case '+' : col=1; break;
            case '-' : col=2; break;
            case '*' : col=3; break;
            case '/' : col=4; break;
            case '(' : col=5; break;
            case ')' : col=6; break;
            case '$' : col=7; break;
            case ';' : col=8; break;
            case '=' : col=9; break;
            case '#' : col=9; break;
            case 'n' : col=10; break;
            case ',' : col=11; break;
            default  : cout << "\n[line 119/106/97 expr.cpp] SYNTAX ERROR while looking up table : "+a+" is not a valid token!\n"
                             "**Now Exiting...";
                       exit(-1); 
                       break;
        }
        //  get column of the table that corresponds to the token type
        switch (X[0]) 
        {
            case 'E' : row=0; break;
            case 'e' : row=1; break;
            case 'T' : row=2; break;
            case 't' : row=3; break;
            case 'F' : row=4; break;
        }
        return RULES[row][col];
    }
    // expand and print the production rules into their expressions (hard-coded the statements)
    string convert(string S)        // expands one production rule at a time (e.g. E -> T E')
    {
        if (S == "") {return NULL;}
        string tmp;
        //  Override for tokens belonging to statement assignment-declaration
        if (!assigned)
        {
            if (once)
            {
                tmp = "     <Statement> -> <Assign>\n     <Assign> -> <ID> = <Expression>;\n"
                      "     <Statement> -> <Declarative>\n     <Declarative> -> <Type> <ID>\n"
                      "     <Type> -> bool | float | int>\n";     // not sure about this line
                cout << tmp;
                //  prevent printing this multiple times
                once = false;
            }
            
            return "";
        }
        if (artificial && str2[0] == ';')
        {
            return "";
        }
        //  needs fixing ~ done
        //  Production Rules for all tokens belonging to Expression are printed here
        for (char c : S)
        {
            switch(c)
            {
                case 'E' :      //  expand E -> T E'
                    tmp += "    <Expression> -> <Term> <ExpressionPrime> ";
                    break;
                case 'e' :      //  ONLY print on semicolon  ::  expand E' -> ± T E' | epsilon   (false positives on Te, +Te, -Te)
                    if (str2[0] == ';')
                    {
                        tmp += "    <Empty> -> Epsilon\n    <ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Empty> ";
                    }
                    break;
                case '+' :      //  expand E' -> + T E' | epsilon
                    tmp += "    <Expression Prime> -> + <Term> <ExpressionPrime> | <Empty> ";      
                    break;
                case '-' :      //  expand E' -> - T E' | epsilon
                    tmp += "    <Expression Prime> -> - <Term> <ExpressionPrime> | <Empty> "; 
                    break;
                case 'T' :      //  expand T -> F T' | epsilon
                    tmp += "    <Term> -> <Factor> <TermPrime> ";
                    break;
                case '*' :      //  expand T' -> * F T' | epsilon
                    tmp += "    <Term Prime> -> * <Factor> <TermPrime> | <Empty> ";
                    break;
                case '/' :      //  expand T' -> / F T' | epsilon
                    tmp += "    <Term Prime> -> / <Factor> <TermPrime> | <Empty> ";
                    break;
                case 't' :      //  ONLY print on semicolon  ::  expand T' -> F T' | epsilon    (false positives on Ft, *Ft, /Ft))
                    if (str2[0] == ';')
                    {
                        tmp += "    <Empty> -> Epsilon\n    <TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty> ";
                    }
                    break;
                case 'F' :      //  ONLY print on id or (  ::  expand F -> ( E ) | id | num     (false positives on *Ft and /Ft)
                    if (str2[0] == '(' || isalnum(str2[0]))
                    {
                        tmp += "    <Factor> -> ( Expression ) | <ID> | <Num> ";
                    }
                    break;
                case 'i' :      //  print ID -> id (actual)
                    tmp += "    <ID> -> "+str2;
                    break;
                case '~' :      //  expand epsilon
                    tmp += "    <Empty> -> Epsilon ";
                    break;
                default  :
                    tmp += "    <Empty> -> Epsilon ";
                    break;
            }
        }
        // don't print empty lines
        if (tmp!= "") { cout << tmp << endl; }
        return tmp;
    }
    // gets the lexeme's name while ruling out bad syntax such as duplicate consecutive operators
    string getLex(Token tok)
    {
        string tmp, tmp2;
        string tk = tok.lexeme;
        //  consecutive Identifiers OK
        if (isalpha(tk[0]))
        {
            tmp = (KEYWORDS.find(tk) != KEYWORDS.end() ? "KEYWORD" : "IDENTIFIER");
            prev = tmp;
            tmp2 = tk;
            return tmp;
        }
        //  crashes for wrong syntax: consecutive Numbers
        if (isdigit(tk[0]))
        {
            tmp = "INTEGER";
            if (prev == tmp)
            {
                cout << "\n[line 236/217 expr.cpp] CRITICAL SYNTAX ERROR : Consecutive " << tmp << " tokens found in the sentence!\n** Now Exiting..."; exit(1);
            }
            prev = tmp;
            tmp2 = tk;
            return "INTEGER";
        }
        //  crashes for wrong syntax: consecutive Operators
        if (OPERATORS.find(tk[0]) != OPERATORS.end())
        {
            tmp = "OPERATOR";
            if (prev == tmp)
            {
                cout << "\n** [line 248/217 expr.cpp] SYNTAX ERROR : Consecutive " << tmp << " tokens found in the sentence!\n** Now Exiting..."; exit(1);
            }
            prev = tmp;
            tmp2 = tk;
            return "OPERATOR";
        }
        //  crashes for wrong syntax: consecutive Separators if not same-parentheses (with a warning for same-parentheses)
        if (SEPERATORS.find(tk[0]) != SEPERATORS.end())
        {
            tmp = "SEPARATOR";
            if (tk == ";" && prev == "OPERATOR")
            {
                cout << "\n** [line 260/217 expr.cpp] SYNTAX ERROR : " << tmp << " right before " << tk << " token!\n** Now Exiting..."; exit(1);
                exit(1);
            }
            if (tk == tmp2)
            {
                if (tk != "(" && tk != ")")
                {
                    cout << "\n** [line 267/217 expr.cpp] SYNTAX ERROR : consecutive " << tk << " tokens in the same sentence!\n** Now Exiting..."; exit(1);
                }
                cout << "\nWarning : consecutive " << tk << " tokens encountered\n";
            }
            else if (tmp2 == "(" && tk == ")")
            {
                cout << "\n** [line 273/217 expr.cpp] SYNTAX ERROR : Empty parenthetical enclosure\n** Now Exiting..."; exit(1);
            }
            prev = tmp;
            tmp2 = tk;
            return (artificial ? "NOTHING (FAKE SEMICOLON)" : "SEPARATOR");
        }
        //  crashes if a token that does not belong to any of the above groups made it to this point
        cout << tk << endl;
        cout << "\n** [line 282/217 expr.cpp] SYNTAX ERROR : Illegal or mismatched token present in the sentence!\n** Now Exiting..."; exit(1);
        return NULL;
    }

    bool interpret (vector<Token> tkns)
    {
        //token = tkns[0];
        str2 = token.lexeme;
        string sentence;
        while (!stk.empty()) { stk.pop();}
        while (!fullstack.empty()) { fullstack.pop_front();}
        //  Start of new line or statement/expression
        //  Print the contents of the sentence
        //  Print the token and lexeme about to be syntactically analyzed    
        //  Start stack with basic default elements
            //cout << "Token: " << getLex(token) << "      " << "Lexeme:    " << token.lexeme << endl;
            stk.push("$"); 
            stk.push("E");
            fullstack.push_front("E");
            for (auto tk : tkns)
            {
                sentence += tk.lexeme;
            }
        int index;                                      // only holds index of first EQUALS sign, if one exists
        //  ignore comment blocks and special characters
        if (sentence[curr] == '!' || sentence[curr] == '_')     // don't parse if these characters are found
        {
            return false;
        }
        if ((index = sentence.find('=')) == string::npos)   // if no EQUALS sign present skip statement assignment
        {
            assigned = true;
        }
        string a, X;
        //  a = current lexeme, X = top of stack
        //  Loop until error or end of sentence / bottom of stack is reached
        int k = 0;
        for(auto tkn : tkns) {
            if (tkn.lexeme == ",")
            { 
                stk.push("T");
                fullstack.push_front("T");
                continue;
            }
            token = tkn;
            str2 = token.lexeme;
            //  Print the token and lexeme about to be syntactically analyzed
            print("\nToken: ", 8);
            print(getLex(token), 20);
            print("Lexeme: ", 8);
            print(token.lexeme, 20);
            cout << endl;
            for (;;)
            {
            a = token.lexeme[0];
            X = stk.top();
            //  Special conditions for assignment statement
            if (token.lexeme == "=")
            {
                if (assigned)           
                {
                    if (auto j = count(sentence.begin(), sentence.end(), '=') > 1 )      //  logic check for bad syntax
                    {
                        cout << "Forbidden syntax: " << j << " occurences of the EQUALS sign { = } found " << "\n";
                        cout << "[line 318/286 expr.cpp] Bad Syntax Error : multiple instances of the lexeme { " << a << " } were found in the current sentence\n** Now Exiting..."; exit(-1);
                    }
                }
                //  don't assign after EQUALS sign
                assigned = true;
                once = false;
            }
            //  Check if Stack points to a valid terminal Production Element (not belonging in {E, T, e, t, F})
            if (isTerminal(X) || X == "$") 
            {
                //  Check if both the stack and current token point to an identifier
                if (a == X || (isalnum(a[0]) && X == "i")) 
                {                       
                    //  Fully expand the production rules
                    //  Empty the stack (stk) and unordered set (expansion), restore stack with default contents
                    //  Increment token pointer
                    expansion.insert(expansion.begin(), stk.top());
                    token.productionRules += stk.top();
                    expandTerms();
                    expansion.clear();                  
                    stk.pop(); 
                    curr++;
                    k++;
                    //cout << formatPRs(token);
                    if (!assigned)
                    {
                        assigned = true;
                    }
                    break;
                }   
                else
                //  Semicolon denotes end of current sentence so process the completed expansion set and clear all values for the next sentence
                //  If not a semicolon the syntax must be wrong -> crash
                {
                    if (token.lexeme == ";")
                    {
                        fullstack.push_front("&");
                        expandTerms();
                        expansion.clear();
                        cout << "\nParse Tree contents (& stands for Epsilon): \n";
                        while (!fullstack.empty())
                        {
                            string cc = fullstack.back();
                            switch (cc[0])
                            {
                                case 'e' : cc = "E'"; break;
                                case 't' : cc = "T'"; break;
                                case 'i' : cc = "id"; break;
                                //case '&' : cc = "eps"; break;
                                default : break;
                            }
                            cout << cc << " ";
                            fullstack.pop_back();
                        }
                        cout << endl;
                        while (!stk.empty()) { stk.pop();}
                        curr = 0;
                        assigned = false;
                        once = true;
                        return true;
                    }
                    cout << "\n** [line 352/331/286 expr.cpp] SYNTAX ERROR: interpreted value = false\nreason : bad token " 
                         << a << " is not compatible with stack top " << X << "\n** Now Exiting...";
                    exit(1);
                    return false;
                }
            } 
            else
            {
            //  All Non-Terminal Production Elements are processed here {E, T, e, t, F} 
                //  lookup the RULES table for shorthand production rule corresponding to current stack pointer and lexeme
                string prod = getTable(X,a);
                //  cout << "X = " << X << "  a = " << a << endl;   // Debug Line
                //  Special rules for EQUALS sign
                //  Empty both stacks and unordered set (expansion), and restore stacks with default contents
                //  Statement assignment won't be used in expression parsing
                //  Increment token pointer
                if (prod == "skip")
                {
                    while(!stk.empty())
                    {
                        stk.pop();
                    }                    
                    expansion.clear();
                    stk.push("$");
                    stk.push("E");
                    fullstack.clear();
                    fullstack.push_front("E");
                    assigned = true;
                    curr++;
                    k++;
                    //cout << formatPRs(token);
                    break;
                }
                //  Immediately process top value of stack and expansion
                //  Print expanded terms in expansion
                //  Pop top element of stack and reset expansion
                expansion.insert(expansion.begin(), stk.top());
                expandTerms();
                expansion.clear();
                stk.pop();
                //  Breakpoint for bad syntax: rule mismatch
                if (prod == "nil") 
                {
                    if (tkns[k-1].lexemeName == "IDENTIFIER" || tkns[k-1].lexemeName == "KEYWORD" )
                    {
                        prod = "i";
                    }
                    if (prod == "nil")
                    {
                        cout << "\n** [line 417/387/97/286 expr.cpp] SYNTAX ERROR - interpreted value = false\nreason : token "
                            << a << " has broken a nil production rule\n** Now Exiting...";
                        exit(-1);
                        return false;
                    }
                }                
                token.productionRules += prod;
                // Insert each letter of the production rule onto the top of the stack
                // Insert each letter of the production rule to the front of the unordered set
                for(int i = prod.length() - 1; i>=0; i--)
                {
                    stk.push(prod.substr(i,1));
                    fullstack.push_front(stk.top());
                    expansion.insert(expansion.begin(), prod.substr(i,1));
                    // Insert EPSILON if requirements are met                  
                    if ((a == "+" || a == "-" || a == "*" || a == "/") && (prod[i] == 'e' || prod[i] == 't'))
                    {
                        expansion.insert("~");      // for EPSILON use
                        fullstack.push_front("&");  // "&" is EPSILON for printing parse tree
                        token.productionRules += "&";
                    }
                }
                // Insert EPSILON if table lookup condition is met    
                if (prod == "")
                {
                    expansion.insert("~");      // for EPSILON use
                    fullstack.push_front("&");  // "&" is EPSILON for printing parse tree
                    token.productionRules += "&";
                }
                //cout << "PRODUCTION RULES" << token.productionRules << endl;
            }
            // Finished with no errors
            if (X == "$") 
            {
                cout << "Finished with no errors\n";
                return true;
            }
            }
        }

        return false;
    }
    //  Process contents of expansion (unordered set) so the Production Rules can be printed
    vector<string> expandTerms()
    {
        vector<string> tmp;
        for (string st : expansion)
        {
            tmp.push_back(convert(st));            
        }
        expanded = tmp;
        return tmp;
    }
    // Just a basic call to reduce confusion with lexer's own artificial construct
    void setArtificial (bool b)
    {
        artificial = b;
    }

    string formatPRs (Token tk)
    {
        string cc;
        for (auto c : tk.productionRules)
        {
            switch (c)
            {
                case 'e' : cc += "E'"; break;
                case 't' : cc += "T'"; break;
                case 'i' : cc += "id"; break;
                case '&' : cc += "eps"; break;
                default : break;
            }
        }
        return cc;
    }
};

