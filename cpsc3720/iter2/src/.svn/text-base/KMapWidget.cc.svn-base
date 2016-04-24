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
\brief Interface file for the KMapWidget class

\date Feb 17, 2010
\author Nathan
**********************************************************************/

#include<cassert>
#include<QHeaderView>
#include<QScrollBar>

#include "Common.h"
#include "DataBackend.h"
#include "KMapWidget.h"

/********************************************************************
public
**********************************************************************/

/**
   Constructor
*/
KMapWidget::KMapWidget(DataBackend*& data, QWidget* parent) : QWidget(parent){
  myData=data;
  editable=false;
  stateChanged=false;
  nRow=0;
  nCol=0;

  layout=new QGridLayout(this);
  
  horizontalTitle=new QLabel("TOP",this);
  layout->addWidget(horizontalTitle,0,1,Qt::AlignHCenter);
  
  verticalTitle=new QLabel("LEFT",this);
  layout->addWidget(verticalTitle,1,0,Qt::AlignVCenter);
  
  table=new QTableWidget(this);
  layout->addWidget(table,1,1);
  
  setLayout(layout);

  valueButtons=new QButtonGroup(this);
  connect(valueButtons, SIGNAL(buttonClicked(int)),
	  this,SLOT(incrementValue(int)));
  setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

KMapWidget::~KMapWidget(){
   clear();
}

/**
   Return a size hint for this widget
*/

QSize KMapWidget::sizeHint () const{
  int height=horizontalTitle->height() +
    table->horizontalHeader()->height() + hFudge;
  for(int i=0;i<table->rowCount();i++)
    height+=table->rowHeight(i);
  int width=verticalTitle->width() + 
    table->verticalHeader()->width() + wFudge;
  for(int i=0;i<table->columnCount();i++)
    width+=table->columnWidth(i);
  return QSize(width,height);
}
/**
   Return the minimum size hint for this widget
*/
QSize KMapWidget::minimumSizeHint() const{
   int height=horizontalTitle->height() + 
     table->horizontalHeader()->height() + hFudge;
   for(int i=0;i<table->rowCount();i++)
      height+=table->rowHeight(i);
   int width=verticalTitle->width() +
     table->verticalHeader()->width() + wFudge;
   for(int i=0;i<table->columnCount();i++)
      width+=table->columnWidth(i);
   return QSize(min(width,800),min(height,800));
}

/********************************************************************
public slots
**********************************************************************/

/**
   Clear all elements in the table
 */
void KMapWidget::clear(){
  horizontalTitle->clear();
  verticalTitle->clear();
  table->setRowCount(0);
}

/** 
    Set whether the user can edit the contents of the widget.

    Set if the widget is editable according to parameter.  Update the
    widget accrodingly.  
    \param editable If the widget will be set active or not.
 */
void KMapWidget::setEditable(bool editable){
   this->editable=editable;
   stateChanged=true;
   update();
}

/** 
    Set the table's headers.
*/
void KMapWidget::setHeaders(){
  horizontalTitle->setText(myData->getHorizontalTitle());
  verticalTitle->setText(myData->getVerticalTitle());
  QStringList tmp=myData->getHorizontalKMapHeader();
  table->setHorizontalHeaderLabels(tmp);
  tmp=myData->getVerticalKMapHeader();
  table->setVerticalHeaderLabels(tmp);
}

/**
   Sets the value in the KMap to the one stored in DataBackend

   \param r The row in the KMap
   \param c The column in the KMap
 */
void KMapWidget::setValue(int r, int c){
  QString text=myData->valueToString(myData->getMinTerm(r,c));
  QPushButton* widget=(QPushButton*)table->cellWidget(r, c);
  if(widget) widget->setText(text);
  QTableWidgetItem* myItem=table->item(r, c);
  if(myItem) myItem->setText(text);
}

/**
   updates the KMap widget with the most recent data

   \\param inData Pointer to the new data.
*/
void KMapWidget::update(DataBackend* inData) {
   if(inData) myData=inData;
   assert(myData);
   int r,c;
   myData->getKMapSize(r,c);
   if(r!=nRow || c!=nCol || stateChanged){
      resizeTable();
   }
   colorGroups();
   setHeaders();
}
/********************************************************************
private slots
**********************************************************************/
/**
   Increment the value at given position

   \param n The index of the button clicked.  This corresponds to nCol*row + col
in the KMap.
*/
void KMapWidget::incrementValue(int n){
  int r, c;
  assert(nCol);
  r=n/nCol;
  c=n%nCol;
  myData->increment(r,c);
  setValue(r,c);
}

/********************************************************************
private
**********************************************************************/

/**
   Color the table according to minimization groupings
*/
void KMapWidget::colorGroups(){
   int nRow,nCol;
   myData->getKMapSize(nRow,nCol);
   QVector<int> mintermCount=myData->getNumberOfTimes();
   for(int i=0;i<nRow;i++){
      for(int j=0;j<nCol;j++){
	 QTableWidgetItem* item=table->item(i, j);
	 if(item){
	    int index=myData->getMinTermLocation(i,j);
	    switch(mintermCount[index]){
	       case 0:
		  break;
	       case 1:
		  item->setBackground(QBrush(QColor(0,0,255,50)));
		  break;
	       case 2:
		  item->setBackground(QBrush(QColor(0,0,255,100)));
		  break;
	       case 3:
		  item->setBackground(QBrush(QColor(0,0,255,150)));
		  break;
	       case 4:
		  item->setBackground(QBrush(QColor(0,0,255,200)));
		  break;
	       default:
		  item->setBackground(QBrush(QColor(0,0,255,250)));
		  break;
	    }
	 }
	 
      }
   }
}

/**
   Resizes the table to the correct size, as determined by the databackend

*/
void KMapWidget::resizeTable(){
  clear();
  myData->getKMapSize(nRow,nCol);
  table->setRowCount(nRow);
  table->setColumnCount(nCol);
  for(int i=0;i<nRow;i++){
    for(int j=0;j<nCol;j++){
      QString text=myData->valueToString(myData->getMinTerm(i,j));
      if(editable){
	QPushButton* tmp=new QPushButton(text, this);
	valueButtons->addButton(tmp, i*nCol+j);
	table->setCellWidget(i,j, tmp);
      }
      else{
	QTableWidgetItem* tmp=new QTableWidgetItem(text);
	tmp->setFlags(Qt::ItemIsEnabled);
	table->setItem(i,j,tmp);
      }
      setValue(i,j);
    }
  }

  for(int i=0;i<nCol;i++){
    table->setColumnWidth(i,40);
  }
}

