/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef DISPLAY_LIST_DEMO_WINDOW_H
#define DISPLAY_LIST_DEMO_WINDOW_H

#include <iostream>
#include <vector>
using std::vector;

#include "glow.h"
using namespace glow;

#include "geometry/S2/point_s2.h"
#include "geometry/S2/triangle_s2.h"
typedef Point_S2<double>       Point_S2d;
typedef Triangle_S2<double> Triangle_S2d;

#include "misc/clock.h"
#include "opengl/fpscounter.h"
#include "opengl/gldrawstring.h"

class Display_list_demo_window : public GlowWindow, public GlowIdleReceiver
{
public:
    Display_list_demo_window(int number_of_subdivisions)
        : GlowWindow("Display list demo window",
                     GlowWindow::autoPosition, GlowWindow::autoPosition,
                     700, 700,
                     Glow::rgbBuffer | Glow::doubleBuffer | Glow::depthBuffer,
                     Glow::keyboardEvents),
          myclock(),
          lastSeconds(myclock.getSecondsSinceStart()),
          myfps(),
          myGLstringRenderer(GLUT_BITMAP_HELVETICA_12, 0.05, 0.05)
    {
        setup_projection_matrices();

        myDisplayList = setup_display_list(number_of_subdivisions);

        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);

        Glow::RegisterIdle(this);
    }

    virtual ~Display_list_demo_window()
    {
        glDeleteLists(myDisplayList, 1);
    }
protected:

    GLuint setup_display_list(int number_of_subdivisions)
    {
//----------------setup_display_list_Begin----------------
        GLuint display_list_number = glGenLists(1);

        initialize_root_level();

        while(number_of_subdivisions--)
            recursive_subdivide();

        glNewList(display_list_number, GL_COMPILE); {
            typedef vector<Triangle_S2d>::iterator VIT;
            for(VIT vit = V.begin(); vit != V.end(); ++vit) {
                glColor3f((drand48()>0.5) ? 0.0 : 1.0,
                          (drand48()>0.5) ? 0.0 : 1.0,
                          (drand48()>0.5) ? 0.0 : 1.0);
                glBegin(GL_TRIANGLES); {
                    glVertex3f(vit->P0().x(), vit->P0().y(), vit->P0().z());
                    glVertex3f(vit->P2().x(), vit->P2().y(), vit->P2().z());
                    glVertex3f(vit->P1().x(), vit->P1().y(), vit->P1().z());
                } glEnd();
            }
        } glEndList();            
//----------------setup_display_list_End----------------
        std::cout << V.size() << " were generated" << std::endl;
        return display_list_number;
    }

    void setup_projection_matrices()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, 1.0, 1.0, 100.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(2.5, 1.0, 1.5,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);
    }

    virtual void OnEndPaint()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_LIGHTING);

        GLfloat position[] = { 6, 4, -1, 0.0 };
        glLightfv (GL_LIGHT0, GL_POSITION, position);

        double s = myclock.getSecondsSinceStart();
        double i = s - 2.0 * M_PI * std::floor(s / 2.0 / M_PI);

        glPushMatrix(); {

            glRotated(i * 180.0 / M_PI, 0,1,0);
            glRotated(90, 1,0,0);
            glCallList(myDisplayList);

        } glPopMatrix();

        myGLstringRenderer.draw(myfps.getFrameRate());
    }

    virtual void OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                            Glow::Modifiers /*modifiers*/)
    {
        switch (key) {
        case 'q': case 'Q': case Glow::escapeKey: exit(0);
        default: ;
        }
    }

    virtual void OnMessage(const GlowIdleMessage & /*message*/)
    {
        float seconds = myclock.getSecondsSinceStart();
        if(seconds - lastSeconds > 0.001) {
            Refresh();
            lastSeconds = seconds;
        }
    }

    virtual void OnReshape(int width, int height)
    {
        int bigger = std::max( width, height );
        glViewport(0, 0, bigger, bigger);        // cheaply ensure 1:1 aspect
    }

    void recursive_subdivide()
    {
        vector<Triangle_S2d> newV;
        typedef vector<Triangle_S2d>::iterator VIT;
        for(VIT vit = V.begin(); vit != V.end(); ++vit) {
            vector<Triangle_S2d> newtriangles;
            newtriangles = vit->get_recursive_subdivision();
            newV.insert(newV.end(), newtriangles.begin(), newtriangles.end());
        }
        V = newV;
    }

    void initialize_root_level()
    {
        Point_S2d p0( 1, 1, 1);
        Point_S2d p1(-1, 1, 1);
        Point_S2d p2(-1,-1, 1);
        Point_S2d p3( 1,-1, 1);

        Point_S2d p4( 1, 1,-1);
        Point_S2d p5(-1, 1,-1);
        Point_S2d p6(-1,-1,-1);
        Point_S2d p7( 1,-1,-1);

        V.push_back(Triangle_S2d(p1, p0, p3));
        V.push_back(Triangle_S2d(p1, p3, p2));

        V.push_back(Triangle_S2d(p0, p4, p7));
        V.push_back(Triangle_S2d(p0, p7, p3));

        V.push_back(Triangle_S2d(p4, p6, p7));
        V.push_back(Triangle_S2d(p4, p5, p6));

        V.push_back(Triangle_S2d(p5, p1, p2));
        V.push_back(Triangle_S2d(p5, p2, p6));

        V.push_back(Triangle_S2d(p0, p5, p4));
        V.push_back(Triangle_S2d(p0, p1, p5));

        V.push_back(Triangle_S2d(p3, p7, p6));
        V.push_back(Triangle_S2d(p3, p6, p2));
    }

private:
    Clock myclock;
    float lastSeconds;

    vector<Triangle_S2d> V;

    GLuint myDisplayList;
    FPScounter myfps;
    GLstringRenderer myGLstringRenderer;
};

#endif // DISPLAY_LIST_DEMO_WINDOW_H
