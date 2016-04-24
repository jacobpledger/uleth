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
\brief Interface file for the TruthTableWidget class -- TruthTableWidget.h

\date Jan 31, 2010
\author Nathan
**********************************************************************/


#ifndef TRUTHTABLEWIDGET_H
#define TRUTHTABLEWIDGET_H


#include<QButtonGroup>
#include<QList>
#include<QPushButton>
#include<QString>
#include<QStringList>
#include<QTableWidget>

class DataBackend;

/*********************************************************************//**
\brief TruthTable Widget class for GUI representation of a Truth Table 

This class is a widget that represents data as a Truth Table and allows 
the user to modify the TruthTable.
**********************************************************************/
class TruthTableWidget : public QTableWidget{
   
  Q_OBJECT
    
 public:
   /// Constructor
   TruthTableWidget(DataBackend*&, QWidget* = 0);
   /// Destructor
   ~TruthTableWidget();
   /// Accessor method for if the widget is editable
   bool isEditable() { return editable; }
   /// Return a size hint for this widget
   virtual QSize sizeHint () const;
   /// Return the minimum size hint for this widget
   virtual QSize minimumSizeHint() const;
  signals:

   /**Signal emitted when a value in the table is changed.
      
      \param n the row of the variable that was just changed.
   */
   void valueChanged(int n);
   
   public slots:
   /// Clear all elements in the table.
   virtual void clear();
   /// Set whether the user can edit the contents of the widget.
   void setEditable(bool);
   /// Set the table's headers.
   void setHeaders();
   /// Indicate the widget to update the value at given position.  
   void setValue(int);
   /// Update the widget
   void update(DataBackend* data=0);

   private slots:
   /// Set the value at given position
   void incrementValue(int);
   
  private:
   
   static const int wFudge=5; ///<Width fudge factor in size hint
   static const int hFudge=5; ///<Height fudge factor in size hint

   ///Resizes the table to r rows, c columns
   void resizeTable();
   
   bool editable; ///< Store if the widget is editable or not.
   bool stateChanged; ///<Store if the widget's state has changed since last update.
   int numVars; ///< Store the number of variables this widget is set to hold

   DataBackend* myData; ///<Pointer to the actual data
   QButtonGroup* valueButtonGroup;
   
};

#endif
