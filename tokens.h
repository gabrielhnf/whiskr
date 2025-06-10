#include "types.h"

Token* CreateToken(char* str);

void AnalyzeToken(Token* token);

Token* LinkTokens(Token* token, Token* prevToken);

Token* Tokenize(char* filename);
