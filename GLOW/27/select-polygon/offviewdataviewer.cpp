/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <algorithm>
#include "glowViewTransform.h"

#include "offviewdataviewer.h"
#include "solid/heds/heds_reader.h"
#include "solid/heds/heds.h"

typedef HEDS_reader<My_heds_traits>   HEDS_reader_ff;

OffviewDataViewer::OffviewDataViewer(const string& filename,
                                     GlowComponent* parent)
    : GlowComponent(parent)
{
    if(HEDS_reader_ff::read(myHEDS, filename.c_str() /*, true*/) )
    {
        cerr << "Unable to read " << filename << endl;
        exit(1);
    }

    initCamera();

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    glDisable(GL_LIGHTING); 

    glClearColor(0.0, 0.0, 0.2, 0.0);
}

void OffviewDataViewer::initCamera(void)
{
    const Bbox_E3f bbox = HEDS_misc_fn::get_Bbox(myHEDS);

    cnt = bbox.center();

    maxSpan = std::max( bbox.UR().x() - bbox.LL().x(),
                        std::max( bbox.UR().y() - bbox.LL().y(), 
                                  bbox.UR().z() - bbox.LL().z() ));
    // Non-CFG demo:
    eye = Point_E3f(cnt.x(),
                    cnt.y(),
                    cnt.z() + 3.0 * maxSpan);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(40.0, 1.0, 1.0, 6.0 * maxSpan);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(eye.x(), eye.y(), eye.z(),
              cnt.x(), cnt.y(), cnt.z(),
              0.0,1.0,0.0);

    glPushMatrix();             // dummy push
}

void OffviewDataViewer::OnEndPaint()
{
    drawFilledAndWireframe(GL_RENDER);
}

void OffviewDataViewer::drawFilled(GLenum mode)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_POLYGON_OFFSET_LINE); 
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); 

    draw_polyhedron(true, mode);
}

void OffviewDataViewer::drawWireframe( /*GLenum mode*/ )
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); 
    glEnable(GL_POLYGON_OFFSET_LINE); 
    glPolygonOffset(-1.0,-1.0); 

    draw_polyhedron(false, GL_RENDER); // we're not trying to pick segments
}

void OffviewDataViewer::drawFilledAndWireframe(GLenum mode)
{
    drawFilled(mode);
    drawWireframe();
}

void OffviewDataViewer::draw_polyhedron(bool usePolyColors, GLenum mode)
{
    for(unsigned int f=0; f<myHEDS.F.size(); f++) {

        if(usePolyColors) {
            Color_3f & c = myHEDS.F[f]->ft.color;
            glColor3f(c.r(), c.g(), c.b());
        }

        if(mode == GL_SELECT)
            glLoadName(f);

        My_edge_ptr firstEdge = myHEDS.F[f]->edge;
        My_edge_ptr myEdge = firstEdge;
        glBegin(GL_POLYGON);
        do {
            Point_E3f & pnt = myEdge->source->nt.coords;
            glVertex3f(pnt.x(), pnt.y(), pnt.z());
            myEdge = myEdge->succ;
        } while( myEdge != firstEdge );
        glEnd();
    }
}

void OffviewDataViewer::processNearestHit(GLint hits, GLuint selectBuf[])
{
    int n = 0;
    double minz = selectBuf[1];
    for(int i=1; i<hits; i++) {
        if( selectBuf[1+i*4] < minz ) {
            n = i;
            minz = selectBuf[1+i*4];
        }
    }

    int selected_face = selectBuf[3+n*4];
    myHEDS.F[ selected_face ]->ft.color.set_r(1.0);
    selected_faces.push_back(selected_face);
}

const int BUFSIZE = 512;

void OffviewDataViewer::pickPolygon(int x, int y)
{
    GLuint selectBuf[BUFSIZE];
    GLint viewport[4];

    glGetIntegerv(GL_VIEWPORT, viewport);

    glSelectBuffer(BUFSIZE, selectBuf);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); {
        glLoadIdentity();

        //  create 1x1 pixel picking region at cursor location
        gluPickMatrix(GLdouble(x), GLdouble(viewport[3] - y), 1.0, 1.0, viewport);

        gluPerspective( 40.0, 1.0, 1.0, 6.0 * maxSpan );

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix(); {

            static_cast<GlowViewManipulator*>(Parent())->ApplyToGLMatrix();

            drawFilled(GL_SELECT);

            glMatrixMode(GL_PROJECTION);

        } glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    } glPopMatrix();

    glFlush();

    GLint hits = glRenderMode(GL_RENDER);
    if(hits != 0)
        processNearestHit(hits, selectBuf);

    static_cast<GlowWindow*>(Parent())->Refresh();
}

void OffviewDataViewer::extrude_faces()
{
    for(unsigned int i=0; i<selected_faces.size(); ++i)
    {
        // ...
    }
}

void OffviewDataViewer::extrude_drag(float /*current_y*/, float /*starting_y*/)
{
    // ...
}
