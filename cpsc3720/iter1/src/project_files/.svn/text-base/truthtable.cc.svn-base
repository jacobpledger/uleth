#include "truthtable.h"
#include <QLayout>
#include <QButtonGroup>

TruthTable::TruthTable(QWidget *parent) : QWidget(parent) {



   QHBoxLayout *layout=new QHBoxLayout(this);
   setupTruthTables();
   connect(truthTable6vButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),this, SLOT(sigNextButtonValue(QAbstractButton*)));
   layout->addWidget(truthTable6v);
   setMinimumWidth(200);

   for(int i=0;i<64;i++) {
      QString temp = "m" + QString::number(i);
      minTermLabel << temp;
   }
   truthTable6v->setVerticalHeaderLabels(minTermLabel);

	for(int i=0;i<64;i++) {
		if(i<4)
			truthTable6v->showRow(i);
		else
			truthTable6v->hideRow(i);
	}
	for(int i=0;i<7;i++) {
		if(i<4)
			truthTable6v->hideColumn(i);
		else
			truthTable6v->showColumn(i);
	}
	QStringList variableNames;
         numberOfVariables=2;
		variableNames << " " << " " << " " << " " << "a" << "b" << "f(x)";
	truthTable6v->setHorizontalHeaderLabels(variableNames);
	      truthTable6v->resizeColumnsToContents();
}

void TruthTable::toggleTruthTable(bool checked) {
   setEnabled(checked);
}

void TruthTable::clearTruthTable()
{
	for (QList<QPushButton*>::iterator iter=truthTableButtonsList.begin(); iter != truthTableButtonsList.end(); ++iter)
	{
		(*iter)->setText("0");
	}
}

void TruthTable::setTruthTableData(QVector<QString> currentData) {

}

void TruthTable::sendKmapData() {
   QString temp;
   for(int i=0;i<1<<numberOfVariables;i++)
      temp[i]=truthTable6vButtonGroup->button(i)->text().at(0);
   if(truthTable6v->isEnabled()) {
      emit sendTruthToKmap(temp);
      emit sendTruthTableToEquation(temp);
   }
}
void TruthTable::setTruthTableString(QString str) {
    for(int i=0;i<str.size();i++) {
        truthTable6vButtonGroup->button(i)->setText(str.at(i));
   }

}

QVector<QString> TruthTable::getTruthTableData() {

}

void TruthTable::setVariableNames(QStringList varNames) {
   truthTable6v->setHorizontalHeaderLabels(varNames);
   truthTable6v->resizeColumnsToContents();
}

void TruthTable::setNumberOfVariables(int numVars) {
   numberOfVariables = numVars;
   if(numberOfVariables==2) {
    for(int i=0;i<64;i++) {
        if(i<4)
        truthTable6v->showRow(i);
        else
        truthTable6v->hideRow(i);
    }
    for(int i=0;i<7;i++) {
        if(i<4)
            truthTable6v->hideColumn(i);
        else
            truthTable6v->showColumn(i);
    }
   }
   if(numberOfVariables==3) {
    for(int i=0;i<64;i++) {
        if(i<8)
        truthTable6v->showRow(i);
        else
        truthTable6v->hideRow(i);
    }
    for(int i=0;i<7;i++) {
        if(i<3)
            truthTable6v->hideColumn(i);
        else
            truthTable6v->showColumn(i);
    }
   }
   if(numberOfVariables==4) {
    for(int i=0;i<64;i++) {
        if(i<16)
        truthTable6v->showRow(i);
        else
        truthTable6v->hideRow(i);
    }
    for(int i=0;i<7;i++) {
        if(i<2)
            truthTable6v->hideColumn(i);
        else
            truthTable6v->showColumn(i);
    }

   }
   if(numberOfVariables==5) {
    for(int i=0;i<64;i++) {
        if(i<32)
        truthTable6v->showRow(i);
        else
        truthTable6v->hideRow(i);
    }
    for(int i=0;i<7;i++) {
        if(i<1)
            truthTable6v->hideColumn(i);
        else
            truthTable6v->showColumn(i);
    }

   }
   if(numberOfVariables==6) {
    for(int i=0;i<64;i++) {
        if(i<64)
        truthTable6v->showRow(i);
        else
        truthTable6v->hideRow(i);
    }
    for(int i=0;i<7;i++) {
        if(i<0)
            truthTable6v->hideColumn(i);
        else
            truthTable6v->showColumn(i);
    }

   }
}

void TruthTable::sigNextButtonValue(QAbstractButton * button) {
   if(button->text()=="0") {
      button->setText("1");
   }
   else if(button->text()=="1") {
      button->setText("X");
   }
   else if(button->text()=="X") {
      button->setText("0");
   }

}





void TruthTable::setupTruthTables() {

///QStringLists containing the values for the binary bits in the truth table
   QString truthTableValues;
   truthTableValues =
   "000000000001000010000011000100000101000110000111001000001001001010001011001100001101001110001111010000010001010010010011010100010101010110010111011000011001011010011011011100011101011110011111100000100001100010100011100100100101100110100111101000101001101010101011101100101101101110101111110000110001110010110011110100110101110110110111111000111001111010111011111100111101111110111111";
///Six Variable Truthtable setup

   truthTable6v = new QTableWidget(64,7,this);
   truthTable6v->show();
   truthTable6vButtonGroup = new QButtonGroup();

   int indexOfTableValues = 0;
   int rowIndex=0;
   for (int col = 0; col < 448; ++col) {

      if((col+1)%7) {
         QTableWidgetItem *name = new QTableWidgetItem(truthTableValues.at(indexOfTableValues));
         name->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
         truthTable6v->setItem(0, col, name);
         indexOfTableValues++;
      }
      else {
///Loading the buttons onto the table
         truthTableButtonsList.append(new QPushButton("0"));
         truthTable6vButtonGroup->addButton(truthTableButtonsList.at(rowIndex));
         truthTable6v->setCellWidget(rowIndex,col%7,truthTableButtonsList.at(rowIndex));
         truthTable6vButtonGroup->setId(truthTableButtonsList.at(rowIndex),rowIndex);
         rowIndex++;
      }
   }
}
