#pragma once

#include "../utils/token.h"
#include "expression.h"
#include "statement.h"
#include <list>
#include <memory>
#include <stdexcept>

class Parser {

    public:
    Token* currentToken;
    Parser(Token* token);
    std::unique_ptr<Expression> parse();

    std::list<std::unique_ptr<Statement>> statementList;
    std::list<std::unique_ptr<Statement>> parseStatements();

    private:
    std::unique_ptr<Expression> parsePrimary();

    std::unique_ptr<Expression> parseUnary();

    std::unique_ptr<Expression> parseFactor();

    std::unique_ptr<Expression> parseTerm();

    std::unique_ptr<Expression> parseComparison();

    std::unique_ptr<Expression> parseEquality();

    std::unique_ptr<Expression> parseExpression();
};
