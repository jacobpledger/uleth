#ifndef KMAP_H
#define KMAP_H

#include <QWidget>
#include <QTableWidget>
#include <QVector>
#include <QPushButton>
#include <QString>
#include <QButtonGroup>

/*!
   @class Kmap
   @brief The widget containing kmap information.
   The kmap class handles information regarding 
   the values of a kmap.
   @author Curtis, Gezim, Jacob, Jeremy

*/

class Kmap : public QWidget {

   Q_OBJECT

public:


///Kmap constructor.
/*!
   A constructor that creates a kmap object.
*/
   Kmap(QWidget *parent = 0);

signals:
   void sendDataToTruthTable(QString tempString);
public slots:
/*!
   Changes the symbol displayed in the sector of the kmap to the next symbol.
   Order: 0,1,X
   @param *QAbstractButton
*/
   void setNextButtonValue(QAbstractButton *button);
   void setNumberOfVariables(int numVars);
   void setKmapString(QString str);
   void toggleKmap(bool checked);
   void sendTruthTableData();
   void setKmapColors(QVector<int>);
   void clearKmap();

private:
///QTableWidget to organize the widget
   QTableWidget *kmapTable1;
///Buttons for each Kmap block.
   QList<QPushButton*> kmapButtonsList;
///QVector of strings storing the kmap data
   QString kmapData;
///QButtonGroup for the buttons on the kmap regions
   QButtonGroup *kmapButtonGroup1;
   int numberOfVariables;
   int numberOfRows, numberOfCols;
   void buttonSetup();
   bool enabled;

};

#endif

