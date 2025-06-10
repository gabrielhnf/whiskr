#include <stdio.h>
#include "tokens.h"

#define INITIAL_SIZE 10

int main(){

    Token* startToken = Tokenize("op");

    //Printing tokens
    for(Token* i = startToken; i != NULL; i = i->nextToken){
        printf("Token: %s\n", i->string);
    }
}
