#include <iostream>
#include <lexer.hpp>
#include <stdio.h>

int main() {
  std::string input;
  std::cout << "Welcome to colon: 1.0" << std::endl;

  std::cout << ">>> ";
  while (std::getline(std::cin, input)) {
    Lexer lexer(input);

    while (true) {
      Token got = lexer.next();
      std::cout << got.string() << std::endl;
      if (got._type == TokenType::TOKEN_EOF) {
        std::cout << ">>> ";
        break;
      }
    }
  }
}
