/****************************************************************************
This file is part of KMapper.

KMapper is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
KMapper is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with KMapper.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

/********************************************************************//**
\file
\brief Interface file for the EquationInDialog class

\date Feb 22, 2010
\author Nathan
**********************************************************************/

#include<QLineEdit>
#include<QStringList>
#include<QMessageBox>
				  
#include "EquationParser.h"				  
#include "DataBackend.h"
#include "EquationInDialog.h"

/********************************************************************
public
**********************************************************************/

/**
 Constructor
*/
EquationInDialog::EquationInDialog(DataBackend*& inData, QWidget* parent) : 
  InDialog(inData, parent) {
  setWindowTitle("Enter Equation");
  equationLabel=new QLabel("f()=", this);
  widgetHBox->addWidget(equationLabel);
  equationLine = new QLineEdit(this);
  widgetHBox->addWidget(equationLine);
  update();
}

/********************************************************************
public slots
**********************************************************************/

/**
Submit data from the EquationInDialog
*/
void EquationInDialog::submit() {
   EquationParser checkInput;
   std::vector<string> variableNames;
   QList<QString> tempVarNames = myData->getVarNames();
   for(int i=0;i<tempVarNames.size();i++)
      variableNames.push_back(tempVarNames.at(i).toStdString());
   
   if (!checkInput.isValid(equationLine->text().toStdString(),variableNames))
      QMessageBox::warning(this, tr("Invalid input!"),
			   tr(checkInput.getErrorMessage().c_str()));
   else{
      myData->parse(equationLine->text());
      InDialog::submit();
   }
}

/**
  Refresh the dialog to represent the data in myData
*/
void EquationInDialog::update(){
  InDialog::update();

  QStringList varNames=myData->getVarNames();

  QString equationTxt=tr("f(");
  for(int i=0;i<varNames.size();i++){
    if(i!=0) equationTxt+=tr(",");
    equationTxt+=varNames[i];
  }
  equationTxt+=tr(")=");
  equationLabel->setText(equationTxt);
}

/********************************************************************
private
**********************************************************************/
