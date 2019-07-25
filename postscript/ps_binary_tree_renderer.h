/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PS_BINARY_TREE_RENDERER_H
#define PS_BINARY_TREE_RENDERER_H

#include <string>
#include <map>

#include "geometry/E2/point_e2.h"
#include "geometry/E2/vector_e2.h"
#include "geometry/E2/segment_e2.h"
#include "geometry/E2/bbox_e2.h"

#include "postscript/postscript.h"

template<typename Node_type, typename T>
struct
Simple_Node_Renderer
{
    void operator() (Postscript<T>& PS,
                     const Node_type& /*node*/,
                     const Point_E2<T> coords,
                     T diameter)
    {    
        // We do nothing with the node in the simple renderer.
        PS.set_gray_fill(0.8);
        PS.draw_disk( coords, diameter );
        PS.set_gray_stroke(0.0);
        PS.draw_circle( coords, diameter );
    }
};

template<typename Node_type,
         typename T,
         typename Node_Renderer = Simple_Node_Renderer<Node_type, T> >
class
PS_Binary_Tree_Renderer
{
    typedef Point_E2<T> Point_E2ps;
    typedef std::map<const Node_type*, Point_E2ps > My_map;

    std::string filename;
    Node_type * mytree;
    My_map M;
    T diameter;
    Bbox_E2<T> bbox;
    Node_Renderer my_Node_Renderer;

public:
    PS_Binary_Tree_Renderer(
                            const std::string & filename,
                            Node_type * mytree,
                            My_map & M,
                            T diameter)
        : filename(filename),
          mytree(mytree),
          M(M),
          diameter(diameter),
          my_Node_Renderer(Node_Renderer())
    {
        bbox = get_Bbox( M );
        bbox += bbox.LL() + Vector_E2<T>(-1,-1);
        bbox += bbox.UR() + Vector_E2<T>(1,1);
    }

    void
    draw()
    {
        Postscript<T> PS( filename, bbox );
        PS.set_gray_stroke(0.8);
        PS.set_line_width(0.1);
        PS.draw_grid();

        PS.set_gray_stroke(0.0);
        PS.set_line_width(1);
        draw_tree_edges( PS, mytree, M );
        draw_tree_nodes( PS, mytree, M );
    }

private:
    Bbox_E2<T>
    get_Bbox( const My_map & M )
    {
        Bbox_E2<T> bbox;
        typename My_map::const_iterator mi = M.begin();

        while( mi != M.end() )
            bbox += mi++->second;
        return bbox;
    }

    void
    draw_tree_edges(
                    Postscript<T> & PS,
                    const Node_type * mynode,
                    My_map & M )
    {
        if(mynode->get_negative_child()) {
            Node_type * N = mynode->get_negative_child();
            PS.draw( Segment_E2<T>( M[mynode], M[N] ) );
            draw_tree_edges( PS, N, M );
        }
        if(mynode->get_positive_child()) {
            Node_type * P = mynode->get_positive_child();
            PS.draw( Segment_E2<T>( M[mynode], M[P] ) );
            draw_tree_edges( PS, P, M );
        }
    }

    void
    draw_tree_nodes(
                    Postscript<T> & PS,
                    const Node_type * mynode,
                    My_map & M )
    {
        my_Node_Renderer(PS, *mynode, M[mynode], diameter);

        if(mynode->get_negative_child())
            draw_tree_nodes( PS, mynode->get_negative_child(), M );
        if(mynode->get_positive_child())
            draw_tree_nodes( PS, mynode->get_positive_child(), M );
    }
};

#endif // PS_BINARY_TREE_RENDERER_H
