#include "types.h"

const Keyword keyword_table[] = {
    {"int", INT},
    {"float", FLOAT}
};

const unsigned int keyword_size = sizeof(keyword_table) / sizeof(Keyword);

const Operator operator_table[] = {
    {'+', SUM}, {'-', SUB},
    {'*', MUL}, {'/', DIV},

    {'!', NOT}, {'=', EQUAL},
    {'>', GREATER}, {'<', LESS},
};

const unsigned int operator_size = sizeof(operator_table) / sizeof(Operator);

const Delimiter delimiter_table[] = {
    {'(', OPEN_PAREN},
    {')', CLOSED_PAREN},
    {'{', OPEN_CBRACK},
    {'}', CLOSED_CBRACK},
    {',', COMMA},
    {'.', DOT},
    {';', SEMICOLON}
};

const unsigned int delimiter_size = sizeof(delimiter_table) / sizeof(Delimiter);
