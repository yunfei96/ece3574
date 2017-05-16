#include "expression.hpp"

// Default construct an Expression of type None
Expression::Expression()
{
    type = "None";
    number_value = 0;
    bool_value = false;
    symbol = "";
    
}

// Construct an Expression with a single Boolean atom with value
Expression::Expression(bool value)
{
    type = "bool";
    number_value = 0;
    bool_value = value;
    symbol = "";
    
}

// Construct an Expression with a single Number atom with value
Expression::Expression(double value)
{
    type = "number";
    number_value = value;
    bool_value = false;
    symbol = "";
    
}

// Construct an Expression with a single Symbol atom with value
Expression::Expression(const std::string & value)
{
    type = "symbol";
    number_value = 0;
    bool_value = false;
    symbol = value;
    
    
}

// Equality operator for two Expressions, two expressions are equal if the have the same
// type, atom value, and number of arguments
bool Expression:: operator==(const Expression & exp) const noexcept
{
    bool equal = (exp.type == type) && (exp.number_value == number_value) && (exp.bool_value == bool_value) && (exp.symbol == symbol);
    return equal;
}
