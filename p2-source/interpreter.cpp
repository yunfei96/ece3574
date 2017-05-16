#include "interpreter.hpp"


Interpreter::Interpreter()
{
    Expression atom;
    result.node.clear();
    fail_flag = false;
}

//-----------------------------build ast tree-----------------------
bool Interpreter::parse(std::istream & expression) noexcept
{
    token token;
    vector<string> input;
    input = token.token_result(expression);
    //test if there is (
    int find_left=0;
    int find_right=0;
    for(int i =0; i<input.size();i++)
    {
        if(input[i] == "(")
        {
            find_left++;
        }
        if(input[i] == ")")
        {
            find_right++;
        }
    }
    if(find_right == find_left && find_right != 0 )
    {
       //build the tree
        result = build_tree(input);
    }
    //return false if input is empty or no (
    bool succ = !(fail_flag == true || !input.empty() || find_right != find_left || find_right == 0);
    return succ;
}

_list Interpreter::build_tree(vector<string> &token)
{
    //take the first string
    string tokens = token[0];
    token.erase(token.begin());
    //if is (, add a node
    if( tokens == "(")
    {
        _list list;
        int count = 0;
        while(token[0] != ")" )
        {
            count++;
//            //push the object
//            if(fail_flag == true)
//                return list;
            list.node.push_back(build_tree(token));
        }
        //pop )
        if(count == 0)
        {
            fail_flag = true;
        }
        token.erase(token.begin());
        return list;
    }
    else
    {
        //return list
        return to_list(tokens);
    }
}


//-------------------------eval and eval recursive-------------------

Expression Interpreter::eval()
{
    Expression return_result;
    eval_tree(result, environment);
    return_result = result.atom;
    return return_result;
    
}

void Interpreter::eval_tree(_list &input, envir &environent_set_up)
{
    //while there are input
    while(input.node.size() != 0 )
    {
        //loop node
        for(int i=0; i < input.node.size(); i++)
        {
            //if node have sub tree
            if(input.node.size() != 0)
            {
                //if is special condition
                if(input.node[0].atom.symbol == "if")
                {
                    special(input, environent_set_up, i);
                }
                else //find its child until no sub tree(inorder)
                    eval_tree(input.node[i], environent_set_up);
            }
        }
        //no node(post order)
        vector<Expression> args;
        for(int i=0; i < input.node.size(); i++)
        {
            args.push_back(input.node[i].atom);
            
        }
        calculate(input, environent_set_up, args);
    }
}

//--------------------------------------helper func---------------------------------
double Interpreter::string_to_double(string input)
{
    int add = 0;
    int minus = 0;
    int dot = 0;
    int e = 0;
    for(int i=0; i<input.size();i++)
    {
        if(input[i] == '+')
        {
            add++;
        }
        if(input[i] == '-')
        {
            minus++;
        }
        if(input[i] == '.')
        {
            dot++;
        }
        if(input[i] == 'e')
        {
            e++;
        }
        if (is_number(input[i]) || input[i] == '+' || input[i] == '-' || input[i] == '.' || input[i] == 'e')
        {
            if((add <= 2) && (minus <= 2) && (dot <= 1) && (e <= 1))
            {
                continue;
            }
        }
        fail_flag = true;
        return 0;
    }
    string::size_type sz;
    double result = std::stod (input,&sz);
    return result;
}

//call calculation function
void Interpreter::calculate(_list &input, envir &environent_set_up, vector<Expression> args)
{
    if(is_numop(input.node[0].atom.symbol))
    {
        double result;
        result = environent_set_up.number(args);
        input.node.clear();
        Expression res(result);
        input.atom = res;
        
    }
    else if(is_boolop(input.node[0].atom.symbol))
    {
        bool result;
        result = environent_set_up.which_bool(args);
        input.node.clear();
        Expression res(result);
        input.atom = res;
    }
    else if(is_draw(input.node[0].atom.symbol))
    {
        Expression result;
        result = environent_set_up.which_draw(args);
        input.node.clear();
        input.atom = result;
    }
    else if(input.node[0].atom.symbol == "draw")
    {
        vector<Expression> temp;
        Expression result;
        input.node.clear();
        input.atom = result;
        temp = environent_set_up.draw(args);
        for(int i=1; i < temp.size();i++)
        {
            drawlist.push_back(temp[i]);
        }
        
    }
    else if(input.node[0].atom.symbol == "if")
    {
        Expression result;
        result = environent_set_up._if(args);
        input.node.clear();
        input.atom = result;
    }
    else if(input.node[0].atom.symbol == "define")
    {
        Expression result;
        result = environent_set_up.define(args);
        input.node.clear();
        input.atom = result; //void function, just return none
    }
    else if(input.node[0].atom.symbol == "begin")
    {
        Expression result;
        result = environent_set_up.begin(args);
        input.node.clear();
        input.atom = result;
    }
    else if(input.node.size() == 1)
    {
        Expression result;
        result = environent_set_up.single(args);
        input.node.clear();
        input.atom = result;
    }
    else
    {
        InterpreterSemanticError error("no such procedure");
        throw error;
    }
}

void Interpreter::special(_list &input, envir &environent_set_up, int i)
{
    //update first node
    if(input.node[1].node.size() == 0)
    {
        vector<Expression> in;
        in.push_back(input.node[1].atom);
        Expression result;
        result = environent_set_up.single(in);
        input.node[1].atom = result;
    }
    else
    {
       eval_tree(input.node[1], environent_set_up);
    }
    //if true eval second node, clean third node
    if(input.node[1].atom.bool_value == true)
    {
        eval_tree(input.node[2], environent_set_up);
        input.node[3].node.clear();
        //after set up
        eval_tree(input.node[i], environent_set_up);
    }
    //if false eval third node, clean second node
    else
    {
        eval_tree(input.node[3], environent_set_up);
        input.node[2].node.clear();
        //after set up
        eval_tree(input.node[i], environent_set_up);
    }
}

_list Interpreter::to_list(string tokens)
{
    _list numlist;
    if(tokens == "True")
    {
        Expression in(true);
        numlist.atom = in;
        
    }
    else if(tokens == "False")
    {
        Expression in(false);
        numlist.atom = in;
    }
    else if(is_number(tokens[0]) || ((tokens[0] == '-' || tokens[0] == '+') && (tokens.size() != 1)))
    {
        
        Expression in(string_to_double(tokens));
        numlist.atom = in;
    }
    else
    {
        Expression in(tokens);
        numlist.atom = in;
    }
    return numlist;}
