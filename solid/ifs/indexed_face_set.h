/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef INDEXED_FACE_SET_H
#define INDEXED_FACE_SET_H

#include <list>
#include <vector>

#include "geometry/E3/point_e3.h"
#include "geometry/E3/direction_e3.h"

template<typename NT>
struct Indexed_face_set
{
    struct Polygon
    {
        std::vector<int> vertex_indices;
        Direction_E3<NT> normal;

        Polygon(const std::list<int>& vi)
        {
            std::list<int>::const_iterator lci = vi.begin();
            while(lci != vi.end())
                vertex_indices.push_back(*lci++);
        }
    };

    Indexed_face_set() {}

    unsigned int push_back_vertex(const Point_E3<NT>& p)
    {
        vertices.push_back(p);
        return vertices.size();
    }

    unsigned int push_back_polygon(const Polygon& myPolygon)
    {
        polygons.push_back(myPolygon);
        return polygons.size();
    }

    unsigned int number_of_vertices() const { return vertices.size(); }
    unsigned int number_of_polygons() const { return polygons.size(); }

    Point_E3<NT> getPoint_E3(unsigned int i) const
    {
        return vertices[i];
    }

    std::vector<Point_E3<NT> > vertices;
    std::vector<Polygon> polygons;
};

#endif // INDEXED_FACE_SET_H
