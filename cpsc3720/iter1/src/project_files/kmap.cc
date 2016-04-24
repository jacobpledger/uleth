#include "kmap.h"
#include <QLayout>
#include <QStringList>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;
unsigned int Log_Base_2(unsigned int value);
int Bin_To_Grey(int binary_number);
int Get_KMap_Cell_Index(int row, int col, int cells);
string Generate_Binary_String(unsigned int decimal_value, unsigned int desired_string_length);

Kmap::Kmap(QWidget *parent) : QWidget(parent) {

   QGridLayout *glayout = new QGridLayout(this);



   kmapTable1 = new QTableWidget(this);
   kmapButtonGroup1 = new QButtonGroup();
   connect(kmapButtonGroup1, SIGNAL(buttonClicked(QAbstractButton*)),this, SLOT(setNextButtonValue(QAbstractButton*)));
   buttonSetup();

///Populates the table with the buttons
      setMinimumSize(kmapTable1->sizeHint());
      setMinimumHeight((kmapTable1->sizeHint().height())*2);

	// set initial size 
	numberOfRows = 2;
	numberOfCols = 2;
	kmapTable1->hideRow(2);
	kmapTable1->hideRow(3);
	kmapTable1->hideRow(4);
	kmapTable1->hideRow(5);
	kmapTable1->hideRow(6);
	kmapTable1->hideRow(7);
	kmapTable1->hideColumn(2);
	kmapTable1->hideColumn(3);
	kmapTable1->hideColumn(4);
	kmapTable1->hideColumn(5);
	kmapTable1->hideColumn(6);
	kmapTable1->hideColumn(7);
        numberOfVariables=2;
	QStringList columnHeader, rowHeader;
	rowHeader << "0" << "1" << "f(x)";
	kmapTable1->setHorizontalHeaderLabels(rowHeader);
	kmapTable1->setVerticalHeaderLabels(rowHeader);
	 kmapTable1->resizeColumnsToContents();
   glayout->addWidget(kmapTable1);

}


void Kmap::toggleKmap(bool checked) {
   enabled = checked;
   setEnabled(checked);
}
void Kmap::setKmapString(QString str) {
    for(int i=0;i<numberOfRows;i++) {
      for(int j=0;j<numberOfCols;j++) {
        qobject_cast<QPushButton *>(kmapTable1->cellWidget(i,j))->
         setText(str.at(Get_KMap_Cell_Index(i,j,numberOfRows*numberOfCols)));

      }
   }
}

void Kmap::setNextButtonValue(QAbstractButton *button) {
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

void Kmap::sendTruthTableData() {
   if(kmapTable1->isEnabled()) {
      for(int i=0;i<numberOfRows;i++) {
         for(int j=0;j<numberOfCols;j++) {
            kmapData[Get_KMap_Cell_Index(i,j,numberOfRows*numberOfCols)] 
            = qobject_cast<QPushButton *>(kmapTable1->cellWidget(i,j))->text().at(0);
         }
      }
      if(enabled)
      emit sendDataToTruthTable(kmapData);
   }
}

void Kmap::clearKmap()
{
	for (QList<QPushButton*>::iterator iter=kmapButtonsList.begin(); iter != kmapButtonsList.end(); ++iter)
	{
		(*iter)->setText("0");
                QPalette pal = (*iter)->palette( );
                QPushButton *ballz2 = new QPushButton();
                (*iter)->setPalette( ballz2->palette() );
                (*iter)->setAutoFillBackground( true );
	}

}

void Kmap::setNumberOfVariables(int numVars) {
   numberOfVariables = numVars;
   QStringList colHeader, rowHeader;

   if(numberOfVariables==2) {
       numberOfRows = 2;
       numberOfCols = 2;
       kmapTable1->hideRow(2);
       kmapTable1->hideRow(3);
       kmapTable1->hideRow(4);
       kmapTable1->hideRow(5);
       kmapTable1->hideRow(6);
       kmapTable1->hideRow(7);
       kmapTable1->hideColumn(2);
       kmapTable1->hideColumn(3);
       kmapTable1->hideColumn(4);
       kmapTable1->hideColumn(5);
       kmapTable1->hideColumn(6);
       kmapTable1->hideColumn(7);
   }
   if(numberOfVariables==3) {
       numberOfRows = 2;
       numberOfCols = 4;
       kmapTable1->hideRow(2);
       kmapTable1->hideRow(3);
       kmapTable1->hideRow(4);
       kmapTable1->hideRow(5);
       kmapTable1->hideRow(6);
       kmapTable1->hideRow(7);
       kmapTable1->showColumn(2);
       kmapTable1->showColumn(3);
       kmapTable1->hideColumn(4);
       kmapTable1->hideColumn(5);
       kmapTable1->hideColumn(6);
       kmapTable1->hideColumn(7);
   }
   if(numberOfVariables==4) {
       numberOfRows = 4;
       numberOfCols = 4;
       kmapTable1->showRow(2);
       kmapTable1->showRow(3);
       kmapTable1->hideRow(4);
       kmapTable1->hideRow(5);
       kmapTable1->hideRow(6);
       kmapTable1->hideRow(7);
       kmapTable1->showColumn(2);
       kmapTable1->showColumn(3);
       kmapTable1->hideColumn(4);
       kmapTable1->hideColumn(5);
       kmapTable1->hideColumn(6);
       kmapTable1->hideColumn(7);
   }
   if(numberOfVariables==5) {
       numberOfRows = 4;
       numberOfCols = 8;
       kmapTable1->showRow(2);
       kmapTable1->showRow(3);
       kmapTable1->hideRow(4);
       kmapTable1->hideRow(5);
       kmapTable1->hideRow(6);
       kmapTable1->hideRow(7);
       kmapTable1->showColumn(2);
       kmapTable1->showColumn(3);
       kmapTable1->showColumn(4);
       kmapTable1->showColumn(5);
       kmapTable1->showColumn(6);
       kmapTable1->showColumn(7);
   }
   if(numberOfVariables==6) {
       numberOfRows = 8;
       numberOfCols = 8;
       kmapTable1->showRow(2);
       kmapTable1->showRow(3);
       kmapTable1->showRow(4);
       kmapTable1->showRow(5);
       kmapTable1->showRow(6);
       kmapTable1->showRow(7);
       kmapTable1->showColumn(2);
       kmapTable1->showColumn(3);
       kmapTable1->showColumn(4);
       kmapTable1->showColumn(5);
       kmapTable1->showColumn(6);
       kmapTable1->showColumn(7);
   }

   for(int i=0;i<numberOfCols;i++) {
      colHeader << QString::fromStdString(Generate_Binary_String(Bin_To_Grey(i),Log_Base_2(numberOfCols)));
   }
   for(int i=0;i<numberOfRows;i++) {
      rowHeader << QString::fromStdString(Generate_Binary_String(Bin_To_Grey(i),Log_Base_2(numberOfRows)));
   }

   kmapTable1->setHorizontalHeaderLabels(colHeader);
   kmapTable1->setVerticalHeaderLabels(rowHeader);


   kmapTable1->resizeColumnsToContents();
kmapTable1->resize(size());
}

string Generate_Binary_String(unsigned int decimal_value, unsigned int desired_string_length)
{
    string binary_string;

    // build the binary string starting from the least significant bit on the left and working to the most significant bit on the right
    for(unsigned int bit_offset = 0; bit_offset < desired_string_length; ++bit_offset)
    {
        // to get the value of the bit at offset n, shift the decimal's bits to the right n times and return the bit at offset 0 by anding the decimal's bits with 1
        if((decimal_value >> bit_offset) & 1)
        {
            binary_string += '1';
        }
        else
        {
            binary_string += '0';
        }
    }

    // reverse the string so that the most significant bit appears on the left (as in standard binary notation)
    reverse(binary_string.begin(), binary_string.end());

    return binary_string;
}

unsigned int Log_Base_2(unsigned int value)
{
    int exponent = 0;

    while(value > 1)
    {
        ++exponent;
        value /= 2;
    }

    return exponent;
}

int Bin_To_Grey(int binary_number)
{
    return binary_number ^ (binary_number >> 1);
}

int Get_KMap_Cell_Index(int row, int col, int cells)
{
    int bits = Log_Base_2(cells);
    //int row_bit_count = bits / 2; 
    int col_bit_count = (bits + 1) / 2; // the one that's larger with an uneven number of bits
    int row_greycode = Bin_To_Grey(row);
    int col_greycode = Bin_To_Grey(col);
    int result = row_greycode << col_bit_count | col_greycode;

    return result;
}
void Kmap::setKmapColors(QVector<int> str) {
  //int index = 0;
   for(int i=0;i<numberOfRows;i++) {
      for(int j=0;j<numberOfCols;j++) {
          QPalette pal = qobject_cast<QPushButton *>(kmapTable1->cellWidget(i,j))->palette( );
          
         if(str.at( Get_KMap_Cell_Index(i,j,numberOfRows*numberOfCols))==1) {
            pal.setColor( QPalette::Button, Qt::red );
            qobject_cast<QPushButton *>(kmapTable1->cellWidget(i,j))->setPalette( pal );
            qobject_cast<QPushButton *>(kmapTable1->cellWidget(i,j))->setAutoFillBackground( true );
         }
         if(str.at(Get_KMap_Cell_Index(i,j,numberOfRows*numberOfCols))==0) {
            QPushButton *ballz = new QPushButton();
            qobject_cast<QPushButton *>(kmapTable1->cellWidget(i,j))->setPalette( ballz->palette()  );
            //qobject_cast<QPushButton *>(kmapTable1->cellWidget(i,j))->setAutoFillBackground( true );

         }
         if(str.at(Get_KMap_Cell_Index(i,j,numberOfRows*numberOfCols))>1) {
            pal.setColor( QPalette::Button, Qt::darkRed );
            qobject_cast<QPushButton *>(kmapTable1->cellWidget(i,j))->setPalette( pal );
            qobject_cast<QPushButton *>(kmapTable1->cellWidget(i,j))->setAutoFillBackground( true );
         }
      }
   }
}
void Kmap::buttonSetup(){
       kmapTable1->setRowCount(8);
       kmapTable1->setColumnCount(8);
   int buttonLocation = 0;
      for(int i=0;i<8;i++) {
         for(int j=0;j<8;j++) {
            //kmapTable1->setCellWidget(i, j, kmapButtonGroup1->button(buttonLocation));
            kmapButtonsList.append(new QPushButton("0"));
            kmapButtonGroup1->addButton(kmapButtonsList.at(buttonLocation));
            kmapButtonGroup1->setId(kmapButtonsList.at(buttonLocation),buttonLocation);
            kmapTable1->setCellWidget(i, j, kmapButtonGroup1->button(buttonLocation));
            buttonLocation++;
         }
      }
}
