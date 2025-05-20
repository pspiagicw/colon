#include <token.hpp>

Token::Token(std::string value, TokenType type) {
    _type = type;
    _value = value;
}
