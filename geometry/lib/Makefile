#  The following code example is described in the book "Introduction
#  to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
#  
#  Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
#  modified, or republished electronically or in print provided that
#  this copyright notice appears in all copies. This software is
#  provided "as is" without express or implied warranty; not even for
#  merchantability or fitness for a particular purpose.

CC = g++
TR = transformations

mlib: $(TR).o
#================================================================
$(TR).o: $(TR).h $(TR).cpp
	$(CC) $(CXXFLAGS) -c $(TR).cpp
	ar crs lib$(TR).a $(TR).o
#================================================================
libclean:
	rm -f lib$(TR).a $(TR).o $(TR).d
#================================================================
