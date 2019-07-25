
# win32 {
#     QMAKE_CXXFLAGS_WARN_ON = /W4
# }

TEMPLATE  = app
CONFIG   += console

# include( ../../../stl-boost-qt-igc.pri )
DEPENDPATH  += ../../..
INCLUDEPATH += ../../..

# RESOURCES = ../../../objects/objects.qrc

HEADERS = MyWidget.h
SOURCES = main.cpp MyWidget.cpp

