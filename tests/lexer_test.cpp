#include <catch.hpp>
#include <lexer.hpp>
#include <magic_enum.hpp>
#include <vector>
#include <cstdio>

#define CHECK_MESSAGE(cond, msg) do { INFO(msg); CHECK(cond); } while((void)0, 0)
#define REQUIRE_MESSAGE(cond, msg) do { INFO(msg); REQUIRE(cond); } while((void)0, 0)

void test(std::string, std::vector<Token> expectedTokens);

TEST_CASE("Test symbols", "[lexer]") {
  std::string input = "-+*/";

  std::vector<Token> expectedTokens = {
      Token("-", TokenType::TOKEN_MINUS), Token("+", TokenType::TOKEN_PLUS),
      Token("*", TokenType::TOKEN_STAR),  Token("/", TokenType::TOKEN_DIVIDE),
      Token("", TokenType::TOKEN_EOF),
  };

  test(input, expectedTokens);
}

TEST_CASE("Test square brackets", "[lexer]") {
    std::string input = "[]";

    std::vector<Token> expectedTokens = {
        Token("[", TokenType::TOKEN_LSQUARE),
        Token("]", TokenType::TOKEN_RSQUARE),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test curly braces", "[lexer]") {
    std::string input = "{}";

    std::vector<Token> expectedTokens = {
        Token("{", TokenType::TOKEN_LCURLY),
        Token("}", TokenType::TOKEN_RCURLY),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test parentheses", "[lexer]") {
    std::string input = "()";

    std::vector<Token> expectedTokens = {
        Token("(", TokenType::TOKEN_LPAREN),
        Token(")", TokenType::TOKEN_RPAREN),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test angle brackets", "[lexer]") {
    std::string input = "<>";

    std::vector<Token> expectedTokens = {
        Token("<", TokenType::TOKEN_LT),
        Token(">", TokenType::TOKEN_GT),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test less than or equal and greater than or equal", "[lexer]") {
    std::string input = "<=>=";

    std::vector<Token> expectedTokens = {
        Token("<=", TokenType::TOKEN_LTE),
        Token(">=", TokenType::TOKEN_GTE),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test spaces and tabs", "[lexer]") {
    std::string input = "< >\t< >\n<";

    std::vector<Token> expectedTokens = {
        Token("<", TokenType::TOKEN_LT),
        Token(">", TokenType::TOKEN_GT),
        Token("<", TokenType::TOKEN_LT),
        Token(">", TokenType::TOKEN_GT),
        Token("<", TokenType::TOKEN_LT),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);

}

TEST_CASE("Test assignment and equality", "[lexer]") {
    std::string input = "== =";

    std::vector<Token> expectedTokens = {
        Token("==", TokenType::TOKEN_EQ),
        Token("=", TokenType::TOKEN_ASSIGN),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test bang and bang equal", "[lexer]") {
    std::string input = "! !=";

    std::vector<Token> expectedTokens = {
        Token("!", TokenType::TOKEN_BANG),
        Token("!=", TokenType::TOKEN_NEQ),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test dot and comma", "[lexer]") {
    std::string input = ".,";
    
    std::vector<Token> expectedTokens = {
        Token(".", TokenType::TOKEN_DOT),
        Token(",", TokenType::TOKEN_COMMA),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test semicolon", "[lexer]") {
    std::string input = ";";

    std::vector<Token> expectedTokens = {
        Token(";", TokenType::TOKEN_SEMICOLON),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test modulo and modulo equal", "[lexer]") {
    std::string input = "%";

    std::vector<Token> expectedTokens = {
        Token("%", TokenType::TOKEN_MODULO),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test shift operators", "[lexer]") {
    std::string input = "<< >>";

    std::vector<Token> expectedTokens = {
        Token("<<", TokenType::TOKEN_SLEFT),
        Token(">>", TokenType::TOKEN_SRIGHT),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

// TODO: Add support for these bitwise operators
// TEST_CASE("Test bitwise operators", "[lexer]") {
//     std::string input = "& | ^ ~";
//
//     std::vector<Token> expectedTokens = {
//         Token("&", TokenType::TOKEN_AND),
//         Token("|", TokenType::TOKEN_OR),
//         Token("^", TokenType::TOKEN_XOR),
//         Token("~", TokenType::TOKEN_TILDE),
//         Token("", TokenType::TOKEN_EOF),
//     };
//
//     test(input, expectedTokens);
// }


// TODO: Add support for && and || tokens.
// TEST_CASE("Test logical operators", "[lexer]") {
//     std::string input = "&& ||";
//
//     std::vector<Token> expectedTokens = {
//         Token("&&", TokenType::TOKEN_AND_AND),
//         Token("||", TokenType::TOKEN_OR_OR),
//         Token("", TokenType::TOKEN_EOF),
//     };
//
//     test(input, expectedTokens);
// }

TEST_CASE("Test string literal", "[lexer]") {
    std::string input = "\"hello\"";

    std::vector<Token> expectedTokens = {
        Token("hello", TokenType::TOKEN_STRING),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test char literal", "[lexer]") {
    std::string input = "'a'";

    std::vector<Token> expectedTokens = {
        Token("a", TokenType::TOKEN_CHAR),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}
TEST_CASE("Test identifiers", "[lexer]") {
    std::string input = "foo bar baz123";

    std::vector<Token> expectedTokens = {
        Token("foo", TokenType::TOKEN_IDENTIFIER),
        Token("bar", TokenType::TOKEN_IDENTIFIER),
        Token("baz123", TokenType::TOKEN_IDENTIFIER),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}
TEST_CASE("Test keywords", "[lexer]") {
    std::string input = "if else for while let";

    std::vector<Token> expectedTokens = {
        Token("if", TokenType::TOKEN_IF),
        Token("else", TokenType::TOKEN_ELSE),
        Token("for", TokenType::TOKEN_FOR),
        Token("while", TokenType::TOKEN_WHILE),
        Token("let", TokenType::TOKEN_LET),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}
TEST_CASE("Test integer literals", "[lexer]") {
    std::string input = "42 0 123456";

    std::vector<Token> expectedTokens = {
        Token("42", TokenType::TOKEN_INT),
        Token("0", TokenType::TOKEN_INT),
        Token("123456", TokenType::TOKEN_INT),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}
TEST_CASE("Test double literals", "[lexer]") {
    std::string input = "3.14 0.0 10.5";

    std::vector<Token> expectedTokens = {
        Token("3.14", TokenType::TOKEN_DOUBLE),
        Token("0.0", TokenType::TOKEN_DOUBLE),
        Token("10.5", TokenType::TOKEN_DOUBLE),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test minus before int literal", "[lexer]") {
    std::string input = "-42";

    std::vector<Token> expectedTokens = {
        Token("-", TokenType::TOKEN_MINUS),
        Token("42", TokenType::TOKEN_INT),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test minus before double literal", "[lexer]") {
    std::string input = "-3.14";

    std::vector<Token> expectedTokens = {
        Token("-", TokenType::TOKEN_MINUS),
        Token("3.14", TokenType::TOKEN_DOUBLE),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}

// TODO: Espcape sequences!

// TEST_CASE("Test string literal with escape sequences", "[lexer]") {
//     std::string input = "\"Hello\\nWorld\\t!\"";
//
//     std::vector<Token> expectedTokens = {
//         Token("\"Hello\\nWorld\\t!\"", TokenType::TOKEN_STRING),
//         Token("", TokenType::TOKEN_EOF),
//     };
//
//     test(input, expectedTokens);
// }
//
// TODO: Espcape sequences!

// TEST_CASE("Test char literal with escape sequence", "[lexer]") {
//     std::string input = "'\\n'";
//
//     std::vector<Token> expectedTokens = {
//         Token("'\\n'", TokenType::TOKEN_CHAR),
//         Token("", TokenType::TOKEN_EOF),
//     };
//
//     test(input, expectedTokens);
// }
TEST_CASE("Test single-line comment skipping", "[lexer]") {
    std::string input = "42 // this is a comment\n + 5";

    std::vector<Token> expectedTokens = {
        Token("42", TokenType::TOKEN_INT),
        Token("+", TokenType::TOKEN_PLUS),
        Token("5", TokenType::TOKEN_INT),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);
}
TEST_CASE("Test multi-line comment skipping", "[lexer]") {
    std::string input = "42 /* comment \n spanning multiple \n lines */ + 5";

    std::vector<Token> expectedTokens = {
        Token("42", TokenType::TOKEN_INT),
        Token("+", TokenType::TOKEN_PLUS),
        Token("5", TokenType::TOKEN_INT),
        Token("", TokenType::TOKEN_EOF),
    };

    test(input, expectedTokens);

}

TEST_CASE("Test immediate token recognition with numbers.", "[lexer]") {

    std::string input = "3+5";

    std::vector<Token> expectedTokens = {
        Token("3", TokenType::TOKEN_INT),
        Token("+", TokenType::TOKEN_PLUS),
        Token("5", TokenType::TOKEN_INT),
    };

    test(input, expectedTokens);
}

TEST_CASE("Test immediate token recognition with identifiers", "[lexer]") {
    std::string input = "ident1+ident2";

    std::vector<Token> expectedTokens = {
        Token("ident1", TokenType::TOKEN_IDENTIFIER),
        Token("+", TokenType::TOKEN_PLUS),
        Token("ident2", TokenType::TOKEN_IDENTIFIER),
    };

    test(input, expectedTokens);
}


void test(std::string input, std::vector<Token> expectedTokens) {
  Lexer lexer(input);

  for (auto expected : expectedTokens) {
    Token actual = lexer.next();

    std::string tokenMessage = "Token type doesn't match, got=" + std::string(magic_enum::enum_name(actual._type)) + " expected=" + std::string(magic_enum::enum_name(expected._type));
    std::string valueMessage = "Value doesn't match, got=" + actual._value + " expected=" + expected._value;
    CHECK_MESSAGE(actual._value == expected._value, valueMessage);
    CHECK_MESSAGE(actual._type == expected._type, tokenMessage);
  }

  lexer.next();
}
