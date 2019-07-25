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

#include "solid/ifs/indexed_face_set.h"
#include "solid/ifs/ifs_reader.h"

typedef double MyDouble;
typedef Indexed_face_set<MyDouble> Indexed_face_set_d;
typedef IFS_reader<MyDouble> IFS_reader_d;

#include "opengl/gldraw_s2.h"

class Regular_spherical_models_dataviewer : public GlowComponent
{
public:
    Regular_spherical_models_dataviewer(GlowComponent* parent)
        : GlowComponent(parent),
          gldraw(),
          objectType('t')
    {
    }

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
    }
    void cube()
    {
    }
    void octahedron()
    {
    }
    void icosahedron()
    {
    }
    void dodecahedron()
    {
    }

private:
    Indexed_face_set_d ifs_t;
    Indexed_face_set_d ifs_c;
    Indexed_face_set_d ifs_o;
    Indexed_face_set_d ifs_d;
    Indexed_face_set_d ifs_i;

    GLdraw_S2 gldraw;
    char objectType;
};

#endif // SPHERICAL_MODELS_DATAVIEWER_H
