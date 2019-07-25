/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef DUALITYDATA_H
#define DUALITYDATA_H

#include <vector>
#include <iostream>
using namespace std;

#include "geom_types.h"

class DualityData
{
    vector<Point_E2d> P;
public:
    void
    insertPoint(const Point_E2d& p);

    DualityData() {};

    virtual ~DualityData() {};

    static void getDual(const Point_E2d& p, Point_E2d& pd1, Point_E2d& pd2);

    void draw_point_and_dual(const Point_E2d& p);
    void drawScene(float foreground, float background);

    friend std::ostream&
    operator<<(std::ostream& os, const DualityData& B);
};

#endif // DUALITYDATA_H
