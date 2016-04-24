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
\brief Interface file for the AboutDialog class

\date April 4, 2010
\author Nathan
**********************************************************************/

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include<QDialog>

class QLabel;
class QPushButton;
class QTextBrowser;

/*********************************************************************//**
\brief The help dialog

This class provides the help dialog to display an html help file to the user
**********************************************************************/
class AboutDialog : public QDialog {
  Q_OBJECT

 public:
  /// Constructor
  AboutDialog(QWidget* parent=0);

 public slots:
  ///Display the contents of the license file
  void displayLicense();
  
 private:
  ///Setup the dialog's objects
  void setupObjects();
  ///Setup the dialog's layout
  void setupLayout();
  ///Set the content of the text browser
  void setContent();

  QLabel* imageLabel; ///<The program image
  QLabel* content;
  QPushButton* licenseButton; ///< Display the GPL
  QPushButton* doneButton; ///< Button to close dialog
 
};

#endif
