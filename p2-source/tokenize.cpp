#include "tokenize.hpp"
#include <sstream>
#include <stack>
#include <fstream>
using namespace std;

vector<string> token::futher_sep(vector<string> &nospace)
{
    
    for(int i =0; i < nospace.size(); i++) //in vector
    {
        string word= "";
        for(int k =0;k < nospace[i].size();k++) //in string
        {
            
            if(nospace[i][k] == '(')
            {
                wellsep.push_back("(");
                
            }
            else if(nospace[i][k] == ')')
            {
                wellsep.push_back(")");
            }
            else
            {
                word = word +nospace[i][k];
                if((k+1) == nospace[i].size())
                {
                    wellsep.push_back(word);
                }
                else if(nospace[i][k+1] == ')')
                {
                    wellsep.push_back(word);
                    word = "";
                }
                else if(nospace[i][k+1] == '(')
                {
                    wellsep.push_back(word);
                    word = "";
                }
            }
        }
        
    }
    return wellsep;
}

vector<string> token::token_result(istream & expression)
{
    string pass;
    string comment;
    vector<string> no_space;
    vector<string> input;
    //token the stirng
    getline(expression, pass);
    while(!expression.fail())
    {
        if(pass[0] != ';')
        {
            string pass2;
            istringstream iss(pass);
            iss >> pass2;
            //remove space
            while(!iss.fail())
            {
                if(pass2 != ";")
                {
                    no_space.push_back(pass2);
                    iss >> pass2;
                }
                else
                {
                    while(!iss.fail())
                    {
                        iss >> comment;
                    }
                }
            }
        }
        getline(expression, pass);
        
    }
    input = futher_sep(no_space);
    return input;
}

