#pragma once

#include "../utils/token.h"
#include <algorithm>
#include <memory>

class Visitor; //Forwards declaration

struct Expression {
    virtual ~Expression() = default;
    virtual double accept(Visitor& visitor) = 0;
};

struct Binary : Expression {
    public:
    Binary(Token* op, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : m_op(op), m_left(std::move(left)), m_right(std::move(right)) {}

    const Token* op() const { return m_op; }
    const std::unique_ptr<Expression>& left() const { return m_left; }
    const std::unique_ptr<Expression>& right() const { return m_right; }

    double accept(Visitor& visitor) override;

    private:
    Token* m_op;
    std::unique_ptr<Expression> m_left;
    std::unique_ptr<Expression> m_right;
};

struct Unary : Expression {
    public:
    Unary(Token* op, std::unique_ptr<Expression> expr)
        : m_op(op), m_expr(std::move(expr)) {}

    const Token* op() const { return m_op; }
    const std::unique_ptr<Expression>& expr() const { return m_expr; }

    double accept(Visitor& visitor) override;

    private:
    Token* m_op;
    std::unique_ptr<Expression> m_expr;
};

struct Literal : Expression {
    public:
    Literal(Token* token)
        : m_token(token) {}

    const Token* token() const { return m_token; }

    double accept(Visitor& visitor) override;

    private:
    Token* m_token;
};

struct Grouping : Expression {
    public:
    Grouping(std::unique_ptr<Expression> expr)
        : m_expr(std::move(expr)) {}

    const std::unique_ptr<Expression>& expr() const { return m_expr; }

    double accept(Visitor& visitor) override;

    private:
    std::unique_ptr<Expression> m_expr;
};
