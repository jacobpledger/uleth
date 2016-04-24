#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QTableWidget>
#include <QString>
#include <QStringList>
#include <QLabel>
#include "equation.h"

/*!
   @class TruthTable
   @brief The widget containing truth table information.
   The truth table class handles information regarding 
   the values of equation function results.
   @author Curtis, Gezim, Jacob, Jeremy

*/

class TruthTable : public QWidget {

   Q_OBJECT

public:
///TruthTable constructor.
/*!
   A constructor that creates a TruthTable object.
*/
   TruthTable(QWidget *parent = 0);
/*!
   Stores the truth table information in a QVector of QStrings.
   @param QVector<QString>
*/
   void setTruthTableData(QVector<QString> currentData);
/*!
   Gets the values entered into the TruthTable in the form of a QString.
   @return QVector<QString> truthTableData
*/
   QVector<QString> getTruthTableData();
signals:
   void signalChangedButtonText(int i);
   void sendTruthToKmap(QString str);
   void sendTruthTableToEquation(QString str);
public slots:
/*!
   Changes the symbol displayed in the sector of the truth table to the next symbol.
   Order: 0,1
   @param *AbstractButton
*/
   void sigNextButtonValue(QAbstractButton * button);
   void setVariableNames(QStringList varNames);
   void setNumberOfVariables(int numVars);
   void setTruthTableString(QString str);
   void toggleTruthTable(bool checked);
   void sendKmapData();
   void clearTruthTable();

private:
///Private function to load the setup the various truth tables
   void setupTruthTables();
///Button group for the function buttons
   QButtonGroup *truthTable6vButtonGroup;
///Buttons for the function result section of the truth table.
   QList<QPushButton*> truthTableButtonsList;
///QVector of Strings for storing the truth table data.
   QVector<QString> truthTableData;
///QTableWidget for the static truth table values.
   QTableWidget *truthTable6v;
///QStringList for variable names
   QStringList varNames, minTermLabel;
///integer for storing the current number of variables
   int numberOfVariables;
///QLabel for the number 1
   QLabel *label1, *label0;
};

#endif

