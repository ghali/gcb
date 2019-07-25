#  The following code example is described in the book "Introduction
#  to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
#  
#  Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
#  modified, or republished electronically or in print provided that
#  this copyright notice appears in all copies. This software is
#  provided "as is" without express or implied warranty; not even for
#  merchantability or fitness for a particular purpose.

# Type 'make' while debugging
# Type 'make opt' to generate an optimized executable

dbg: $(PROG)
opt: $(PROG)

test: opt
	./$(PROG)$(EXEC_SUFFIX) 

#================================================================
CC = g++
#================================================================
MYOSTYPE := $(shell uname)
#================================================================
ifeq ($(MYOSTYPE),Linux)
    EXEC_SUFFIX=
    CXXFLAGS = -Wall -W -LANG:std -c -MMD
    LDFLAGS += -lpthread -ldl -lm -lstdc++
else
    ifeq ($(MYOSTYPE),CYGWIN_NT-5.1)
        EXEC_SUFFIX=".exe"
        CXXFLAGS = -Wall -W -LANG:std -c -MMD
    else
        ifeq ($(MYOSTYPE),Darwin)
            EXEC_SUFFIX=
            CXXFLAGS = -Wall -W -ansi -pedantic -LANG:std -c -MMD
        endif
    endif
endif
#================================================================
ifeq ($(MAKECMDGOALS),dbg)
    CXXFLAGS += -ggdb
else				# optimized version generated by default
    CXXFLAGS += # -O2 (use on demand)
endif
#================================================================
.cpp.o:
	$(CC) $(CXXFLAGS) $<

$(PROG): $(OBJS)
	$(RM) $@
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: opt dbg clean dclean

clean:
	rm -f *.d *.o
dclean: clean
	rm -f $(PROG) $(PROG).exe

-include $(OBJS:.o=.d)
#================================================================