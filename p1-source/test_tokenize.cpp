#include "catch.hpp"
#include "tokenize.hpp"
#include "test_config.hpp"
#include <sstream>
#include <fstream>
TEST_CASE("Test tokenize atom", "[tokenize]")
{
    {
        vector<string> result;
        std::istringstream iss("(1)");
        token tok;
        result = tok.token_result(iss);
        vector<string> test;
        test.push_back("(");
        test.push_back("1");
        test.push_back(")");
        REQUIRE(result == test);
    }
    {
        vector<string> result;
        std::istringstream iss("(a)");
        token tok;
        result = tok.token_result(iss);
        vector<string> test;
        test.push_back("(");
        test.push_back("a");
        test.push_back(")");
        REQUIRE(result == test);
    }
    {
        vector<string> result;
        std::istringstream iss("(-1)");
        token tok;
        result = tok.token_result(iss);
        vector<string> test;
        test.push_back("(");
        test.push_back("-1");
        test.push_back(")");
        REQUIRE(result == test);
    }
    
}

TEST_CASE("Test tokenize equation(no special, no nest)", "[tokenize]")
{
    {
        vector<string> result;
        std::istringstream iss("(+ 1 2 3)");
        token tok;
        result = tok.token_result(iss);
        vector<string> test;
        test.push_back("(");
        test.push_back("+");
        test.push_back("1");
        test.push_back("2");
        test.push_back("3");
        test.push_back(")");
        REQUIRE(result == test);
    }
    {
        vector<string> result;
        std::istringstream iss("(< a b)");
        token tok;
        result = tok.token_result(iss);
        vector<string> test;
        test.push_back("(");
        test.push_back("<");
        test.push_back("a");
        test.push_back("b");
        test.push_back(")");
        REQUIRE(result == test);
    }
    {
        vector<string> result;
        std::istringstream iss("(/ a b)");
        token tok;
        result = tok.token_result(iss);
        vector<string> test;
        test.push_back("(");
        test.push_back("/");
        test.push_back("a");
        test.push_back("b");
        test.push_back(")");
        REQUIRE(result == test);
    }
    
}

TEST_CASE("Test tokenize nest structure)", "[tokenize]")
{
    {
        vector<string> result;
        std::istringstream iss("(+ (- 1 3) 2 3)");
        token tok;
        result = tok.token_result(iss);
        vector<string> test;
        test.push_back("(");
        test.push_back("+");
        test.push_back("(");
        test.push_back("-");
        test.push_back("1");
        test.push_back("3");
        test.push_back(")");
        test.push_back("2");
        test.push_back("3");
        test.push_back(")");
        REQUIRE(result == test);
    }
    {
        vector<string> result;
        std::istringstream iss("(begin (define a 10) (< a 10))");
        token tok;
        result = tok.token_result(iss);
        vector<string> test;
        test.push_back("(");
        test.push_back("begin");
        test.push_back("(");
        test.push_back("define");
        test.push_back("a");
        test.push_back("10");
        test.push_back(")");
        test.push_back("(");
        test.push_back("<");
        test.push_back("a");
        test.push_back("10");
        test.push_back(")");
        test.push_back(")");
        REQUIRE(result == test);
    }
    {
        vector<string> result;
        std::istringstream iss("(if True (/ a b) 10)");
        token tok;
        result = tok.token_result(iss);
        vector<string> test;
        test.push_back("(");
        test.push_back("if");
        test.push_back("True");
        test.push_back("(");
        test.push_back("/");
        test.push_back("a");
        test.push_back("b");
        test.push_back(")");
        test.push_back("10");
        test.push_back(")");
        REQUIRE(result == test);
    }
    
}

TEST_CASE( "Test token files", "[tokenize]" )
{
    
    std::string fname = TEST_FILE_DIR + "/test3.vts";
    std::ifstream ifs(fname);
    token tok;
    vector<string> result;
    vector<string> test;
    //(begin(define a 1)(define b 2)(if (< a b) b a))
    result = tok.token_result(ifs);
    test.push_back("(");
    test.push_back("begin");
    test.push_back("(");
    test.push_back("define");
    test.push_back("a");
    test.push_back("1");
    test.push_back(")");
    test.push_back("(");
    test.push_back("define");
    test.push_back("b");
    test.push_back("2");
    test.push_back(")");
    test.push_back("(");
    test.push_back("if");
    test.push_back("(");
    test.push_back("<");
    test.push_back("a");
    test.push_back("b");
    test.push_back(")");
    test.push_back("b");
    test.push_back("a");
    test.push_back(")");
    test.push_back(")");
    REQUIRE(result == test);
}
