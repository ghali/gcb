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
#include "glowQuickPalette.h"
#include "glowViewTransform.h"
using namespace glow;

#include "scene.h"
#include "opengl/fpscounter.h"

const int initViewportWidth  = 500;
const int initViewportHeight = 500;

class ArcballWindow : public GlowWindow
{
    GlowViewManipulator* manipulator;
    FPScounter myfps;

    GlowQuickPaletteWindow* controlWindow;
    GlowLabelWidget* fpsIndicator;

public:
    ArcballWindow()
        : GlowWindow("Arcball Window",
                     GlowWindow::autoPosition, GlowWindow::autoPosition,
                     initViewportWidth, initViewportHeight,
                     Glow::rgbBuffer | Glow::doubleBuffer | Glow::depthBuffer,
                     Glow::mouseEvents | Glow::dragEvents | Glow::keyboardEvents),
          myfps()
    {
        setupProjectionMatrices();

        //----------------------------------------------------------------
        // GLOW seems to be picky here: the manipulator must be initialized
        // before the control window
        //----------------------------------------------------------------

        //----------------Manipulator----------------
        GlowViewManipulatorParams manipparams = GlowViewManipulatorParams::defaults;
        manipparams.draw = true;
        manipulator = new GlowViewManipulator(this, manipparams);
        manipulator->SetSpinnable(true);
        new Scene(manipulator);

        //----------------Control Window----------------
        controlWindow = new GlowQuickPaletteWindow("Frame rate",
                                                   GlowWindow::autoPosition, GlowWindow::autoPosition, GlowQuickPalette::vertical);

        GlowQuickPanelWidget* panel = controlWindow->AddPanel(GlowQuickPanelWidget::etchedStyle, "Panel");

        fpsIndicator = panel->AddLabel("0000.00 fps");

        controlWindow->Pack();
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

    virtual void OnEndPaint()
    {
        fpsIndicator->SetText(myfps.getFrameRate().c_str());
    }

    virtual void OnMouseDown(Glow::MouseButton button,
                             int x, int y,
                             Glow::Modifiers modifiers)
    {
        if (!manipulator->IsDragging())
        {
            float xn, yn;
            GlowSubwindow::NormalizeCoordinates(x, y, xn, yn);
            switch (button) {
            case Glow::leftButton:
                switch (modifiers) {
                case Glow::noModifier:
                    manipulator->BeginRotationDrag(xn, yn);
                    break;
                case Glow::shiftModifier:
                    manipulator->BeginTranslationDrag(xn, yn);
                    break;
                default:
                    break;
                }
                break;
            case Glow::middleButton:
                manipulator->BeginScaleDrag(xn, yn);
                break;
            default:
                break;
            }
        }
    }

    virtual void OnMouseDrag(int x, int y)
    {
        if (manipulator->IsDragging())
        {
            float xn, yn;
            GlowSubwindow::NormalizeCoordinates(x, y, xn, yn);
            manipulator->InDrag(xn, yn);
        }
    }

    virtual void OnMouseUp(Glow::MouseButton /*button*/,
                           int x, int y,
                           Glow::Modifiers /*modifiers*/)
    {
        if (manipulator->IsDragging())
        {
            float xn, yn;
            GlowSubwindow::NormalizeCoordinates(x, y, xn, yn);
            manipulator->EndDrag(xn, yn);
        }
    }

    virtual void OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                            Glow::Modifiers /*modifiers*/)
    {
        switch (key) {
        case 'q': case 'Q': case Glow::escapeKey:
            Close();
            controlWindow->Close();
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
