#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include <stack>
#include <string>
#include <vector>
using namespace std;

#include "expressiontoken.h"

class ExpressionParser
{
public:
    typedef char ExpressionStringSymbol_t;
    typedef string ExpressionString_t;
    typedef ExpressionString_t::size_type ExpressionIndex_t;

    typedef char VariableNameSymbol_t;
    typedef string VariableName_t;
    typedef vector<VariableName_t> VariableNames_t;
    typedef VariableNames_t::size_type VariableIndex_t;

    typedef bool VariableValue_t;
    typedef vector<VariableValue_t> VariableValues_t;

    //! Assigns the expression string to be evaluated.
    void Set_Expression_String(ExpressionString_t);
    //! Returns the expression string to be evaluated.
    ExpressionString_t Get_Expression_String(void) const;

    //! Returns the number of variables that have been defined.
    VariableIndex_t Get_Number_Of_Variables(void) const;

    //! Assigns the variable names to be used in the expression.
    void Set_Variable_Names(VariableNames_t);
    //! Returns the variable names to be used in the expression.
    VariableNames_t Get_Variable_Names(void) const;

    //! Assigns the variable values to be used in the expression.
    void Set_Variable_Values(VariableValues_t);
    //! Returns the variable values to be used in the expression.
    VariableValues_t Get_Variable_Values(void) const;

    //! Returns the result of evaluating the expression.
    bool Evaluate_Expression(void);

private:
    typedef vector<ExpressionToken> TokenStream_t;
    typedef stack<ExpressionToken> TokenStack_t;

    //! Debugging function. Displays a representation of the tokens found in the argument.
    void Print_Token_Stream_(TokenStream_t) const;

    //! Parses the expression to allow for its evaluation. Returns true on success, and false on failure.
    bool Parse_Expression_(void);

    //! Returns a TokenStream_t containing the tokenized representation of expression.
    TokenStream_t Tokenize_Expression_(ExpressionString_t);
    //! Returns a TokenStream_t containing the postfix representation of the infix argument. Also checks the syntax of the stream.
    TokenStream_t Convert_Infix_To_Postfix_With_Error_Checking_(TokenStream_t);
    //! Returns a TokenStream_t containing the postfix representation of the infix argument.
    TokenStream_t Convert_Infix_To_Postfix_(TokenStream_t);

    //! Returns the index of the first variable with a name matching the argument in variable_names_. If no match is found, returns Number_Of_Variables_().
    VariableIndex_t Get_Variable_Index_(VariableName_t) const;
    //! Assigns the name of a single variable. Returns true if successful.
    bool Set_Variable_Name_(VariableIndex_t, VariableName_t);
    //! Returns the name of a single variable. Returns an empty string if unsuccessful.
    VariableName_t Get_Variable_Name_(VariableIndex_t) const;

    //! Tests if the argument, an expression string, is parsable by the tokenizer.
    bool Expression_String_Is_Parsable_(ExpressionString_t) const;
    //! Tests if the argument, an expression string, contains only valid symbols.
    bool Expression_String_Symbols_Are_All_Valid_(ExpressionString_t) const;
    //! Tests if the argument, an expression string symbol, is allowed in an expression string.
    bool Expression_String_Symbol_Is_Valid_(ExpressionStringSymbol_t) const;

    //! Tests if the argument, a variable name, is parsable by the tokenizer.
    bool Variable_Name_Is_Parsable_(VariableName_t) const;
    //! Tests if the argument, a variable name, contains only valid symbols.
    bool Variable_Name_Symbols_Are_All_Valid_(VariableName_t) const;
    //! Tests if the argument, a variable name symbol, is allowed in a variable name.
    bool Variable_Name_Symbol_Is_Valid_(VariableNameSymbol_t) const;

    //! Indicates that the expression was parsed successfully and thus, Evaluate() may be called.
    bool expression_string_is_parsed_;

    //! The expression string to be evaluated.
    ExpressionString_t expression_string_;

    //! The variable names used in the expression evaluation.
    VariableNames_t variable_names_;
    //! The variable values used in the expression evaluation.
    VariableValues_t variable_values_;

    //! The infix representation of the expression after it is parsed successfully.
    TokenStream_t infix_expression_;
    //! The postfix representation of the expression after it is parsed successfully.
    TokenStream_t postfix_expression_;
};

#endif
