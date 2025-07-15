#include "../../include/utils/token.h"
#include "../../include/lexer/helpers.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    if(argc != 2){
        cout << "Usage: " << argv[0] << " path/to/file.w" << endl;
        return -1;
    }

    Token* startToken = tokenize(argv[1]);
    if(startToken == nullptr){
        cout << "ERROR: Could not tokenize file " << argv[1] << endl;
        return -1;
    }

    for(Token* i = startToken; i != nullptr; i = i->next()){
        cout << "Token: " << i->name() << endl;
        cout << "Token type: " << i->type() << endl;
        cout << "Token subtype: " << i->subtype() << endl;
        cout << "--------------------------" << endl;

    }

    checkTokens(startToken);

    return 0;
}
