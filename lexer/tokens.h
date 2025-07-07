#pragma once
#include <string>
#include "types.h"

void scanToken(Token* token);
void linkTokens(Token* token, Token* prevToken);
void freeTokens(Token* startToken);
void checkTokens(Token* token);

Token* tokenize(std::string filename);

void report(int line, std::string where, std::string message);
bool isNumber(std::string buffer);
