#include "../../include/visitor/visitor.h"
#include <string>

double Visitor::visit(Expression& expr){
    return expr.accept(*this);
}

double Visitor::visitLiteral(Literal& literal){
    return std::stod(literal.token()->name());
}

double Visitor::visitGrouping(Grouping& grouping){
    return visit(*grouping.expr());
}

double Visitor::visitUnary(Unary& unary){
    double value = visit(*unary.expr());

    return unary.op()->subtype() == MINUS ? -value : value;
}

double Visitor::visitBinary(Binary& binary){
    double left = visit(*binary.left());
    double right = visit(*binary.right());
    int type = binary.op()->subtype();

    //Make switch-case
    if(type == PLUS) return (double)(left + right);
    else if(type == MINUS) return (double)(left - right);
    else if(type == STAR) return (double)(left * right);
    else if(type == SLASH) return (double)(left/right);
    //TODO: Implement boolean comparison
    else return 0;

}
