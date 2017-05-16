#ifndef INTER
#define INTER
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include "expression.hpp"
#include "tokenize.hpp"
#include "environment.hpp"
#include <vector>
#include <sstream>
#include <iomanip>
#include <exception>
#include "interpreter_semantic_error.hpp"

using namespace std;

struct list
{
    vector<list> node;
    Expression atom;
    
};

class Interpreter
{
public:
    //init an empty AST
    Interpreter();
    
    // Given a vtscript program as a std::istream, attempt to parse into an internal AST
    // return true on success, false on failure
    bool parse(std::istream & expression) noexcept;
    
    // Evaluate the current AST and return the resulting Expression
    // throws InterpreterSemanticError if a semantic error is encountered
    // the exception message string should document the nature of the semantic error
    Expression eval();
private:
    list result;
    envir environment;
    //recursive helper
    list build_tree(vector<string> &token);
    void eval_tree(list &input, envir &environent_set_up);
    double string_to_double(string input);
    bool fail_flag = false;
    void calculate(list &input, envir &environent_set_up, vector<Expression> args);
    void special(list &input, envir &environent_set_up, int i);
    list to_list(string tokens);
};
#endif
