/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

//----------------Bbox_E2d_Begin----------------
class Bbox_E2d
{
    Point_E2d _LL; // lower left corner
    Point_E2d _UR; // upper right corner
public:
    Bbox_E2d() : _LL(), _UR() {}

    Bbox_E2d(const Point_E2d& p) : _LL(p), _UR(p) {}

    Bbox_E2d(const Point_E2d& pLL, const Point_E2d& pUR)
        : _LL(pLL), _UR(pUR) {}

    T width()  const { return _UR.x() - _LL.x(); }
    T height() const { return _UR.y() - _LL.y(); }

    Point_E2d LL() const { return _LL; }
    Point_E2d UR() const { return _UR; }

    Point_E2d center() const { return Point_E2d(
                                                (_LL.x() + _UR.x())/2.0,
                                                (_LL.y() + _UR.y())/2.0); }
};
//----------------Bbox_E2d_End----------------
