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
\brief Interface file for the TruthTableInDialog class

\date Feb 22, 2010
\author Nathan
**********************************************************************/

#include<QVBoxLayout>

#include "TruthTableInDialog.h"
#include "TruthTableWidget.h"

/********************************************************************
public
**********************************************************************/

/**
 Constructor
*/
TruthTableInDialog::
TruthTableInDialog(DataBackend*& inData, QWidget* parent) : 
  InDialog(inData,parent){
  setWindowTitle("Enter Truth Table");

  ttWidget=new TruthTableWidget(inData, this);
  ttWidget->setEditable(true);
  
  QVBoxLayout* lyt = new QVBoxLayout;
  lyt->addWidget(ttWidget);
  lyt->addStretch();
  widgetHBox->addLayout(lyt);
  widgetHBox->addStretch();
  setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
}


/********************************************************************
public slots
**********************************************************************/

/** 
    Check and then set the names into the databackend
 */
void TruthTableInDialog::setNames(){
  InDialog::setNames();
  ttWidget->setHeaders();
}

/**
 Submit data from the TruthTableInDialog
*/
void TruthTableInDialog::submit() {
  InDialog::submit();
}

/**
  Update the contents of the dialog
*/
void TruthTableInDialog::update() {
   InDialog::update();
   ttWidget->update();
}
/********************************************************************
private
**********************************************************************/
