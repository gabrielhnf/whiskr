#include <string>
#include "types.h"

class Token {
    public:
    Token(std::string m_name, int m_line){
        name = m_name;
        line = m_line;
    }

    std::string name;
    Type type;
    int subtype;
    int line;

    Token* next = NULL;
    Token* prev = NULL;
};

void scanToken(Token* token);
void linkTokens(Token* token, Token* prevToken);
void freeTokens(Token* startToken);
void checkTokens(Token* token);

Token* tokenize(std::string filename);

void report(int line, std::string where, std::string message);
