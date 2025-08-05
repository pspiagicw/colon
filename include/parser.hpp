#include <vector>
#include <memory>
#include <ast.hpp>
#include <lexer.hpp>



class Parser {
    public: 
        Parser(Lexer lexer);
        std::vector<std::unique_ptr<Statement>> parse();

    private:
        std::string _lexer;
};



