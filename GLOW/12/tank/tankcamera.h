/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TANKCAMERA_H
#define TANKCAMERA_H

#include "geom_types.h"

/** A TankCamera object consists of the various parameters for the
 * flight: the location of the observer, the center of interest, etc.
 * 
 */

class TankCamera {
protected:

    static const double FORWARD_INC; /// speed (ycontrol) increment/decrement controlled by mouse-Y
    static const double TURN_INC;    /// turn  (xcontrol) increment/decrement controlled by mouse-X
    static const double Y_INC;       /// Y increment/decrement when 'z'/'x' are pressed


    /// the three increment factors above are modified by specifying a
    // UISpeedupFactor different from 1.
    double UISpeedupFactor;

    Point_E3d  currEye;
    Vector_E3d viewDir;
    Point_E3d  currCoi;

public:
    TankCamera(short myUISpeedupFactor = 1);

    const Point_E3d&  getCurrEye()  const { return currEye; }
    const Point_E3d&  getCurrCoi()  const { return currCoi; }

    /// This is convenient if we "get lost."
    void resetView();
    
    void update(int xcontrol, int ycontrol, int W, int H, float seconds);

    void increaseY();
    void decreaseY();
};

#endif // TANKCAMERA_H
