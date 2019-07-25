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
#include <cstdlib>

using namespace std;

#include "opengl/gldraw_e2.h"
#include "sketchpadwindow.h"

// initial values
const int initViewportWidth = 640;
const int initViewportHeight = 480;

const Point2d lowerLeft(-16,-12);
const Point2d upperRight(16,12);

const double initScale1x = 0.8;
const double initScale1y = 0.8;
const double initRotate1 = 0.0;
const double initTrnsl1x = -4.0;
const double initTrnsl1y = +3.0;

const double initScale2x = 1.2;
const double initScale2y = 1.2;
const double initRotate2 = M_PI/4.0;
const double initTrnsl2x = +4.0;
const double initTrnsl2y = -3.0;

int SketchpadWindow::howManyOfMe = 0;

SketchpadWindow::SketchpadWindow() :
    GlowWindow("Sketchpad",
               GlowWindow::autoPosition, GlowWindow::autoPosition,
               initViewportWidth, initViewportHeight,
               Glow::rgbBuffer | Glow::doubleBuffer,
               Glow::mouseEvents | Glow::dragEvents | Glow::keyboardEvents),

    mySketchpadData(),

    viewportWidth(initViewportWidth),
    viewportHeight(initViewportHeight),
    _alpha(0.0),
    basculateUp(true)
{
    GLdraw_E2<double>::setup_projection( lowerLeft, upperRight );
    ++howManyOfMe;
    Glow::RegisterIdle(this);

    //----------------
    // Control window
    //----------------
    controlWindow = new GlowQuickPaletteWindow("Controls", 
                                               GlowWindow::autoPosition, GlowWindow::autoPosition, GlowQuickPalette::vertical);

    GlowQuickPanelWidget* panel1 = controlWindow->AddPanel(GlowQuickPanelWidget::etchedStyle, "Key Frame 1");

    scale1x = panel1->AddSlider(0, 3,       initScale1x, GlowSliderWidget::defaultOptions, 2, "%.1f", "Scale1.x:\n%.1f", this);
    scale1y = panel1->AddSlider(0, 3,       initScale1y, GlowSliderWidget::defaultOptions, 2, "%.1f", "Scale1.y:\n%.1f", this);
    rotate1 = panel1->AddSlider(0, 2*M_PI,  initRotate1, GlowSliderWidget::defaultOptions, 2, "%.1f", "Rotate1:\n%.1f", this);
    translate1x = panel1->AddSlider(-12, 9, initTrnsl1x, GlowSliderWidget::defaultOptions, 2, "%.1f", "Translate1.x:\n%.1f", this);
    translate1y = panel1->AddSlider(-12, 9, initTrnsl1y, GlowSliderWidget::defaultOptions, 2, "%.1f", "Translate1.y:\n%.1f", this);

    GlowQuickPanelWidget* panel2 = controlWindow->AddPanel(GlowQuickPanelWidget::etchedStyle, "Key Frame 2");

    scale2x = panel2->AddSlider(0, 3,       initScale2x, GlowSliderWidget::defaultOptions, 2, "%.1f", "Scale2.x:\n%.1f", this);
    scale2y = panel2->AddSlider(0, 3,       initScale2y, GlowSliderWidget::defaultOptions, 2, "%.1f", "Scale2.y:\n%.1f", this);
    rotate2 = panel2->AddSlider(0, 2*M_PI,  initRotate2, GlowSliderWidget::defaultOptions, 2, "%.1f", "Rotate2:\n%.1f", this);
    translate2x = panel2->AddSlider(-12, 9, initTrnsl2x, GlowSliderWidget::defaultOptions, 2, "%.1f", "Translate2.x:\n%.1f", this);
    translate2y = panel2->AddSlider(-12, 9, initTrnsl2y, GlowSliderWidget::defaultOptions, 2, "%.1f", "Translate2.y:\n%.1f", this);

    GlowQuickPanelWidget* panel3 = controlWindow->AddPanel(GlowQuickPanelWidget::etchedStyle, "Interpolation Method");

    animationCheckbox = panel3->AddCheckBox("Animation", GlowCheckBoxWidget::on, this);

    _RBGroup = panel3->AddRadioGroup(GlowQuickPalette::vertical,3, this);
    _rb1 = _RBGroup->AddRadioButton("1. Vertex Interpolation");
    _rb2 = _RBGroup->AddRadioButton("2. Matrix Entry Interpolation");
    _rb3 = _RBGroup->AddRadioButton("3. Matrix Parameter Interpolation");

    controlWindow->Pack();

    // Tell mySketchpadData what the initial values are.

    mySketchpadData.setInterpolationMethod(1);
    mySketchpadData.setAlpha(_alpha);

    mySketchpadData.setScale1x    (initScale1x);
    mySketchpadData.setScale1y    (initScale1y);
    mySketchpadData.setRotate1    (initRotate1);
    mySketchpadData.setTranslate1x(initTrnsl1x);
    mySketchpadData.setTranslate1y(initTrnsl1y);

    mySketchpadData.setScale2x    (initScale2x);
    mySketchpadData.setScale2y    (initScale2y);
    mySketchpadData.setRotate2    (initRotate2);
    mySketchpadData.setTranslate2x(initTrnsl2x);
    mySketchpadData.setTranslate2y(initTrnsl2y);
}

void
SketchpadWindow::quitProg()
{
    howManyOfMe--;
    Close();
    if(!howManyOfMe) exit(0);
}

void
SketchpadWindow::OnEndPaint()
{
    GLdraw_E2<double>::clear_screen();
    mySketchpadData.drawNextFrame();
}

void
SketchpadWindow::OnMessage(const GlowIdleMessage &)
{
    const double unitIncrement = 0.0005;
    if(basculateUp) {
        _alpha += unitIncrement;
        if(_alpha>1.0)
            basculateUp = !basculateUp;
    }
    else {
        _alpha -= unitIncrement;
        if(_alpha<0.0)
            basculateUp = !basculateUp;
    }

    mySketchpadData.setAlpha(_alpha);

    Refresh();
}

void
SketchpadWindow::OnKeyboard(Glow::KeyCode key, int, int,
                            Glow::Modifiers)
{
    switch (key) {
    case 'q': case 'Q': case Glow::escapeKey: quitProg();
    case '1': case '2': case '3': structureDrawn = key - 48; break;
    default:
        ;
    }
}

void
SketchpadWindow::OnReshape(int width, int height)
{
    ::glViewport(0, 0, width, height);

    viewportWidth = width;
    viewportHeight = height;

    GLdraw_E2<double>::setup_projection( lowerLeft, upperRight );
}

void
SketchpadWindow::OnMessage(const GlowSliderMessage& message)
{
    if (message.widget == scale1x)
        mySketchpadData.setScale1x(message.value);
    else if (message.widget == scale1y)
        mySketchpadData.setScale1y(message.value);
    else if (message.widget == rotate1)
        mySketchpadData.setRotate1(message.value);
    else if (message.widget == translate1x)
        mySketchpadData.setTranslate1x(message.value);
    else if (message.widget == translate1y)
        mySketchpadData.setTranslate1y(message.value);

    else if (message.widget == scale2x)
        mySketchpadData.setScale2x(message.value);
    else if (message.widget == scale2y)
        mySketchpadData.setScale2y(message.value);
    else if (message.widget == rotate2)
        mySketchpadData.setRotate2(message.value);
    else if (message.widget == translate2x)
        mySketchpadData.setTranslate2x(message.value);
    else if (message.widget == translate2y)
        mySketchpadData.setTranslate2y(message.value);

    Refresh();
}

void
SketchpadWindow::OnMessage(const GlowRadioButtonMessage& message)
{
    if(message.groupWidget == _RBGroup)
        if(message.buttonWidget == _rb1)
            mySketchpadData.setInterpolationMethod(1);
        else if(message.buttonWidget == _rb2)
            mySketchpadData.setInterpolationMethod(2);
        else if(message.buttonWidget == _rb3)
            mySketchpadData.setInterpolationMethod(3);
    Refresh();
}

void
SketchpadWindow::OnMessage(const GlowCheckBoxMessage& message)
{
    if (message.widget == animationCheckbox)
        if (message.state == GlowCheckBoxWidget::on)
            Glow::RegisterIdle(this);
        else
            Glow::UnregisterIdle(this);
}
