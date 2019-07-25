/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef COINCIDENCEWINDOW_H
#define COINCIDENCEWINDOW_H

#include <sstream>

#include "glow.h"
#include "glowPushButtonWidget.h"
#include "glowQuickPalette.h"
#include "glowPanelWidget.h"
#include "glowLabelWidget.h"
using namespace glow;

#include "coincidencedata.h"

const int initPixelWidth = 600;
const int initPixelHeight = 600;

const Point_E2d initLL(-2,-2);
const Point_E2d initUR(2,2);

const double initEpsilon = 1e-5;

class CoincidenceWindow :
    public GlowWindow,
    public GlowPushButtonReceiver,
    public GlowSliderReceiver
{
    CoincidenceData * myCoincidenceData;

    Bbox_E2d myBbox;

    GlowQuickPaletteWindow * controlWindow;
    GlowLabeledSliderWidget * epsilonSlider;
    GlowLabeledSliderWidget * rotationSlider;
    GlowPushButtonWidget * quitButton;

    GlowLabelWidget * bboxLabelWidget;

    double beginXdrag, beginYdrag;
    bool dragging;
    bool scaling;

public:
    CoincidenceWindow() :
        GlowWindow("Coincidence Window",
                   GlowWindow::autoPosition, GlowWindow::autoPosition,
                   initPixelWidth, initPixelHeight,
                   Glow::rgbaBuffer | Glow::doubleBuffer | Glow::depthBuffer,
                   Glow::mouseEvents | Glow::dragEvents | Glow::keyboardEvents),
        dragging(false),
        scaling(false)
    {
        init();

        //----------------Control Window----------------
        controlWindow = new GlowQuickPaletteWindow("Coincidence Controls", GlowWindow::autoPosition, GlowWindow::autoPosition);

        // 1e-18 is how much precision double provides
        epsilonSlider = controlWindow->AddSlider(1e-18, 0.5, initEpsilon, GlowSliderWidget::logarithmic,
                                                 10, "%5.1f", "Epsilon=%5.10f",this);
        rotationSlider = controlWindow->AddSlider(0, 360, 0, GlowSliderWidget::defaultOptions,
                                                  8, "%5.1f", "rotation=%5.1f",this);

        bboxLabelWidget = controlWindow->AddLabel("Bbox Width=  2.0000000000000");

        quitButton = controlWindow->AddPushButton("Quit", this);
        controlWindow->Pack();
    }
protected:
    void init()
    {
        myCoincidenceData = new CoincidenceData();
        myBbox = Bbox_E2d(initLL, initUR);
        myCoincidenceData->setBbox(myBbox); // used to draw disk and for eps bbox
        setupProjectionMatrices();
    }

    void setupProjectionMatrices()
    {
        ::glMatrixMode(GL_PROJECTION);
        ::glPushMatrix();
        ::glLoadIdentity();

        ::gluOrtho2D(myBbox.LL().x(), myBbox.UR().x(),
                     myBbox.LL().y(), myBbox.UR().y());

        ::glMatrixMode(GL_MODELVIEW);
        ::glPushMatrix();
        ::glLoadIdentity();

        ::glEnable(GL_LINE_SMOOTH);
        ::glEnable(GL_BLEND);
        ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    }

    virtual void OnEndPaint()
    {
        myCoincidenceData->draw();
    }

    void shrink(Bbox_E2d& b)
    {
        b = Bbox_E2d(interpolate(b.LL(), b.UR(), 0.1),
                     interpolate(b.LL(), b.UR(), 0.9));
    }
    void enlarge(Bbox_E2d& b)
    {
        b = Bbox_E2d(interpolate(b.LL(), b.UR(), -0.125),
                     interpolate(b.LL(), b.UR(),  1.125));
    }

    virtual void OnMouseDown(Glow::MouseButton button, int x, int y,
                             Glow::Modifiers modifiers)
    {
        float xn, yn;
        NormalizeCoordinates(x, y, xn, yn);

        switch (button) {
        case Glow::leftButton: /* 0 */
            switch(modifiers) {
            case Glow::noModifier:
                beginXdrag = xn;
                beginYdrag = yn;
                dragging = true;
            case Glow::shiftModifier:
                beginXdrag = yn;
                beginYdrag = yn;
                scaling = true;
            default:
                break;
            }
            break;
        case Glow::middleButton: /* 1 */
            switch(modifiers) {
            case Glow::noModifier:
                beginXdrag = yn;
                beginYdrag = yn;
                scaling = true;
            default:
                break;
            }
            break;

        case 3: shrink(myBbox); break;
        case 4: enlarge(myBbox); break;
        default:
            break;
        }

        std::ostringstream os;
        os << std::setprecision(10);
        os << "Bbox Width=  " << myBbox.width();
        bboxLabelWidget->SetText(os.str().c_str());
        myCoincidenceData->setBbox(myBbox); // used to draw disk and for eps bbox

        setupProjectionMatrices();
        Refresh();
    }

    virtual void OnMouseDrag(int x, int y)
    {
        if(dragging)
        {
            float xn, yn;
            NormalizeCoordinates(x, y, xn, yn);

            Vector_E2d translation((xn - beginXdrag) / 2.0 * myBbox.width(),
                                   (yn - beginYdrag) / 2.0 * myBbox.height());
                             
            myBbox = Bbox_E2d(myBbox.LL() - translation, myBbox.UR() - translation);

            beginXdrag = xn;
            beginYdrag = yn;

            setupProjectionMatrices();

            Refresh();
        }
        else if(scaling)
        {
            float xn, yn;
            NormalizeCoordinates(x, y, xn, yn);

            if(yn < beginYdrag)
                enlarge(myBbox);
            else if(yn > beginYdrag)
                shrink(myBbox);

            beginYdrag = yn;

            setupProjectionMatrices();

            Refresh();
        }
    }

    void OnMouseUp(Glow::MouseButton /*button*/,
                   int /*x*/, int /*y*/,
                   Glow::Modifiers /*modifiers*/)
    {
        dragging = false;
        scaling = false;
    }

    void OnReshape(int width, int height)
    {
        int bigger = std::max( width, height );
        ::glViewport(0, 0, bigger, bigger); // ensure aspect is 1:1
        setupProjectionMatrices();
    }

    void OnMessage(const GlowPushButtonMessage& message)
    {
        if (message.widget == quitButton) {
            exit(0);
        }
    }

    void OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                    Glow::Modifiers /*modifiers*/)
    {
        if('p' == key)
            myCoincidenceData->outputToPostScript();
        else {
            double angle = epsilonSlider->GetValue();
            switch (key) {
            case 'a': angle =         0;         break;
            case 'b': angle =       180.0 / 8.0; break;
            case 'c': angle = 2.0 * 180.0 / 8.0; break;
            case 'd': angle = 3.0 * 180.0 / 8.0; break;
            case 'e': angle = 4.0 * 180.0 / 8.0; break;
            case 'f': angle = 5.0 * 180.0 / 8.0; break;
            case 'g': angle = 6.0 * 180.0 / 8.0; break;
            case 'h': angle = 7.0 * 180.0 / 8.0; break;
            case 'i': angle = 8.0 * 180.0 / 8.0; break;

            case 'p': 

            case ' ':
                init();
                break;
            case 'q':
            case 'Q':
            case Glow::escapeKey:
                exit(0);
            default:
                ;
            }

            myCoincidenceData->setUpValues(epsilonSlider->GetValue(), angle);
            rotationSlider->SetValue(angle);
        }
        Refresh();
    }

    void OnMessage(const GlowSliderMessage & /*message*/)
    {
        myCoincidenceData->setUpValues(epsilonSlider->GetValue(), rotationSlider->GetValue());
        Refresh();
    }
};

#endif // COINCIDENCEWINDOW_H
