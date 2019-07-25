/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <iostream>
#include <string>
using namespace std;

#include "glow.h"
using namespace glow;

#include "offviewwindow.h"

int main(int argc, char **argv)
{
    const string sceneFilePrefix("../../../objects/");
    const string sceneFileSuffix(".off");

    if ( argc != 2) {
        cerr << "Usage: offview <filename> " << endl;
        cerr << "    (in "
             << sceneFilePrefix << "<filename>"
             << sceneFileSuffix << endl;
        exit(1);
    }

    Glow::Init(argc, argv);

    string filename = string(argv[1]);
    string sceneFile = sceneFilePrefix + filename + sceneFileSuffix;;

    new OffviewWindow(sceneFile);

    Glow::MainLoop();
}
