#include "../../include/utils/token.h"
#include "../../include/lexer/helpers.h"
#include "../../include/parser/parser.h"
#include "../../include/visitor/visitor.h"

#include <iostream>

double visitAST(Visitor visitor, Expression* expr) {

    if (auto binary = dynamic_cast<Binary*>(expr)) {
        return visitor.visitBinary(*binary);
    }

    if (auto unary = dynamic_cast<Unary*>(expr)) {
        return visitor.visitUnary(*unary);
    }

    if (auto grouping = dynamic_cast<Grouping*>(expr)) {
        return visitor.visitGrouping(*grouping);
    }

    if (auto literal = dynamic_cast<Literal*>(expr)) {
        return visitor.visitLiteral(*literal);
    }

    std::cout << "Unknown Expression." << std::endl;
    return 0;

}

int main(){
    Token* startToken = tokenize("main.w");
    Token* currentToken = startToken;

    if (currentToken == nullptr) {
        std::cout << "No tokens returned." << std::endl;
        return -1;
    }

    std::cout << "Token list: " << std::endl;
    while(1){
        if(currentToken->next() != nullptr){
            std::cout << currentToken->name() << ", ";
            currentToken = currentToken->next();
        } else {
            std::cout << currentToken->name() << ". ";
            break;
        }
    }
    std::cout << "\n\n";

    Parser parser(startToken);
    Visitor v;

    auto expr = parser.parse();
    std::cout << "Result: " << visitAST(v, expr.get()) << std::endl;


    return 0;
}
