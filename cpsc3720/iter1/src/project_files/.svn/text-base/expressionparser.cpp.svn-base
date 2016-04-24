#include "expressionparser.h"
#include "expressiontoken.h"

#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

/*!
Note: Calling this function will force a reparse of the equation the next time evaluate() is called
\sa Parse_Expression_(), Evaluate_Expression()
*/
void ExpressionParser::Set_Expression_String(ExpressionString_t expression_string)
{
    expression_string_is_parsed_ = false;
    expression_string_ = expression_string;
}

ExpressionParser::ExpressionString_t ExpressionParser::Get_Expression_String(void) const
{
    return expression_string_;
}

/*!
returns the number of variable names that have been defined
*/
ExpressionParser::VariableIndex_t ExpressionParser::Get_Number_Of_Variables(void) const
{
    return variable_names_.size();
}

/*!
Note: Calling this function will force a reparse of the equation the next time evaluate is called
\sa Parse_Expression_(), Evaluate_Expression()
*/
void ExpressionParser::Set_Variable_Names(VariableNames_t variable_names)
{
    expression_string_is_parsed_ = false;
    variable_names_ = variable_names;
}

ExpressionParser::VariableNames_t ExpressionParser::Get_Variable_Names(void) const
{
    return variable_names_;
}

void ExpressionParser::Set_Variable_Values(VariableValues_t variable_values)
{
    variable_values_ = variable_values;
}

ExpressionParser::VariableValues_t ExpressionParser::Get_Variable_Values(void) const
{
    return variable_values_;
}

/*!
Will attempt to evaluate the expression it was given. If the expression it was given has not been parsed, then this will try to call the parser first.
\sa Parse_Expression_()
*/
bool ExpressionParser::Evaluate_Expression(void)
{
    if(!expression_string_is_parsed_)
    {
        // attempt to parse the expression and store the 
        bool parse_was_successful = Parse_Expression_();

        if(!parse_was_successful) return false;
    }

    bool function_result;

    TokenStack_t operands;
    ExpressionToken token;
    bool boolean_1;
    bool boolean_2;

    for(TokenStream_t::iterator token_iter = postfix_expression_.begin(); token_iter != postfix_expression_.end(); ++token_iter)
    {
        if(token_iter->Is_Operand())
        {
            operands.push(*token_iter);
        }
        else if(token_iter->Is_Operator())
        {
            switch(token_iter->type)
            {
            case ExpressionToken::OP_AND:
            case ExpressionToken::OP_XOR:
            case ExpressionToken::OP_OR:
                token = operands.top();
                operands.pop();

                if(token.type == ExpressionToken::ID)
                {
                    boolean_2 = variable_values_[token.value];
                }
                else if(token.type == ExpressionToken::BOOLEAN)
                {
                    boolean_2 = token.value != 0;
                }

                token = operands.top();
                operands.pop();

                if(token.type == ExpressionToken::ID)
                {
                    boolean_1 = variable_values_[token.value];
                }
                else if(token.type == ExpressionToken::BOOLEAN)
                {
                    boolean_1 = token.value != 0;
                }

                token.type = ExpressionToken::BOOLEAN;

                switch(token_iter->type)
                {
                case ExpressionToken::OP_AND: token.value = boolean_1 && boolean_2; break;
                case ExpressionToken::OP_XOR: token.value = boolean_1 ^ boolean_2; break;
                case ExpressionToken::OP_OR: token.value = boolean_1 || boolean_2; break;
                default: break; // you shouldn't be here...
                }

                operands.push(token);

                break;
            case ExpressionToken::OP_NOT:
                token = operands.top();
                operands.pop();

                if(token.type == ExpressionToken::ID)
                {
                    boolean_1 = variable_values_[token.value];
                }
                else if(token.type == ExpressionToken::BOOLEAN)
                {
                    boolean_1 = token.value != 0;
                }

                token.type = ExpressionToken::BOOLEAN;
                token.value = !boolean_1;
                operands.push(token);

                break;
            case ExpressionToken::OP_EOL:
                token = operands.top();
                operands.pop();

                if(token.type == ExpressionToken::ID)
                {
                    boolean_1 = variable_values_[token.value];
                }
                else if(token.type == ExpressionToken::BOOLEAN)
                {
                    boolean_1 = token.value != 0;
                }
                else
                {
                    // freak out
                }

                return boolean_1;
                break;
            default: break; // you shouldn't be here
            }
        }
    }

    return function_result;
}

/*!
*/
void ExpressionParser::Print_Token_Stream_(TokenStream_t tokens) const
{
    for(TokenStream_t::const_iterator iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        if(iter->Is_Operator())
        {
            if(iter->type == ExpressionToken::OP_EOL)
            {
                cout << "<EOL>";
            }
            else
            {
                cout << "< " << iter->Symbol() << " >";
            }
        }
        else if(iter->type == ExpressionToken::ID)
        {
            cout << "<ID>";
        }
        else
        {
            cout << "<UNKNOWN>";
        }
    }

    cout << endl;
}

/*!
attempts to parse the expression

returns true on success, false on failure
*/
bool ExpressionParser::Parse_Expression_(void)
{
    infix_expression_ = Tokenize_Expression_(expression_string_);

    if(!infix_expression_.empty())
    {
        Print_Token_Stream_(infix_expression_);

        postfix_expression_ = Convert_Infix_To_Postfix_(infix_expression_);

        if(!postfix_expression_.empty())
        {
            Print_Token_Stream_(postfix_expression_);

            expression_string_is_parsed_ = true;
        }
        else
        {
            cerr << "Error occurred during infix to postfix conversion." << endl;
            expression_string_is_parsed_ = false;
        }
    }
    else
    {
        cerr << "Error occurred during expression tokenization." << endl;
        expression_string_is_parsed_ = false;
    }

    return expression_string_is_parsed_;
}

/*!
given an expression string, tokenizes the expression and returns a token stream representation of the expression
*/
ExpressionParser::TokenStream_t ExpressionParser::Tokenize_Expression_(ExpressionString_t expression_string)
{
    TokenStream_t function_result;
    VariableName_t variable_name;

    for(ExpressionIndex_t index = 0; index < expression_string.length(); ++index)
    {
        ExpressionStringSymbol_t symbol = expression_string[index];

        if(Variable_Name_Symbol_Is_Valid_(symbol))
        {
            variable_name += symbol;
        }
        else
        {
            if(!variable_name.empty())
            {
                function_result.push_back(ExpressionToken(ExpressionToken::ID, Get_Variable_Index_(variable_name)));

                variable_name.clear();
            }

            if(symbol == Expression_Token_Type_Symbol(ExpressionToken::OP_AND)) function_result.push_back(ExpressionToken(ExpressionToken::OP_AND));
            else if(symbol == Expression_Token_Type_Symbol(ExpressionToken::OP_XOR)) function_result.push_back(ExpressionToken(ExpressionToken::OP_XOR));
            else if(symbol == Expression_Token_Type_Symbol(ExpressionToken::OP_NOT)) function_result.push_back(ExpressionToken(ExpressionToken::OP_NOT));
            else if(symbol == Expression_Token_Type_Symbol(ExpressionToken::OP_OR)) function_result.push_back(ExpressionToken(ExpressionToken::OP_OR));
            else if(symbol == Expression_Token_Type_Symbol(ExpressionToken::OP_LP)) function_result.push_back(ExpressionToken(ExpressionToken::OP_LP));
            else if(symbol == Expression_Token_Type_Symbol(ExpressionToken::OP_RP)) function_result.push_back(ExpressionToken(ExpressionToken::OP_RP));
        }
    }

    if(!variable_name.empty())
    {
        function_result.push_back(ExpressionToken(ExpressionToken::ID, Get_Variable_Index_(variable_name)));

        variable_name.clear();
    }

    function_result.push_back(ExpressionToken(ExpressionToken::OP_EOL));

    return function_result;
}
/*
ExpressionParser::TokenStream_t ExpressionParser::Convert_Infix_To_Postfix_With_Error_Checking_(TokenStream_t tokens)
{
    typedef int OperationDepth_t;
    typedef pair<TokenStream_t, OperationDepth_t> Operand_t;
    typedef pair<ExpressionToken, OperationDepth_t> Operator_t;

    OperationDepth_t operation_depth = 0;

    TokenStream_t function_result;

    stack<Operand_t> operands;
    stack<Operator_t> operators;
    Operand_t top_operand;

    for(TokenStream_t::iterator token_iter = tokens.begin(); token_iter != tokens.end(); ++token_iter)
    {
        if(token_iter->Is_Operand())
        {
            // operands are pushed onto the operands stack with the current value operation_depth
            // create a pair where first = the token, second = operation depth
            top_operand.first.push_back(*token_iter);
            top_operand.second = operation_depth;
            operands.push(top_operand);
            top_operand.first.clear();
        }
        else if(token_iter->Is_Operator())
        {
            ++operation_depth;

            if(operators.empty())
            {
                switch(token_iter->type)
                {
                case ExpressionToken::OP_EOL: // Unary postfix operator, expects an operand before it
                    // error, empty expression
                    break;
                case ExpressionToken::OP_RP:  // Unary postfix operator, expects a matching OP_LP somewhere before it, but since the operator stack is empty this is an error
                    // error, OP_LP found before matching OP_RP
                    break;
                case ExpressionToken::OP_AND: // Binary infix operators, expect an operand before and after themselves (can't check the 'after operand' here)
                case ExpressionToken::OP_XOR:
                case ExpressionToken::OP_OR:
                    // check if the operand that is on the top of the operands stack has an operation depth equal to than operator_depth
                    if(!operands.empty())
                    {
                        if(operands.top().second == operation_depth - 1)
                        {
                        ++operation_depth;
                        operators.push(make_pair(*token_iter, operation_depth));
                    }
                    else
                    {
                        // error, operator is expecting an operand before itself
                    }

                    break;
                case ExpressionToken::OP_LP: // Unary prefix operators, expect an operand after themselves (can't check the 'after operand' here), so we'll be optimistic
                case ExpressionToken::OP_NOT:
                    ++operation_depth;
                    operators.push(make_pair(*token_iter, operation_depth));
                    break;
                default: // you shouldn't be here
                    // TODO: freak out severely... mumbling something about an unrecognized operator
                    break;
                }
            }
            else
            {
                if(operators.top().Precedence() < token_iter->Precedence())
                {
                    operators.push(*token_iter);
                }
                else
                {
                    if(token_iter->type == ExpressionToken::OP_LP)
                    {
                        operators.push(*token_iter);
                    }
                    else if(token_iter->type == ExpressionToken::OP_RP)
                    {
                        bool inner_operand_found = false;

                        while(!operators.empty() && (operators.top().type != ExpressionToken::OP_LP))
                        {
                            switch(operators.top().type)
                            {
                            case ExpressionToken::OP_AND: // Binary infix operators, expect an operand before and after themselves 
                            case ExpressionToken::OP_XOR:
                            case ExpressionToken::OP_OR:
                                // check if the binary operator has an operand after itself by checking if the operand stack's top operand's operation depth matches the top operator's operation depth

                                // if the operator's second operand exists
                                if(top_operand.second == operators.top().second)
                                {
                                    top_operand = operands.top();
                                    operands.pop();
                                }
                                else
                                {
                                    // error. expected operand after binary operator (operators.top().type) (at location operators.top().column)
                                }


                                if(!operands.empty())
                                {
                                    // if the operator's first operand exists
                                    if(operands.top().second == operators.top().second)
                                    {
                                        operands.top().insert(operands.top().end(), top_operand.begin(), top_operand.end());
                                        operands.top().push_back(operators.top());
                                        operators.pop();
                                        top_operand.clear();
                                    }
                                    else
                                    {
                                        // error. expected operand before binary operator (operators.top().type) (at location operators.top().column) 
                                    }
                                }
                                else
                                {
                                    // error. expected operand before binary operator (operators.top().type) (at location operators.top().column)
                                }

                                break;
                            case ExpressionToken::OP_NOT: // Unary prefix operator
                                if(!operands.empty())
                                {
                                    if(operands.top().second == operators.top().second)
                                    {
                                        operands.top().push_back(operators.top());
                                        operators.pop();
                                    }
                                    else
                                    {
                                        // error. expected operand after unary operator (operators.top().type) (at location operators.top().column)
                                    }
                                }
                                else
                                {
                                    // error. expected operand after unary operator (operators.top().type) (at location operators.top().column)
                                }

                                break;
                            default: break; // you shouldn't be here
                            }
                        }

                        if(!inner_operand_found) // we had <OP_LP><OP_RP>
                        {
                            // error. There must be an operand between the OP_LP (at operators.top()->column) and OP_RP (at token_iter->column)
                        }

                        if(!operators.empty())
                        {
                            operators.pop();
                        }
                        else
                        {
                            // error. No matching OP_LP found for OP_RP (at token_iter->column)
                        }

                        continue;
                    }
                    else
                    {
                        while(!operators.empty() && !(operators.top().Precedence() < token_iter->Precedence()))
                        {
                            if(operators.top().type == ExpressionToken::OP_LP)
                            {
                                break;
                            }

                            switch(operators.top().type)
                            {
                            case ExpressionToken::OP_AND:
                            case ExpressionToken::OP_XOR:
                            case ExpressionToken::OP_OR:
                                top_operand = operands.top();
                                operands.pop();
                                operands.top().insert(operands.top().end(), top_operand.begin(), top_operand.end());
                                operands.top().push_back(operators.top());
                                operators.pop();
                                top_operand.clear();
                                break;
                            case ExpressionToken::OP_NOT:
                                operands.top().push_back(operators.top());
                                operators.pop();
                                break;
                            default: break; // you shouldn't be here
                            }
                        }

                        operators.push(*token_iter);
                    }
                }
            }
        }
    }

    while(!operators.empty())
    {
        switch(operators.top().type)
        {
        case ExpressionToken::OP_AND:
        case ExpressionToken::OP_XOR:
        case ExpressionToken::OP_OR:
            top_operand = operands.top();
            operands.pop();
            operands.top().insert(operands.top().end(), top_operand.begin(), top_operand.end());
            operands.top().push_back(operators.top());
            operators.pop();
            top_operand.clear();
            break;
        case ExpressionToken::OP_NOT:
        case ExpressionToken::OP_EOL:
            operands.top().push_back(operators.top());
            operators.pop();
            break;
        default: break; // you shouldn't be here
        }
    }

    function_result = operands.top();

    return function_result;
}
*/
/*!
given a token stream representing an infix expression, returns a token stream representing the postfix equivalent expression
*/
ExpressionParser::TokenStream_t ExpressionParser::Convert_Infix_To_Postfix_(TokenStream_t tokens)
{
    TokenStream_t function_result;

    stack<TokenStream_t> operands;
    TokenStream_t top_operand;
    TokenStack_t operators;

    for(TokenStream_t::iterator token_iter = tokens.begin(); token_iter != tokens.end(); ++token_iter)
    {
        if(token_iter->Is_Operand())
        {
            top_operand.push_back(*token_iter);
            operands.push(top_operand);
            top_operand.clear();
        }
        else if(token_iter->Is_Operator())
        {
            if(operators.empty())
            {
                operators.push(*token_iter);
            }
            else
            {
                if(operators.top().Precedence() < token_iter->Precedence())
                {
                    operators.push(*token_iter);
                }
                else
                {
                    if(token_iter->type == ExpressionToken::OP_LP)
                    {
                        operators.push(*token_iter);
                    }
                    else if(token_iter->type == ExpressionToken::OP_RP)
                    {
                        while(!operators.empty() && (operators.top().type != ExpressionToken::OP_LP))
                        {
                            switch(operators.top().type)
                            {
                            case ExpressionToken::OP_AND:
                            case ExpressionToken::OP_XOR:
                            case ExpressionToken::OP_OR:
                                top_operand = operands.top();
                                operands.pop();
                                operands.top().insert(operands.top().end(), top_operand.begin(), top_operand.end());
                                operands.top().push_back(operators.top());
                                operators.pop();
                                top_operand.clear();
                                break;
                            case ExpressionToken::OP_NOT:
                                operands.top().push_back(operators.top());
                                operators.pop();
                                break;
                            default: break; // you shouldn't be here
                            }
                        }

                        if(!operators.empty())
                        {
                            operators.pop();
                        }

                        continue;
                    }
                    else
                    {
                        while(!operators.empty() && !(operators.top().Precedence() < token_iter->Precedence()))
                        {
                            if(operators.top().type == ExpressionToken::OP_LP)
                            {
                                break;
                            }

                            switch(operators.top().type)
                            {
                            case ExpressionToken::OP_AND:
                            case ExpressionToken::OP_XOR:
                            case ExpressionToken::OP_OR:
                                top_operand = operands.top();
                                operands.pop();
                                operands.top().insert(operands.top().end(), top_operand.begin(), top_operand.end());
                                operands.top().push_back(operators.top());
                                operators.pop();
                                top_operand.clear();
                                break;
                            case ExpressionToken::OP_NOT:
                                operands.top().push_back(operators.top());
                                operators.pop();
                                break;
                            default: break; // you shouldn't be here
                            }
                        }

                        operators.push(*token_iter);
                    }
                }
            }
        }
    }

    while(!operators.empty())
    {
        switch(operators.top().type)
        {
        case ExpressionToken::OP_AND:
        case ExpressionToken::OP_XOR:
        case ExpressionToken::OP_OR:
            top_operand = operands.top();
            operands.pop();
            operands.top().insert(operands.top().end(), top_operand.begin(), top_operand.end());
            operands.top().push_back(operators.top());
            operators.pop();
            top_operand.clear();
            break;
        case ExpressionToken::OP_NOT:
        case ExpressionToken::OP_EOL:
            operands.top().push_back(operators.top());
            operators.pop();
            break;
        default: break; // you shouldn't be here
        }
    }

    function_result = operands.top();

    return function_result;
}

/*!
given a variable name, returns the variable's lookup index

if an error occurred, returns the number of variables
*/
ExpressionParser::VariableIndex_t ExpressionParser::Get_Variable_Index_(VariableName_t name) const
{
    for(VariableIndex_t index = 0; index < Get_Number_Of_Variables(); ++index)
    {
        if(variable_names_[index] == name) return index;
    }

    return Get_Number_Of_Variables();
}

/*!
given a variable lookup index and a variable name, attempts to set the name of the variable in the lookup table

returns true if successful, false if there was something wrong 
*/
bool ExpressionParser::Set_Variable_Name_(VariableIndex_t index, VariableName_t name)
{
    if(0 <= index && index < Get_Number_Of_Variables())
    {
        variable_names_[index] = name;
        return true;
    }

    return false;
}

/*!
returns an empty variable name on failure
*/
ExpressionParser::VariableName_t ExpressionParser::Get_Variable_Name_(VariableIndex_t index) const
{
    if(0 <= index && index < Get_Number_Of_Variables())
    {
        return variable_names_[index];
    }

    return VariableName_t();
}

/*!
Given an expression string, returns true if the string is parsable by the expression class

In order to be parsable, the string must have a length of at least one and contain no invalid symbols
*/
bool ExpressionParser::Expression_String_Is_Parsable_(ExpressionString_t expression_string) const
{
    if(Expression_String_Symbols_Are_All_Valid_(expression_string) && !expression_string.empty())
    {
        return true;
    }

    return false;
}

/*!
Given an expression string, returns true if the string contains only valid symbols
*/
bool ExpressionParser::Expression_String_Symbols_Are_All_Valid_(ExpressionString_t expression_string) const
{
    for(ExpressionIndex_t index = 0; index < expression_string.length(); ++index)
    {
        if(!Expression_String_Symbol_Is_Valid_(expression_string[index])) return false;
    }

    return true;
}

/*!
Given an expression string symbol, returns true if the string symbol can appear in an expression string
*/
bool ExpressionParser::Expression_String_Symbol_Is_Valid_(ExpressionStringSymbol_t symbol) const
{
    if
    (
        (symbol == Expression_Token_Type_Symbol(ExpressionToken::OP_AND)) ||
        (symbol == Expression_Token_Type_Symbol(ExpressionToken::OP_XOR)) ||
        (symbol == Expression_Token_Type_Symbol(ExpressionToken::OP_NOT)) ||
        (symbol == Expression_Token_Type_Symbol(ExpressionToken::OP_OR)) ||
        (symbol == Expression_Token_Type_Symbol(ExpressionToken::OP_LP)) ||
        (symbol == Expression_Token_Type_Symbol(ExpressionToken::OP_RP)) ||
        Variable_Name_Symbol_Is_Valid_(symbol)
    )
        return true;
    else
        return false;    
}

/*!
Given a variable name, returns true if the variable is parsable by the expression class

In order to be parsable, the variable name must have a length of at least one and must contain no invalid symbols
*/
bool ExpressionParser::Variable_Name_Is_Parsable_(VariableName_t name) const
{
    if(Variable_Name_Symbols_Are_All_Valid_(name) && !name.empty())
    {
        return true;
    }

    return false;
}

/*!
Given a variable name, returns true if the variable only contains symbols that are valid
*/
bool ExpressionParser::Variable_Name_Symbols_Are_All_Valid_(VariableName_t name) const
{
    for(VariableName_t::size_type index = 0; index < name.length(); ++index)
    {
        if(!Variable_Name_Symbol_Is_Valid_(name[index])) return false;
    }

    return true;
}

/*!
Given a symbol from a variable name, returns true if the symbol can appear in a variable name
*/
bool ExpressionParser::Variable_Name_Symbol_Is_Valid_(VariableNameSymbol_t symbol) const
{
    if((symbol >= '0' && symbol <= '9') ||
       (symbol >= 'a' && symbol <= 'z') ||
       (symbol >= 'A' && symbol <= 'Z')) return true;

    return false;
}
