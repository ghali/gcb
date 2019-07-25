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
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

#include "misc/conversions.h"
#include "opengl/gldraw_e2.h"
#include "grapheditwindow.h"
#include "graph_draw.h"
#include "graph_IO.h"

// initial values
const int initViewportWidth  = 1530;
const int initViewportHeight = 1100;
const double threshold = 0.5;

GraphEditWindow::GraphEditWindow() :
    GlowWindow("GraphEdit",
               GlowWindow::autoPosition, GlowWindow::autoPosition,
               initViewportWidth, initViewportHeight,
               Glow::rgbBuffer | Glow::doubleBuffer,
               Glow::mouseEvents | Glow::dragEvents | Glow::keyboardEvents),

    viewportWidth(initViewportWidth),
    viewportHeight(initViewportHeight),

    draggingNode(false),
    draggingEdge(false),
    currently_drawing(false),
    pscounter(0)
{
    //----------------
    // Control window
    //----------------
    controlWindow = new GlowQuickPaletteWindow("Controls");

    GlowQuickPanelWidget* panel = controlWindow->AddArrangingPanel(
        GlowQuickPanelWidget::vertical);
    clearButton = panel->AddPushButton("Clear", this);
    printButton = panel->AddPushButton("Print", this);
    drawOnceButton = panel->AddPushButton("Once", this);
    drawButton = panel->AddPushButton("Draw", this);
    loadButton = panel->AddPushButton("Load", this);
    saveButton = panel->AddPushButton("Save", this);
    quitButton = panel->AddPushButton("Quit", this);

    controlWindow->Pack();
}

GraphEditWindow::~GraphEditWindow()
{
}

//----------------------------------------------------------------
void
GraphEditWindow::OnEndPaint()
{
    ::glClear(GL_COLOR_BUFFER_BIT);

    if(currently_drawing)
        currently_drawing = barycentric_iteration( G, threshold );

    // draw edges
    for(std::list<My_edge*>::const_iterator Eit = G.edges.begin();
        Eit != G.edges.end();
        ++Eit)
        GLdraw_E2<double>::draw_segment( (*Eit)->source()->info().coords,
                                         (*Eit)->target()->info().coords );

    // draw nodes
    for(std::list<My_node*>::const_iterator Nit = G.nodes.begin();
        Nit != G.nodes.end();
        ++Nit)
        if( (*Nit)->info().is_free )
            GLdraw_E2<double>::draw_point((*Nit)->info().coords, GlowColor::yellow);
        else
            GLdraw_E2<double>::draw_point((*Nit)->info().coords, GlowColor::red);

    if(draggingEdge)
        GLdraw_E2<double>::draw_segment(sourcePoint, currentPoint);

    if(currently_drawing)
        Refresh();
}

//----------------------------------------------------------------
My_node*
GraphEditWindow::findNearest(const Point_E2d& clicked)
{
    // If we're at a node, return it. Otherwise, return NULL
    double dist2 = 1e99;

    My_node *nearestNode = NULL;

    std::list<My_node*>& LN = G.nodes;
    for(std::list<My_node*>::const_iterator Nit = LN.begin();
        Nit != LN.end();
        ++Nit) {
        double thisdist2 =
            std::fabs((*Nit)->info().coords.x() - clicked.x()) +
            std::fabs((*Nit)->info().coords.y() - clicked.y());

        if( thisdist2 < dist2 ) {
            dist2 = thisdist2;
            nearestNode = *Nit;
        }
    }
    if( dist2 < 8.0 )
        return nearestNode;
    else
        return NULL;
}

//----------------------------------------------------------------
void
GraphEditWindow::OnMouseDown(Glow::MouseButton button,
                             int x, int y, Glow::Modifiers /*modifiers*/)
{
    // Point_E2d aPoint;
    unproject(Point_E2i(x,y), currentPoint);

    // handle 3 cases:
    // 1- the user inserts a new node (click with LMB)
    // 2- the user inserts a new edge (click and drag with LMB)
    // 3- the user moves a node (click and drag with MMB)

    My_node *currentNode = findNearest(currentPoint);

    switch (button) {
    case Glow::leftButton:

        if(!currentNode)        // user is entering a node (1)
            G.insert_node(currentPoint);
        else {                        // user is dragging (entering) an edge (2)
            draggingEdge = true;
            sourceNode  = currentNode;
            sourcePoint = sourceNode->info().coords;
        }
        break;
    case Glow::middleButton:
        if(currentNode) {
            draggingNode = true;
            draggedNode = currentNode;
        }
        break;

    case Glow::rightButton:
        if(currentNode)
            currentNode->info().flip_status();
        break;
    }
    Refresh();
}

void
GraphEditWindow::OnMouseDrag(int x, int y)
{
    // handle 2 cases:
    // 1- the user is inserting an edge (dragging with LMB)
    // 2- the user is moving a node (dragging with MMB)

    if(draggingEdge) {                // (1)
        unproject(Point_E2i(x,y), currentPoint);
        Refresh();
    }
    if(draggingNode) {                // (2)
        unproject(Point_E2i(x,y), currentPoint);
        draggedNode->info().set_coords(currentPoint);
        Refresh();
    }
}

void
GraphEditWindow::OnMouseUp(Glow::MouseButton button,
                           int x, int y, Glow::Modifiers /*modifiers*/)
{
    // handle cases:
    // 1- the user has just inserted an edge (releasing LMB on a node)
    // 2- the user has just abandoned inserting an edge (releasing LMB elsewhere)
    // 3- the user has just placed a node in its new position (releasing MMB)

    switch (button) {
    case Glow::leftButton:
        if(draggingEdge) {        // (1)
            draggingEdge = false;
            Point_E2d targetPoint;
            unproject(Point_E2i(x,y), targetPoint);
            My_node *targetNode = findNearest(targetPoint);
            if(targetNode)
                G.insert_edge(sourceNode, targetNode);
            // otherwise the user aborted entering an edge: do nothing. (2)
            Refresh();
        }
        break;
    case Glow::middleButton:
        if(draggingNode) {
            draggingNode = false;
            unproject(Point_E2i(x,y), currentPoint);
            draggedNode->info().set_coords(currentPoint);
            Refresh();
        }
        break;
    case Glow::rightButton:
        break;
    }
}

void
GraphEditWindow::OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                            Glow::Modifiers /*modifiers*/)
{
    switch (key) {
    case 'q':
    case 'Q':
    case Glow::escapeKey:
        exit(0);
    default:
        ;
    }
}

void
GraphEditWindow::OnReshape(int width, int height)
{
    ::glViewport(0, 0, width, height);

    viewportWidth = width;
    viewportHeight = height;

    GLdraw_E2<double>::setup_projection(Point_E2d(0,0), Point_E2d(width, height));

    myBbox_E2d = Bbox_E2d( Point_E2d(0,0), Point_E2d(width,height) );
}

// Receive pushbutton events
void
GraphEditWindow::OnMessage(const GlowPushButtonMessage& message)
{
    if (message.widget == clearButton)
        G.clear();
    else if (message.widget == printButton)
        cout << G << endl;
    else if (message.widget == drawOnceButton) {
        barycentric_iteration( G, threshold );
        render();
    }
    else if (message.widget == drawButton)
        currently_drawing = true;
    else if (message.widget == loadButton)
        load(G, "../graphs/savedgraph01.xpm");
    else if (message.widget == saveButton)
        save(G, "../graphs/savedgraph01.xpm");
    else if (message.widget == randomButton)
        // generate random graph
        ;
    else if (message.widget == quitButton)
        exit(0);

    Refresh();
}

void
GraphEditWindow::unproject(const Point_E2i& pin, Point_E2d& pout)
{
    GLint realy = static_cast<GLint>(viewportHeight - pin.y() - 1);
    pout = Point_E2d(static_cast<double>(pin.x()), static_cast<double>(realy));
}

void
GraphEditWindow::render()
{
    Postscript_d myPS("psout/file_" + integer_to_zero_padded_string(++pscounter) + ".eps", myBbox_E2d);

    // draw edges
    for(std::list<My_edge*>::const_iterator Eit = G.edges.begin();
        Eit != G.edges.end();
        ++Eit)
        myPS.draw( Segment_E2d( (*Eit)->source()->info().coords,
                                (*Eit)->target()->info().coords ) );

    // draw nodes
    for(std::list<My_node*>::const_iterator Nit = G.nodes.begin();
        Nit != G.nodes.end();
        ++Nit)
        if((*Nit)->info().is_free)
            myPS.draw_small_circle( (*Nit)->info().coords );
        else
            myPS.draw_small_disk( (*Nit)->info().coords );
}
