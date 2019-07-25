
# win32 {
#     QMAKE_CXXFLAGS_WARN_ON = /W4
# }

TEMPLATE  = app
CONFIG   += console

DEPENDPATH  +=  ../../../
INCLUDEPATH +=  ../../../

#include( ../../../stl-boost-qt-igc.pri )
#DEPENDPATH  += . .. ../.. ../../../
#INCLUDEPATH += . .. ../.. ../../../
#
#DEPENDPATH  += ../../../../try/igc_qt
#INCLUDEPATH += ../../../../try/igc_qt
#
#DEPENDPATH  += ../../../../trynew/igc_qt
#INCLUDEPATH += ../../../../trynew/igc_qt

HEADERS = MyWidget.h
SOURCES = geometry_types.h main.cpp MyWidget.cpp

