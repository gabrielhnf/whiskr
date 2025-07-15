#pragma once

#include "expression.h"
#include <memory>

struct Statement {
    virtual ~Statement() = default;
};

struct ExpressionStatement : Statement {
    public:
    ExpressionStatement(std::unique_ptr<Expression> expr)
        : m_expr(std::move(expr)) {}

    const std::unique_ptr<Expression> expr() { return std::move(m_expr); }

    private:
    std::unique_ptr<Expression> m_expr;
};
