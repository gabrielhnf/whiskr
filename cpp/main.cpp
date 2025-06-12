#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

typedef enum {
    KEYWORD,
    LITERAL,
    OPERATOR,
    UNKNOWN
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
    GREATER_EQUAL, LESS_EQUAL

} Operators;

class Token {
    public:
    Token(string m_name, int m_line){
        name = m_name;
        line = m_line;
    }

    string name;
    Type type;
    int subtype;
    int line;

    Token* next = NULL;
    Token* prev = NULL;
};

unordered_map<string, Keywords> keywordMap = {
    {"and", AND}, {"or", OR}, {"true", TRUE}, {"false", FALSE},
    {"purrcedure", PURRCEDURE}, {"clawss", CLAWSS}, {"supurr", SUPURR}, {"thiss", THISS},
    {"fur", FUR}, {"sniff", SNIFF}, {"mewlse", MEWLSE}, {"backpaw", BACKPAW}, {"while", WHILE},
    {"furget", FURGET}, {"meow", MEOW}, {"paw", PAW}, {"nap", NAP}
};

unordered_map<string, Operators> operatorMap = {
    {"(", OPEN_PAREN}, {")", CLOSED_PAREN}, {"{", OPEN_CURLY}, {"}", CLOSED_CURLY},
    {",", COMMA}, {".", DOT}, {"-", MINUS}, {"+", PLUS}, {";", SEMICOLON}, {"/", SLASH}, {"*", STAR},

    {"=", EQUAL}, {"!", NOT},
    {">", GREATER}, {"<", LESS},
    {"==", EQUAL_EQUAL}, {"!=", NOT_EQUAL},
    {">=", GREATER_EQUAL}, {"<=", LESS_EQUAL}
};

void ScanToken(Token* token){
    if(auto search = keywordMap.find(token->name); search != keywordMap.end()){
        token->type = KEYWORD;
        token->subtype = search->second;
    } else if (auto search = operatorMap.find(token->name); search != operatorMap.end()) {
        token->type = OPERATOR;
        token->subtype = search->second;
    } else {
        token->type = LITERAL;
        token->subtype = 0;
    }
}

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

void report(int line, string where, string message){
    cout << "Error at line " << line << ", in '" << where << "'." << endl;
    cout << message << endl;
    exit(-1);
}

void checkTokens(Token* token){
    for(Token* i = token; i != nullptr; i = i->next){
        //Rules for operators
        if(i->type == OPERATOR){
            if(i->next != nullptr){
                if(i->next->type != LITERAL){
                    report(i->line, i->name, "Invalid syntax. 1");
                }

                if(i->next->line != i->line){
                    report(i->line, i->name, "Invalid syntax. 2");
                }
            } else {
                report(i->line, i->name, "Invalid syntax. 3");
            }
            if(i->prev == nullptr){
                report(i->line, i->name, "Invalid syntax. 4");
            }
        }

        //Rules for literals
        if(i->type == LITERAL){
            if(i->next != nullptr){
                if(i->next->line == i->line){
                    if(i->next->type != OPERATOR && i->next->type != KEYWORD){
                        report(i->line, i->name, "Invalid syntax. 5");
                    }
                }
            }
        }

        //Rules for keywords
        if(i->type == KEYWORD){
            if(i->next != nullptr){
                if(i->next->line == i->line){
                    if(i->next->type != LITERAL){
                        report(i->line, i->name, "Expected expression. 6");
                    }
                } else{
                    report(i->line, i->name, "Expected expression. 7");
                }
            } else {
                report(i->line, i->name, "Expected expression. 8");
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
            Token* token = new Token("", line);
            if(prevToken == nullptr) startToken = token;

            if(buffer.length()) {
                //Token* token = new Token(buffer, line);
                token->name = buffer;
                //ScanToken(token);

                //if(prevToken == nullptr) startToken = token;
                //LinkTokens(token, prevToken);
                //prevToken = token;

                buffer = "";
            }

            if(isOperator(ch)){
                //Token* token = new Token("", line);
                //if(prevToken == nullptr) startToken = token;

                string temp = {ch, (char)fd.peek()};

                if(isMultiCharOp(temp)){
                    fd.get(ch); //Consume to not lose order
                    token->name = temp;

                } else {
                    token->name = ch;
                }

                if(temp == "//"){
                    token->name = "";
                    while(fd.get() != '\n'){
                        continue; //Consume until next line
                    }
                }

                //ScanToken(token);
                //LinkTokens(token, prevToken);
                //prevToken = token;
            }

            if(!token->name.length()) free(token);
            else{
                ScanToken(token);
                LinkTokens(token, prevToken);
                prevToken = token;
            }

            if(ch == '\n' || ch == ';') line++;

        }

    }

    fd.close();

    for(Token* i = startToken; i != nullptr; i = i->next){
        cout << "Token: " << i->name << endl;

    }

    checkTokens(startToken);

    return 0;
}
