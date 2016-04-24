
TEMPLATE = app
TARGET = kmapper
DEPENDPATH += .
DESTDIR = ../bin
INCLUDEPATH += .

# Input
HEADERS += AboutDialog.h \
           Common.h \
           DataBackend.h \
           EquationInDialog.h \
           HelpDialog.h \
           InDialog.h \
           KMapInDialog.h \
           KMapWidget.h \
           MainWindow.h \
           MainWindowWidget.h \
           TruthTableInDialog.h \
           TruthTableWidget.h \
           InputVariableNameWidget.h \
           TTVal.h \
	   EquationParser.h
SOURCES += main.cc \
           AboutDialog.cc \
           DataBackend.cc \
           EquationInDialog.cc \
           HelpDialog.cc \
           InDialog.cc \
           KMapInDialog.cc \
           KMapWidget.cc \
           MainWindow.cc \
           MainWindowWidget.cc \
           TruthTableInDialog.cc \
           TruthTableWidget.cc \
           InputVariableNameWidget.cc \
           TTVal.cc \
	   EquationParser.cc
           
RESOURCES += resources.qrc
