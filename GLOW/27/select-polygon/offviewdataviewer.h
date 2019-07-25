/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef OFFVIEWDATAVIEWER_H
#define OFFVIEWDATAVIEWER_H

#include "solid/heds/geometry_types.h"
#include "solid/heds/heds_types.h"

#include <string>
#include <algorithm>
using namespace std;

#include "glow.h"
using namespace glow;

class OffviewDataViewer : public GlowComponent
{
    HEDS_ff myHEDS;
public:
    OffviewDataViewer(const string& filename,
                      GlowComponent* parent);
private:
    void initLight (void);
    void initCamera (void);
protected:

    virtual void OnEndPaint();

    void drawFilled(GLenum mode);
    void drawWireframe( /*GLenum mode*/ );
    void drawFilledAndWireframe(GLenum mode);

    void draw_polyhedron(bool usePolyColors, GLenum mode);

    void processNearestHit(GLint hits, GLuint selectBuf[]);

public:

    void pickPolygon(int x, int y);

    void extrude_faces();
    void extrude_drag(float current_y, float starting_y);

private:
    Point_E3f eye, cnt;

    double maxSpan;

    vector<unsigned int> selected_faces;
};

#endif // OFFVIEWDATAVIEWER_H
