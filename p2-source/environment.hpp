#ifndef ENVIR
#define ENVIR
#include "expression.hpp"
#include <exception>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include "interpreter_semantic_error.hpp"
#define is_numop(c) (c == "+") || (c == "-") || (c == "*") || (c == "/") || (c == "sin") || (c == "cos") || (c == "arctan")
#define is_boolop(c) (c == "and") || (c == "or") || (c == "not") || (c == "=") || (c == ">") || (c == "<") || (c == ">=") || (c == "<=")
#define is_number(c) (c == '0' || c == '1' || c == '2'|| c == '3'|| c == '4'|| c == '5'|| c == '6'|| c == '7'|| c == '8'|| c == '9')
#define is_specialop(c) (c == "if") || (c == "begin") || (c == "define")
#define is_draw(c) (c == "point") || (c == "line") || (c == "arc")
using namespace std;

class envir
{
public:
    envir();
    //------------cal func--------
    double number(vector<Expression> args);
    bool which_bool(vector<Expression> args);
    Expression which_draw(vector<Expression> args);
    //-------------return double---------
    double add(vector<Expression> input);
    double sub(vector<Expression> input);
    double times(vector<Expression> input);
    double divid(vector<Expression> input);
    double _sin(vector<Expression> input);
    double _cos(vector<Expression> input);
    double arctan(vector<Expression> input);
    //-------------special--------------
    vector<Expression> draw(vector<Expression> input);
    Expression define(vector<Expression> input);
    Expression begin(vector<Expression> input);
    Expression _if(vector<Expression> input);
    Expression single(vector<Expression> input);
    //------------return bool-----------
    bool _and(vector<Expression> input);
    bool _or(vector<Expression> input);
    bool _not(vector<Expression> input);
    bool small(vector<Expression> input);
    bool small_equal(vector<Expression> input);
    bool larger(vector<Expression> input);
    bool larger_equal(vector<Expression> input);
    bool equal(vector<Expression> input);
    //------------draw---------------------
    Expression point(vector<Expression> input);
    Expression line(vector<Expression> input);
    Expression arc(vector<Expression> input);
    //the environment set up
    map<string, bool> bool_envir;
    map<string,double> environment;
    map<string, Expression> exp_envir;
private:
    //helper
    void build_string_vector(vector<Expression> &input,vector<double> &result);
    void not_found(string key);
    void not_found_bool(string key);
    void not_found_exp(string key);
};

#endif
