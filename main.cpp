#include "lexer/tokens.h"
#include "parser/parser.h"
#include <iostream>

void printAST(const Expression* expr, int indent = 0) {
    auto padding = std::string(indent * 2, ' ');

    if (auto binary = dynamic_cast<const Binary*>(expr)) {
        std::cout << padding << "Binary " << binary->op->name << "\n";
        printAST(binary->left.get(), indent + 1);
        printAST(binary->right.get(), indent + 1);
        return;
    }

    if (auto unary = dynamic_cast<const Unary*>(expr)) {
        std::cout << padding << "Unary " << unary->op->name << "\n";
        printAST(unary->expr.get(), indent + 1);
        return;
    }

    if (auto grouping = dynamic_cast<const Grouping*>(expr)) {
        std::cout << padding << "Grouping\n";
        printAST(grouping->expr.get(), indent + 1);
        return;
    }

    if (auto literal = dynamic_cast<const Literal*>(expr)) {
        std::cout << padding << "Literal " << literal->var->name << "\n";
        return;
    }

    std::cout << padding << "Unknown Expression\n";
}

int main(){
    Token* startToken = tokenize("main.w");
    Parser parser(startToken);

    auto expr = parser.parse();
    printAST(expr.get());
}
