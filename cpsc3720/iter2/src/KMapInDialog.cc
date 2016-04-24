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
\brief Interface file for the KMapInDialog class

\date Feb 22, 2010
\author Nathan
**********************************************************************/

#include <QVBoxLayout>

#include "DataBackend.h"
#include "KMapInDialog.h"
#include "KMapWidget.h"

/********************************************************************
public
**********************************************************************/

/**
 Constructor
*/
KMapInDialog::KMapInDialog(DataBackend*& inData, QWidget* parent) : InDialog(inData, parent){
  setWindowTitle("Enter Karnaugh Map");

  kmapWidget=new KMapWidget(inData, this);
  kmapWidget->setEditable(true);
  
  QVBoxLayout* lyt=new QVBoxLayout();
  lyt->addWidget(kmapWidget);
  lyt->addStretch();

  widgetHBox->addLayout(lyt);
  widgetHBox->addStretch();
}

/********************************************************************
public slots
**********************************************************************/

/** 
    Check and then set the names into the databackend
 */
void KMapInDialog::setNames(){
  InDialog::setNames();
  kmapWidget->setHeaders();
}

/**
Submit data from the KMapInDialog
*/
void KMapInDialog::submit() {
  InDialog::submit();
}

/**
 Update the window's components according to data in myData
*/
void KMapInDialog::update() {
  InDialog::update();
  kmapWidget->update();
}

/********************************************************************
private
**********************************************************************/

