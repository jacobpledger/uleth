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

/********************************************************************//**
\file
\brief Interface file for the MainWindow class

\date Feb 17, 2010
\author Nathan
**********************************************************************/

#include<iostream>
#include<QDir>
#include<QMessageBox>

#include "MainWindow.h"
#include "DataBackend.h"
#include "MainWindowWidget.h"
#include "AboutDialog.h"
#include "HelpDialog.h"
#include "InDialog.h"
#include "EquationInDialog.h"
#include "KMapInDialog.h"
#include "TruthTableInDialog.h"


/********************************************************************
public
**********************************************************************/

/**
Constructor 

Creates the main window, and all objects that it contains.
\param parent The parent of this window.  Defaults to NULL.
*/
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent){
  aboutDialog=NULL;
  helpDialog=NULL;
  hasActiveData=false;
  myData=new DataBackend();
  mainWidget=new MainWindowWidget(myData, this);
  resize(500,500);
  setWindowIcon(QIcon(":/icons/appIcon.png"));  
  setCentralWidget(mainWidget);

  setupActions();
  setupMenus();

  statusBar()->show();
  
  update();
}

/********************************************************************
public slots
**********************************************************************/

/********************************************************************
private slots
**********************************************************************/

/**
 imports K-Map data from a .pla file

 Gets file name from user, then uses a PlaAdaptor to read the file.
*/
void MainWindow::importFile() {
  QString fileName;
  fileName=QFileDialog::getOpenFileName(this, "Select file to import:",
					QDir::homePath(), "*.pla");
  
  if(fileName.isNull()){
    std::cerr << "WARNING: No filename selected\n";
    return;
  }

  DataBackend* pla=new DataBackend();
  if(pla->importFile(fileName)){
     delete myData;
     myData=pla;
     //Reactivate the menu items.
     hasActiveData=true;
     mainWidget->update(myData);
     minimize();
  }
  else{
     QMessageBox::
	warning(this, "File read failed", 
		QString("File \"%1\" could not be read.").arg(fileName));
     std::cerr << "ERROR: File read failed\n";
  }
}

/**
 exports K-Map data to a .pla file

 Gets the filename from user, and uses a PlaAdaptor to save current contents 
 to file.
*/
void MainWindow::exportFile() {
  QString fileName;
  fileName=QFileDialog::getSaveFileName(this, "Select filename to export:",
					QDir::homePath());
  if(fileName.isNull()){
    std::cerr << "WARNING: No filename selected\n";
    return;
  }
  if(!myData->exportFile(fileName)){
    QMessageBox::warning(this, 
			 "File not saved", 
			 QString("File \"%1\" not saved.").arg(fileName));
  }
}

/**
 minimizes the K-Map data to obtain a solution
*/
void MainWindow::minimize() {
   //std::cerr<<"MINIMIZE\n";
  mainWidget->minimize();
  //std::cerr<<"UPDATE\n";
  update();
  //std::cerr<<"DONE\n";
}

/**
 create a new K-Map project

 Gets input method from user, then spawns appropriate window to read data 
 from user
*/
void MainWindow::newMap() {
   DataBackend* tmpData=new DataBackend(4);
  if(getInput(tmpData)){
     delete myData;
     myData=tmpData;
     hasActiveData=true;
     mainWidget->update(myData);
     minimize();
  }
}

/**
 modify an existing K-Map project

 Gets the input method from user, then spawns appropriate window (which 
 shows the current contents of the Databackend) and allows the user to modify
 the input.
*/
void MainWindow::modifyMap() {
   DataBackend* tmpData=new DataBackend();
   (*tmpData) = (*myData);
   if(getInput(tmpData)){
      delete myData;
      myData=tmpData;
      hasActiveData=true;
      mainWidget->update(myData);
      minimize();
   }
}

/**
   Close the program

   Prompt the user to make sure they want to quit and quit if a
   positive response is recieved.
*/
void MainWindow::closeProgram() {
   QMessageBox* prompt=
      new QMessageBox(QMessageBox::Question,
		      QString("Close program"),
		      QString("Are you sure you want to quit?"),
		      QMessageBox::Yes | QMessageBox::No);
   prompt->setDefaultButton( (QPushButton*)prompt->button(QMessageBox::No));

   int button=prompt->exec();
   if(button==QMessageBox::Yes) close();
}

/**
   Open the help dialog

   Opens a help dialog which displays a set of html help documentation
*/
void MainWindow::userHelp(){
   if(!helpDialog)
      helpDialog = new HelpDialog(this);
   helpDialog->show();
}


/**
   Display info about the current program
*/
void MainWindow::aboutKMapper(){
  if(!aboutDialog)
     aboutDialog = new AboutDialog(this);
  aboutDialog->exec();
}


/**
   Display the current version of qt being used, for user reference
*/
void MainWindow::aboutQt(){
  QMessageBox::aboutQt(this, "About Qt");
}

/** 
    Update the state of the window
*/
void MainWindow::update(){
   mainWidget->setVisible(hasActiveData);
   modifyAction->setEnabled(hasActiveData);
   exportAction->setEnabled(hasActiveData);
   mainWidget->update();
}

/********************************************************************
private
**********************************************************************/

/** 
    Get the input from user

    \param data The object to read data into.
    \return true if the data read was succesful
    \post data is set to the new input, or unchanged if input did not occur
*/
bool MainWindow::getInput(DataBackend* data){
   INPUT_TYPE type=getInputType();
   InDialog* inputDialog;
   switch(type){
      case KMAP:{
	inputDialog = new KMapInDialog(data);
	break;
      }
      case TRUTH_TABLE:{
	inputDialog = new TruthTableInDialog(data);
	break;
      }
      case EQUATION:{
	//QMessageBox::warning(this, "Incomplete", "Sorry, this feature is currently not implemented.");
	inputDialog = new EquationInDialog(data);
	break;
      }
      default:{
	 return false;
      }
   };
   if(inputDialog){
      int result=inputDialog->exec();
      return(result==QDialog::Accepted);
   }
   return false;
}

/**
   Get the input type from the user.

   Use an input dialog to ask the user which type of input they would
   like to make.
   \return The type of input to be read
*/
MainWindow::INPUT_TYPE MainWindow::getInputType(){
  QStringList items;
  items << "Truth Table" << "K Map" << "Equation";
  
  bool ok;
  QString choice = QInputDialog::
    getItem(this, "Choose input method", 
	    "Please select which type of input you would like to use", 
	    items, 0, false, &ok);

  if(!ok) return MainWindow::NONE;
  if(choice=="Truth Table") return MainWindow::TRUTH_TABLE;
  if(choice=="K Map") return MainWindow::KMAP;
  if(choice=="Equation") return MainWindow::EQUATION;

  return MainWindow::NONE; //default
}

/** 
Setup actions

Setup all of the main window's actions.  These exist for the menu's
functionality.
*/
void MainWindow::setupActions(){
  newAction = new QAction("&New...", this); 
  newAction->setShortcut(QKeySequence::New);
  newAction->setStatusTip("Input a new data set");
  connect(newAction, SIGNAL(triggered()), this, SLOT(newMap()));

  modifyAction = new QAction("&Modify...", this);
  modifyAction->setShortcut(tr("Ctrl+m"));
  modifyAction->setStatusTip("Modify the existing data set");
  modifyAction->setEnabled(false);
  connect(modifyAction, SIGNAL(triggered()), this, SLOT(modifyMap()));

  importAction = new QAction("&Import", this);
  importAction->setShortcut(QKeySequence::Open);
  importAction->setStatusTip("Import the contents of a file");
  connect(importAction, SIGNAL(triggered()), this, SLOT(importFile()));

  exportAction = new QAction("&Export", this);
  exportAction->setShortcut(QKeySequence::Save);
  exportAction->setStatusTip("Export the current data set to file");
  exportAction->setEnabled(false);
  connect(exportAction, SIGNAL(triggered()), this, SLOT(exportFile()));

  closeAction = new QAction("&Close", this);
  closeAction->setShortcut(QKeySequence::Close);
  closeAction->setStatusTip("Exit the program");
  connect(closeAction, SIGNAL(triggered()), this, SLOT(closeProgram()));
  
  helpAction = new QAction("User &Manual", this);
  helpAction->setShortcut(QKeySequence::HelpContents);
  helpAction->setStatusTip("Access the help manual");
  connect(helpAction, SIGNAL(triggered()), this, SLOT(userHelp()));

  aboutAction = new QAction("&About", this);
  aboutAction->setStatusTip("About this program");
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutKMapper()));

  aboutQtAction = new QAction("About &QT", this);
  aboutQtAction->setStatusTip("About the current version of QT");
  connect(aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQt()));
}

/**
   Setup menus

   Create all menu objects and add them to the main window
*/
void MainWindow::setupMenus(){
  
  QMenu* fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction(newAction);
  fileMenu->addSeparator();
  fileMenu->addAction(modifyAction);
  fileMenu->addSeparator();
  fileMenu->addAction(importAction); 
  fileMenu->addAction(exportAction); 
  fileMenu->addSeparator();
  fileMenu->addAction(closeAction);

  QMenu* helpMenu = menuBar()->addMenu("&Help");
  helpMenu->addAction(helpAction);
  helpMenu->addSeparator();
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}
