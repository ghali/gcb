/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SPHERICAL_MODELS_DATAVIEWER_H
#define SPHERICAL_MODELS_DATAVIEWER_H

#include <string>
using std::string;

#include "glow.h"
using namespace glow;

#include "geom_types.h"

#include "opengl/gldraw_s2.h"

const double innerRadius = 0.04;

class Spherical_models_dataviewer : public GlowComponent
{
public:
    Spherical_models_dataviewer(GlowComponent* parent)
        : GlowComponent(parent),
          gldraw(),
          objectType('t')
    {}

    void setObject(char t) { objectType = t; }

protected:

    virtual void OnEndPaint()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gldraw.drawAxis();
        glEnable(GL_LIGHTING);

        GLfloat position[] = { 6, 4, -1, 0.0 };
        glLightfv (GL_LIGHT0, GL_POSITION, position);

        switch(objectType) {
        case 't': tetrahedron() ; break;
        case 'c': cube()        ; break;  
        case 'o': octahedron()  ; break;
        case 'i': icosahedron() ; break;
        case 'd': dodecahedron(); break;
        }

        gldraw.draw_unit_sphere();
    }

    void tetrahedron()
    {
        // ...
    }
    void cube()
    {
        // ...
    }
    void octahedron()
    {
        // ...
    }
    void icosahedron()
    {
        // ...
    }
    void dodecahedron()
    {
        // ...
    }

private:
    GLdraw_S2 gldraw;
    char objectType;
};

#endif // SPHERICAL_MODELS_DATAVIEWER_H
