#include "../../include/parser/expression.h"
#include "../../include/parser/parser.h"
#include "../../include/lexer/helpers.h"

#include <iostream>
#include <memory>

void printAST(const Expression* expr, int indent = 0) {
    auto padding = std::string(indent * 2, ' ');

    if (auto binary = dynamic_cast<const Binary*>(expr)) {
        std::cout << padding << "Binary " << binary->op() << "\n";
        printAST(binary->left().get(), indent + 1);
        printAST(binary->right().get(), indent + 1);
        return;
    }

    if (auto unary = dynamic_cast<const Unary*>(expr)) {
        std::cout << padding << "Unary " << unary->op()->name() << "\n";
        printAST(unary->expr().get(), indent + 1);
        return;
    }

    if (auto grouping = dynamic_cast<const Grouping*>(expr)) {
        std::cout << padding << "Grouping\n";
        printAST(grouping->expr().get(), indent + 1);
        return;
    }

    if (auto literal = dynamic_cast<const Literal*>(expr)) {
        std::cout << padding << "Literal " << literal->token()->name() << "\n";
        return;
    }

    std::cout << padding << "Unknown Expression\n";
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

    auto list = parser.parseStatements();
    std::cout << "Statement list size: \n" << list.size() << "\n\n";
    //for(const auto& stmt : list){
    //    printAST(stmt->expr().get());
    //}
}
