#include "../lexer/tokens.h"
#include <memory>
#include <stdexcept>

class Visitor;

struct Expression {
    virtual ~Expression() = default;
    virtual void accept(Visitor& v){};
};

//Operations
struct Grouping : Expression {
    std::unique_ptr<Expression> expr;
    Grouping(std::unique_ptr<Expression> e): expr(std::move(e)){
    }

    void accept(Visitor& v) override;
};

struct Binary : Expression {
    std::unique_ptr<Expression> left;
    Token* op;
    std::unique_ptr<Expression> right;

    Binary(std::unique_ptr<Expression> l, Token* o, std::unique_ptr<Expression> r):
    left(std::move(l)), op(o), right(std::move(r)){}

    void accept(Visitor& v) override;
};

struct Unary : Expression {
    Token* op;
    std::unique_ptr<Expression> expr;

    Unary(Token* o, std::unique_ptr<Expression> e):
    op(o), expr(std::move(e)){}

    void accept(Visitor& v) override;
};

struct Literal: Expression {
    Token* var;

    Literal(Token* v): var(v) {}

    void accept(Visitor& v) override;
};

class Visitor {
    public:
    void visitGrouping(Grouping& group);
    void visitBinary(Binary& binary);
    void visitUnary(Unary& unary);
    void visitLiteral(Literal& literal);
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
