
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
HEADERS += intersection_t3.h polygon_t3.h geometry_free/clip_2.h
SOURCES += test_t3.cpp
