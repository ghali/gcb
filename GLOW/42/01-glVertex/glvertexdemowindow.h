/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef GLVERTEXDEMOWINDOW_H
#define GLVERTEXDEMOWINDOW_H

#include "glow.h"
using namespace glow;

#include "opengl/glimagewriter.h"

const int initViewportWidth  = 2*644;
const int initViewportHeight = 2*484;

struct Point2f { float x, y; };

Point2f points1[] = {{  10.0f,  80.0f }, {  40.0f, 140.0f },
                     {  50.0f,  40.0f }, {  90.0f, 100.0f },
                     { 130.0f,  50.0f }, { 150.0f, 150.0f }};

Point2f points2[] = {{ 80.0f,   80.0f }, {  20.0f, 140.0f },
                     { 130.0f, 150.0f }, { 140.0f,  90.0f },
                     { 100.0f,  30.0f }, {  40.0f,  50.0f }};

Point2f points3[] = {{ 10.0f,   80.0f }, {  30.0f, 140.0f },
                     {  70.0f, 140.0f }, {  50.0f,  50.0f },
                     {  90.0f,  40.0f }, { 110.0f, 140.0f },
                     { 140.0f, 130.0f }, { 150.0f,  40.0f }};

Point2f points4[] = {{ 10.0f,   80.0f }, {  30.0f, 140.0f },
                     {  50.0f,  50.0f }, {  70.0f, 140.0f },
                     {  90.0f,  40.0f }, { 110.0f, 140.0f },
                     { 150.0f,  40.0f }, { 140.0f, 130.0f }};


class GLvertexDemoWindow : public GlowWindow
{
    GLimageWriter myGLimageWriter;
public:
    GLvertexDemoWindow()
        : GlowWindow("GLvertex Demo Window",
                     GlowWindow::autoPosition, GlowWindow::autoPosition,
                     initViewportWidth, initViewportHeight,
                     Glow::rgbBuffer | Glow::doubleBuffer,
                     Glow::keyboardEvents)
    {
        setupProjectionMatrices();

        glShadeModel(GL_FLAT);
    }

protected:
    void setupProjectionMatrices()
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(-2, 642, -2, 482);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

        glPointSize(5.0);
        glLineWidth(2.0);
    }

    void mydraw1(
                 float x, float y, float gray,
                 Point2f* points, int numPoints, GLenum type)
    {
        glColor3f(gray,gray,gray);
        glPushMatrix(); {
            glTranslatef(x,y,0.0f);
            glBegin(type); {
                int i=-1;
                while(++i != numPoints)
                    glVertex2f( points[i].x, points[i].y );
            } glEnd();
        } glPopMatrix();
    }

//----------------mydraw2_Begin----------------
    void mydraw2(
                 float x, float y, float gray,
                 Point2f* points, int numPoints, GLenum type)
    {
        bool colorFlag = false;
        glPushMatrix(); {
            glTranslatef(x,y,0.0f);
            glBegin(type); {
                int i=-1;
                while(++i != numPoints) {
                    if((type==GL_TRIANGLES && i%3==0) ||
                       ((type==GL_TRIANGLE_STRIP ||
                         type==GL_TRIANGLE_FAN) && i>2))
                        colorFlag = !colorFlag;
                    float f = colorFlag ? gray : gray + 0.2;
                    glColor3f(f,f,f);
                    glVertex2f( points[i].x, points[i].y );
                }
            } glEnd();
        } glPopMatrix();
    }
//----------------mydraw2_End----------------

    void mydraw3(
                 float x, float y, float gray,
                 Point2f* points, int numPoints, GLenum type)
    {
        bool colorFlag = false;
        glPushMatrix(); {
            glTranslatef(x,y,0.0f);
            glBegin(type); {
                int i=-1;
                while(++i != numPoints) {
                    if((type==GL_QUADS && i%4==0) ||
                       (type==GL_QUAD_STRIP && i%2==0))
                        colorFlag = !colorFlag;
                    float f = colorFlag ? gray : gray + 0.2;
                    glColor3f(f,f,f);
                    glVertex2f( points[i].x, points[i].y );
                }
            } glEnd();
        } glPopMatrix();
    }

//----------------OnEndPaint_Begin----------------
    virtual void OnEndPaint()
    {
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        
        drawBoard();

        float i[] = { 0.0f, 160.0f, 320.0f, 480.0f };

        mydraw1( i[0], i[2], 0.0f, points1, 6, GL_POINTS);
        mydraw1( i[1], i[2], 0.0f, points1, 6, GL_LINES);
        mydraw1( i[2], i[2], 0.0f, points1, 6, GL_LINE_STRIP);
        mydraw1( i[3], i[2], 0.0f, points1, 6, GL_LINE_LOOP);

        mydraw2( i[0], i[1], 0.6f, points1, 6, GL_TRIANGLES);
        mydraw2( i[1], i[1], 0.6f, points1, 6, GL_TRIANGLE_STRIP);
        mydraw2( i[2], i[1], 0.6f, points2, 6, GL_TRIANGLE_FAN);

        mydraw3( i[0], i[0], 0.6f, points3, 8, GL_QUADS);
        mydraw3( i[1], i[0], 0.6f, points4, 8, GL_QUAD_STRIP);
        mydraw3( i[2], i[0], 0.6f, points2+1, 5, GL_POLYGON);
    }
//----------------OnEndPaint_End----------------

    virtual void drawBoard()
    {
        glColor3b(0,0,0);

        float x = 800.0f;
        do {
            x -= 160.0f;
            glBegin(GL_LINES); {
                  glVertex2f(x,  0.0f);
                  glVertex2f(x,480.0f);
            } glEnd();
        } while(x);

        float y = 640.0f;
        do {
            y -= 160.0f;
            glBegin(GL_LINES); {
                  glVertex2f(  0.0f, y);
                  glVertex2f(640.0f, y);
            } glEnd();
        } while(y);
    }

    virtual void OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                            Glow::Modifiers /*modifiers*/)
    {
        switch (key) {
        case 'w': myGLimageWriter.writeImage("image", GlowSubwindow::Width(), GlowSubwindow::Height()); break;
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

#endif // GLVERTEXDEMOWINDOW_H
