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

/*********************************************************************//**
\file
\brief Implementation file for the HelpDialog class

\date April 4, 2010
\author Nathan
**********************************************************************/

#include<QFile>
#include<QHBoxLayout>
#include<QPushButton>
#include<QTextBrowser>
#include<QTextStream>
#include<QVBoxLayout>

#include "HelpDialog.h"

/********************************************************************
public
**********************************************************************/
HelpDialog::HelpDialog(QWidget* parent) : QDialog(parent) {
  setupObjects();
  setupLayout();
  setContent();
  resize(400,500);
}

/********************************************************************
private
**********************************************************************/

/**
Setup the dialog's objects
*/
void HelpDialog::setupObjects(){
  doneButton = new QPushButton("&Close",this);
  connect(doneButton, SIGNAL(clicked()), this, SLOT(accept()));

  content = new QTextBrowser(this);
}

/**
   Setup the dialog's layout
*/
void HelpDialog::setupLayout(){
  QHBoxLayout* horLyt = new QHBoxLayout;
  horLyt->addStretch();
  horLyt->addWidget(doneButton);
  
  QVBoxLayout* mainLyt = new QVBoxLayout;
  mainLyt->addWidget(content);
  mainLyt->addLayout(horLyt);

  setLayout(mainLyt);
  
}

/**
   Set the content of the text browser
*/
void HelpDialog::setContent(){
  QFile helpFile(":/help/index.html");
  helpFile.open(QIODevice::ReadOnly);
  QTextStream in(&helpFile);
  QString lines=in.readAll();
  helpFile.close();
  
  content->setHtml(lines);
}
