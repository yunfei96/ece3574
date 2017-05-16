#include "environment.hpp"

envir::envir()
{
    environment["pi"] = atan2(0, -1);
}

//----------------call func-------------------
double envir::number(vector<Expression> args)
{
    if(args[0].symbol == "+")
    {
        args.erase(args.begin());
        return add(args);
    }
    else if(args[0].symbol== "-")
    {
        args.erase(args.begin());
        return sub(args);
    }
    else if(args[0].symbol == "/")
    {
        args.erase(args.begin());
        return divid(args);
    }
    else
    {
        args.erase(args.begin());
        return times(args);
    }
}
//
bool envir::which_bool(vector<Expression> args)
{
    if(args[0].symbol == "and")
    {
        args.erase(args.begin());
        return _and(args);
    }
    else if(args[0].symbol == "or")
    {
        args.erase(args.begin());
        return _or(args);
    }
    else if(args[0].symbol == "not")
    {
        args.erase(args.begin());
        return _not(args);
    }
    else if(args[0].symbol == "<")
    {
        args.erase(args.begin());
        return small(args);
    }
    else if(args[0].symbol == "<=")
    {
        args.erase(args.begin());
        return small_equal(args);
    }
    else if(args[0].symbol == ">")
    {
        args.erase(args.begin());
        return larger(args);
    }
    else if(args[0].symbol == ">=")
    {
        args.erase(args.begin());
        return larger_equal(args);
    }
    else
    {
        args.erase(args.begin());
        return equal(args);
    }
}
//
//--------------------return bool---------------------
bool envir::_and(vector<Expression> input)
{
    if(input.size() == 1)
    {
        InterpreterSemanticError error("args number not right");
        throw error;
    }
    for(int i =0; i<input.size(); i++)
    {
        if(input[i].type != "bool" && input[i].type != "symbol")
        {
            InterpreterSemanticError error("args type not right");
            throw error;
        }
        if(input[i].type == "symbol")
        {
            not_found_bool(input[i].symbol);
            input[i].bool_value = bool_envir.find(input[i].symbol) -> second;
        }
        if(input[i].bool_value == true)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
//
bool envir::_or(vector<Expression> input)
{
    if(input.size() == 1)
    {
        InterpreterSemanticError error("args number not right");
        throw error;
    }
    for(int i=0; i<input.size();i++)
    {
        if(input[i].type != "bool" && input[i].type != "symbol")
        {
            InterpreterSemanticError error("args type not right");
            throw error;
        }
        if(input[i].type == "symbol")
        {
            not_found_bool(input[i].symbol);
            input[i].bool_value = bool_envir.find(input[i].symbol) -> second;
        }
        if(input[i].bool_value == true )
        {
            return true;
        }
    }
    return false;
    
}
//
bool envir::_not(vector<Expression> input)
{
    if(input.size() != 1)
    {
        InterpreterSemanticError error("args number not right");
        throw error;
    }
    if(input[0].type != "bool" && input[0].type != "symbol")
    {
        InterpreterSemanticError error("args type not right");
        throw error;
    }
    if(input[0].type == "symbol")
    {
        not_found_bool(input[0].symbol);
        input[0].bool_value = bool_envir.find(input[0].symbol) -> second;
    }
    if(input[0].bool_value == true)
    {
        return false;
    }
    else
    {
        return true;
    }
}
//
bool envir::small(vector<Expression> input)
{
    vector<double> result;
    build_string_vector(input, result);
    if(result[0] < result[1])
    {
        return true;
    }
    else
    {
        return false;
    }
}
//
bool envir::small_equal(vector<Expression> input)
{
    vector<double> result;
    build_string_vector(input, result);
    if(result[0] <= result[1])
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool envir::larger(vector<Expression> input)
{
    vector<double> result;
    build_string_vector(input, result);
    if(result[0] > result[1])
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool envir::larger_equal(vector<Expression> input)
{
    vector<double> result;
    build_string_vector(input, result);
    if(result[0] >= result[1])
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool envir::equal(vector<Expression> input)
{
    vector<double> result;
    build_string_vector(input, result);
    if(result[0] == result[1])
    {
        return true;
    }
    else
    {
        return false;
    }
}
////-----------------------------special-------------------------------

Expression envir::_if(vector<Expression> input)
{
    input.erase(input.begin()); //delete if
    if(input.size() != 3 || (input[0].type != "symbol" && input[0].type != "bool"))
    {
        InterpreterSemanticError error("args number not right");
        throw error;
    }
    if(input[0].bool_value == true)
    {
        if(input[1].type == "number" || input[1].type == "bool")
        {
            return input[1];
        }
        not_found(input[1].symbol);
        double val = environment.find(input[1].symbol) -> second;
        Expression result(val);
        return result;
    }
    else
    {
        if(input[2].type == "number" || input[2].type == "bool")
        {
            return input[2];
        }
        not_found(input[2].symbol);
        double val = environment.find(input[2].symbol) -> second;
        Expression result(val);
        return result;
    }
}

Expression envir::begin(vector<Expression> input)
{
    input.erase(input.begin());
    vector<Expression> result;
    for(int i=0; i<input.size();i++)
    {
        result.push_back(input[i]);
    }
    if(result.back().type == "number" || result.back().type == "bool")
    {
        return result.back();
    }
    else
    {
        not_found(result.back().symbol);
        double val = environment.find(result.back().symbol) -> second;
        Expression result(val);
        return result;
    }
}

Expression envir::single(vector<Expression> input)
{
    double value;
    Expression result;
    if (input[0].type == "symbol")
    {
        if(environment.find(input[0].symbol) == environment.end())
        {
            if(bool_envir.find(input[0].symbol) != bool_envir.end())
            {
                bool val = bool_envir.find(input[0].symbol)-> second;
                Expression temp(val);
                result = temp;
                return result;
            }
            InterpreterSemanticError error("not defined");
            throw error;
        }
        else
        {
            value = environment.find(input[0].symbol) -> second;
            Expression temp(value);
            result = temp;
        }
        
    }
    else
    {
        result = input[0];
    }
    return result;
}

Expression envir::define(vector<Expression> input)
{
    input.erase(input.begin());
    if(input.size() != 2)
    {
        InterpreterSemanticError error("args number not right");
        throw error;
    }
    string v_name;
    double val;
    bool bool_val;
    v_name = input[0].symbol;
    if(input[0].type == "number" || input[0].type == "bool")
    {
        InterpreterSemanticError error("args type not right");
        throw error;
    }
    if(is_number(v_name[0]) || is_boolop(v_name) || is_numop(v_name) || is_specialop(v_name) || environment.find(v_name) != environment.end() || bool_envir.find(v_name) != bool_envir.end())
    {
        InterpreterSemanticError error("re-define");
        throw error;
    }
    
    if(input[1].type == "number")
    {
        val = input[1].number_value;
        environment[v_name] = val;
        Expression result(val);
        return result;
    }
    else if(input[1].type == "symbol")
    {
        if(environment.find(input[1].symbol) == environment.end())
        {
            if(bool_envir.find(input[1].symbol) != bool_envir.end())
            {
                bool val = bool_envir.find(input[1].symbol)-> second;
                bool_envir[v_name] = val;
                Expression temp(val);
                return temp;
            }
            InterpreterSemanticError error("not defined");
            throw error;
        }
        else
        {
            val = environment.find(input[1].symbol) -> second;
            environment[v_name] = val;
            Expression result(val);
            return result;
        }
        
    }
    else
    {
        bool_val = input[1].bool_value;
        bool_envir[v_name] = bool_val;
        Expression result(bool_val);
        return result;
    }
}


//-------------------------return double--------------------------

double envir::times(vector<Expression> input)
{
    double result=1;
    if(input.size() == 1)
    {
        InterpreterSemanticError error("args number not right");
        throw error;
    }
    for(int i=0; i < input.size();i++)
    {
        if(input[i].type == "number") //is number
        {
            result = (input[i].number_value)*result;
        }
        else if(input[i].type == "symbol") //is var
        {
            not_found(input[i].symbol);
            result = result*(environment.find(input[i].symbol) -> second);
        }
        else
        {
            InterpreterSemanticError error("args type not right");
            throw error;
        }
    }
    return result;
}

double envir::divid(vector<Expression> input)
{
    vector<double> result;
    if(input.size() == 2)
    {
        //sub
        for(int i=0; i < 2; i++)
        {
            if(input[i].type == "number") //is number
            {
                result.push_back(input[i].number_value);
            }
            else if(input[i].type == "symbol") //is var
            {
                not_found(input[i].symbol);
                result.push_back((environment.find(input[i].symbol) -> second));
            }
            else
            {
                InterpreterSemanticError error("args type not right");
                throw error;
            }
        }
    }
    else
    {
        InterpreterSemanticError error("args number not right");
        throw error;
    }
    return result[0] / result[1];
}

double envir::add(vector<Expression> input)
{
    double sum = 0;
    if(input.size() == 0)
    {
        InterpreterSemanticError error("args number not right");
        throw error;
    }
    for(int i=0; i < input.size();i++)
    {
        if(input[i].type == "number") //is number
        {
            sum = input[i].number_value + sum;
        }
        else if(input[i].type == "symbol") //is var
        {
            not_found(input[i].symbol);
            sum = sum + (environment.find(input[i].symbol) -> second);
        }
        else
        {
            InterpreterSemanticError error("args type not right");
            throw error;
        }
    }
    return sum;
}

double envir::sub(vector<Expression> input)
{
    //if sub
    if(input.size() == 2)
    {
        vector<double> result;
        for(int i=0; i < 2; i++)
        {
            if(input[i].type == "number") //is number
            {
                result.push_back((input[i].number_value));
            }
            else if(input[i].type == "symbol") //is var
            {
                not_found(input[i].symbol);
                result.push_back((environment.find(input[i].symbol) -> second));
            }
            else
            {
                InterpreterSemanticError error("args type not right");
                throw error;
            }
        }
        return result[0] - result[1];
    }
    //if negate
    else if(input.size() == 1)
    {
        double result = 0;
        if(input[0].type == "number") //is number
        {
            result = input[0].number_value;
        }
        else if(input[0].type == "symbol") //is var
        {
            not_found(input[0].symbol);
            result = environment.find(input[0].symbol) -> second;
        }
        else
        {
            InterpreterSemanticError error("args type not right");
            throw error;
        }
        return -result;

    }
    else
    {
        InterpreterSemanticError error("args number not right");
        throw error;
    }
}

////------------------helper func--------------------
void envir::build_string_vector(vector<Expression> &input,vector<double> &result)
{
    if(input.size() != 2)
    {
        InterpreterSemanticError error("args number not right");
        throw error;
    }
    for(int i=0; i < input.size(); i++)
    {
        if(input[i].type == "number") //is number
        {
            result.push_back(input[i].number_value);
        }
        else if(input[i].type == "symbol") //is var
        {
            not_found(input[i].symbol);
            result.push_back((environment.find(input[i].symbol) -> second));
        }
        else
        {
            InterpreterSemanticError error("args type not right");
            throw error;
        }
    }
}

void envir::not_found(string key)
{
    if(environment.find(key) == environment.end())
    {
        InterpreterSemanticError error("not defined");
        throw error;
    }
}

void envir::not_found_bool(string key)
{
    if(bool_envir.find(key) == bool_envir.end())
    {
        InterpreterSemanticError error("not defined");
        throw error;
    }
}
