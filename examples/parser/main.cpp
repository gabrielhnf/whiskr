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
    for(Token* i = startToken; i != nullptr; i = i->next()){
        std::cout << "Token: " << i->name() << std::endl;
    }

    Parser parser(startToken);

    auto list = parser.parseStatements();
    //for(const auto& stmt : list){
    //    printAST(stmt->expr().get());
    //}
}
