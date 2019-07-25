#  The following code example is described in the book "Introduction
#  to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
#  
#  Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
#  modified, or republished electronically or in print provided that
#  this copyright notice appears in all copies. This software is
#  provided "as is" without express or implied warranty; not even for
#  merchantability or fitness for a particular purpose.

GLIBS = geometry/lib raster_image

GLOWDIRS = GLOW

GDIRS = \
       geometry \
       postscript \
       graph misc raster_image \
       solid \
       tree_draw visibility_E2

# geometry_S3

all: mlibs test glowexamples

dclean: libclean dclean_geom dclean_glow

mlibs:
	for f in $(GLIBS); do \
	  (echo "----" $$f "----" && cd $$f && $(MAKE) mlib) || exit; \
	done

glowexamples:
	for f in $(GLOWDIRS); do \
	   (echo "----" $$f "----" && cd $$f && $(MAKE)) || exit; \
	done

libclean: 
	for f in $(GLIBS); do \
	  (echo "----" $$f "----" && cd $$f && $(MAKE) libclean) || exit; \
	done

test: mlibs
	for f in $(GDIRS); do \
	   (echo "----" $$f "----" && cd $$f && $(MAKE) test) || exit; \
	done

clean:
	for f in $(GDIRS); do \
	   (echo "----" $$f "----" && cd $$f && $(MAKE) clean) || exit; \
	done

dclean_geom:
	for f in $(GDIRS); do \
	   (echo "----" $$f "----" && cd $$f && $(MAKE) dclean) || exit; \
	done

dclean_glow:
	for f in $(GLOWDIRS); do \
	   (echo "----" $$f "----" && cd $$f && $(MAKE) dclean) || exit; \
	done

