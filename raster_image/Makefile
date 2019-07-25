#  The following code example is described in the book "Introduction
#  to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
#  
#  Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
#  modified, or republished electronically or in print provided that
#  this copyright notice appears in all copies. This software is
#  provided "as is" without express or implied warranty; not even for
#  merchantability or fitness for a particular purpose.

#================================================================
PROG = test_raster

OBJS =  test_raster.o image.o
#================================================================
include ../Makefile-solo.mk
#================================================================
CXXFLAGS += -I../
#================================================================

CC = g++

mlib: image.o
#================================================================
image.o: image.h image.cpp
	$(CC) $(CXXFLAGS) -c image.cpp
	ar crs libimage.a image.o
#================================================================
libclean:
	rm -f libimage.a image.o image.d
#================================================================
