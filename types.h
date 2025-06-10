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
    //One character operators
    SUM, SUB, MUL, DIV,
    NOT, EQUAL, GREATER, LESS,

    //Two character operators
    EQUAL_EQUAL, NOT_EQUAL,
    GREATER_EQUAL, LESS_EQUAL,
} OperatorTypes;

typedef struct {
    char op_name;
    OperatorTypes type;
} Operator;

extern const Operator operator_table[];
extern const unsigned int operator_size;

typedef enum {
    OPEN_PAREN, CLOSED_PAREN,
    OPEN_CBRACK, CLOSED_CBRACK,
    COMMA, DOT, SEMICOLON

} DelimiterTypes;

typedef struct {
    char delim_char;
    DelimiterTypes type;
} Delimiter;

extern const Delimiter delimiter_table[];
extern const unsigned int delimiter_size;

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

int isOperator(char* str);
