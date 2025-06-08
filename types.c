#include "types.h"

const Keyword keyword_table[] = {
    {"int", INT},
    {"float", FLOAT}
};

const unsigned int keyword_size = sizeof(keyword_table) / sizeof(Keyword);

const Operator operator_table[] = {
    {'+', SUM},
    {'-', SUB},
    {'*', MUL},
    {'/', DIV}
};

const unsigned int operator_size = sizeof(operator_table) / sizeof(Operator);
