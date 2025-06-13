#include <string>
#include <unordered_map>
#include "types.h"


std::unordered_map<std::string, Keywords> keywordMap = {
    {"and", AND}, {"or", OR}, {"true", TRUE}, {"false", FALSE},
    {"purrcedure", PURRCEDURE}, {"clawss", CLAWSS}, {"supurr", SUPURR}, {"thiss", THISS},
    {"fur", FUR}, {"sniff", SNIFF}, {"mewlse", MEWLSE}, {"backpaw", BACKPAW}, {"while", WHILE},
    {"furget", FURGET}, {"meow", MEOW}, {"paw", PAW}, {"nap", NAP}
};

std::unordered_map<std::string, Operators> operatorMap = {
    {"(", OPEN_PAREN}, {")", CLOSED_PAREN}, {"{", OPEN_CURLY}, {"}", CLOSED_CURLY},
    {",", COMMA}, {".", DOT}, {"-", MINUS}, {"+", PLUS}, /*{";", SEMICOLON},*/ {"/", SLASH}, {"*", STAR},
    {"=", EQUAL}, {"!", NOT},
    {">", GREATER}, {"<", LESS},
    {"==", EQUAL_EQUAL}, {"!=", NOT_EQUAL},
    {">=", GREATER_EQUAL}, {"<=", LESS_EQUAL}
};

bool isDelimiter(char ch){
    switch (ch) {
        case ' ':
            return 1;
        case '\n':
            return 1;
        case ';':
            return 1;
        default:
            return 0;
    }
}

bool isOperator(char ch){
    return operatorMap.find(std::string(1, ch)) != operatorMap.end();
}

bool isMOperator(std::string str){
    return operatorMap.find(str) != operatorMap.end();
}
