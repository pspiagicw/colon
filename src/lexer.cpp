#include <algorithm>
#include <cassert>
#include <lexer.hpp>
#include <stdexcept>

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
  if (_readPos == _inputLen) {
    return '\0';
  }
  return _input[_readPos];
}

char Lexer::current() {
  if (_isEOF) {
    return '\0';
  }
  return _input[_curPos];
}

void Lexer::whitespace() {
  char curChar = current();
  while (!_isEOF && (curChar == ' ' || curChar == '\t' || curChar == '\n')) {
    advance();
    curChar = current();
  }
}

Token Lexer::skipComment() {
  if (current() == '/') {
    while (!_isEOF && current() != '\n') {
      advance();
    }
    return next();
  } else if (current() == '*') {
    advance(); // skip over the '*'
    while (!_isEOF && current() != '*' && peek() != '/') {
      advance();
    }
    advance(); // skip over the '/'
    return next();
  } else {
    throw std::runtime_error(
        "Fatal error: tried skipping comment without comment symbol!");
  }
}

std::string Lexer::extractChar() {
  assert(current() == '\'');
  advance();

  int startPoint = _curPos;
  while (!_isEOF && current() != '\'') {
    advance();
  }

  int endPoint = _curPos;

  int width = endPoint - startPoint;

  // substring function takes width, not start and endPoint;
  return _input.substr(startPoint, width);
}

std::string Lexer::extractString() {
  // Assert we start on " and not somewhere else.
  assert(current() == '"');
  advance();

  int startPoint = _curPos;

  while (!_isEOF && current() != '"') {
    advance();
  }

  int endPoint = _curPos;

  return _input.substr(startPoint, endPoint - 1);
}

std::string Lexer::extractIdent() {
  assert(std::isalpha(current()));

  int startPoint = _curPos;

  while (!_isEOF &&
         ((std::isalpha(peek()) || std::isdigit(peek())) && peek() != ' ')) {
    advance();
  }

  int endPoint = _curPos + 1;

  int width = endPoint - startPoint;

  return _input.substr(startPoint, width);
}

std::string Lexer::extractNumber() {
  assert(std::isdigit(current()));

  int startPoint = _curPos;

  while (!_isEOF && (std::isdigit(peek()) || peek() == '.')) {
    advance();
  }

  int endPoint = _curPos + 1;

  int width = endPoint - startPoint;

  return _input.substr(startPoint, width);
}

TokenType Lexer::predictType(std::string value) {
  if (value == "if") {
    return TokenType::TOKEN_IF;
  } else if (value == "else") {
    return TokenType::TOKEN_ELSE;
  } else if (value == "for") {
    return TokenType::TOKEN_FOR;
  } else if (value == "while") {
    return TokenType::TOKEN_WHILE;
  } else if (value == "let") {
    return TokenType::TOKEN_LET;
  }

  if (std::isdigit(value[0])) {
    int count = std::count(value.begin(), value.end(), '.');

    if (count == 0) {
      return TokenType::TOKEN_INT;
    } else if (count == 1) {
      return TokenType::TOKEN_DOUBLE;
    } else {
      return TokenType::TOKEN_ILLEGAL;
    }
  }

  return TokenType::TOKEN_IDENTIFIER;
}
Token Lexer::next() {
  advance();
  whitespace();
  if (_isEOF) {
    return Token("", TokenType::TOKEN_EOF);
  }
  char _cur = current();
  switch (_cur) {
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
    if (peek() == '/') {
      // skip over the first /
      advance();
      return skipComment();
    } else if (peek() == '*') {
      // skip over the first /
      advance();
      return skipComment();
    }
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
  case '"': {
    std::string extractedString = extractString();
    return Token(extractedString, TokenType::TOKEN_STRING);
    break;
  }
  case '\'': {
    std::string extractedChar = extractChar();
    return Token(extractedChar, TokenType::TOKEN_CHAR);
    break;
  }
  default:
    if (std::isalpha(_cur)) {
      std::string value = extractIdent();
      TokenType type = predictType(value);
      return Token(value, type);
    } else if (std::isdigit(_cur)) {
      std::string value = extractNumber();
      TokenType type = predictType(value);
      return Token(value, type);
    }
    return Token(std::to_string(_cur), TokenType::TOKEN_ILLEGAL);
    break;
  }
}
