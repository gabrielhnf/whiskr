#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokens.h"

#define INITIAL_SIZE 10

static char* multicharOperators[] = { "==", "!=", ">=", "<=" };

Token* CreateToken(char* str){
    Token* token = malloc(sizeof(Token));

    token->nextToken = NULL;
    token->prevToken = NULL;
    token->string = str;

    return token;
}

void AnalyzeToken(Token* token){
    if(token == NULL) return;

    //If is operator
    if(strlen(token->string) == 1){
        switch (token->string[0]) {
            case '+':
                token->type = OPERATOR;
                token->value.op = operator_table[0];
                break;
            case '-':
                token->type = OPERATOR;
                token->value.op = operator_table[1];
                break;
            case '*':
                token->type = OPERATOR;
                token->value.op = operator_table[2];
                break;
            case '/':
                token->type = OPERATOR;
                token->value.op = operator_table[3];
                break;
            default:
                break;
        }
    }

    //If is literal
    if(token->string[0] >= '0' && token->string[0] <= '9'){
        token->type = LITERAL;
        for(int i = 0; i < strlen(token->string); i++){
            //reminder: handle if not number (in case of, say, a "3d100" token)
            token->value.literal += (token->string[i] - '0')*(pow(10, (strlen(token->string) - (i + 1))));
        }

        return;
    }

    //If is keyword
    for(int i = 0; i < keyword_size; i++){
        if(!strcmp(token->string, keyword_table[i].kw_name)){
            token->type = KEYWORD;
            token->value.keyword = keyword_table[i];

            return;
        }
    }

    token->type = IDENTIFIER;
    return;
}

Token* LinkTokens(Token* token, Token* prevToken){
    Token* startToken = NULL;

    if(prevToken != NULL){
        token->prevToken = prevToken;
        prevToken->nextToken = token;
    }

    for(Token* i = token; i != NULL; i = i->prevToken){
        startToken = i;
    }

    return startToken;
}

static int isDelimiter(char ch){
    switch (ch) {
        case ' ':
            return 2; //Return 2 if should not be treated as a separate token
        case '\n':
            return 2;
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
        case ';':
            return 1;
        default:
            return 0;
    }
}

static char peek(char* buffer, int index){
    return buffer[index + 1];
}

Token* Tokenize(char* filename){
    FILE* fd = fopen(filename, "r");
    char ch;
    char* buf = malloc(INITIAL_SIZE);
    unsigned int currentSize = INITIAL_SIZE;

    unsigned int counter = 0;
    unsigned int line = 1;

    Token* prevToken = NULL;
    Token* startToken = NULL;

    while((ch = getc(fd)) != EOF){

        if(counter >= currentSize){
            currentSize *= 2;
            char* temp = realloc(buf, currentSize);
            if(temp != NULL) buf = temp;
            else {
                free(buf);
                temp = NULL;
                buf = NULL;
            }
        }

        int delimiter = isDelimiter(ch);

        if(ch == '\n') line++; //Fuck macOS

        if(!delimiter){
            //Keep reading
            buf[counter] = ch;
            buf[counter + 1] = '\0';
            counter += 1;
        } else {
            if(strlen(buf)){
                //Assign token to string
                Token* token = CreateToken(strdup(buf));
                AnalyzeToken(token);
                startToken = LinkTokens(token, prevToken);

                prevToken = token;
            }

            if(delimiter == 1){

                char* tempStr = malloc(3);
                tempStr[0] = ch;

                for(int i = 0; i < 4; i++){ //Hardcoded, and very ugly
                    if(ch == multicharOperators[i][0] && peek(buf, counter) == multicharOperators[i][1]){
                        tempStr[1] = '=';
                        tempStr[2] = '\0';
                    } else {
                        tempStr[1] = '\0';
                    }

                }
                //Assign token to delimiter

                Token* delimToken = CreateToken(strdup(tempStr));
                AnalyzeToken(delimToken);
                startToken = LinkTokens(delimToken, prevToken);

                prevToken = delimToken;

                free(tempStr);
                tempStr = NULL;
            }

            //Reset buffer;
            counter = 0;
            memset(buf, '\0', currentSize);

        }

    }

    return startToken;
}
