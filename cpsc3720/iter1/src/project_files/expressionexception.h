#ifndef EXPRESSIONEXCEPTION_H
#define EXPRESSIONEXCEPTION_H

/*
Possible Exceptions Arranged By Phase:

Tokenization:
    Illegal symbol found in the expression string
        The error message should return the offset of the symbol in the expression string
        "Warning: Illegal symbol found in input stream at column <offset>. Attempting to ignore it."

    Undefined variable name in the expression string
        The error message should return the name of the variable and the offset of its first character in the expression string
        "Error: Undefined variable name "<name>" found in input stream starting at column <offset>."

Parsing:
    Binary infix operator missing leading operand
        The error message should return the name of the operator and its offset in the expression string
        "Error: Binary infix operator "<name>" at column <offset> expects two operands. Missing leading operand."

    Binary infix operator missing following operand
        The error message should return the name of the operator and its offset in the expression string
        "Error: Binary infix operator "<name>" at column <offset> expects two operands. Missing following operand."

    Binary infix operator missing leading and following operands
        The error message should return the name of the operator and its offset in the expression string
        "Error: Binary infix operator "<name>" at column <offset> expects two operands. Missing leading and following operands."

    Unary prefix operator missing following operand
        The error message should return the name of the operator and its offset in the expression string
        "Error: Unary prefix operator "<name>" at column <offset> expects one operand. Missing following operand."

    Unary suffix operator missing leading operand
        The error message should return the name of the operator and its offset in the expression string
        "Error: Unary suffix operator "<name>" at column <offset> expects one operand. Missing leading operand."

    Right parenthesis immediately followed by a left parenthesis
        The error message should return the offset of the left parenthesis in the expression string
        "Error: Unexpected left parenthesis at column <offset> after right parenthesis. Expecting one of: binary infix operator, right parenthesis, or end of line."

    Left parenthesis immediately followed by a right parenthesis
        The error message should return the offset of the right parenthesis in the expression string
        "Error: Unexpected right parenthesis at column <offset> after left parenthesis. Expecting intervening operand."

    End of line reached without passing any evaluable operands
        The error message should return the offset of the last symbol of the input string or 0 (zero) if the input string is empty
        "Error: End of line reached at column <offset> before evaluable expression was read."

    Unmatched left parenthesis
        "Error:
    Unmatched right parenthesis

Evaluation:
*/

#endif
