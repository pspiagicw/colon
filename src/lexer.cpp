#include <lexer.hpp>

Lexer::Lexer(std::string input) {
    _input = input;
}

Token Lexer::next() {
    return Token("", TokenType::TOKEN_EOF);
}
