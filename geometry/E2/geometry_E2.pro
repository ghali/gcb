
# Future work: use qmake rather than makefiles.

TEMPLATE = app
TARGET = 

include( ../../stl-boost-qt-igc.pri )

DEPENDPATH  += . ..
INCLUDEPATH += . ..

DEPENDPATH  += ../..
INCLUDEPATH += ../..

DEPENDPATH  += ../../../../try/igc_qt
INCLUDEPATH += ../../../../try/igc_qt

# Input
HEADERS += geometry_e2.h
SOURCES += test_e2.cpp
