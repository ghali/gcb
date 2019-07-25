#  The following code example is described in the book "Introduction
#  to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
#  
#  Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
#  modified, or republished electronically or in print provided that
#  this copyright notice appears in all copies. This software is
#  provided "as is" without express or implied warranty; not even for
#  merchantability or fitness for a particular purpose.

#================================================================
PROG = offview
#================================================================
OBJS =  offview.o \
	offviewdataviewer.o \
	offviewwindow.o
#================================================================
include ../../../Makefile-glow.mk
#================================================================
CXXFLAGS += -I../../../
#================================================================
