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
\brief Interface file for the MainWindowWidget class

\date Feb 19, 2010
\author Nathan
**********************************************************************/

#ifndef MAINWINDOWWIDGET_H
#define MAINWINDOWWIDGET_H

#include<QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QTextEdit>

class DataBackend;
class KMapWidget;
class TruthTableWidget;

/**********************************************************************//**
\brief The MainWindow's central widget 

This class is a widget to be used as the centra   moc_TableButton.o
KMapInDialog.o                  l widget to the main window.
**********************************************************************/
class MainWindowWidget : public QWidget{
   
  Q_OBJECT

public:
  /// Constructor
   MainWindowWidget(DataBackend*&, QWidget*);
signals:

public slots:
  /// Slot to be called when we want to minimize the data.
  void minimize();
  /// Slot to be used when the widget's contents should be updated from data
  void update(DataBackend* data=0);
private:

  ///Align all widgets within the widget
  void setupLayout();
  
  DataBackend* myData;
  TruthTableWidget* TT;
  KMapWidget* KMap;
  
  QLabel* POSFunction;
  QLabel* SOPFunction;
  QLineEdit* POSTermsLine;
  QLineEdit* SOPTermsLine;
  QTextEdit* POSLine;
  QTextEdit* SOPLine;

};

#endif
