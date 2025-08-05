#include <catch.hpp>
#include <vector>
#include <memory>
#include <parser.hpp>

#define CHECK_MESSAGE(cond, msg) do { INFO(msg); CHECK(cond); } while((void)0, 0)
#define REQUIRE_MESSAGE(cond, msg) do { INFO(msg); REQUIRE(cond); } while((void)0, 0)

void test_parser(std::string input, std::vector<std::unique_ptr<Statement>> ast);

TEST_CASE("Test let statements", "[parser]") {
    std::string input = "let a = 5;";

    std::vector<std::unique_ptr<Statement>> ast;
    ast.push_back(std::make_unique<LetStatement>("a", std::make_unique<IntegerExpression>(5)));

    test_parser(input, std::move(ast));

}

void test_parser(std::string input, std::vector<std::unique_ptr<Statement>> expected) {
    Lexer lexer(input);
    Parser parser(lexer);

    auto actual = parser.parse();

    REQUIRE_MESSAGE(actual.size() == expected.size(),"Actual AST statement size and expected statement size doesn't match");
}


