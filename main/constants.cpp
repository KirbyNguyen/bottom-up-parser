#include "lexer.cpp"

enum COLUMN
{
    ID,
    PLUS,
    MINUS,
    TIME,
    DIVIDE,
    LEFT_PAR,
    RIGHT_PAR,
    MONEY,
    E_STATE,
    T_STATE,
    F_STATE,
    COL_ERROR,
};

COLUMN tokenParser(Token token) {
    switch(token.lexemeNum) {
        case IDENTIFIER:
            return ID;
        break;
        case SEPERATOR:
            if (token.lexeme == "(") return LEFT_PAR;
            if (token.lexeme == ")") return RIGHT_PAR;
            if (token.lexeme == "$") return MONEY;
            return COL_ERROR;
        break;
        case OPERATOR:
            if (token.lexeme == "+") return PLUS;
            if (token.lexeme == "-") return MINUS;
            if (token.lexeme == "*") return TIME;
            if (token.lexeme == "/") return DIVIDE;
            return COL_ERROR;
        break;
        default:
        return COL_ERROR;
    }
}

enum STATE
{
    EMPTY,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    R8,
    S4,
    S5,
    S6,
    S7,
    S8,
    S9,
    S15,
    N1,
    N2,
    N3,
    N10,
    N11,
    N12,
    N13,
    N14,
    ACCT,
    STATE_ERROR
};

int grammarStateTable[16][11] = {
    {S5,    EMPTY,  EMPTY,  EMPTY,  EMPTY,  S4,     EMPTY,  EMPTY,  N1,     N2,     N3},
    {EMPTY, S6,     S7,     EMPTY,  EMPTY,  EMPTY,  EMPTY,  ACCT,   EMPTY,  EMPTY,  EMPTY},
    {EMPTY, R3,     R3,     S8,     S9,     EMPTY,  R3,     R3,     EMPTY,  EMPTY,  EMPTY},
    {EMPTY, R6,     R6,     R6,     R6,     EMPTY,  R6,     R6,     EMPTY,  EMPTY,  EMPTY},
    {S5,    EMPTY,  EMPTY,  EMPTY,  EMPTY,  S4,     EMPTY,  EMPTY,  N10,    N2,     N3},
    {EMPTY, R8,     R8,     R8,     R8,     EMPTY,  R8,     R8,     EMPTY,  EMPTY,  EMPTY},
    {S5,    EMPTY,  EMPTY,  EMPTY,  EMPTY,  S4,     EMPTY,  EMPTY,  EMPTY,  N11,    N3},
    {S5,    EMPTY,  EMPTY,  EMPTY,  EMPTY,  S4,     EMPTY,  EMPTY,  EMPTY,  N12,    N3},
    {S5,    EMPTY,  EMPTY,  EMPTY,  EMPTY,  S4,     EMPTY,  EMPTY,  EMPTY,  EMPTY,  N13},
    {S5,    EMPTY,  EMPTY,  EMPTY,  EMPTY,  S4,     EMPTY,  EMPTY,  EMPTY,  EMPTY,  N14},
    {EMPTY, S6,     S7,     EMPTY,  EMPTY,  EMPTY,  S15,    EMPTY,  EMPTY,  EMPTY,  EMPTY},
    {EMPTY, R1,     R1,     S8,     S9,     EMPTY,  R1,     R1,     EMPTY,  EMPTY,  EMPTY},
    {EMPTY, R2,     R2,     S8,     S9,     EMPTY,  R2,     R2,     EMPTY,  EMPTY,  EMPTY},
    {EMPTY, R4,     R4,     R4,     R4,     EMPTY,  R4,     R4,     EMPTY,  EMPTY,  EMPTY},
    {EMPTY, R5,     R5,     R5,     R5,     EMPTY,  R5,     R5,     EMPTY,  EMPTY,  EMPTY},
    {EMPTY, R7,     R7,     R7,     R7,     EMPTY,  R7,     R7,     EMPTY,  EMPTY,  EMPTY},
};