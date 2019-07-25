/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "display_list_demo_window.h"

const int NUMBER_OF_RECURSIVE_SUBDIVISIONS = 5;

int main(int argc, char **argv)
{
    Glow::Init(argc, argv);
    int number_of_subdivisions = (argc==2) ? atoi(argv[1]) : NUMBER_OF_RECURSIVE_SUBDIVISIONS;
    new Display_list_demo_window(number_of_subdivisions);
    Glow::MainLoop();
}
