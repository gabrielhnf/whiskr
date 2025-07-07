#include "parser.h"
#include <memory>

Parser::Parser(Token* token): currentToken(token){}

std::unique_ptr<Expression> Parser::parse(){
    return parseExpression();
}

std::unique_ptr<Expression> Parser::parsePrimary(){
    if(currentToken->type == OPERATOR && currentToken->subtype == OPEN_PAREN){

        currentToken = currentToken->next;
        std::unique_ptr<Expression> expr = parseExpression();

        if(currentToken->type != OPERATOR || currentToken->subtype != CLOSED_PAREN){
            throw std::runtime_error("')' Expected.");
        }

        if(currentToken->next != nullptr) currentToken = currentToken->next;
        return std::make_unique<Grouping>(Grouping(std::move(expr)));
    }

    if(currentToken->type == LITERAL) {
        Visitor v;
        auto literal = std::make_unique<Literal>(Literal(currentToken));
        literal->accept(v);
        if(currentToken->next != nullptr) currentToken = currentToken->next;
        return literal;
    }

    throw std::runtime_error("Expected expression.");
}

std::unique_ptr<Expression> Parser::parseUnary(){
    if(currentToken->type == OPERATOR && (currentToken->subtype == NOT || currentToken->subtype == MINUS)){
        Token* op = currentToken;
        currentToken = currentToken->next;
        auto expr = parseUnary();

        return std::make_unique<Unary>(op, std::move(expr));
    }

    return parsePrimary();
}

std::unique_ptr<Expression> Parser::parseFactor(){
    auto expr = parseUnary();

    while(currentToken->type == OPERATOR && (currentToken->subtype == SLASH || currentToken->subtype == STAR)){
        Token* op = currentToken;
        currentToken = currentToken->next;
        auto right = parseUnary();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::parseTerm(){
    auto expr = parseFactor();

    while(currentToken->type == OPERATOR && (currentToken->subtype == PLUS || currentToken->subtype == MINUS)){
        Token* op = currentToken;
        currentToken = currentToken->next;
        auto right = parseFactor();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::parseComparison(){
    auto expr = parseTerm();

    while(currentToken->type == OPERATOR &&
        (currentToken->subtype == GREATER || currentToken->subtype == GREATER_EQUAL ||
            currentToken->subtype == LESS || currentToken->subtype == LESS_EQUAL)){

        Token* op = currentToken;
        currentToken = currentToken->next;
        auto right = parseTerm();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;

}

std::unique_ptr<Expression> Parser::parseEquality(){
    auto expr = parseComparison();

    while(currentToken->type == OPERATOR && (currentToken->subtype == EQUAL_EQUAL ||
        currentToken->subtype == NOT_EQUAL)){

        Token* op = currentToken;
        currentToken = currentToken->next;
        auto right = parseComparison();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::parseExpression(){
    return parseEquality();
}

void Grouping::accept(Visitor& v){
    v.visitGrouping(*this);
}

void Binary::accept(Visitor& v){
    v.visitBinary(*this);
}

void Unary::accept(Visitor& v){
    v.visitUnary(*this);
}

void Literal::accept(Visitor& v){
    v.visitLiteral(*this);
}

void Visitor::visitUnary(Unary& unary){

}

void Visitor::visitBinary(Binary& binary){

}

void Visitor::visitGrouping(Grouping& group){

}

void Visitor::visitLiteral(Literal& literal){

}
