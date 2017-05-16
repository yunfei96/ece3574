#ifndef EXP
#define EXP
#include <iostream>
#include <string>
#include <tuple>
using namespace std;

class Expression
{
public:
    // Default construct an Expression of type None
    Expression();
    
    // Construct an Expression with a single Boolean atom with value
    Expression(bool value);
    
    // Construct an Expression with a single Number atom with value
    Expression(double value);
    
    // Construct an Expression with a single Symbol atom with value
    Expression(const std::string & value);
    
    // Equality operator for two Expressions, two expressions are equal if the have the same
    // type, atom value, and number of arguments
    bool operator==(const Expression & exp) const noexcept;
    
    // Construct an Expression with a single Point atom with value
    Expression(std::tuple<double,double> value);
    
    // Construct an Expression with a single Line atom with starting
    // point start and ending point end
    Expression(std::tuple<double,double> start,
               std::tuple<double,double> end);
    
    // Construct an Expression with a single Arc atom with center
    // point center, starting point start, and spanning angle angle in radians
    Expression(std::tuple<double,double> center,
               std::tuple<double,double> start,
               double angle);
    string type;
    string symbol;
    tuple<double,double> start{0,0};
    tuple<double,double> end{0,0};
    tuple<double,double> center{0,0};
    double angle;
    double number_value;
    bool bool_value;
    
};
#endif
