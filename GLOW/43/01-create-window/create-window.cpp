/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "glow.h"
#include "hellosegmentwindow.h"

//----------------main_Begin----------------
int main(int argc, char **argv)
{
    glow::Glow::Init(argc, argv);
    new HelloSegmentWindow();
    glow::Glow::MainLoop();
}
//----------------main_End----------------
