#include <string>
#include <token.hpp>

class Lexer {
    public:
        Lexer(std::string input);
        Token next();

    private:
        std::string _input;
        int _curPos;
        int _readPos;
        char _curChar;

        int _inputLen;
        bool _isEOF;

        void advance();
        char peek();
        void whitespace();
        
};

