#include "prefpane.h"
#include <QtGui>

PrefPane::PrefPane(QWidget *parent) : QWidget(parent) {
///setup for QLabels

///Setup for the combo box which allows the user to select the number of variables they would like to use.
   QVBoxLayout *layout = new QVBoxLayout;
   selectNumberVariables = new QComboBox();
   selectNumberVariables->addItem("2");
   selectNumberVariables->addItem("3");
   selectNumberVariables->addItem("4");
   selectNumberVariables->addItem("5");
   selectNumberVariables->addItem("6");

///Setup for the QLineEdits to allow the user to name each of their variables
   variableOne = new QLineEdit("a");
   variableTwo = new QLineEdit("b");
   variableThree = new QLineEdit("c");
   variableFour = new QLineEdit("d");
   variableFive = new QLineEdit("e");
   variableSix = new QLineEdit("f");

   variableThree->hide();
   variableFour->hide();
   variableFive->hide();
   variableSix->hide();
///setup for the QPushButton to set the users selections
   setPushButton = new QPushButton("&Set",this);
///setup the connection for the comboboxes activated signal to this widges selected Var slot
   connect(selectNumberVariables, SIGNAL(activated(int)),this, SLOT(selectVar(int)));
   connect(setPushButton, SIGNAL(clicked()),this, SLOT(setVariableNames()));
///Layout for the widget
   layout->addWidget(selectNumberVariables);
   layout->addWidget(variableOne);
   layout->addWidget(variableTwo);
   layout->addWidget(variableThree);
   layout->addWidget(variableFour);
   layout->addWidget(variableFive);
   layout->addWidget(variableSix);
   layout->addWidget(setPushButton);
      variableNames.clear();
      variableNames << " " << " " << " " << " " << variableOne->text() << variableTwo->text() << "f(x)";
    numberOfVariables = 2;
   setMaximumWidth(200);
   setLayout(layout);
   adjustSize();
}

QStringList PrefPane::getVariableNames() {
   return variableNames;
}

int PrefPane::getNumberOfVariables() {
   return numberOfVariables;
}

void PrefPane::selectVar(int numberSelected) {
   numberOfVariables = numberSelected+2;
	variableNames.clear();

   if(numberOfVariables == 2) {
      variableOne->show();
      variableTwo->show();
      variableThree->hide();
      variableFour->hide();
      variableFive->hide();
      variableSix->hide();
   }
   if(numberOfVariables == 3) {
      variableOne->show();
      variableTwo->show();
      variableThree->show();
      variableFour->hide();
      variableFive->hide();
      variableSix->hide();
   }
   if(numberOfVariables == 4) {
      variableOne->show();
      variableTwo->show();
      variableThree->show();
      variableFour->show();
      variableFive->hide();
      variableSix->hide();
   }
   if(numberOfVariables == 5) {
      variableOne->show();
      variableTwo->show();
      variableThree->show();
      variableFour->show();
      variableFive->show();
      variableSix->hide();
   }
   if(numberOfVariables == 6) {
      variableOne->show();
      variableTwo->show();
      variableThree->show();
      variableFour->show();
      variableFive->show();
      variableSix->show();
   }

}

void PrefPane::setVariableNames() {
	emit sendReset();
   if(numberOfVariables == 2) {
      variableNames.clear();
      variableNames << " " << " " << " " << " " << variableOne->text() << variableTwo->text() << "f(x)";
   }
   if(numberOfVariables == 3) {
      variableNames.clear();
      variableNames << " " << " " << " " << variableOne->text() << variableTwo->text() << variableThree->text() << "f(x)";
   }
   if(numberOfVariables == 4) {
      variableNames.clear();
      variableNames << " " << " " << variableOne->text() << variableTwo->text() << variableThree->text()
      << variableFour->text() << "f(x)";
   }
   if(numberOfVariables == 5) {
      variableNames.clear();
      variableNames << " " << variableOne->text() << variableTwo->text() << variableThree->text()
      << variableFour->text() << variableFive->text() << "f(x)";
   }
   if(numberOfVariables == 6) {
      variableNames.clear();
      variableNames << variableOne->text() << variableTwo->text() << variableThree->text()
      << variableFour->text() << variableFive->text() << variableSix->text() << "f(x)";
   }
   emit sendVariableNumber(numberOfVariables);
   emit sendVariableNames(variableNames);
   QStringList testQList;
   testQList << variableOne->text() << variableTwo->text() << variableThree->text()
      << variableFour->text() << variableFive->text() << variableSix->text();
   emit sendVariableNames2(testQList);

}