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
\brief Interface file for the KMapInDialog class

\date Jan 31, 2010
\author Nathan
**********************************************************************/


#ifndef KMAPINDIALOG_H
#define KMAPINDIALOG_H


#include"InDialog.h"
class DataBackend;
class KMapWidget;

/*********************************************************************//**
\brief The KMap input dialog

This class contains the dialog for receiving KMap input from user
**********************************************************************/
class KMapInDialog : public InDialog{

  Q_OBJECT
   
 public:
  
  /// Constructor
  KMapInDialog(DataBackend*& myData, QWidget* parent=0); 
  ///Destructor
  virtual ~KMapInDialog(){}
  
public slots:
  /// Check and then set the names into the databackend
  virtual void setNames();
  ///Submit data from the KMapInDialog
  virtual void submit();
  ///Update the window
  virtual void update();
  
private:
  KMapWidget* kmapWidget;

};

#endif
