#  The following code example is described in the book "Introduction
#  to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
#  
#  Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
#  modified, or republished electronically or in print provided that
#  this copyright notice appears in all copies. This software is
#  provided "as is" without express or implied warranty; not even for
#  merchantability or fitness for a particular purpose.

CDIRS = 01 03 04 05 06 07 08 09 11 12 15 19 20 21 24 25 26 27 31 32 42 43

chaps:
	for f in $(CDIRS); do \
	   (echo "----" $$f "----" && cd $$f && $(MAKE) ) || exit; \
	done

clean:
	for f in $(CDIRS); do \
	   (echo "----" $$f "----" && cd $$f && $(MAKE) clean) || exit; \
	done

dclean:
	for f in $(CDIRS); do \
	   (echo "----" $$f "----" && cd $$f && $(MAKE) dclean) || exit; \
	done
