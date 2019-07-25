#  The following code example is described in the book "Introduction
#  to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
#  
#  Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
#  modified, or republished electronically or in print provided that
#  this copyright notice appears in all copies. This software is
#  provided "as is" without express or implied warranty; not even for
#  merchantability or fitness for a particular purpose.

CDIRS = E1 E2 E3 P1 P2 P3 S1 S2 T1 T2 T3 free

test:
	for f in $(CDIRS); do \
	   (echo "----" $$f "----" && cd $$f && $(MAKE) test) || exit; \
	done

clean:
	for f in $(CDIRS); do \
	   (echo "----" $$f "----" && cd $$f && $(MAKE) clean) || exit; \
	done

dclean:
	for f in $(CDIRS); do \
	   (echo "----" $$f "----" && cd $$f && $(MAKE) dclean) || exit; \
	done
