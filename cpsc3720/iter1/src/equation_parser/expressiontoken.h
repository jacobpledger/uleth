#ifndef EXPRESSIONTOKEN_H
#define EXPRESSIONTOKEN_H

//! ExpressionToken Class
/*!
This class is used by the ExpressionParser class to represent the individual lexical units making up an equation's input string (eg, AND, NOT, XOR, variable, left/right parentheses, etc...)
*/
class ExpressionToken
{
public:
    //! ExpressionToken Classification Type
    /*! Unless otherwise specified, the data member, value, is not applicable */
    enum Type_t
    {
        NULLTYPE = 256, /*!< This is the type assigned to a token that has been created using the default constructor */
        ID,       /*!< This token is a variable. Value: index of the variable in the variable_names_ and variable_values_ vectors */
        BOOLEAN,  /*!< This token is a boolean value. Value: zero represents false, otherwise true */
        OP_LP,    /*!< Left parenthesis operator. Overrides operator precedence. Nullary operator (arity: 0). */
        OP_RP,    /*!< Right parenthesis operator. Overrides operator precedence. Nullary operator (arity: 0). */
        OP_NOT,   /*!< NOT operator. Logical negation. Unary operator (arity: 1). */
        OP_AND,   /*!< AND operator. Logical conjunction. Binary operator (arity: 2). */
        OP_OR,    /*!< OR operator. Logical (inclusive) disjunction. Binary operator (arity: 2). */
        OP_XOR,   /*!< XOR operator. Logical (exclusive) disjunction. Binary operator (arity: 2). */
        OP_EOL    /*!< End-of-line operator. Indicates the end of an input sequence. Nullary operator (arity: 0). */
    };

    typedef int Value_t;
    typedef char Symbol_t;
    typedef int Precedence_t;
    typedef int Column_t;

    //! ExpressionToken Constructor
    /*!
    \param t (optional) The type of token, chosen from the enum Type_t (default value = NULLTYPE)
    \param v (optional) The value of the token, (default value = 0)
    \param c (optional) The column of the symbol beginning the token 
    */
    ExpressionToken(Type_t t = NULLTYPE, Value_t v = 0, Column_t c = 0);

    Symbol_t Symbol(void) const;
    Precedence_t Precedence(void) const;
    Column_t Column(void) const;

    //! Returns true if the token's type is an operator
    bool Is_Operator(void) const;
    //! Returns true if the token's type is an operand (ID, BOOLEAN)
    bool Is_Operand(void) const;

    Type_t type;
    Value_t value;
    Column_t column;
};

//! Given a token operator type, returns a token's symbol as a ExpressionToken::Symbol_t
/*!
    Note: This only works if the token is an operator, otherwise 0 is returned
    \param type The type of token to return the symbol of
*/
ExpressionToken::Symbol_t Expression_Token_Type_Symbol(ExpressionToken::Type_t type);

//! Given a token operator type, returns the precedence of the token
/*~
    Note: This only works if the token is an operator, otherwise 0 is returned
    \param type The type of token to return the precedence of
*/
ExpressionToken::Precedence_t Expression_Token_Type_Precedence(ExpressionToken::Type_t type);

#endif
