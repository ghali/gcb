// splitting_2.h

#ifndef SPLITTING_2_H
#define SPLITTING_2_H

// This generic routine does not know in which Geometry it will be used.
// Therefore it includes no intersection routines.
// The client should include the necessary one(s).

#include "misc/orientation.h"
#include "geometry/free/splitting/2D/polygon_vertices.h"

// Types:
// Point_E2<NT>                             ---> Point
// Segment_E2<NT> (in lieu of Line_E2<NT>)  ---> Hyperplane
// BSP_E2_convex_polygon<NT>                ---> Convex_polytope

template<typename NT, typename Geometry>
struct Splitter
{
    static
    void
    split( const typename Geometry::Convex_polytope & a_polygon,
           const typename Geometry::Hyperplane splitting_line, // Segment_E2<NT>
           typename Geometry::Convex_polytope & positive_side,
           typename Geometry::Convex_polytope & negative_side )

    // We use a Segment_2 object for the splitting line because
    // Line_E2 does not maintain a source/target pair (it may have
    // been defined directly using coefficients.)

    {
        //    typedef Geometry_E2d::Point                    Point;
        //    typedef Geometry_E2d::Hyperplane          Hyperplane;
        //    typedef Geometry_E2d::Convex_polytope  Convex_polytope;

        typedef typename Geometry::Point                    Point;
        typedef typename Geometry::Hyperplane          Hyperplane;
        typedef typename Geometry::Convex_polytope  Convex_polytope;


        const std::vector<Hyperplane > a_polygon_lines = a_polygon.get_lines();
        const std::vector<bool> a_polygon_line_is_closed = a_polygon.get_line_is_closed();

        {
            // quick exit
            if (a_polygon.is_empty()) {
                positive_side = Convex_polytope(); // empty set
                negative_side = Convex_polytope(); // empty set
                return;
            }
        }

        std::vector<Point> points = polygon_vertices<Geometry>(a_polygon);

        bool all_on_positive_side = true;
        bool all_on_oriented_boundary = true;
        bool all_on_negative_side = true;

        typedef typename std::vector<Point >::const_iterator EPit;
        for(EPit vi = points.begin();
            vi != points.end(); ++vi)
        {

            int s = oriented_side( splitting_line, *vi );

            switch(s) {
            case ON_POSITIVE_SIDE:
                all_on_negative_side = false;
                all_on_oriented_boundary = false;
                break;
            case ON_ORIENTED_BOUNDARY:
                break;
            case ON_NEGATIVE_SIDE:
                all_on_positive_side = false;
                all_on_oriented_boundary = false;
                break;
            }
        }

        if(all_on_positive_side || all_on_negative_side) {

            // To ensure there are no duplicates in any path from root to leaf,
            // we reset the bits corresponding to edges that coincide with the partitioning line.

            // If we wish to handle concave polygons as well, the next block should move
            // outside the enclosing if-statement. This makes it possible to handle a
            // concave polygon with one or more edges lying on the splitting line.

            std::vector<bool> edgeFlags = a_polygon.get_line_is_closed();

            {
                std::vector<bool>::iterator edgeFlagIt = edgeFlags.begin();

                typedef typename std::vector<Hyperplane >::const_iterator ESit;
                for(ESit lit = a_polygon_lines.begin();
                    lit != a_polygon_lines.end(); ++lit)
                {
                    // Does this carrying line coincide with the partitioning line?
                    // ----------------
                    // We answer line equality by checking for segment endpoint coincidence.

                    if( oriented_side(*lit, splitting_line.source()) == ON_ORIENTED_BOUNDARY &&
                        oriented_side(*lit, splitting_line.target()) == ON_ORIENTED_BOUNDARY )
                        *edgeFlagIt = false; // true;

                    ++edgeFlagIt;
                }
            }

            if(all_on_positive_side) // case (1)
            {
                positive_side = Convex_polytope( a_polygon_lines, edgeFlags );
                /*, a_polygon.attributes() */
                negative_side = Convex_polytope(); // the empty set

                return;
            }

            if(all_on_negative_side) // case (2)
            {
                positive_side = Convex_polytope(); // the empty set
                negative_side = Convex_polytope( a_polygon_lines, edgeFlags );
                /*,a_polygon.attributes() */

                return;
            }
        }

        if(all_on_oriented_boundary) // case (3)
        {
            positive_side = Convex_polytope(); // the empty set
            negative_side = Convex_polytope(); // the empty set

            return;
        }

        // assert(static_cast<int>(sides.size()) == a_polygon.polygon.size());

        std::vector<Hyperplane > positive_lines;  std::vector<bool> flags_of_positive_lines;
        std::vector<Hyperplane > negative_lines;  std::vector<bool> flags_of_negative_lines;

        typedef std::vector<bool>::const_iterator Bit;
        Bit edgeFlagI = a_polygon_line_is_closed.begin();

        typename std::vector<Point >::const_iterator pi = points.begin();
        typename std::vector<Point >::const_iterator pj = pi + 1;

        typedef typename std::vector<Hyperplane >::const_iterator ESit;
        for(ESit eit = a_polygon_lines.begin();
            eit != a_polygon_lines.end();
            ++eit)
        {
            int vertexI = oriented_side(splitting_line, *pi);
            int vertexJ = oriented_side(splitting_line, *pj);

            //----------------------------------------------------------------
            // Segment is on one side of the plane only (possibly touching).
            // The following correctly handles the case when both points are ON_ORIENTED_BOUNDARY
            //----------------------------------------------------------------
            if( vertexI != ON_NEGATIVE_SIDE &&
                vertexJ != ON_NEGATIVE_SIDE )
            {
                // case (4)
                positive_lines.push_back( *eit );
                flags_of_positive_lines.push_back( *edgeFlagI );

                if( vertexJ == ON_ORIENTED_BOUNDARY ) {
                    positive_lines.push_back( splitting_line );
                    flags_of_positive_lines.push_back( true );
                }
            }
            else if( vertexI != ON_POSITIVE_SIDE &&
                     vertexJ != ON_POSITIVE_SIDE )
            {
                // case (6)
                negative_lines.push_back( *eit );
                flags_of_negative_lines.push_back( *edgeFlagI );

                if( vertexJ == ON_ORIENTED_BOUNDARY ) {
                    negative_lines.push_back( Hyperplane (splitting_line.target(),
                                                          splitting_line.source()) );
                    flags_of_negative_lines.push_back( true );
                }
            }
            else
            {
                //----------------------------------------------------------------
                // Segment straddles the plane; split
                //----------------------------------------------------------------

                // // The following assertion must hold if the input polygons are convex
                // assert((*vertexI == ON_POSITIVE_SIDE && *vertexJ == ON_NEGATIVE_SIDE) ||
                //        (*vertexI == ON_NEGATIVE_SIDE && *vertexJ == ON_POSITIVE_SIDE));

                Point  ipoint = intersection_of_lines( *eit, splitting_line );

                // splitting line appears on both +ve and -ve sides

                // but we treat adjacency differently depending whether we are going

                // from +ve to -ve
                if(vertexI == ON_POSITIVE_SIDE && vertexJ == ON_NEGATIVE_SIDE) // case (8)
                {
                    positive_lines.push_back( *eit );
                    flags_of_positive_lines.push_back( *edgeFlagI );

                    // reverse orientation (polygons are oriented *clockwise*):
                    positive_lines.push_back( Hyperplane (splitting_line.target(),
                                                          splitting_line.source()) );
                    // edges resulting from splits have partitioning_line_encountered==true
                    flags_of_positive_lines.push_back( false ); // true );

                    negative_lines.push_back( *eit );
                    flags_of_negative_lines.push_back( *edgeFlagI );
                }

                // or from -ve to +ve
                if(vertexI == ON_NEGATIVE_SIDE && vertexJ == ON_POSITIVE_SIDE) // case (9)
                {
                    negative_lines.push_back( *eit );
                    flags_of_negative_lines.push_back( *edgeFlagI );

                    negative_lines.push_back( splitting_line );
                    flags_of_negative_lines.push_back( false ); // true );

                    positive_lines.push_back( *eit );
                    flags_of_positive_lines.push_back( *edgeFlagI );
                }
            }

            ++edgeFlagI;
            ++pi;

            if(pi == points.end() - 1)
                pj = points.begin();
            else
                pj = pi + 1;
        }

        positive_side = Convex_polytope( positive_lines, flags_of_positive_lines /*, a_polygon.attributes()*/ );
        negative_side = Convex_polytope( negative_lines, flags_of_negative_lines /*, a_polygon.attributes()*/ );
    }
};

// We include this convenience function definition to make it possible
// for clients to call the split function above by using
//     split<Geometry_E2<double> >(..)
// instead of 
//     Splitter<double, Geometry_E2<double> >:: split(..)
#include "geometry/free/splitting/Splitter.h"

#endif // SPLITTING_2_H
