#include "catch.hpp"
#include "environment.hpp"
#include "test_config.hpp"

/*
 This test only test for the store function of the envrionment. Accroding to my design, the calculation function are also in the envrionemt module due to the easy access to the list variable.
 
 The test for the calculation part are in test_intepreter.cpp
 */
TEST_CASE("Test check default pi", "[environment]")
{
    {
        envir env;
        REQUIRE(env.environment.find("pi")-> second == atan2(0, -1));
    }
    
}

TEST_CASE("Test set symbols some number value", "[environment]")
{
    {
        envir env;
        env.environment["a"] = 1.2;
        REQUIRE(env.environment.find("a")-> second == 1.2);
    }
    
    {
        envir env;
        env.environment["x"] = 3.;
        REQUIRE(env.environment.find("x")-> second == 3);
    }
    
}

TEST_CASE("Test get number invalid key", "[environment]")
{
    {
        envir env;
        REQUIRE(env.environment.find("a") == env.environment.end());
    }
    
    {
        envir env;
        REQUIRE(env.environment.find("b") == env.environment.end());
    }
    
}

TEST_CASE("Test set symbol some bool value", "[environment]")
{
    {
        envir env;
        env.bool_envir["a"] = true;
        REQUIRE(env.bool_envir.find("a")-> second == true);
    }
    
    {
        envir env;
        env.bool_envir["x"] = false;
        REQUIRE(env.bool_envir.find("x")-> second == false);
    }
    
}

TEST_CASE("Test get bool invalid key", "[environment]")
{
    {
        envir env;
        REQUIRE(env.bool_envir.find("a") == env.bool_envir.end());
    }
    
    {
        envir env;
        REQUIRE(env.bool_envir.find("b") == env.bool_envir.end());
    }
    
}
