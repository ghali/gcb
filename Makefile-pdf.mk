#  The following code example is described in the book "Introduction
#  to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
#  
#  Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
#  modified, or republished electronically or in print provided that
#  this copyright notice appears in all copies. This software is
#  provided "as is" without express or implied warranty; not even for
#  merchantability or fitness for a particular purpose.

.SUFFIXES : .eps .pdf .svg

PSFILES := $(wildcard *.eps)
PDFSP = $(patsubst %.eps,%.pdf,$(PSFILES))
SVGSP = $(patsubst %.eps,%.svg,$(PSFILES))
PS2PDF = epstopdf 
PS2SVG = pstoedit

%.pdf: %.eps
	$(PS2PDF) $<

%.svg: %.eps
	$(PS2SVG) -f plot-svg $< $@

pdf: $(PDFSP)
	@echo "done."

svg: $(SVGSP)
	@echo "done."

all: pdf svg

clean:
	rm -f $(PDFSP) $(SVGSP)
