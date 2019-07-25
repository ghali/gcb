/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef ARCBALLWINDOW_H
#define ARCBALLWINDOW_H

#include "glow.h"
#include "glowViewTransform.h"
using namespace glow;

#include "scene.h"

const int initViewportWidth  = 500;
const int initViewportHeight = 500;

class ArcballWindow : public GlowWindow
{
    GlowViewManipulator* myManipulator;
public:
    ArcballWindow()
        : GlowWindow("Arcball Window",
                     GlowWindow::autoPosition, GlowWindow::autoPosition,
                     initViewportWidth, initViewportHeight,
                     Glow::rgbBuffer | Glow::doubleBuffer | Glow::depthBuffer,
                     Glow::mouseEvents | Glow::dragEvents | Glow::keyboardEvents)
    {
        setupProjectionMatrices();

        //----Manipulator----
        GlowViewManipulatorParams manipparams = GlowViewManipulatorParams::defaults;
        manipparams.draw = true;
        myManipulator = new GlowViewManipulator(this, manipparams);
        myManipulator->SetSpinnable(true);
        /* Scene* myScene = */ new Scene(myManipulator);
    }

protected:
    void setupProjectionMatrices()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(40.0 /*fov*/, 1.0 /*aspect*/, 1.0/*Znear*/, 100.0/*Zfar*/);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(4.0f, 3.0f, 4.0f /*eye*/,
                  0.0f, 0.0f, 0.0f /*coi*/,
                  0.0f, 1.0f, 0.0f /*up*/);
        glPushMatrix();

        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    }

    virtual void OnMouseDown(Glow::MouseButton button,
                             int x, int y,
                             Glow::Modifiers modifiers)
    {
        if (!myManipulator->IsDragging())
        {
            float xn, yn;
            GlowSubwindow::NormalizeCoordinates(x, y, xn, yn);
            switch (button) {
            case Glow::leftButton:
                switch (modifiers) {
                case Glow::noModifier:
                    myManipulator->BeginRotationDrag(xn, yn);
                    break;
                case Glow::shiftModifier:
                    myManipulator->BeginTranslationDrag(xn, yn);
                    break;
                default:
                    break;
                }
                break;
            case Glow::middleButton:
                myManipulator->BeginScaleDrag(xn, yn);
                break;
            default:
                break;
            }
        }
    }

    virtual void OnMouseDrag(int x, int y)
    {
        if (myManipulator->IsDragging())
        {
            float xn, yn;
            GlowSubwindow::NormalizeCoordinates(x, y, xn, yn);
            myManipulator->InDrag(xn, yn);
        }
    }

    virtual void OnMouseUp(Glow::MouseButton /*button*/,
                           int x, int y,
                           Glow::Modifiers /*modifiers*/)
    {
        if (myManipulator->IsDragging())
        {
            float xn, yn;
            GlowSubwindow::NormalizeCoordinates(x, y, xn, yn);
            myManipulator->EndDrag(xn, yn);
        }
    }

    virtual void OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                            Glow::Modifiers /*modifiers*/)
    {
        switch (key) {
        case 'q': case 'Q': case Glow::escapeKey:
            Close();
        default:
            ;
        }
    }

    virtual void OnReshape(int width, int height)
    {
        GlowSubwindow::OnReshape(width, height);

        setupProjectionMatrices();
    }
};

#endif // ARCBALLWINDOW_H
