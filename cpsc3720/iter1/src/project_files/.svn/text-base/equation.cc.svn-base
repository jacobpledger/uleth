#include "equation.h"
#include <QLayout>

Equation::Equation(QWidget *parent) : QWidget(parent), ExpressionParser() {
   QHBoxLayout *hlayout = new QHBoxLayout(this);
   equation = new QLineEdit();
   hlayout->addWidget(equation);
QStringList fuck;
numberOfVariables = 2;
fuck << "a" << "b" << "c" << "d" << "f";
   setVariableNames(fuck);
}

QString Equation::getEquation() {
    // create a QString using the expression string's c_str() method
    return QString(Get_Expression_String().c_str());
}

void Equation::toggleEquation(bool checked) {
   setEnabled(checked);
}



void Equation::setVariableNames(QStringList varNames) {
    variableNames = varNames;
    ExpressionParser::VariableNames_t parser_variable_names;

    cout << "setVariableNames()" << endl;

    for(QStringList::iterator iter = variableNames.begin(); iter < variableNames.end(); ++iter)
    {
        cout << iter->toStdString() << endl;
        parser_variable_names.push_back(iter->toStdString());
    }

    Set_Variable_Names(parser_variable_names);
}

void Equation::setNumberOfVariables(int numVars) {
   numberOfVariables = numVars;
}

void Equation::setEquation() {
   if(!equation->text().isEmpty() && equation->isEnabled()) {
        cout << "Equation: '" << equation->text().toStdString() << "'" << endl;
      Set_Expression_String(equation->text().toStdString());
      QString truthTableString = makeTruthTableString();
      emit sendTruthTableString(truthTableString);  
   }
}

QString Equation::makeTruthTableString(void) {
    bool result;
    QString truthTableString;
    ExpressionParser::VariableValues_t variable_values;

    int num_vars = numberOfVariables;
    int combinations = 1 << num_vars; // 2 ^ num_vars

    for(int combo = 0; combo < combinations; ++combo)
    {
        variable_values.clear();

        int bit_mask = combinations; // this is used to extract the individual bits from the integer, combo

        for(int bit_offset = 0; bit_offset < num_vars; ++bit_offset)
        {
            bit_mask >>= 1; // move the masking bit to the right one place
            variable_values.push_back((combo & bit_mask) > 0);
        }

        Set_Variable_Values(variable_values);
        result = Evaluate_Expression();

        truthTableString += (result ? "1" : "0");
    }

    optimizeTruthTableExpression(truthTableString);

    return truthTableString;
}

QVector<int> Equation::countTimesEachMintermWasUsed(const Implicants_t &minterm_implicants, const int &truth_table_row_count) const
{
    QVector<int> times_each_truth_table_row_was_used(truth_table_row_count, 0);

    for(Implicants_t::const_iterator implicant = minterm_implicants.begin(); implicant != minterm_implicants.end(); ++implicant)
    {
        for(SetOfRowNumbers_t::const_iterator row_number = implicant->first.begin(); row_number != implicant->first.end(); ++row_number)
        {
            ++times_each_truth_table_row_was_used[*row_number];
        }
    }

    return times_each_truth_table_row_was_used;
}

void Equation::optimizeTruthTableExpression(QString truthTableString)
{
    cout << "optimizeTruthTableExpression = '" << truthTableString.toStdString() << "'" << endl;

    optimalMaxterms = Get_Optimal_Maxterms(truthTableString.toStdString());
    optimalMinterms = Get_Optimal_Minterms(truthTableString.toStdString());

    QVector<int> mintermUseCount = countTimesEachMintermWasUsed(optimalMinterms, truthTableString.length());
    emit sendKmapColoring(mintermUseCount); 
    cout << "optimalMaxterms: " << endl << optimalMaxterms;
    cout << "optimalMinterms: " << endl << optimalMinterms;


    cout << "Variable Names: " << endl;
    ExpressionParser::VariableNames_t variable_names = Get_Variable_Names();

    for(VariableNames_t::iterator variable_name = variable_names.begin(); variable_name != variable_names.end(); ++variable_name)
    {
        cout << *variable_name << endl;
    }

    string pos_string = Get_POS_Expression_String(optimalMaxterms, Get_Variable_Names());
    cout << "POS string: " << pos_string << endl;
    string sop_string = Get_SOP_Expression_String(optimalMinterms, Get_Variable_Names());
    cout << "SOP string: " << sop_string << endl;

    // run the Quine-McCluskey algorithm to optimize the expression
    posExpression = QString::fromStdString(pos_string);
    sopExpression = QString::fromStdString(sop_string);

    emit sendPosAndSop(posExpression, sopExpression);
}
