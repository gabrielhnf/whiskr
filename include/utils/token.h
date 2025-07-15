#pragma once

#include <string>
#include "types.h"

struct Token {
    public:
    Token(std::string name)
        : m_name(name) {}

    const std::string name() const { return m_name; }
    const Type type() const { return m_type; }
    const int subtype() const { return m_subtype; }
    Token* next() { return m_next; }

    void name(std::string str) { m_name = str; }
    void type(Type type) { m_type = type; }
    void subtype(int subtype) { m_subtype = subtype; }
    void next(Token* token) { m_next = token; }

    private:
    std::string m_name;
    Type m_type;
    int m_subtype;
    Token* m_next;
};
