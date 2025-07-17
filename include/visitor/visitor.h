#pragma once

#include "../../include/parser/expression.h"

class Visitor {
    public:
    Visitor() = default;

    double visit(Expression& expr);
    double visitLiteral(Literal& literal);
    double visitGrouping(Grouping& grouping);
    double visitUnary(Unary& unary);
    double visitBinary(Binary& binary);
};
