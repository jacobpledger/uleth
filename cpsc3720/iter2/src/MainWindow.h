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
\brief Interface file for the MainWindow class

\date Jan 31, 2010
\author Nathan
**********************************************************************/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QInputDialog>
#include<QtGui>

class DataBackend;
class AboutDialog;
class HelpDialog;
class MainWindowWidget;

/*********************************************************************//**
\brief The main GUI display window 

This class represents the main GUI window of the application.
**********************************************************************/
class MainWindow : public QMainWindow{
  
  Q_OBJECT

public:
  ///Constructor 
  MainWindow(QWidget* parent=NULL); 
    
public slots:

private slots:

  /// imports K-Map data from a .pla file
  void importFile();
  /// exports K-Map data to a .pla file
  void exportFile(); 
  /// minimizes the K-Map data to obtain a solution
  void minimize(); 
  /// create a new K-Map project
  void newMap(); 
  /// modify an existing K-Map project
  void modifyMap(); 
  /// close the program
  void closeProgram();
  /// open the help dialog
  void userHelp();
  ///  Display info about the current program
  void aboutKMapper();
  /// Display the current version of qt being used, for user reference
  void aboutQt();
  /// update the state of the window
  void update();

private:

  /// The different allowed types of input.  None if no input will be read.
  enum INPUT_TYPE {KMAP=259, TRUTH_TABLE=260, EQUATION=261, NONE=262};
  /// Get the input from user
  bool getInput(DataBackend*);
  /// Get the input type from the user.
  INPUT_TYPE getInputType();
  /// Setup actions
  void setupActions();
  // Setup menus
  void setupMenus();


  DataBackend* myData; ///<Stores the applications truth table data.
  MainWindowWidget* mainWidget; ///<The central widget
  AboutDialog* aboutDialog; ///<An about dialog for the program
  HelpDialog* helpDialog; ///<A help dialog for the program
  bool hasActiveData; ///< Stores if there is active data

  QAction* newAction; ///<Action to create new KMap
  QAction* modifyAction; ///<Action to modify KMap
  QAction* importAction; ///<Action to import from file
  QAction* exportAction; ///<Action to export to file
  QAction* closeAction; ///<Action to close the program
  QAction* helpAction; ///<Action to open the help dialog
  QAction* aboutAction; ///<Action to open the about dialog
  QAction* aboutQtAction; ///<Action for about QT
};

#endif
