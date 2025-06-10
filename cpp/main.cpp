#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

typedef enum {
    KEYWORD,
    LITERAL, //Both numbers and identifiers for now
    OPERATOR,
    UNKNOWN
} Type;

class Token {
    public:
    Token(string m_name, Type m_type, int m_line){
        name = m_name;
        type = m_type;
        line = m_line;
    }

    string name;
    Type type;
    int line;

    Token* next = NULL;
    Token* prev = NULL;
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
    switch (ch) {
        case '(':
            return 1;
        case ')':
            return 1;
        case '{':
            return 1;
        case '}':
            return 1;
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 1;
        case '/':
            return 1;
        case '!':
            return 1;
        case '=':
            return 1;
        case '>':
            return 1;
        case '<':
            return 1;
        default:
            return 0;
    }
}

bool isMultiCharOp(string str){
    if(str == "==") return true;
    if(str == "!=") return true;
    if(str == ">=") return true;
    if(str == "<=") return true;

    return false;
}

void LinkTokens(Token* token, Token* prevToken){
    if(prevToken != nullptr){
        prevToken->next = token;
        token->prev = prevToken;
    }
}

void FreeTokens(Token* startToken){
    for(Token* i = startToken; i != nullptr; i = i->next){
        free(i);
    }
}

void report(int line, string message){
    cout << "Error at line " << line << "." << endl;
    cout << message << endl;
    exit(-1);
}

void checkTokens(Token* token){
    for(Token* i = token; i != nullptr; i = i->next){
        if(i->type == OPERATOR){
            if(i->prev->type != LITERAL || i->next->type != LITERAL){
                report(i->line, "Invalid syntax.");
            }
            if(i->prev->line != i->line || i->next->line != i->line){
                report(i->line, "Invalid syntax.");
            }
        }
    }
}


int main(){
    ifstream fd;
    fd.open("op");

    string buffer = "";

    Token* startToken = nullptr;
    Token* prevToken = nullptr;

    char ch;
    int line = 1;
    while(fd.get(ch)){
        if(!isDelimiter(ch) && !isOperator(ch)){
            buffer.append(1, ch);
        } else {

            if(buffer.length()) {
                Token* token = new Token(buffer, LITERAL, line);

                if(prevToken == nullptr) startToken = token;
                LinkTokens(token, prevToken);
                prevToken = token;

                buffer = "";
            }

            if(isOperator(ch)){

                Token* token = new Token("", OPERATOR, line);

                string temp = {ch, (char)fd.peek()};

                if(isMultiCharOp(temp)){
                    fd.get(ch); //Consume to not lose order
                    token->name = temp;

                } else {
                    token->name = ch;
                }

                LinkTokens(token, prevToken);
                prevToken = token;
            }

            if(ch == '\n' || ch == ';') line++;

        }

    }

    fd.close();

    for(Token* i = startToken; i != nullptr; i = i->next){
        cout << "Token: " << i->name << endl;
        cout << "Line: " << i->line << endl;
        cout << endl;

    }

    checkTokens(startToken);

    return 0;
}
