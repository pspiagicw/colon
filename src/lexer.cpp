#include <lexer.hpp>

Lexer::Lexer(std::string input) {
    _input = input;
    _inputLen = input.length();

    _curPos = -1;
    _readPos = 0;

    _isEOF = false;
}

void Lexer::advance() {
    _curPos = _readPos;
    _readPos++;

    if (_curPos == _inputLen) {
        _isEOF = true;
        _curChar = '\0';
    } else {
        _curChar = _input[_curPos];
    }
}

char Lexer::peek() {
    if(_readPos == _inputLen) {
        return '\0';
    }
    return _input[_readPos];
}

void Lexer::whitespace() {
    char curChar = _input[_curPos];
    while(!_isEOF && (curChar == ' ' || curChar == '\t' || curChar == '\n')) {
        advance();
        curChar = _input[_curPos];
    }
}
Token Lexer::next() {
    advance();
    whitespace();
    if (_isEOF) {
        return Token("", TokenType::TOKEN_EOF);
    }
    char currentChar = _input[_curPos];
    switch (currentChar) {
        case '+':
            return Token("+", TokenType::TOKEN_PLUS);
            break;
        case '-':
            return Token("-", TokenType::TOKEN_MINUS);
            break;
        case '*':
            return Token("*", TokenType::TOKEN_STAR);
            break;
        case '/':
            return Token("/", TokenType::TOKEN_DIVIDE);
            break;
        case '[':
            return Token("[", TokenType::TOKEN_LSQUARE);
            break;
        case ']':
            return Token("]", TokenType::TOKEN_RSQUARE);
            break;
        case '{':
            return Token("{", TokenType::TOKEN_LCURLY);
            break;
        case '}':
            return Token("}", TokenType::TOKEN_RCURLY);
            break;
        case '(':
            return Token("(", TokenType::TOKEN_LPAREN);
            break;
        case ')':
            return Token(")", TokenType::TOKEN_RPAREN);
            break;
        case '<':
            if (peek() == '=') {
                advance();
                return Token("<=", TokenType::TOKEN_LTE);
            } else if (peek() == '<') {
                advance();
                return Token("<<", TokenType::TOKEN_SLEFT);
            }
            return Token("<", TokenType::TOKEN_LT);
            break;
        case '>':
            if (peek() == '=') {
                advance();
                return Token(">=", TokenType::TOKEN_GTE);
            } else if (peek() == '>') {
                advance();
                return Token(">>", TokenType::TOKEN_SRIGHT);
            }
            return Token(">", TokenType::TOKEN_GT);
            break;
        case '=':
            if (peek() == '=') {
                advance();
                return Token("==", TokenType::TOKEN_EQ);
            }
            return Token("=", TokenType::TOKEN_ASSIGN);
            break;
        case '!':
            if (peek() == '=') {
                advance();
                return Token("!=", TokenType::TOKEN_NEQ);
            }
            return Token("!", TokenType::TOKEN_BANG);
        case '.':
            return Token(".", TokenType::TOKEN_DOT);
            break;
        case ',':
            return Token(",", TokenType::TOKEN_COMMA);
            break;
        case ';':
            return Token(";", TokenType::TOKEN_SEMICOLON);
            break;
        case '%':
            return Token("%", TokenType::TOKEN_MODULO);
            break;
        default:
            return Token(std::to_string(currentChar), TokenType::TOKEN_ILLEGAL);
            break;
    }
}
