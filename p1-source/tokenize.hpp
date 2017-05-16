#include <iostream>
#include <string>
#include <vector>
using namespace std;

class token
{
public:
    vector<string> futher_sep(vector<string> &nospace);
    vector<string> token_result(istream & expression);
private:
    vector<string> wellsep;
};
