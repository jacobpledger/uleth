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
\brief Interface file for the KMapWidget class

\date Jan 31, 2010
\author Nathan
**********************************************************************/


#ifndef KMAPWIDGET_H
#define KMAPWIDGET_H

#include<QButtonGroup>
#include<QLabel>
#include<QGridLayout>
#include<QTableWidget>
#include<QWidget>


class DataBackend;

/**********************************************************************//**
\brief The KMap Widget class for GUI representation of a K-Map 

This class is a widget that represents a K-Map.  It passes data to/from
the DataBackEnd via a KMapAdaptor.
**********************************************************************/

class KMapWidget : public QWidget{
   
  Q_OBJECT

 public:
   
  /// Constructor
  KMapWidget(DataBackend*&, QWidget* parent=0);
  /// Destructor
  ~KMapWidget();
  /// Accessor method for if the widget is editable
  bool isEditable() { return editable; }
  /// Return a size hint for this widget
  virtual QSize sizeHint () const;
  /// Return the minimum size hint for this widget
  virtual QSize minimumSizeHint() const;
 public slots:

  /// Clear all elements in the table
  virtual void clear();
  /// Set whether the user can edit the contents of the widget.
  void setEditable(bool);
  /// Set the table's headers
  void setHeaders();
  /// Set the value in the KMap to the one stored in DataBackend
  void setValue(int, int);
  /// updates the KMap widget with the most recent data
  void update(DataBackend* inData=0);

  private slots:

  ///Increment the value at given position
  void incrementValue(int);
  
  private:

  static const int hFudge=30; ///<Height fudge factor in size hint
  static const int wFudge=30; ///<Width fudge factor in size hint

  ///Color the table according to minimization groupings
  void colorGroups();
  ///Resize the table, according to the size of the table
  void resizeTable();
  
  int height; ///< The total height of this widget
  int width; ///< The total width of this widget

  int nRow; ///< The number of rows in the KMap
  int nCol; ///< The number of columns in the KMap
  bool editable; ///< Store if the widget is editable or not.
  bool stateChanged; ///<Store if the widgets state has changed
  
  QButtonGroup* valueButtons; ///< The buttons in the table.
  QLabel* horizontalTitle;
  QLabel* verticalTitle;
  QTableWidget* table;
  QGridLayout* layout;
  
  DataBackend* myData; ///<Pointer to the actual data
   
};

#endif
