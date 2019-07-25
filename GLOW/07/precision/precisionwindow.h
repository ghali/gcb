/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PRECISIONWINDOW_H
#define PRECISIONWINDOW_H

#include "glow.h"
using namespace glow;

#include "precisiondata.h"

class PrecisionWindow : public GlowWindow
{
public:

    PrecisionWindow(PrecisionData* data, bool debug = false);

protected:

    virtual void drawPrecisionData();

    // Refresh event
    virtual void OnEndPaint();

    virtual void OnKeyboard(Glow::KeyCode key, int x, int y, Glow::Modifiers modifiers);

private:

    PrecisionData* myPrecisionData;
    bool debugMode;
};

#endif // PRECISIONWINDOW_H
