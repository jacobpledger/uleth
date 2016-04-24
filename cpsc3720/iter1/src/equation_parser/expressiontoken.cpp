#include "expressiontoken.h"

/*!
constructor
*/
ExpressionToken::ExpressionToken(Type_t t, Value_t v, Column_t c) : type(t), value(v), column(c)
{
}

/*!
returns the symbol of this token (if it is an operator)
*/
ExpressionToken::Symbol_t ExpressionToken::Symbol(void) const
{
    return Expression_Token_Type_Symbol(type);
}

/*!
returns the precedence of this token (if it is an operator)
*/
ExpressionToken::Precedence_t ExpressionToken::Precedence(void) const
{
    return Expression_Token_Type_Precedence(type);
}

ExpressionToken::Column_t ExpressionToken::Column(void) const
{
    return column;
}

/*!
returns true if this token is an operator
*/
bool ExpressionToken::Is_Operator(void) const
{
    return Precedence() > 0;
}

/*!
returns true if this token is an operand
*/
bool ExpressionToken::Is_Operand(void) const
{
    return type == ID || type == BOOLEAN;
}

/*!
given a token type representing an operator, returns the corresponding symbol

if the token type is not an operator, returns 0
*/
ExpressionToken::Symbol_t Expression_Token_Type_Symbol(ExpressionToken::Type_t type)
{
    switch(type)
    {
    case ExpressionToken::OP_LP:  return '(';
    case ExpressionToken::OP_RP:  return ')';
    case ExpressionToken::OP_NOT: return '~';
    case ExpressionToken::OP_AND: return '*';
    case ExpressionToken::OP_OR:  return '+';
    case ExpressionToken::OP_XOR: return '^';
    case ExpressionToken::OP_EOL: return '=';
    default: return 0;
    }
}

/*!
given a token type representing an operator, returns the corresponding precedence (higher the value, the higher the precedence)

if the token type is not an operator, return 0
*/
ExpressionToken::Precedence_t Expression_Token_Type_Precedence(ExpressionToken::Type_t type)
{
    switch(type)
    {
    case ExpressionToken::OP_LP:  return 5;
    case ExpressionToken::OP_NOT: return 4;
    case ExpressionToken::OP_AND: return 3;
    case ExpressionToken::OP_OR:  return 2;
    case ExpressionToken::OP_XOR: return 2;
    case ExpressionToken::OP_RP:  return 1;
    case ExpressionToken::OP_EOL: return 1;
    default: return 0;
    }
}

