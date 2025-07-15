#include "../../include/lexer/helpers.h"
#include "../../include/utils/types.h"
#include "../../include/utils/token.h"

#include <stdexcept>
#include <string>
#include <fstream>
#include <unordered_map>
#include <iostream>

extern std::unordered_map<std::string, Keywords> keywordMap;
extern std::unordered_map<std::string, Operators> operatorMap;
extern std::unordered_map<std::string, Operators> mOperatorMap;

void scanToken(Token* token){
    if(auto search = keywordMap.find(token->name()); search != keywordMap.end()){
        token->type(KEYWORD);
        token->subtype(search->second);
    } else if (auto search = operatorMap.find(token->name()); search != operatorMap.end()) {
        token->type(OPERATOR);
        token->subtype(search->second);
    } else {
        token->type(LITERAL);
        if(isNumber(token->name())) token->subtype(NUMBER);
        else if(token->name()[0] == '"') token->subtype(STRING);
        else token->subtype(IDENTIFIER);
    }
}

void linkTokens(Token* token, Token* prevToken){
    if(prevToken != nullptr){
        prevToken->next(token);
    }
}

void freeTokens(Token* startToken){
    for(Token* i = startToken; i != nullptr; i = i->next()){
        free(i);
    }
}

void checkTokens(Token* token){
}

Token* deployToken(std::string name, Token** startToken, Token* prevToken){
    Token* token = new Token(name);
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
    while(fd.get(ch)){
        if(!isDelimiter(ch) && !isOperator(ch)){
            buffer.append(1, ch);
        } else {

            if(buffer.length()) {
                prevToken = deployToken(buffer, &startToken, prevToken);
                buffer = "";
            }

            if(ch == ';'){
                prevToken = deployToken(std::string(1, ch), &startToken, prevToken);
                continue;
            }

            if(isOperator(ch)){
                if(ch == '"'){
                    buffer.append(1, ch);
                    bool stringOpened = true;
                    while(fd.get(ch)){
                        buffer.append(1, ch);
                        if(ch == '"'){
                            stringOpened = false;
                            fd.get(); //Advance
                            break;
                        }


                    }
                    prevToken = deployToken(buffer, &startToken, prevToken);
                    buffer = "";
                    continue;
                }

                std::string temp = {ch, (char)fd.peek()}; //Lookahead 1 char

                if(temp == "//"){
                    while(fd.get() != '\n'){
                        continue; //Consume until next line
                    }
                    continue;
                }

                if(isMOperator(temp)){
                    fd.get(ch); //Consume to not lose order
                    prevToken = deployToken(temp, &startToken, prevToken);

                } else {
                    prevToken = deployToken(std::string(1, ch), &startToken, prevToken);
                }
            }
        }
    }
    fd.close();
    return startToken;
}

bool isNumber(std::string buffer){
    try {
        std::string::size_type sz;
        int a = std::stoi(buffer, &sz);
        return sz == buffer.length();

    } catch (std::invalid_argument) {
        return false;
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
    return operatorMap.find(std::string(1, ch)) != operatorMap.end();
}

bool isMOperator(std::string str){
    return operatorMap.find(str) != operatorMap.end();
}
