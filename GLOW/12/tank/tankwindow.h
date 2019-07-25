/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TANKWINDOW_H
#define TANKWINDOW_H

#include "glow.h"
#include "glowQuickPalette.h"
using namespace glow;

#include "geom_types.h"
#include "tankcamera.h"
#include "opengl/fpscounter.h"
#include "opengl/gldrawstring.h"
#include "misc/clock.h"

/**
 * Maintain the following links between the modules.
 * The table below identifies whether a class sends messages to a given module.
 *                      GLOW      OpenGL
 *  class TankWindow     yes          no
 *  class TankCamera      no          no
 *  class Draw            no         yes
 *
 */

class TankWindow :
    public GlowWindow,
    public GlowPushButtonReceiver,
    public GlowCheckBoxReceiver,
    public GlowIdleReceiver
{
protected:

    TankCamera mytankcamera; // Only TankWindow instance should touch mytankcamera.

    int W, H;                   // Window dimensions

    // If the mouse is inside a square twice this size, the vehicle is stationary
    static int SMALL_BOX;

    int xcontrol, ycontrol;

    Point_E3d lightPosition;

    Point_E3d MovingCB;
    bool basculateUp;

    FPScounter myfps;
    GLstringRenderer myGLstringRenderer;

    Clock myclock;

    // Notice that the isolation of GL code is not absolute; we store texture ids in TankWindow.
    // But a separate class is in any case needed for the terrain and another class for
    // each moving object. The following two variables would migrate to those classes.
    GLuint terrainTextureName;
    GLuint movingTargetTextureName;

    // Pointer to the control window
    GlowQuickPaletteWindow* _controlWindow;

    // Pointers to selected widgets. We store these so that we can tell what
    // widget was hit when we receive events.
    GlowCheckBoxWidget* _axisCheckbox;
    GlowCheckBoxWidget* _fillPolygonCheckbox;
    GlowCheckBoxWidget* _monolithsCheckbox;
    GlowCheckBoxWidget* _checkerboardCheckbox;

    GlowPushButtonWidget* _quitButton;
    GlowPushButtonWidget* _resetviewButton;

    float lastSeconds;

    bool isMaximized;

    static int initialWidth;
    static int initialHeight;

public:
    TankWindow(bool help = false, short UISpeedupFactor=1);

    void showHelp();

    // calcView uses the currEye/nextEye pair to set the modelview matrix
    void calcView();

    virtual void OnEndPaint(void); // definitions in GlowComponent and in GlowSubwindow

    virtual void OnReshape(int width, int height);

    virtual void OnMouseEnter(void);
    virtual void OnMouseExit(void);

    virtual void OnVisible();
    virtual void OnInvisible();

    virtual void OnMouseMotion(int x, int y);

    virtual void OnMessage(const GlowIdleMessage& message);

    void quitProg();

    virtual void OnMouseDown(Glow::MouseButton mouseButton, int x, int y,
                             Glow::Modifiers modifiers);

    virtual void OnKeyboard(Glow::KeyCode key, int x, int y, Glow::Modifiers modifiers);

    void OnMessage(const GlowPushButtonMessage& message);
    void OnMessage(const GlowCheckBoxMessage& message);

    void makeCheckImages();
    void initTextures();
    void displayCheckerboard();
    void displayMovingTarget();
    void displayMonoliths();
};

#endif // TANKWINDOW_H
