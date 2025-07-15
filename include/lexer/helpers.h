#pragma once

#include <string>
#include "../utils/token.h"

bool isDelimiter(char ch);
bool isOperator(char ch);
bool isMOperator(std::string str);
bool isNumber(std::string buffer);

void scanToken(Token* token);
void linkTokens(Token* token, Token* prevToken);
void freeTokens(Token* startToken);
void checkTokens(Token* token);

Token* tokenize(std::string filename);
