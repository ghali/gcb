/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <cmath>
using std::fabs;
#include <algorithm>
#include <iterator>

#include "glow.h"
using namespace glow;

#include "dualitydata.h"

void
DualityData::insertPoint(const Point_E2d& p)
{
    P.push_back(p);
}

void
DualityData::getDual(const Point_E2d& p, Point_E2d& pd1, Point_E2d& pd2)
{
    if(p.x() == 0.0 && p.y() == 0.0)
        pd1 = pd2 = p;

    // Point(a,b) has as dual the line: a.x + b.y = 1
    if(fabs(p.x()) > fabs(p.y())) { // point is closer to vertical
        pd1 = Point_E2d(( -1.0 + 3.0 * p.y()) / p.x(), -3.0);
        pd2 = Point_E2d(( -1.0 - 3.0 * p.y()) / p.x(),  3.0);
    }
    else {
        pd1 = Point_E2d(-3.0, ( -1.0 + 3.0 * p.x()) / p.y());
        pd2 = Point_E2d( 3.0, ( -1.0 - 3.0 * p.x()) / p.y());
    }
}

std::ostream&
operator<<(std::ostream& os, const DualityData& D)
{
    std::copy(D.P.begin(), D.P.end(), std::ostream_iterator<Point_E2d>(os, "\n"));
    return os;
}

void
DualityData::draw_point_and_dual(const Point_E2d& p)
{
    glBegin(GL_POINTS); {
        glVertex2f( p.x(), p.y() );
    } glEnd();

    glLineWidth(3.0);

    Point_E2d pd1, pd2;
    DualityData::getDual(p, pd1, pd2);
    glBegin(GL_LINES); {
        glVertex2f( pd1.x(), pd1.y() );
        glVertex2f( pd2.x(), pd2.y() );
    } glEnd();
    glFlush();
}

//----------------------------------------------------------------
void
DualityData::drawScene(float foreground, float /*background*/)
{
    glColor3f(foreground, foreground, foreground);
    glLineWidth(3.0);

    glPointSize(7.0);
    for(vector<Point_E2d>::iterator iter = P.begin();
        iter != P.end();
        ++iter)
    {
        const Point_E2d& p = *iter;

        draw_point_and_dual(p);
    }

    glFlush();
}
