#include "../lexer/tokens.h"
#include <memory>
#include <stdexcept>

struct Expression {
    virtual ~Expression() = default;
};

//Operations
struct Grouping : Expression {
    std::unique_ptr<Expression> expr;
    Grouping(std::unique_ptr<Expression> e): expr(std::move(e)){
    }
};

struct Binary : Expression {
    std::unique_ptr<Expression> left;
    Token* op;
    std::unique_ptr<Expression> right;

    Binary(std::unique_ptr<Expression> l, Token* o, std::unique_ptr<Expression> r):
    left(std::move(l)), op(o), right(std::move(r)) {}
};

struct Unary : Expression {
    Token* op;
    std::unique_ptr<Expression> expr;

    Unary(Token* o, std::unique_ptr<Expression> e):
    op(o), expr(std::move(e)) {}
};

struct Literal: Expression {
    Token* var;

    Literal(Token* v): var(v) {}
};

class Parser {
    Token* currentToken;

    public:
    Parser(Token* token);
    std::unique_ptr<Expression> parse();

    private:
    std::unique_ptr<Expression> parsePrimary();

    std::unique_ptr<Expression> parseUnary();

    std::unique_ptr<Expression> parseFactor();

    std::unique_ptr<Expression> parseTerm();

    std::unique_ptr<Expression> parseComparison();

    std::unique_ptr<Expression> parseEquality();

    std::unique_ptr<Expression> parseExpression();
};
