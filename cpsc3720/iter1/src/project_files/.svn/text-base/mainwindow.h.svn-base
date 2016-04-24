#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include "prefpane.h"
#include "kmap.h"
#include "truthtable.h"
#include "equation.h"
/*!
   @class MainWindow
   @brief The main window containing all other widgets.
   The main window is a class which inherits the QMainWindow Class 
   from QT and is an interface to the main window.

   @author Curtis, Gezim, Jacob, Jeremy

*/

class MainWindow : public QMainWindow {

  Q_OBJECT
  
public:
///Main window constructor.
/*!
   A constructor that creates a main window object.
*/
  MainWindow(QWidget *parent = 0);

public slots:
    void setPosAndSop(QString sop, QString pos);
private:
///PrefPane preferences
///Pointer to the widget containing the preference information.
   PrefPane *preferences;
///Pointer to the widget containing the truth table information.
   TruthTable *truthTable;
///Pointer to the widget containing the equation information.
   Equation *equation;
///Pointer to the widget containing the kmap information.
   Kmap *kmap;
///Pointer to the radio button associated with the TruthTable widget.
///Pointer to the radio button associated with the Kmap widget.
///Pointer to the radio button associated with the Equation widget.
   QRadioButton *truthTableRadioButton, *kmapRadioButton, *equationRadioButton;
///Pointer to the push button calculate.
   QPushButton *calculate;
    QLabel *SOP, *POS;

};

#endif

