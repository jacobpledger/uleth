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
\brief Interface file for the HelpDialog class

\date April 4, 2010
\author Nathan
**********************************************************************/

#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include<QDialog>
class QPushButton;
class QTextBrowser;

/*********************************************************************//**
\brief The help dialog

This class provides the help dialog to display an html help file to the user
**********************************************************************/
class HelpDialog : public QDialog {
  Q_OBJECT

 public:
  /// Constructor
  HelpDialog(QWidget* parent=0);

 private:
  ///Setup the dialog's objects
  void setupObjects();
  ///Setup the dialog's layout
  void setupLayout();
  ///Set the content of the text browser
  void setContent();

  QTextBrowser* content; ///< Holds the content of the dialog
  QPushButton* doneButton; ///< Button to close dialog
 
};

#endif
