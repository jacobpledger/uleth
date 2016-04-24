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
\brief Interface file for the InDialog class

\date Jan 31, 2010
\author Nathan
**********************************************************************/


#ifndef INDIALOG_H
#define INDIALOG_H

#include<iostream>

#include<QDialog>
#include<QHBoxLayout>
#include<QPushButton>
#include<QSpinBox>
#include<QVBoxLayout>
#include<QVector>

#include"DataBackend.h"
#include "InputVariableNameWidget.h"

/*********************************************************************//**
\brief The input dialog base class

This class provides the base dialog for receiving input from user
**********************************************************************/
class InDialog : public QDialog{

  Q_OBJECT
   
 public:  
  /// Constructor
  InDialog(DataBackend*&, QWidget* parent=0); 
  ///Destructor
  virtual ~InDialog(){}
 public slots:
  ///Cancel the modify operation
  void cancel();
  /// Resize the window's components according to value in SpinBox
  virtual void changeTableSize(int);
  /// Check and then set the names into the databackend
  virtual void setNames();
  /// Submit data from the KMapInDialog
  virtual void submit();
  ///Refresh the dialog to represent the data in myData
  virtual void update();
  
 protected:
  ///Setup all the dialogs's objects
  virtual void setupObjects();
  ///Setup the dialog's layout
  virtual void setupLayout();

  QHBoxLayout* widgetHBox; ///<HBox for sub classed dialog - specific widget
  DataBackend* myData; ///<The window's data

 private:

  QVector<InputVariableNameWidget*> varNames; ///<Line editors for each variable to be entered.
  QPushButton* saveNameButton; ///<button to check and save variable names
  QPushButton* submitButton; ///<button to submit data
  QPushButton* cancelButton; ///<button to cancel the input of data
  QSpinBox* numVarSelect; ///<Selector for the # of variables in the table.
  QVBoxLayout* namesVBox; ///< VBox holding all variable names
};

#endif
