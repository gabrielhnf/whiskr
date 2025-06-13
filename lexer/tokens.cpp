#include "tokens.h"
#include <string>
#include <fstream>
#include <unordered_map>
#include <iostream>

extern std::unordered_map<std::string, Keywords> keywordMap;
extern std::unordered_map<std::string, Operators> operatorMap;
extern std::unordered_map<std::string, Operators> mOperatorMap;

void scanToken(Token* token){
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

void linkTokens(Token* token, Token* prevToken){
    if(prevToken != nullptr){
        prevToken->next = token;
        token->prev = prevToken;
    }
}

void freeTokens(Token* startToken){
    for(Token* i = startToken; i != nullptr; i = i->next){
        free(i);
    }
}

void checkTokens(Token* token){
    for(Token* i = token; i != nullptr; i = i->next){
        //Rules for operators
        if(i->type == OPERATOR){
            if(i->next != nullptr){
                if(i->next->type != LITERAL){
                    report(i->line, i->name, "Invalid syntax. ERROR: 1");
                }

                if(i->next->line != i->line){
                    report(i->line, i->name, "Invalid syntax. ERROR: 2");
                }
            } else {
                report(i->line, i->name, "Invalid syntax. ERROR: 3");
            }
            if(i->prev == nullptr){
                report(i->line, i->name, "Invalid syntax. ERROR: 4");
            }
        }

        //Rules for literals
        if(i->type == LITERAL){
            if(i->next != nullptr){
                if(i->next->line == i->line){
                    if(i->next->type != OPERATOR && i->next->type != KEYWORD){
                        report(i->line, i->name, "Invalid syntax. ERROR: 5");
                    }
                }
            }
        }

        //Rules for keywords
        if(i->type == KEYWORD){
            if(i->next != nullptr){
                if(i->next->line == i->line){
                    if(i->next->type != LITERAL){
                        report(i->line, i->name, "Expected expression. ERROR: 6");
                    }
                } else{
                    report(i->line, i->name, "Expected expression. ERROR: 7");
                }
            } else {
                report(i->line, i->name, "Expected expression. ERROR: 8");
            }
        }
    }
}

void report(int line, std::string where, std::string message){
    std::cout << "Error at line " << line << ", in '" << where << "'." << std::endl;
    std::cout << message << std::endl;
    exit(-1);
}

Token* createAndSendToken(std::string name, int line, Token** startToken, Token* prevToken){
    Token* token = new Token(name, line);
    scanToken(token);
    linkTokens(token, prevToken);

    if(prevToken == nullptr) *startToken = token;

    return token;
}

Token* tokenize(std::string filename){

    std::ifstream fd;
    fd.open(filename);
    if(fd.fail()){
        std::cout << "Could not open file." << std::endl;
        return nullptr;
    }

    std::string buffer = "";

    Token* startToken = nullptr;
    Token* prevToken = nullptr;

    char ch;
    int line = 1;
    while(fd.get(ch)){
        if(!isDelimiter(ch) && !isOperator(ch)){
            buffer.append(1, ch);
        } else {

            if(buffer.length()) {
                prevToken = createAndSendToken(buffer, line, &startToken, prevToken);
                buffer = "";
            }

            if(isOperator(ch)){
                std::string temp = {ch, (char)fd.peek()};

                if(temp == "//"){
                    while(fd.get() != '\n'){
                        continue; //Consume until next line
                    }
                    continue;
                }

                if(isMOperator(temp)){
                    fd.get(ch); //Consume to not lose order
                    prevToken = createAndSendToken(temp, line, &startToken, prevToken);

                } else {
                    prevToken = createAndSendToken(std::string(1, ch), line, &startToken, prevToken);
                }
            }

            if(ch == '\n' || ch == ';') line++;
        }
    }
    fd.close();

    return startToken;
}
