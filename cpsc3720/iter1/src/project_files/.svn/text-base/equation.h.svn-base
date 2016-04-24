#ifndef EQUATION_H
#define EQUATION_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QTableWidget>
#include <QString>
#include <QLineEdit>
#include "expressionparser.h"
#include "quinemccluskey.h"

/*!
   @class Equation
   @brief The widget containing equation information.
   The equation class handles information regarding 
   equation string entered by the user.
   @author Curtis, Gezim, Jacob, Jeremy

*/

class Equation : public QWidget, public ExpressionParser {

   Q_OBJECT

public:
///Equation constructor.
/*!
   A constructor that creates an equation object.
*/
   Equation(QWidget *parent = 0);
/*!
   Gets the equation in the form of a string.
   @return QString equation
*/
   QString getEquation();

    QString makeTruthTableString(void);


   QVector<int> countTimesEachMintermWasUsed(const Implicants_t &minterm_implicants, const int &truth_table_row_count) const;

signals:
   void sendTruthTableString(QString str);
   void sendPosAndSop(QString pos, QString sop);
   void sendKmapColoring(QVector<int> color);

public slots:
   void setVariableNames(QStringList varNames);
   void setNumberOfVariables(int numVars);
   void setEquation();
   void toggleEquation(bool checked);
   void optimizeTruthTableExpression(QString truthTableString);

private:
   Implicants_t optimalMaxterms;
   QString posExpression;

   Implicants_t optimalMinterms;
   QString sopExpression;

///QTextEdit box for the user to enter an equation
   QLineEdit *equation;
///QString for storing the equations as a string
   QString equationStorage;
///QVector of QString to store suitable input for the Kmap and TruthTable classes.
   QVector<QString> equationAsTruthTableString;

   QStringList variableNames;
   int numberOfVariables;
};

#endif

