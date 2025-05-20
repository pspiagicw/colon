#include <string>
#include <token.hpp>

class Lexer {
    public:
        Lexer(std::string input);
        Token next();

        std::string _input;
};
