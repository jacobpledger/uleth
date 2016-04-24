#include "mainwindow.h"

#include <QtGui>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

   truthTableRadioButton = new QRadioButton("TruthTable", this);
   kmapRadioButton = new QRadioButton("K-Map", this);
   equationRadioButton = new QRadioButton("Equation", this);

   truthTable = new TruthTable;
   preferences = new PrefPane;
   kmap = new Kmap;
   equation = new Equation;
   equationRadioButton->setChecked(true);
   kmap->setEnabled(false);
   truthTable->setEnabled(false);
   QHBoxLayout *hlayout = new QHBoxLayout;
   QHBoxLayout *equationHlayout = new QHBoxLayout;
   SOP = new QLabel();
   POS = new QLabel();
    calculate = new QPushButton("Calculate");

   QVBoxLayout *layout = new QVBoxLayout;
   ///connects the preferences signal with the Variables names to the truth table slot for variable names
   connect(preferences, SIGNAL(sendVariableNames(QStringList)),truthTable, SLOT(setVariableNames(QStringList)));
   ///connects the preferences signal for number of variables to the truthtable slot for that number
   connect(preferences, SIGNAL(sendVariableNumber(int)),truthTable, SLOT(setNumberOfVariables(int)));
   ///connects the preferences signal for number of variables to the kmap slot for that number
   connect(preferences, SIGNAL(sendVariableNumber(int)),kmap, SLOT(setNumberOfVariables(int)));
   ///connects the preferences signal for number of variables to the equation slot for that number
   connect(preferences, SIGNAL(sendVariableNumber(int)),equation, SLOT(setNumberOfVariables(int)));
   ///connects the preferences signal with the Variables names to the equation slot for variable names
   connect(preferences, SIGNAL(sendVariableNames2(QStringList)),equation, SLOT(setVariableNames(QStringList)));
   ///connects the calculate button's signal with the Equations's setEquation() slot
   connect(calculate, SIGNAL(clicked()),equation, SLOT(setEquation()));
   connect(calculate, SIGNAL(clicked()),kmap, SLOT(sendTruthTableData()));
   connect(calculate, SIGNAL(clicked()),truthTable, SLOT(sendKmapData()));
///connects the equation widgets signal that sends the truth table information to the truth tables slot
   connect(equation, SIGNAL(sendTruthTableString(QString)),truthTable, SLOT(setTruthTableString(QString)));
///connects the equation widgets signal that sends the truth table information to the kmaps slot
   connect(equation, SIGNAL(sendTruthTableString(QString)),kmap, SLOT(setKmapString(QString)));
   connect(equation, SIGNAL(sendKmapColoring(QVector<int>)),kmap, SLOT(setKmapColors(QVector<int>)));
//connect sop and pos information to equation table
    connect(equation, SIGNAL(sendPosAndSop(QString, QString)), this, SLOT(setPosAndSop(QString, QString)));
   connect(truthTable, SIGNAL(sendTruthToKmap(QString)),kmap, SLOT(setKmapString(QString)));
   connect(truthTable, SIGNAL(sendTruthTableToEquation(QString)),equation, SLOT(optimizeTruthTableExpression(QString)));
///sends data from kmap to equation to be optimized
   connect(kmap, SIGNAL(sendDataToTruthTable(QString)),equation, SLOT(optimizeTruthTableExpression(QString)));
///connections for radio buttons
   connect(truthTableRadioButton, SIGNAL(toggled(bool)),truthTable,SLOT(toggleTruthTable(bool)));
   connect(equationRadioButton, SIGNAL(toggled(bool)),equation,SLOT(toggleEquation(bool)));
   connect(kmapRadioButton, SIGNAL(toggled(bool)),kmap,SLOT(toggleKmap(bool)));
   connect(preferences, SIGNAL(sendReset()),kmap, SLOT(clearKmap()));
	 connect(preferences, SIGNAL(sendReset()),truthTable, SLOT(clearTruthTable()));


   connect(kmap, SIGNAL(sendDataToTruthTable(QString)),truthTable, SLOT(setTruthTableString(QString)));


   equationHlayout->addWidget(equationRadioButton);
   equationHlayout->addWidget(equation);
   layout->addWidget(truthTableRadioButton);
   layout->addWidget(truthTable);
   layout->addLayout(equationHlayout);
   layout->addWidget(preferences);
   layout->addWidget(calculate);
   QVBoxLayout *vlayout2 = new QVBoxLayout;
   vlayout2->addWidget(kmapRadioButton);
   vlayout2->addWidget(kmap);
   QVBoxLayout *vlayout3 = new QVBoxLayout;
   vlayout3->addWidget(SOP);
   vlayout3->addWidget(POS);
   QVBoxLayout *vlayout4 = new QVBoxLayout;
   QLabel *posLabel = new QLabel("POS:");
   QLabel *sopLabel = new QLabel("SOP:");
   vlayout4->addWidget(posLabel);
   vlayout4->addWidget(sopLabel);
   QHBoxLayout *answerLayout = new QHBoxLayout;
   answerLayout->addLayout(vlayout4);
   answerLayout->addLayout(vlayout3);

   vlayout2->addLayout(answerLayout);
   hlayout->addLayout(layout);
   hlayout->addLayout(vlayout2);

   QWidget *central = new QWidget;
   
   central->setLayout(hlayout);
   
   setCentralWidget(central);

}

void MainWindow::setPosAndSop(QString sop, QString pos) {
    SOP->setText(sop);
    POS->setText(pos);
}
