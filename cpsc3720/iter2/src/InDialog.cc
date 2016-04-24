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
\brief Implementation file for the InDialog class

\date Feb 22, 2010
\author Nathan
**********************************************************************/

#include<QSizePolicy>
#include "InDialog.h"

/********************************************************************
public
**********************************************************************/

/**
 Constructor
*/
InDialog::InDialog(DataBackend*& inData, QWidget* parent) : QDialog(parent){
  myData=inData;

  setupObjects();
  setupLayout();
  setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
  update();
}

/********************************************************************
public slots
**********************************************************************/

/**
   Cancel the modify operation
*/
void InDialog::cancel(){
  reject();
}

/**
 Set the new table size in myData, and redraw the table.
*/
void InDialog::changeTableSize(int n) {
  myData->setNumVars(n);
  update();
}

/**
  Check and then set the names into the databackend
*/
void InDialog::setNames(){
  QList<QString> newNames;
  for(int i=0;i<varNames.size();i++)
    newNames.push_back(varNames[i]->text());
  myData->setVarNames(newNames);
  update();
}

/**
 Submit data from the KMapInDialog
*/
void InDialog::submit() {
  accept();
}


/**
  Refresh the dialog to represent the data in myData
*/
void InDialog::update(){
  int n = myData->getNumVars();
  while(varNames.size()<n){
     varNames.push_back(new InputVariableNameWidget(this, varNames.size()));
     namesVBox->addWidget(varNames.back());
  }
  while(varNames.size()>n){
    namesVBox->removeWidget(varNames.back());
    delete varNames.back();
    varNames.pop_back();
  }

  QStringList tmpNames=myData->getVarNames();
  for(int i=0;i<tmpNames.size();i++){
    varNames[i]->setText(tmpNames[i]);
  }
}


/********************************************************************
protected
**********************************************************************/

/**
Setup the dialog's layout
*/
void InDialog::setupLayout() {
  QHBoxLayout* hbox=new QHBoxLayout();
  hbox->addWidget(new QLabel("# of variables:"));
  hbox->addWidget(numVarSelect);
  hbox->addStretch();
  namesVBox=new QVBoxLayout();

  QVBoxLayout* vbox=new QVBoxLayout();
  vbox->addLayout(hbox);
  vbox->addLayout(namesVBox);
  vbox->addStretch();
  vbox->addWidget(saveNameButton);
  //vbox->addStrut(300);

  widgetHBox=new QHBoxLayout();
  widgetHBox->addLayout(vbox);
  
  QHBoxLayout* buttons = new QHBoxLayout();
  buttons->addStretch();
  buttons->addWidget(cancelButton);
  buttons->addWidget(submitButton);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addLayout(widgetHBox);
  mainLayout->addLayout(buttons);
  
  setLayout(mainLayout);
}

/**
Setup the dialog's buttons
*/
void InDialog::setupObjects() { 
  numVarSelect=new QSpinBox();
  numVarSelect->setRange(MIN_NUM_VARS,MAX_NUM_VARS);
  numVarSelect->setValue(myData->getNumVars());
  connect(numVarSelect, SIGNAL(valueChanged(int)), 
	  this, SLOT(changeTableSize(int)));

  cancelButton = new QPushButton("&Cancel");
  connect(cancelButton,SIGNAL(clicked()), this, SLOT(cancel()));

  saveNameButton = new QPushButton("Save &Names");
  connect(saveNameButton,SIGNAL(clicked()), this, SLOT(setNames()));

  submitButton = new QPushButton("&Submit Data");
  connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
}

/********************************************************************
private
**********************************************************************/
