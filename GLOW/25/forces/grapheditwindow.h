/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef GRAPHEDITWINDOW_H
#define GRAPHEDITWINDOW_H

#include "glow.h"
#include "glowPushButtonWidget.h"
#include "glowCheckBoxWidget.h"
#include "glowQuickPalette.h"
#include "glowPanelWidget.h"
#include "glowLabelWidget.h"
using namespace glow;

#include "geometry_types.h"
#include "graph_draw.h"
#include "graph_IO.h"

class GraphEditWindow : public GlowWindow, public GlowPushButtonReceiver, public GlowSliderReceiver
{
public:
    GraphEditWindow();
    virtual ~GraphEditWindow();

protected:
    void setupProjection();

    My_node* findNearest(const Point_E2d& clicked);

    virtual void OnEndPaint();
    virtual void OnMouseDown(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);
    virtual void OnMouseUp(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);
    virtual void OnMouseDrag(int x, int y);
    virtual void OnKeyboard(Glow::KeyCode key, int x, int y, Glow::Modifiers modifiers);
    virtual void OnReshape(int width, int height);
    virtual void OnMessage(const GlowPushButtonMessage& message);
    virtual void OnMessage(const GlowSliderMessage& message);

    inline void unproject(const Point_E2i& pin, Point_E2d& pout);

    void render();

private:
    My_graph G;

    int viewportWidth, viewportHeight;

    Point_E2d sourcePoint, currentPoint;

    My_node *sourceNode;

    My_node *draggedNode;
    bool draggingNode;
    bool draggingEdge;

    bool currently_drawing;

    int currentFileNum;

    GlowQuickPaletteWindow* controlWindow;

    GlowPushButtonWidget* clearButton;
    GlowPushButtonWidget* printButton;
    GlowPushButtonWidget* drawOnceButton;
    GlowPushButtonWidget* drawButton;

    GlowSliderWidget* fileSlider;

    GlowPushButtonWidget* loadButton;
    GlowPushButtonWidget* saveButton;
    GlowPushButtonWidget* randomButton;
    GlowPushButtonWidget* quitButton;

    int pscounter;
    Bbox_E2d myBbox_E2d;
};

#endif // GRAPHEDITWINDOW_H
