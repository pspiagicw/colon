#include <catch.hpp>
#include <ast.hpp>

#define CHECK_MESSAGE(cond, msg) do { INFO(msg); CHECK(cond); } while((void)0, 0)
#define REQUIRE_MESSAGE(cond, msg) do { INFO(msg); REQUIRE(cond); } while((void)0, 0)

void test(std::string, std::vector<Statement> ast);



