
========================================================================
This code is described in the book "Introduction to Geometric Computing"
by Sherif Ghali, Springer-Verlag, 2008.
========================================================================

=================================
Notes for Release 1.2, April 2011
=================================

- This code has been tested on Linux, Mac OS X, and Cygwin. The Makefiles
  included handle compilation on the three platforms.

- As editors and compilers on Unix variants generally accommodate
  Windows line endings (CR+LF) more gracefully than Windows
  accommodates Linux or Mac line endings, the line endings used are
  those of Windows.

- Because GLUT is all but abandoned on Windows/Visual Studio and
  because GLOW, the toolkit on which a subset of the code is built, is
  itself built on GLUT, it is difficult to compile the GLOW-based code
  using Visual Studio. After migrating the code to Qt, Visual Studio
  will be fully supported.

- To compile on Linux, Mac OS X, and Cygwin:

      - Type 'make mlibs' to generate two brief libraries.
      - Type 'make test' to compile and run the tests.
      - Type 'make glowexamples to compile and run the tests.
      - Type 'make all' to run the previous three makes.

      - Type 'make' to generate an (optimized) executable.
      - Type 'make dbg' to generate an executable for debugging.
      - Type 'make clean' to delete object and dependency files.
      - Type 'make dclean' to delete .o and .d files, as well as executables.

- Recursive makes:
      - Type 'make all' to run the tests and generate all executables.
      - Type 'make test' to (re)run the library test routines.

- Parts of the code depend on two libraries:
      - OpenGL for raster output.
      - GLOW (http://glow.sourceforge.net) as a platform-neutral
        GUI library. GLOW can be compiled on Linux, Mac OS X, and Cygwin.
	GLOW is built on glut only and is thus quite portable.
      - Qt is now (since Release 1.2) occasionally used instead of GLOW.

- The files in the directories 
      geometry/E1 geometry/E2 ... geometry/P1 geometry/P2 ...
  are generic and so need not be compiled, but two brief libraries
      code/geometry/lib> make libtransformations.o
      code/raster_image> make image.o
  need to be compiled. This is done by 'make all'.

- C++ code and chapter exercises refer to the numbered directories
      GLOW/ 01 03 04 ...
      Qt/ ...
  The first few chapters do not use genericity. The generic classes
  and functions are in geometry/*.

- The code for modeling solids in is solid/bsp, solid/csg, solid/ifs,
  and solid/heds.

- The output of vector drawing programs is in Encapsulated PostScript
  and is saved in a subdirectory psout. If the utility epstopdf is
  installed, type 'make' in that directory to generate pdf files. This
  is convenient if a pdf viewer is more readily available than a
  ps/eps viewer.

- The start-up code for exercises is in subdirectories of the numbered
  directories in GLOW/* and Qt/*. Exercises 5.3 and 5.4, for example,
  refer to the start-up code labeled clip-polygon. That code can be
  found in igc/GLOW/05/clip-polygon/*.

========================================================================
