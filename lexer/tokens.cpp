#include "tokens.h"
#include <stdexcept>
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
        //Detect if number, string or identifier
        token->type = LITERAL;
        if(isNumber(token->name)) token->subtype = NUMBER;
        else if(token->name[0] == '"') token->subtype = STRING;
        else token->subtype = IDENTIFIER;
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
}

void report(int line, int charCount, std::string message){
    std::cout << "Error: LN " << line <<"; COL " << charCount << std::endl;
    //TODO: Print couple of chars surrounding it
    std::cout << message << std::endl;
}

Token* deployToken(std::string name, int line, Token** startToken, Token* prevToken){
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
    int charCount = 0;
    while(fd.get(ch)){
        charCount++;
        if(!isDelimiter(ch) && !isOperator(ch)){
            buffer.append(1, ch);
        } else {

            if(buffer.length()) {
                prevToken = deployToken(buffer, line, &startToken, prevToken);
                buffer = "";
            }

            if(ch == ';'){
                prevToken = deployToken(std::string(1, ch), line, &startToken, prevToken);
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
                    prevToken = deployToken(buffer, line, &startToken, prevToken);
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
                    prevToken = deployToken(temp, line, &startToken, prevToken);

                } else {
                    prevToken = deployToken(std::string(1, ch), line, &startToken, prevToken);
                }
            }

            if(ch == '\n'){
                line++;
                charCount = 0;
            };
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
