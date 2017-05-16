#include "expression.hpp"

// Default construct an Expression of type None
Expression::Expression()
{
    type = "None";
    number_value = 0;
    bool_value = false;
    symbol = "";
    angle = 0;
}

// Construct an Expression with a single Boolean atom with value
Expression::Expression(bool value)
{
    type = "bool";
    number_value = 0;
    bool_value = value;
    symbol = "";
    angle = 0;
}

// Construct an Expression with a single Number atom with value
Expression::Expression(double value)
{
    type = "number";
    number_value = value;
    bool_value = false;
    symbol = "";
    angle = 0;
}

// Construct an Expression with a single Symbol atom with value
Expression::Expression(const std::string & value)
{
    type = "symbol";
    number_value = 0;
    bool_value = false;
    symbol = value;
    angle = 0;
}

Expression::Expression(std::tuple<double,double> value)
{
    type = "point";
    number_value = 0;
    bool_value = false;
    symbol = "";
    angle = 0;
    start = value;
    
}

// Construct an Expression with a single Line atom with starting
// point start and ending point end
Expression::Expression(std::tuple<double,double> start,
           std::tuple<double,double> end)
{
    type = "line";
    number_value = 0;
    bool_value = false;
    symbol = "";
    angle = 0;
    this->start = start;
    this->end = end;
}

// Construct an Expression with a single Arc atom with center
// point center, starting point start, and spanning angle angle in radians
Expression::Expression(std::tuple<double,double> center,
           std::tuple<double,double> start,
           double angle)
{
    type = "arc";
    number_value = 0;
    bool_value = false;
    symbol = "";
    this->angle = angle;
    this->start = start;
    this->center = center;
}
// Equality operator for two Expressions, two expressions are equal if the have the same
// type, atom value, and number of arguments
bool Expression:: operator==(const Expression & exp) const noexcept
{
    bool equal = (exp.type == type) && (exp.number_value == number_value) && (exp.bool_value == bool_value) && (exp.symbol == symbol) && (exp.angle == angle) && (exp.center == center) && (exp.start == start) && (exp.end == end);
    return equal;
}
