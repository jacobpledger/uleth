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
\brief Implementation file for the TruthTableWidget class

\date Feb 17, 2010
\author Nathan
**********************************************************************/

#include<iostream>
#include<cassert>

#include<QHeaderView>
#include<QScrollBar>

#include "Common.h"
#include "DataBackend.h"
#include "TruthTableWidget.h"

/********************************************************************
public
**********************************************************************/

/**
 Constructor
*/
TruthTableWidget::TruthTableWidget(
   DataBackend*& data, QWidget* parent) : QTableWidget(parent){
   myData=data;
   editable=false;
   stateChanged=false;
   numVars=0;

   valueButtonGroup=new QButtonGroup(this);
   connect(valueButtonGroup, SIGNAL(buttonClicked(int)),
	   this, SLOT(incrementValue(int)));
   setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

/**
   Destructor
*/
TruthTableWidget::~TruthTableWidget(){
  clear();
}

/**
   Return the size hint for this widget
*/
QSize TruthTableWidget::sizeHint () const{
  int height=horizontalHeader()->height()+hFudge;
  for(int i=0;i<rowCount();i++)
    height+=rowHeight(i);
  int width=verticalHeader()->width()+wFudge;
  QScrollBar* bar=verticalScrollBar();
  if(bar && bar->isVisible()) width+=bar->width();
  for(int i=0;i<columnCount();i++)
    width+=columnWidth(i);
  return QSize(width,height);
}

/**
   Return the minimum size hint for this widget
*/
QSize TruthTableWidget::minimumSizeHint() const{
   int height=horizontalHeader()->height()+hFudge;
   for(int i=0;i<rowCount();i++)
      height+=rowHeight(i);
   int width=verticalHeader()->width()+wFudge;
   QScrollBar* bar=verticalScrollBar();
   if(bar && bar->isVisible()) width+=bar->width();
   for(int i=0;i<columnCount();i++)
      width+=columnWidth(i);
   return QSize(min(width,800),min(height,600));
}

/********************************************************************
public slots
**********************************************************************/

/**
   Clear all elements in the table

   Removes all items in the view. This will also remove 
   all selections. The table dimensions stay the same.  
*/
void TruthTableWidget::clear(){
  QTableWidget::clear();
  setRowCount(0);    
}

/** 
    Set whether the user can edit the contents of the widget.

    Set if the widget is editable according to parameter.  Update the
    widget accordingly.  
    \param editable If the widget will be set active or not.
 */
void TruthTableWidget::setEditable(bool editable){
  this->editable=editable;
  stateChanged=true;
  update();
}

/** 
    Set the table's headers.
*/
void TruthTableWidget::setHeaders(){
  QString tmp;
  QStringList varNames=myData->getVarNames();
  assert(varNames.size()==numVars);
  varNames<<"Value";
  setHorizontalHeaderLabels(varNames);
  varNames.clear();
  for(int i=0;i<rowCount();i++) varNames << tmp.setNum(i);
  setVerticalHeaderLabels(varNames);
}

/**
   Set the truth table's value at given position n

   \param n The position in the truth table to update
*/
void TruthTableWidget::setValue(int n){
  int nRow, nCol;
  myData->getTruthTableSize(nRow, nCol);
  QString text=myData->valueToString(myData->getMinTerm(n));
  QPushButton* widget=(QPushButton*)cellWidget(n, nCol-1);
  if(widget) widget->setText(text);
  QTableWidgetItem* myItem=item(n, nCol-1);
  if(myItem) myItem->setText(text);
}

/**
   Update the widget

   Update all the data and present to the user.  Assumes that if there is data
   in myData, the table exists.
   \param data If set, the databackend object has changed, so refresh it.
*/
void TruthTableWidget::update(DataBackend* data){
   if(data) myData=data;
   assert(myData);
   ///resize only if necessary.
   if(myData->getNumVars()!=numVars || stateChanged){
     resizeTable();
   }
   setHeaders();
   int nRow,nCol;
   myData->getTruthTableSize(nRow,nCol);
   for(int i=0; i<nRow; i++){
     setValue(i);
   }
   updateGeometry();
}


/********************************************************************
private slots
**********************************************************************/
/**
   Increment the value at given position
*/
void TruthTableWidget::incrementValue(int n){
  myData->increment(n);
  setValue(n);
  emit valueChanged(n);
}

/********************************************************************
private
**********************************************************************/

/**
   Resizes the table to r rows, c columns
   
   Sets the new size of the table, and creates table items as needed
   \post The table is set to correct dimensions, and table properties are set
 */
void TruthTableWidget::resizeTable(){
   clear();
   numVars=myData->getNumVars();
   QVector<QVector<TTVal::TYPE> > table=myData->getTable();
   int nRow=table.size();   
   assert(nRow>0);
   int nCol=table[0].size(); 
   assert(nCol>0);
   //Set the size
   setRowCount(nRow);
   setColumnCount(nCol);
   //Add the table elements
   for(int i=0;i<nRow;i++){
     if(editable){
       QPushButton* tmp=new QPushButton(this);
       valueButtonGroup->addButton(tmp,i);
       setCellWidget(i,nCol-1, tmp);
     }
     for(int j=0;j<nCol;j++){
       if(j==nCol-1 && editable) continue;
       QString text=myData->valueToString(table[i][j]);
       QTableWidgetItem* myitem;
       myitem=new QTableWidgetItem(text);	 
       myitem->setFlags(Qt::ItemIsEnabled);
       setItem(i,j,myitem);
     }
   }
   //Set column widths
   for(int i=0;i<nCol-1;i++){
      setColumnWidth(i,30);
   }
   setColumnWidth(nCol-1,50);
}


