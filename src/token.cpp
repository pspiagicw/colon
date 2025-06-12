#include <token.hpp>
#include <fmt/format.h>
#include <magic_enum.hpp>

Token::Token(std::string value, TokenType type) {
    _type = type;
    _value = value;
}

std::string Token::string() {
    // return fmt::format("Token(type: {:d}, value: {})", _type, _value);
    return "Token(type: " + std::string(magic_enum::enum_name(_type)) + ", value: " + _value + ")";
}
