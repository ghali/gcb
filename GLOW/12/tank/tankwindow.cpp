/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <string>
using std::string;
#include "glowMessageWindow.h"
using namespace glow;

#include "geom_types.h"
#include "tankwindow.h"
#include "draw.h"

// Define the static variables:
int TankWindow::SMALL_BOX = 30;
int TankWindow::initialWidth = 700;
int TankWindow::initialHeight = 500;


TankWindow::TankWindow(bool help, short UISpeedupFactor) :
    GlowWindow("tank", 300, 100, // GlowWindow::autoPosition, GlowWindow::autoPosition,
               initialWidth, initialHeight,
               Glow::rgbBuffer | Glow::doubleBuffer |
               Glow::depthBuffer | Glow::multisampleBuffer,
               Glow::keyboardEvents | Glow::mouseEvents | Glow::dragEvents |
               /*Glow::menuEvents | */ Glow::motionEvents | Glow::visibilityEvents |
               Glow::focusEvents /* set glutEntryFunc */ ),

    mytankcamera(UISpeedupFactor),

    W(initialWidth), H(initialHeight),

    xcontrol(0), ycontrol(0),
    myfps(),
    myGLstringRenderer(GLUT_BITMAP_HELVETICA_12, 0.05, 0.05),
    lastSeconds(myclock.getSecondsSinceStart()),
    isMaximized(false)

{
    mytankcamera.resetView();   // initialize eye/coi/up vectors
    Draw<double>::initialiseGL(mytankcamera);

    // initialize textures
    terrainTextureName = Draw<double>::initTexture("textures/terrainGradient.ppm");
    movingTargetTextureName = Draw<double>::initTexture("textures/movingTargetGradient.ppm");

    // Add a bouncing checkerboard
    MovingCB = Point_E3d(0, 2, 0);
    basculateUp = true;

    if(help)
        showHelp();

    // callLists cannot be defined once _controlWindow is contructed -- GLOW bug (?)
    //
    // Create one control panel per main window
    _controlWindow = new GlowQuickPaletteWindow("Controls", 100, 100);

    // Add controls
    _controlWindow->AddLabel("tank\n"
                             "example code\n");

    // Create another panel called "view"
    GlowQuickPanelWidget* panel = _controlWindow->AddPanel( GlowQuickPanelWidget::etchedStyle, "Main" );

    _axisCheckbox         = panel->AddCheckBox("(a): Draw Axis", GlowCheckBoxWidget::on, this);
    _fillPolygonCheckbox  = panel->AddCheckBox("(f): Fill Polygons", GlowCheckBoxWidget::on, this);
    _monolithsCheckbox    = panel->AddCheckBox("Draw Monoliths", GlowCheckBoxWidget::on, this);
    _checkerboardCheckbox = panel->AddCheckBox("Draw Checkerboard", GlowCheckBoxWidget::on, this);

    _resetviewButton  = panel->AddPushButton("(SPACE): Reset view",  this );
    _quitButton       = panel->AddPushButton("ESC: Quit", this );

    // Arrange controls and show the control panel window
    _controlWindow->Pack();

    Glow::RegisterIdle(this);
}

void
TankWindow::quitProg()
{
    delete _controlWindow;
    Close();
    exit(0);
}

void
TankWindow::showHelp()
{
    string msg =
        string("Mouse motion controls the vehicle\n") +
        string("Mouse wheel changes the altitude\n") +
        string("Keys 'z' and 'x' also change the altitude\n") +
        string("Other settings in adjacent control window\n");

    GlowMessageWindow* gmw = new GlowMessageWindow("Help", 300, 300,
                                                   msg.c_str(), "OK", NULL);
    gmw->Show();
}

void
TankWindow::displayMovingTarget()
{
    static float lastSeconds = 0;

    float seconds = myclock.getSecondsSinceStart();

    if(lastSeconds == 0) {
        lastSeconds = seconds;
        return;
    }

    float timegap = seconds - lastSeconds;
    lastSeconds = seconds;    

    if(basculateUp) {
        MovingCB = MovingCB + Vector_E3d( 0.0, 0.0, timegap * 30.0 );
        if(MovingCB.z() > 50.0)
            basculateUp = !basculateUp;
    }
    else {
        MovingCB = MovingCB - Vector_E3d( 0.0, 0.0, timegap * 30.0 );
        if(MovingCB.z() < -50.0)
            basculateUp = !basculateUp;
    }

    Draw<double>::drawMovingTarget(MovingCB, movingTargetTextureName);
}

void
TankWindow::OnEndPaint(void)
{
    Draw<double>::clearColorAndDepth();

    // Handle camera motion
    float seconds = myclock.getSecondsSinceStart();
    mytankcamera.update(xcontrol, ycontrol, W, H, seconds);

    glPushMatrix(); {
        Draw<double>::calcView(mytankcamera);
        
        Draw<double>::handleLightMotion(50*seconds);


        if(_axisCheckbox->GetState() == GlowCheckBoxWidget::on)
            Draw<double>::drawAxis();

        Draw<double>::selectWireframe(_fillPolygonCheckbox->GetState() == GlowCheckBoxWidget::off);

        if (_monolithsCheckbox->GetState() == GlowCheckBoxWidget::on) 
            Draw<double>::displayMonoliths();

        if (_checkerboardCheckbox->GetState() == GlowCheckBoxWidget::on)
            Draw<double>::drawTerrain(terrainTextureName);

        displayMovingTarget();

        myGLstringRenderer.draw(myfps.getFrameRate());
    } glPopMatrix();
}

void
TankWindow::OnReshape(int width, int height)
{
    Draw<double>::setViewport(width, height);

    W = width; H = height;
}

//----------------------------------------------------------------
void TankWindow::OnMouseEnter(){}
void TankWindow::OnMouseExit()
{
    ycontrol = 0;
    xcontrol = 0;
}
void TankWindow::OnVisible(){}
void TankWindow::OnInvisible(){}
//----------------------------------------------------------------

void
TankWindow::OnMouseMotion(int x, int y)
{
    ycontrol = (y - (H >> 1));  // screen center (divide by 2)
    xcontrol = (x - (W >> 1));

    if( abs(ycontrol) < SMALL_BOX && abs(xcontrol) < SMALL_BOX ) {
        ycontrol = 0;
        xcontrol = 0;
    }
    Refresh();
}

void
TankWindow::OnMouseDown(Glow::MouseButton mouseButton, int, int,
                       Glow::Modifiers) 
{
    // it turns out 0/1/2 are the integers returned for LMR mouse buttons
    // and 3/4 are the ones returned when the mouse wheel is moved
    // this is not documented in either GLOW or GLUT, but both pass the numbers through
    switch(mouseButton) {
    case 3: mytankcamera.increaseY(); break;
    case 4: mytankcamera.decreaseY(); break;
    default:
        ;                       // to avoid the compiler warning
    }
    Draw<double>::calcView(mytankcamera);
    Refresh();
}

void
TankWindow::OnKeyboard(Glow::KeyCode key, int, int, Glow::Modifiers)
{
    switch(key) {
    case ' ':
        mytankcamera.resetView();
        Draw<double>::calcView(mytankcamera);
        Refresh();
        break;
    case 'z': mytankcamera.increaseY(); break;
    case 'x': mytankcamera.decreaseY(); break;
    case 'a':  _axisCheckbox->ToggleState(); _controlWindow->Refresh(); break;
    case 'f':  _fillPolygonCheckbox->ToggleState(); _controlWindow->Refresh(); break;
    case 'm':
        if(!isMaximized)
            Maximize();
        else
            Reshape(initialWidth, initialHeight);
        isMaximized = !isMaximized;
        break;
    case 'q': case 'Q': case Glow::escapeKey: 
        quitProg();
    default:
        ;
    }
    Refresh();
}

void
TankWindow::OnMessage(const GlowPushButtonMessage& message)
{
    if(message.widget == _resetviewButton) {
        mytankcamera.resetView();
        Draw<double>::calcView(mytankcamera);
    }
    else if(message.widget == _quitButton)
        quitProg();

    Refresh();
}

void
TankWindow::OnMessage(const GlowCheckBoxMessage&)
{
    // messages are taken care of in OnEndPaint();
    // we don't need to do anything here.
    Refresh();
}

void
TankWindow::OnMessage(const GlowIdleMessage&)
{
    float seconds = myclock.getSecondsSinceStart();
    if(seconds - lastSeconds > 0.01) {
        Refresh();
        lastSeconds = seconds;
    }
}
