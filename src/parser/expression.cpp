#include "../../include/parser/expression.h"
#include "../../include/visitor/visitor.h"

double Literal::accept(Visitor& visitor){
    return visitor.visitLiteral(*this);
}

double Grouping::accept(Visitor& visitor){
    return visitor.visitGrouping(*this);
}

double Unary::accept(Visitor& visitor){
    return visitor.visitUnary(*this);
}

double Binary::accept(Visitor& visitor){
    return visitor.visitBinary(*this);
}
