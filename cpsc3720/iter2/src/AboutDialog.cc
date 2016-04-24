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
\brief Implementation file for the AboutDialog class

\date April 4, 2010
\author Nathan
**********************************************************************/

#include<QFile>
#include<QHBoxLayout>
#include<QLabel>
#include<QMessageBox>
#include<QPushButton>
#include<QTextStream>
#include<QVBoxLayout>

#include "AboutDialog.h"

/********************************************************************
public
**********************************************************************/
AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent) {
  setupObjects();
  setupLayout();
  setContent();
  setFixedSize(250,250);
}

/********************************************************************
public slots
**********************************************************************/
void AboutDialog::displayLicense(){
  QFile aboutFile(":/help/license.txt");
  aboutFile.open(QIODevice::ReadOnly);
  QTextStream in(&aboutFile);
  QString lines=in.readAll();
  QMessageBox::information(this, "License Notice", lines);
}			     
			    

/********************************************************************
private
**********************************************************************/

/**
Setup the dialog's objects
*/
void AboutDialog::setupObjects(){
  licenseButton = new QPushButton("&License",this);
  connect(licenseButton, SIGNAL(clicked()), this, SLOT(displayLicense()));

  doneButton = new QPushButton("&Close",this);
  connect(doneButton, SIGNAL(clicked()), this, SLOT(accept()));

  imageLabel = new QLabel(this);
  content = new QLabel(this);
}

/**
   Setup the dialog's layout
*/
void AboutDialog::setupLayout(){
  QHBoxLayout* horLyt = new QHBoxLayout;
  horLyt->addStretch();
  horLyt->addWidget(licenseButton);
  horLyt->addWidget(doneButton);
  
  QVBoxLayout* mainLyt = new QVBoxLayout;
  mainLyt->addWidget(imageLabel);
  mainLyt->setAlignment(imageLabel, Qt::AlignHCenter);
  mainLyt->addWidget(content);
  mainLyt->addLayout(horLyt);

  setLayout(mainLyt);
  
}

/**
   Set the content of the text browser
*/
void AboutDialog::setContent(){
  imageLabel->setPixmap(QPixmap(":/icons/appIcon.png"));
  imageLabel->setFixedSize(64,64);
  imageLabel->setScaledContents(true);

  QFile aboutFile(":/help/about.html");
  aboutFile.open(QIODevice::ReadOnly);
  QTextStream in(&aboutFile);
  QString lines=in.readAll();
  aboutFile.close();
  content->setAlignment(Qt::AlignHCenter);
  content->setTextFormat(Qt::RichText);
  content->setWordWrap(true);
  content->setText(lines);
}
