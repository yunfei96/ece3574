#include "catch.hpp"
#include "expression.hpp"
#include "test_config.hpp"

TEST_CASE("Test bool equal", "[expression]")
{
    REQUIRE(Expression(false) == Expression(false));
    REQUIRE(Expression(true) == Expression(true));
}

TEST_CASE("Test bool not equal", "[expression]")
{
    string a = "a";
    REQUIRE_FALSE(Expression(true) == Expression(false));
    REQUIRE_FALSE(Expression(false) == Expression(true));
    REQUIRE_FALSE(Expression(false) == Expression(250.));
    REQUIRE_FALSE(Expression(a) == Expression(false));
}

TEST_CASE("Test symbol equal", "[expression]")
{
    string plus = "+";
    string plus_1 = "+";
    string minus = "-";
    string minus_1 = "-";
    string some_string = "!!@#$";
    string some_string_1 = "!!@#$";
    REQUIRE(Expression(plus) == Expression(plus_1));
    REQUIRE(Expression(minus) == Expression(minus_1));
    REQUIRE(Expression(some_string) == Expression(some_string_1));
}

TEST_CASE("Test symbol not equal", "[expression]")
{
    string plus = "+";
    string minus = "-";
    string some_string = "!!@#$";
    string not_some_string = "xxx!!@#$";
    REQUIRE_FALSE(Expression(plus) == Expression(minus));
    REQUIRE_FALSE(Expression(minus) == Expression(false));
    REQUIRE_FALSE(Expression(plus) == Expression(1.));
    REQUIRE_FALSE(Expression(some_string) == Expression(not_some_string));
}

TEST_CASE("Test number equal", "[expression]")
{
    REQUIRE(Expression(1.) == Expression((2.-1)));
    REQUIRE(Expression(6.) == Expression((2.*3.)));
    REQUIRE(Expression(.5) == Expression((1./2.)));
}

TEST_CASE("Test number not equal", "[expression]")
{
    string a = "aaaaa";
    REQUIRE_FALSE(Expression(3.) == Expression(false));
    REQUIRE_FALSE(Expression(3.) == Expression((2.*3.)));
    REQUIRE_FALSE(Expression(3.) == Expression(250.));
    REQUIRE_FALSE(Expression(3.) == Expression(a));
}
