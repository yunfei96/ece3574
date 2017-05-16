#include "catch.hpp"
#include <math.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "interpreter_semantic_error.hpp"
#include "interpreter.hpp"
#include "expression.hpp"
#include "test_config.hpp"

Expression run(const std::string & program){
  
  std::istringstream iss(program);
    
  Interpreter interp;
    
  bool ok = interp.parse(iss);
  if(!ok){
    std::cerr << "Failed to parse: " << program << std::endl; 
  }
  REQUIRE(ok);

  Expression result;
  REQUIRE_NOTHROW(result = interp.eval());

  return result;
}

Expression runfile(const std::string & fname){

  std::ifstream ifs(fname);
  REQUIRE(ifs.good() == true);
  
  Interpreter interp;
    
  bool ok = interp.parse(ifs);
  if(!ok){
    std::cerr << "Failed to parse file: " << fname << std::endl; 
  }
  REQUIRE(ok);

  Expression result;
  REQUIRE_NOTHROW(result = interp.eval());

  return result;
}

TEST_CASE( "Test Interpreter parser with expected input", "[interpreter]" ) {

  std::string program = "(begin (define r 10) (* pi (* r r)))";

  std::istringstream iss(program);
 
  Interpreter interp;

  bool ok = interp.parse(iss);

  REQUIRE(ok);
}

TEST_CASE( "Test Interpreter parser with numerical literals", "[interpreter]" ) {

  std::vector<std::string> programs = {"(1)", "(+1)", "(+1e+0)", "(1e-0)"};
  
  for(auto program : programs){
    std::istringstream iss(program);
 
    Interpreter interp;

    bool ok = interp.parse(iss);

    REQUIRE(ok == true);
  }
}

TEST_CASE( "Test Interpreter parser with truncated input", "[interpreter]" ) {

  {
    std::string program = "(f";
    std::istringstream iss(program);
  
    Interpreter interp;
    bool ok = interp.parse(iss);
    REQUIRE(!ok);
  }
  
  {
    std::string program = "(begin (define r 10) (* pi (* r r";
    std::istringstream iss(program);

    Interpreter interp;
    bool ok = interp.parse(iss);
    REQUIRE(!ok);
  }
}

TEST_CASE( "Test Interpreter parser with extra input", "[interpreter]" ) {

  std::string program = "(begin (define r 10) (* pi (* r r))) )";
  std::istringstream iss(program);

  Interpreter interp;

  bool ok = interp.parse(iss);

  REQUIRE(!ok);
}

TEST_CASE( "Test Interpreter parser with single non-keyword", "[interpreter]" ) {

  std::string program = "hello";
  std::istringstream iss(program);
  
  Interpreter interp;

  bool ok = interp.parse(iss);

  REQUIRE(!ok);
}

TEST_CASE( "Test Interpreter parser with empty input", "[interpreter]" ) {

  std::string program;
  std::istringstream iss(program);
  
  Interpreter interp;

  bool ok = interp.parse(iss);

  REQUIRE(!ok);
}

TEST_CASE( "Test Interpreter parser with empty expression", "[interpreter]" ) {

  std::string program = "( )";
  std::istringstream iss(program);
  
  Interpreter interp;

  bool ok = interp.parse(iss);

  REQUIRE(!ok);
}

TEST_CASE( "Test Interpreter parser with bad number string", "[interpreter]" ) {

  std::string program = "(1abc)";
  std::istringstream iss(program);
  
  Interpreter interp;

  bool ok = interp.parse(iss);

  REQUIRE(!ok);
}

TEST_CASE( "Test Interpreter parser with incorrect input. Regression Test", "[interpreter]" ) {

  std::string program = "(+ 1 2) (+ 3 4)";
  std::istringstream iss(program);
  
  Interpreter interp;

  bool ok = interp.parse(iss);

  REQUIRE(!ok);
}

TEST_CASE( "Test Interpreter result with literal expressions", "[interpreter]" ) {

  { // Boolean True
    std::string program = "(True)";
    Expression result = run(program);
    REQUIRE(result == Expression(true));
  }

  { // Boolean False
    std::string program = "(False)";
    Expression result = run(program);
    REQUIRE(result == Expression(false));
  }
  
  { // Number
    std::string program = "(4)";
    Expression result = run(program);
    REQUIRE(result == Expression(4.));
  }

  { // Symbol
    std::string program = "(pi)";
    Expression result = run(program);
    REQUIRE(result == Expression(atan2(0, -1)));
  }

}

TEST_CASE( "Test Interpreter result with simple procedures (add)", "[interpreter]" ) {

  { // add, binary case
    std::string program = "(+ 1 2)";
    Expression result = run(program);
    REQUIRE(result == Expression(3.));
  }
  
  { // add, 3-ary case
    std::string program = "(+ 1 2 3)";
    Expression result = run(program);
    REQUIRE(result == Expression(6.));
  }

  { // add, 6-ary case
    std::string program = "(+ 1 2 3 4 5 6)";
    Expression result = run(program);
    REQUIRE(result == Expression(21.));
  }
}
  
TEST_CASE( "Test Interpreter special form: if", "[interpreter]" ) {

  {
    std::string program = "(if True (4) (-4))";
    Expression result = run(program);
    REQUIRE(result == Expression(4.));
  }
  
  {
    std::string program = "(if False (4) (-4))";
    Expression result = run(program);
    REQUIRE(result == Expression(-4.));
  }
}

TEST_CASE( "Test Interpreter special forms: begin and define", "[interpreter]" ) {

  {
    std::string program = "(define answer 42)";
    Expression result = run(program);
    REQUIRE(result == Expression(42.));
  }

  {
    std::string program = "(begin (define answer 42)\n(answer))";
    Expression result = run(program);
    REQUIRE(result == Expression(42.));
  }
  
  {
    std::string program = "(begin (define answer (+ 9 11)) (answer))";
    Expression result = run(program);
    REQUIRE(result == Expression(20.));
  }

  {
    std::string program = "(begin (define a 1) (define b 1) (+ a b))";
    Expression result = run(program);
    REQUIRE(result == Expression(2.));
  }
}

TEST_CASE( "Test a complex expression", "[interpreter]" ) {

  {
    std::string program = "(+ (+ 10 1) (+ 30 (+ 1 1)))";
    Expression result = run(program);
    REQUIRE(result == Expression(43.));
  }
}

TEST_CASE( "Test relational procedures", "[interpreter]" ) {

  {
    std::vector<std::string> programs = {"(< 1 2)",
					 "(<= 1 2)",
					 "(<= 1 1)",
					 "(> 2 1)",
					 "(>= 2 1)",
					 "(>= 2 2)",
					 "(= 4 4)"};
    for(auto s : programs){
      Expression result = run(s);
      REQUIRE(result == Expression(true));
    }
  }

  {
    std::vector<std::string> programs = {"(< 2 1)",
					 "(<= 2 1)",
					 "(<= 1 0)",
					 "(> 1 2)",
					 "(>= 1 2)",
					 "(>= 2 3)",
					 "(= 0 4)"};
    for(auto s : programs){
      Expression result = run(s);
      REQUIRE(result == Expression(false));
    }
  }
}

TEST_CASE( "Test arithmetic procedures", "[interpreter]" ) {

  {
    std::vector<std::string> programs = {"(+ 1 -2)",
					 "(+ -3 1 1)",
					 "(- 1)",
					 "(- 1 2)",
					 "(* 1 -1)",
					 "(* 1 1 -1)",
					 "(/ -1 1)",
					 "(/ 1 -1)",
                     "(begin (define a 1) (* -1 a))",
                     "(begin (define a 1) (/ -1 a))",
                     "(begin (define a 1) (- 0 a))",
                     "(begin (define a 1) (- a))"};
        

    for(auto s : programs){
      Expression result = run(s);
      REQUIRE(result == Expression(-1.));
    }
  }
}

TEST_CASE( "Test logical procedures", "[interpreter]" ) {

  REQUIRE(run("(not True)") == Expression(false));
  REQUIRE(run("(not False)") == Expression(true));

  REQUIRE(run("(and True True)") == Expression(true));
  REQUIRE(run("(and True False)") == Expression(false));
  REQUIRE(run("(and False True)") == Expression(false));
  REQUIRE(run("(and False False)") == Expression(false));
  REQUIRE(run("(and True True False)") == Expression(false));

  REQUIRE(run("(or True True)") == Expression(true));
  REQUIRE(run("(or True False)") == Expression(true));
  REQUIRE(run("(or False True)") == Expression(true));
  REQUIRE(run("(or False False)") == Expression(false));
  REQUIRE(run("(or True True False)") == Expression(true));
}

TEST_CASE( "Test trig procedures", "[interpreter]" ) {

  REQUIRE(run("(sin pi)") == Expression(sin(atan2(0, -1))));
  REQUIRE(run("(cos pi)") == Expression(-1.));
  REQUIRE(run("(arctan 1 0)") == Expression(atan2(1,0)));

  std::vector<std::string> programs = {"(sin 0 1)",
				       "(cos 0 1)", 
				       "(arctan 0)",
				       "(sin True)",
				       "(cos True)",
				       "(arctan 1 False)"};
  for(auto s : programs){
    Interpreter interp;
   
    std::istringstream iss(s);
    
    REQUIRE(interp.parse(iss));
    
    REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
  }
}

TEST_CASE( "Test some semantically invalid expresions", "[interpreter]" ) {
  
  std::vector<std::string> programs = {"(@ none)", // so such procedure
				       "(- 1 1 2)", // too many arguments
				       "(define if 1)", // redefine special form
				       "(define pi 3.14)"}; // redefine builtin symbol
    for(auto s : programs){
      Interpreter interp;

      std::istringstream iss(s);
      
      bool ok = interp.parse(iss);
      REQUIRE(ok == true);

      REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
}

TEST_CASE("Test graphic types", "[interpreter]") {

  {
    std::string program = "(point 0 0)";
    std::istringstream iss(program);
    Interpreter interp;

    REQUIRE(interp.parse(iss));
    REQUIRE(interp.eval() == Expression(std::make_tuple(0., 0.)));
  }
  {
    std::string program = "(line (point 0 0) (point 10 0))";
    std::istringstream iss(program);
    Interpreter interp;

    REQUIRE(interp.parse(iss));
    REQUIRE(interp.eval() ==
            Expression(std::make_tuple(0., 0.), std::make_tuple(10., 0.)));
  }
  {
    std::string program = "(arc (point 0 0) (point 10 0) pi)";
    std::istringstream iss(program);
    Interpreter interp;

    REQUIRE(interp.parse(iss));
    REQUIRE(interp.eval() == Expression(std::make_tuple(0., 0.),
                                        std::make_tuple(10., 0.),
                                        atan2(0, -1)));
  }
}

TEST_CASE( "Test file tests/test0.vts", "[interpreter]" ) {

  std::string fname = TEST_FILE_DIR + "/test0.vts";

  std::ifstream ifs(fname);
  REQUIRE(ifs.good() == true);
  
  Interpreter interp;
    
  bool ok = interp.parse(ifs);
  REQUIRE(!ok);
}

TEST_CASE( "Test syntactically correct file using CRLF (Windows) line endings.", "[interpreter]" ) {

  std::string input = TEST_FILE_DIR + "/test_crlf.vts";

  std::string expect = input + ".expected";
  Expression result = runfile(input);
  Expression expected_result = runfile(expect);
  
  REQUIRE(result == expected_result);
  REQUIRE(result == Expression(-1.));
}

TEST_CASE( "Test syntactically INCORRECT files", "[interpreter]" ) {

  std::string fname = TEST_FILE_DIR + "/test1.vts";

  std::ifstream ifs(fname);
  REQUIRE(ifs.good() == true);
  
  Interpreter interp;
    
  bool ok = interp.parse(ifs);
  REQUIRE(!ok);
}

TEST_CASE( "Test all syntactically and semantically CORRECT files.", "[interpreter]" ) {

  const int START_TEST = 2;
  const int LAST_TEST = 5;
  std::string base = TEST_FILE_DIR + "/test";
  
  for(int i = START_TEST; i <= LAST_TEST; ++i){
    
    std::string input = base + std::to_string(i) + ".vts";
    std::string expect = input + ".expected";
    Expression result = runfile(input);
    Expression expected_result = runfile(expect);
  
    REQUIRE(result == expected_result);
  }
}
//---------------------------my own test, funtions of these test might have overleap with test provided by prof--------------------------

TEST_CASE( "Test Interpreter throw exp when arg type/arg number are wrong", "[interpreter]" )
{
    {
        std::vector<std::string> programs =
        {
            //define
            "(define a 1 2 3)","(define True 1)","(define 1 1)","(define a b)",
            //if
            "(if True 1 2 3)","(if a 1 2)","(if a True False)",
            // divide
            "(/ 1 2 3)","(/ b a)","(/ True False)",
            //time
            "(* a 1)","(* True False)","(* a)","(* 1)",
            // -
            "(- False)","(- a)","(-)","(- True 1)","(- a 1)","(- True False)",
            // single
            "(+)",
            // +
            "(+ True False)",
            // and
            "(and True)","(and 1)","(and 1 2)",
            // <
            "(< 0 1 2)","(< True 1)",
            // or
            "(or 1)","(or True)","(or 1 2)",
            //not
            "(not a)","(not 1)","(not True False)"
        };
        for(auto s : programs)
        {
            Interpreter interp;
            std::istringstream iss(s);
            bool ok = interp.parse(iss);
            REQUIRE(ok);
            REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
        }
    }
}

TEST_CASE( "Test Interpreter negtive number convertion", "[interpreter]" ) {
    
    {
        std::string program = "(+ -1 2)";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        Expression result = interp.eval();
        REQUIRE(result == Expression(1.));
    }
    
    {
        std::string program = "(/ -1 2)";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        Expression result = interp.eval();
        REQUIRE(result == Expression(-0.5));
    }
    
}

TEST_CASE( "Test Interpreter define in if", "[interpreter]" )
{
    {
        
        std::vector<std::string> programs =
        {
            "(begin (define a 9) (define b 10) (if true a b))",
            "(begin (define a 9) (define b 10) (if (a = b) a b))",
            "(begin (define b 10) (if False (define a 10) a))",
            "(begin (define a True)(if a b c))",
            "(if False (define a 10) a)",
            "(begin (define a 10) (if (b < a) a b))"
        };
        for(auto s : programs)
        {
            Interpreter interp;
            
            std::istringstream iss(s);
            
            bool ok = interp.parse(iss);
            REQUIRE(ok);
            
            REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
        }
    }
    
    
}

TEST_CASE( "Test Interpreter with =", "[interpreter]" ) {
    
    {
        std::string program = "(= 11 1)";
        Expression result = run(program);
        REQUIRE(result == Expression(false));
    }
    {
        std::string program = "(= 1 1)";
        Expression result = run(program);
        REQUIRE(result == Expression(true));
    }
    {
        std::string program = "(begin (define a 9) (define b 10) (if (= a b) a b))";
        Expression result = run(program);
        REQUIRE(result == Expression(10.));
    }
    
}

TEST_CASE( "Test Interpreter define with bool and single", "[interpreter]" ) {
    
    {
        std::string program = "(define a True)";
        Expression result = run(program);
        REQUIRE(result == Expression(true));
    }
    {
        std::string program = "(begin (define b True) (b))";
        Expression result = run(program);
        REQUIRE(result == Expression(true));
    }
    {
        std::string program = "(begin (define a 10) (b))";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
    
}

TEST_CASE( "Test Interpreter define with number and single", "[interpreter]" ) {
    
    {
        std::string program = "(define a 10)";
        Expression result = run(program);
        REQUIRE(result == Expression(10.));
    }
    {
        std::string program = "(begin (define b 10) (b))";
        Expression result = run(program);
        REQUIRE(result == Expression(10.));
    }
    {
        std::string program = "(begin (define b 10) (define a b))";
        Expression result = run(program);
        REQUIRE(result == Expression(10.));
    }
    {
        std::string program = "(begin (define a True) (if a 1 2))";
        Expression result = run(program);
        REQUIRE(result == Expression(1.));
    }
}

TEST_CASE( "Test Interpreter begin in begin", "[interpreter]" ) {
    
    {
        std::string program = "(begin (begin (define a 10)))";
        Expression result = run(program);
        REQUIRE(result == Expression(10.));
    }
    {
        std::string program = "(begin (begin (define a 10)) a)";
        Expression result = run(program);
        REQUIRE(result == Expression(10.));
    }
    
}

TEST_CASE( "Test Interpreter bool define with and or", "[interpreter]" ) {
    
    {
        std::string program = "(begin (define a True) (and a False))";
        Expression result = run(program);
        REQUIRE(result == Expression(false));
    }
    {
        std::string program = "(begin (define a True) (define b False) (or a b))";
        Expression result = run(program);
        REQUIRE(result == Expression(true));
    }
    {
        std::string program = "(begin (define a True) (define b a) (or a b))";
        Expression result = run(program);
        REQUIRE(result == Expression(true));
    }
    {
        std::string program = "(begin (define a True) (not a))";
        Expression result = run(program);
        REQUIRE(result == Expression(false));
    }
    {
        std::string program = "(begin (define a True) a)";
        Expression result = run(program);
        REQUIRE(result == Expression(true));
    }
    
}

TEST_CASE( "Test Interpreter number of () not right", "[interpreter]" ) {
    
    {
        
        std::vector<std::string> programs =
        {
            "(True))",
            "((True)",
            "True)",
            "(True",
            "True))"
            "(True("
        };
        for(auto s : programs)
        {
            Interpreter interp;
            
            std::istringstream iss(s);
            
            bool ok = interp.parse(iss);
            REQUIRE(!ok);
        }
    }
}
TEST_CASE("Test drawlist", "[interpreter]") {
    
    {
        std::string program = "(draw (point 1 2) (point 0 0))";
        std::istringstream iss(program);
        Interpreter interp;
        
        REQUIRE(interp.parse(iss));
        REQUIRE(interp.eval() == Expression());
        REQUIRE(interp.drawlist[0] == Expression(make_tuple(1.,2.)));
        REQUIRE(interp.drawlist[1] == Expression(make_tuple(0.,0.)));
    }
}

TEST_CASE("Test draw define", "[interpreter]") {
    
    {
        std::string program = "(begin (define a (point 0 0)) (draw a))";
        std::istringstream iss(program);
        Interpreter interp;
        
        REQUIRE(interp.parse(iss));
        REQUIRE(interp.eval() == Expression());
        REQUIRE(interp.drawlist[0] == Expression(make_tuple(0.,0.)));
    }
}
TEST_CASE("Test point", "[interpreter]")
{
    {
        std::string program = "(begin (define a 0) (point a 0))";
        std::istringstream iss(program);
        Interpreter interp;
        
        REQUIRE(interp.parse(iss));
        REQUIRE(interp.eval() == Expression(make_tuple(0.,0.)));
    }
    {
        std::string program = "(begin (define a (point 0 0)) a)";
        std::istringstream iss(program);
        Interpreter interp;
        
        REQUIRE(interp.parse(iss));
        REQUIRE(interp.eval() == Expression(make_tuple(0.,0.)));
    }
    {
        std::string program = "(begin (define a (point 0 0)) (define b a))";
        std::istringstream iss(program);
        Interpreter interp;
        
        REQUIRE(interp.parse(iss));
        REQUIRE(interp.eval() == Expression(make_tuple(0.,0.)));
    }
}
TEST_CASE("Test line", "[interpreter]")
{
    {
        std::string program = "(begin (define a (point 0 0)) (line a (point 1 0)))";
        std::istringstream iss(program);
        Interpreter interp;
        
        REQUIRE(interp.parse(iss));
        REQUIRE(interp.eval() == Expression(make_tuple(0.,0.), make_tuple(1.,0.)));
    }
}
TEST_CASE("Test arc/sin/cos", "[interpreter]") {
    {
        std::string program = "(begin (define a (point 0 0)) (arc a (point 1 0) 0))";
        std::istringstream iss(program);
        Interpreter interp;
        REQUIRE(interp.parse(iss));
        REQUIRE(interp.eval() == Expression(make_tuple(0.,0.), make_tuple(1.,0.),0));
    }
    {
        std::string program = "(sin 3)";
        std::istringstream iss(program);
        Interpreter interp;
        REQUIRE(interp.parse(iss));
        double result = sin(3);
        REQUIRE(interp.eval() == Expression(result));
    }
    {
        std::string program = "(cos 3)";
        std::istringstream iss(program);
        Interpreter interp;
        REQUIRE(interp.parse(iss));
        double result = cos(3);
        REQUIRE(interp.eval() == Expression(result));
    }
    {
        std::string program = "(begin (define a 1)(arctan a 3))";
        std::istringstream iss(program);
        Interpreter interp;
        REQUIRE(interp.parse(iss));
        double result = atan2(1,3);
        REQUIRE(interp.eval() == Expression(result));
    }
    {
        std::string program = "(begin (define a (point 0 0)))";
        std::istringstream iss(program);
        Interpreter interp;
        REQUIRE(interp.parse(iss));
        REQUIRE(interp.eval() == Expression(make_tuple(0.,0.)));
        std::string program1 = "(a)";
        std::istringstream iss1(program1);
        REQUIRE(interp.parse(iss1));
        REQUIRE(interp.eval() == Expression(make_tuple(0.,0.)));
    }
}
TEST_CASE( "Test point error", "[interpreter]" )
{
    {
        std::string program = "(point True 0)";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
    {
        std::string program = "(point)";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
    
}
TEST_CASE( "Test arc error", "[interpreter]" )
{
    {
        std::string program = "(arc 0)";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
    {
        std::string program = "(arc 0 0 0)";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
    {
        std::string program = "(arc (point 0 0) a True)";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
    
    {
        std::string program = "(arc (point 0 0) (point 0 0) True)";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
}
TEST_CASE( "Test draw/line error", "[interpreter]" ) {
    
    
    {
        std::string program = "(begin a)";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
    
    {
        std::string program = "(draw True)";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
    {
        std::string program = "(draw)";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
    {
        std::string program = "(line True 0)";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
    {
        std::string program = "(line 0)";
        Interpreter interp;
        std::istringstream iss(program);
        bool ok = interp.parse(iss);
        REQUIRE(ok);
        REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
    }
    }
