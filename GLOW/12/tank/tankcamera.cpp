/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geom_types.h"
#include "tankcamera.h"

const double TankCamera::FORWARD_INC = 10.0/75.0; // speed increment/decrement controlled by mouse-Y
const double TankCamera::TURN_INC = 1.0/250.0;    // turn increment/decrement controlled by mouse-X
const double TankCamera::Y_INC    = 1.0/5.0;      // Y increment/decrement when mouse wheel is moved


TankCamera::TankCamera(short myUISpeedupFactor) : 
    UISpeedupFactor(static_cast<double>(myUISpeedupFactor)),
    currEye(),                 // note this initializes all to (0,0,0)
    viewDir(),
    currCoi()
{}

void TankCamera::resetView()
{
    currEye = Point_E3d ( -50.0, 5, 0 );
    viewDir = Vector_E3d (1.0, 0.0, 0.0);

    currCoi = currEye + viewDir;
}

void TankCamera::increaseY()
{
    currEye = currEye + Vector_E3d( 0.0, + Y_INC * UISpeedupFactor, 0.0 );
    currCoi = currCoi + Vector_E3d( 0.0, + Y_INC * UISpeedupFactor, 0.0 );
}

void TankCamera::decreaseY()
{
    currEye = currEye + Vector_E3d( 0.0, - Y_INC * UISpeedupFactor, 0.0 );
    currCoi = currCoi + Vector_E3d( 0.0, - Y_INC * UISpeedupFactor, 0.0 );
}

void TankCamera::update(int xcontrol, int ycontrol, int, int, float seconds)
{
    static float lastSeconds = 0;

    if(lastSeconds == 0) {
        lastSeconds = seconds;
        return;
    }

    float timegap = seconds - lastSeconds;
    lastSeconds = seconds;    

    if(ycontrol) {
        double factor = -double(ycontrol) * FORWARD_INC * UISpeedupFactor * timegap;
        currEye = currEye + viewDir * factor;
        currCoi = currCoi + viewDir * factor;
        viewDir = currCoi - currEye; // avoid accumulating errors
    }

    if(xcontrol) {
        double factor = -xcontrol * TURN_INC * UISpeedupFactor * timegap;
        viewDir.rotateY(factor);
        currCoi = currEye + viewDir;
    }
}
