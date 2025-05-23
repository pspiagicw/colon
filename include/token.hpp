#include <string>
enum class TokenType {
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_DIVIDE,

    TOKEN_LSQUARE,
    TOKEN_RSQUARE,

    TOKEN_LPAREN,
    TOKEN_RPAREN,

    TOKEN_LCURLY,
    TOKEN_RCURLY,
    
    TOKEN_LT,
    TOKEN_GT,

    TOKEN_LTE,
    TOKEN_GTE,

    TOKEN_ASSIGN,
    TOKEN_EQ,
    TOKEN_NEQ,
    TOKEN_BANG,

    TOKEN_DOT,
    TOKEN_COMMA,
    TOKEN_SEMICOLON,

    TOKEN_MODULO,

    TOKEN_SLEFT,
    TOKEN_SRIGHT,

    TOKEN_AND,
    TOKEN_OR,
    TOKEN_XOR,
    TOKEN_TILDE,

    TOKEN_STRING,
    TOKEN_CHAR,

    TOKEN_IDENTIFIER,

    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_WHILE,

    TOKEN_INT,
    TOKEN_DOUBLE,

    TOKEN_ILLEGAL,
    TOKEN_EOF,
};

class Token {
    public:
        Token(std::string value, TokenType type);
        TokenType _type;
        std::string _value;
};
