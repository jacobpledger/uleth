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

/**********************************************************************//**
\file
\brief Interface file for the EquationInDialog class

\date Jan 31, 2010
\author Nathan
***********************************************************************/


#ifndef EQUATIONINDIALOG_H
#define EQUATIONINDIALOG_H

class QLabel;
class QLineEdit;

#include"InDialog.h"


/**********************************************************************//**
\brief The equation input dialog

This class contains the dialog for receiving equation input from the user
***********************************************************************/
class EquationInDialog : public InDialog {
   
  Q_OBJECT

 public:
  /// Constructor
  EquationInDialog(DataBackend*&, QWidget* parent=0); 

 public slots:  
  ///Submit data from the EquationInDialog
  virtual void submit(); 
  ///Refresh the dialog to represent the data in myData
  virtual void update();
 private:
  QLabel* equationLabel;
  QLineEdit* equationLine;
};

#endif
