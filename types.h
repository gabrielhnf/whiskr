typedef enum {
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    LITERAL
} Type;

typedef enum {
    INT,
    FLOAT
} KeywordTypes;

typedef struct {
    char* kw_name;
    KeywordTypes kw_type;
} Keyword;

extern const Keyword keyword_table[];
extern const unsigned int keyword_size;

typedef enum {
    SUM,
    SUB,
    MUL,
    DIV
} OperatorTypes;

typedef struct {
    char op_name;
    OperatorTypes type;
} Operator;

extern const Operator operator_table[];
extern const unsigned int operator_size;

typedef struct Token {
    char* string;
    Type type;
    union {
        int literal;
        Keyword keyword;
        Operator op;
    } value;
    struct Token* nextToken;
    struct Token* prevToken;
} Token;
