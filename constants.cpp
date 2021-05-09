#include "lexer.cpp"

enum COLUMN
{
    ID,
    NUM,
    PLUS,
    MINUS,
    TIME,
    DIVIDE,
    EQUAL,
    LESS,
    MORE,
    LEFT_PAR,
    RIGHT_PAR,
    WHILE,
    WHILE_END,
    IF,
    IF_END,
    KEYWORD,
    MONEY,
    W_STATE,
    I_STATE,
    S_STATE,
    C_STATE,
    CO_STATE,
    A_STATE,
    D_STATE,
    TY_STATE,
    E_STATE,
    T_STATE,
    F_STATE,
    COL_ERROR
};

COLUMN parseToken(Token token) {
    switch(token.lexemeNum) {
        case IDENTIFIER:
            return ID;
        break;
        case SEPERATOR:
            if (token.lexeme == "(") return LEFT_PAR;
            if (token.lexeme == ")") return RIGHT_PAR;
            return COL_ERROR;
        break;
        case OPERATOR:
            if (token.lexeme == "+") return PLUS;
            if (token.lexeme == "-") return MINUS;
            if (token.lexeme == "*") return TIME;
            if (token.lexeme == "/") return DIVIDE;
            if (token.lexeme == "=") return EQUAL;
            if (token.lexeme == "<") return LESS;
            if (token.lexeme == ">") return MORE;
            return COL_ERROR;
        break;
        case KEYWORD:
            if (token.lexeme == "while") return WHILE;
            if (token.lexeme == "whileend") return WHILE_END;
            if (token.lexeme == "if") return IF;
            if (token.lexeme == "ifend") return IF_END;
            return COL_ERROR;
        break;
        case INTEGER:
        case REAL:
            return NUM;
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
    STATE_ERROR
};