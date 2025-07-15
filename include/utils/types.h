#pragma once

typedef enum {
    UNKNOWN,
    KEYWORD,
    LITERAL,
    OPERATOR
} Type;

typedef enum {
    //Booleans
    AND, OR, TRUE, FALSE,
    //Functions and classes
    PURRCEDURE, CLAWSS, SUPURR, THISS,
    //Control flow
    FUR, SNIFF, MEWLSE, BACKPAW, WHILE,
    //NULL
    FURGET, //Maybe will use as break;
    //Print
    MEOW,
    //Variable declaration
    PAW,
    //EOF
    NAP
} Keywords;

typedef enum {
    NUMBER, STRING, IDENTIFIER
} Literals;

typedef enum {
    OPEN_PAREN, CLOSED_PAREN, OPEN_CURLY, CLOSED_CURLY,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
    EQUAL, NOT,
    GREATER, LESS,
    EQUAL_EQUAL, NOT_EQUAL,
    GREATER_EQUAL, LESS_EQUAL,
    QUOTES, DOUBLE_QUOTES
} Operators;
