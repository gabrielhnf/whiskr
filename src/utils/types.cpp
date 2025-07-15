#include <string>
#include <unordered_map>
#include "../../include/utils/types.h"


std::unordered_map<std::string, Keywords> keywordMap = {
    {"and", AND}, {"or", OR}, {"true", TRUE}, {"false", FALSE},
    {"purrcedure", PURRCEDURE}, {"clawss", CLAWSS}, {"supurr", SUPURR}, {"thiss", THISS},
    {"fur", FUR}, {"sniff", SNIFF}, {"mewlse", MEWLSE}, {"backpaw", BACKPAW}, {"while", WHILE},
    {"furget", FURGET}, {"meow", MEOW}, {"paw", PAW}, {"nap", NAP}
};

std::unordered_map<std::string, Operators> operatorMap = {
    {"(", OPEN_PAREN}, {")", CLOSED_PAREN}, {"{", OPEN_CURLY}, {"}", CLOSED_CURLY},
    {",", COMMA}, {".", DOT}, {"-", MINUS}, {"+", PLUS}, {"/", SLASH}, {"*", STAR},
    {"=", EQUAL}, {"!", NOT},
    {">", GREATER}, {"<", LESS},
    {"==", EQUAL_EQUAL}, {"!=", NOT_EQUAL},
    {">=", GREATER_EQUAL}, {"<=", LESS_EQUAL},
    {"'", QUOTES}, {std::string(1, '"'), DOUBLE_QUOTES},
    {";", SEMICOLON}
};
