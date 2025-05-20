#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("Simple test", "[setup]") {
    REQUIRE(1 == 1);
}

