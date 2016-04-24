#include "expressionparser.h"

#include <iostream>

int main(void)
{
    ExpressionParser expression_parser;
    ExpressionParser::VariableNames_t variable_names;
    ExpressionParser::VariableValues_t variable_values;
    ExpressionParser::ExpressionString_t expression_string;

    variable_names.push_back("a");
    variable_names.push_back("b");
    variable_names.push_back("c");
    variable_names.push_back("d");
//    variable_names.push_back("e");
//    variable_names.push_back("f");

    cout << "Enter expression string: "; cin >> expression_string;

    expression_parser.Set_Expression_String(expression_string);
    expression_parser.Set_Variable_Names(variable_names);

    bool result;
    int num_vars = variable_names.size();
    int combinations = 1 << num_vars; // 2 ^ num_vars

    std::cout << "Results of the evaluated expression with all combinations of variable values:" << endl;
    for(int var_idx = 0; var_idx < num_vars; ++var_idx)
    {
        cout << variable_names[var_idx] << endl;
    }

    for(int combo = 0; combo < combinations; ++combo)
    {
        variable_values.clear();

        int bit_mask = combinations; // this is used to extract the individual bits from the integer, combo

        for(int bit_offset = 0; bit_offset < num_vars; ++bit_offset)
        {
            bit_mask >>= 1; // move the masking bit to the right one place
            variable_values.push_back((combo & bit_mask) > 0); // 
        }

        expression_parser.Set_Variable_Values(variable_values);
        result = expression_parser.Evaluate_Expression();

        for(int var_idx = 0; var_idx < num_vars; ++var_idx)
        {
            cout << (variable_values[var_idx] ? "1" : "0");
        }

        cout << " | " << (result ? "1" : "0") << endl;
    }


    cin.sync();
    cin.get();

    return 0;
}
