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
\brief Interface file for the TruthTableInDialog class -- TruthTableInDialog.h

\date Jan 31, 2010
\author Nathan
**********************************************************************/

#ifndef TRUTHTABLEINDIALOG_H
#define TRUTHTABLEINDIALOG_H

#include"InDialog.h"

class TruthTableWidget;

/*********************************************************************//**
\brief Input dialog to get input in TruthTable form. 

This class represents the dialog for receiving Truth Table input from the user
**********************************************************************/
class TruthTableInDialog : public InDialog {
   
  Q_OBJECT

 public:
   
  /// Constructor
  TruthTableInDialog(DataBackend*&, QWidget* parent=0); 
  ///Destructor
  virtual ~TruthTableInDialog(){}

 public slots:  
  /// Check and then set the names into the databackend
  virtual void setNames();
  /// Submit data from the KMapInDialog
  virtual void submit();
  /// Update the contents of the dialog
  virtual void update();
  
 private:
  TruthTableWidget* ttWidget; ///< Widget to display TT and get input from user

};

#endif
