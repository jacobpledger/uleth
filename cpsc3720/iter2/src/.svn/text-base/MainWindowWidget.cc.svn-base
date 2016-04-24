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
\brief Interface file for the MainWindowWidget class

\date Feb 17, 2010
\author Nathan
**********************************************************************/

#include<iostream>

#include<QLabel>
#include<QLayout>
#include<QStringList>

#include "DataBackend.h"
#include "KMapWidget.h"
#include "MainWindowWidget.h"
#include "TruthTableWidget.h"

/********************************************************************
public
**********************************************************************/

/**
   Constructor

   Setup all objects in the widget, lay them out, and set defaults.
*/
MainWindowWidget::MainWindowWidget(DataBackend*& data,QWidget* parent=0) : QWidget(parent) {
  myData=data;
  TT=new TruthTableWidget(data, this);
  TT->setEditable(false);
  KMap=new KMapWidget(data, this);
  KMap->setEditable(false);
  POSFunction = new QLabel("POS:");
  SOPFunction = new QLabel("SOP:");

  POSTermsLine=new QLineEdit(this);
  POSTermsLine->setReadOnly(true);
  SOPTermsLine=new QLineEdit(this);
  SOPTermsLine->setReadOnly(true);
  POSLine=new QTextEdit(this);
  POSLine->setReadOnly(true);
  POSLine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  POSLine->setMaximumHeight(80);
  SOPLine=new QTextEdit(this);
  SOPLine->setReadOnly(true);
  SOPLine->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  SOPLine->setMaximumHeight(80);
  setupLayout();

  update();
}

/********************************************************************
public slots
**********************************************************************/
/**
   Slot to be called when we want to minimize the data.

   Minimize slot.  Calls dataBackendMinimize function, and updates widget
*/
void MainWindowWidget::minimize(){
  myData->minimizeBoth();
  update();
}

/**
 Slot to be used when the widget's contents should be updated from data

 Draws the contents of the window according to the current data in myData
*/
void MainWindowWidget::update(DataBackend* data) {
   if(data) myData=data;
   if(!myData) return; //Check that we have real data

  //Update the TT and KMap
  KMap->update(myData);
  TT->update(myData);
  //Update the function labels

  QStringList varNames=myData->getVarNames();

  QString equationTxt=tr("f(");
  for(int i=0;i<varNames.size();i++){
    if(i!=0) equationTxt+=tr(",");
    equationTxt+=varNames[i];
  }

  equationTxt+=tr(")=");
  SOPFunction->setText(equationTxt+QChar(0x03A3));
  POSFunction->setText(equationTxt+QChar(0x03A0));
  //Update the POS and SOP terms.
  QVector<int> POSterms;
  QVector<int> SOPterms;
  //Update the result strings
  POSTermsLine->setText(myData->getPOSMaxTerms());
  SOPTermsLine->setText(myData->getSOPMinTerms());
  POSLine->setText(myData->getPOSResult());
  SOPLine->setText(myData->getSOPResult());
}

/********************************************************************
private
**********************************************************************/

/**
   Align all widgets within the widget
*/
void MainWindowWidget::setupLayout(){
   //The top bar
   QHBoxLayout* topLayout = new QHBoxLayout();
   QVBoxLayout* lyt = new QVBoxLayout();
   lyt->addWidget(TT);
   lyt->addStretch();
   topLayout->addLayout(lyt);

   lyt=new QVBoxLayout();
   lyt->addWidget(KMap);
   lyt->addStretch();
   topLayout->addLayout(lyt);
   //topLayout->addStretch();
   
   //Middle bar
   QHBoxLayout* middleLayout = new QHBoxLayout();
   middleLayout->addWidget(SOPFunction);
   middleLayout->addWidget(SOPTermsLine);
   middleLayout->addWidget(POSFunction);
   middleLayout->addWidget(POSTermsLine);
      
   //Bottom row
   QLabel* lbl1=new QLabel("SOP:");
   QLabel* lbl2=new QLabel("POS:");
   QHBoxLayout* bottomLayout = new QHBoxLayout();
   bottomLayout->addWidget(lbl1);
   bottomLayout->addWidget(SOPLine);
   bottomLayout->addWidget(lbl2);
   bottomLayout->addWidget(POSLine);
   
   //The main layout
   QVBoxLayout* mainLayout = new QVBoxLayout();
   mainLayout->addLayout(topLayout);
   mainLayout->addLayout(middleLayout);
   mainLayout->addLayout(bottomLayout);
   setLayout(mainLayout);
   
}
