#ifndef PREFPANE_H
#define PREFPANE_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QStringList>
#include <QLabel>

/*!
   @class PrefPane
   @brief The widget containing preference information.
   The preference pane class handles information regarding 
   number of variables and the variables names.
   @author Curtis, Gezim, Jacob, Jeremy

*/

class PrefPane : public QWidget {

   Q_OBJECT

public:
///Preference pane constructor.
/*!
   A constructor that creates a preference pain object.
*/
   PrefPane(QWidget *parent = 0);
/*!
   Get the names selected for the variables by the user.
   @return QStringList variableNames
*/
   QStringList getVariableNames();
/*!
   Get the number of variables selected by the user.
   @return int numberOfVariables
*/
   int getNumberOfVariables();

signals:
   void sendVariableNames(const QStringList &strList);
   void sendVariableNames2(const QStringList &strList);
   void sendVariableNumber(const int &numVars);
   void sendReset();
/*!
   Stores the number of variables selected by the user in the private data member numberOfVariables.
   @param int numOfVars
*/
   //void setNumberOfVariables(int numOfVars);
/*!
   Stores the name of variables selected by the user in the private data member variableNames.
@param QStringList varNames
*/
public slots:
   void selectVar(int numberSelected);
   void setVariableNames();

private:
///Test QLABEL
   QLabel *numberOfVariablesLabel;
///Text edit boxes for the names of the variables.
   QLineEdit *variableOne, *variableTwo, *variableThree, *variableFour, *variableFive, *variableSix;
///Combo box for selecting the number of variables.
   QComboBox *selectNumberVariables;
///Button to accept.
   QPushButton *setPushButton;
///QStringList containing variable names.
   QStringList variableNames;
///Integer containing the number of variables selected.
   int numberOfVariables;

};

#endif

