// splitting_s1.h

#ifndef SPLITTING_S1_H
#define SPLITTING_S1_H

#include "geometry/S1/geometry_s1.h"
#include "geometry/E1/predicates_E1.h"

// typedef Geometry_S1<double>::Convex_polytope  Convex_polytope_S1d;
// typedef Geometry_S1<double>::Hyperplane  Hyperplane_S1d;


// We include the (generic between S2 and E2) splitting in 2D class
// to define a partial template specialization on the 2D case.
#include "geometry/free/splitting/2D/splitting_2.h"


template<typename NT>
struct Splitter<NT, Geometry_S1<NT> >
{
    static
    void
    split(const typename Geometry_S1<NT>::Convex_polytope & I,
          const typename Geometry_S1<NT>::Hyperplane & hyperplane,
          typename Geometry_S1<NT>::Convex_polytope & positive_part,
          typename Geometry_S1<NT>::Convex_polytope & negative_part)

    // template<>
    // void
    // split(const Convex_polytope_S1d & I,
    //       const Hyperplane_S1d  hyperplane,
    //       Convex_polytope_S1d & positive_part,
    //       Convex_polytope_S1d & negative_part)
    // split(const typename Geometry::Convex_polytope & I,
    //       const typename Geometry::Hyperplane  hyperplane,
    //       typename Geometry::Convex_polytope & positive_part,
    //       typename Geometry::Convex_polytope & negative_part)
    {
        if( I.is_full() ) {
            positive_part = Convex_polytope_S1d(hyperplane, hyperplane.antipode());
            negative_part = Convex_polytope_S1d(hyperplane.antipode(), hyperplane);
            return;
        }

        const Oriented_side source_of_segment = oriented_side( hyperplane, I.source() );
        const Oriented_side target_of_segment = oriented_side( hyperplane, I.target() );

        // Cases c
        if( source_of_segment != ON_NEGATIVE_SIDE &&
            target_of_segment != ON_NEGATIVE_SIDE )
        {
            negative_part.set_empty( true );
            positive_part = I;
            // Case c1
            if( source_of_segment == ON_ORIENTED_BOUNDARY )
                positive_part.set_source_closed( false );
            // Case c3
            if( target_of_segment == ON_ORIENTED_BOUNDARY )
                positive_part.set_target_closed( false );
            return;
        }

        // Cases a
        if( source_of_segment != ON_POSITIVE_SIDE &&
            target_of_segment != ON_POSITIVE_SIDE )
        {
            positive_part.set_empty( true );
            negative_part = I;
            // case a1
            if( source_of_segment == ON_ORIENTED_BOUNDARY )
                negative_part.set_source_closed( false );
            // case a3
            if( target_of_segment == ON_ORIENTED_BOUNDARY )
                negative_part.set_target_closed( false );
            return;
        }

        // Case b: split by point
        if( source_of_segment == ON_NEGATIVE_SIDE
            && target_of_segment == ON_POSITIVE_SIDE )
        {
            negative_part = Convex_polytope_S1d( I.source(), hyperplane, true, false ); // closed, open
            positive_part = Convex_polytope_S1d( hyperplane, I.target(), false, true ); // open, closed
        }
        // Case d: split by antipode of point
        if( source_of_segment == ON_POSITIVE_SIDE
            && target_of_segment == ON_NEGATIVE_SIDE )
        {
            positive_part = Convex_polytope_S1d( I.source(), hyperplane.antipode(),
                                                 true, false ); // closed, open
            negative_part = Convex_polytope_S1d( hyperplane.antipode(), I.target(),
                                                 false, true ); // open, closed
        }
    }
};

// We include this convenience function definition to make it possible
// for clients to call the split function above by using
//     split<Geometry_S1<double> >(..)
// instead of 
//     Splitter<double, Geometry_S1<double> >:: split(..)
#include "geometry/free/splitting/Splitter.h"

#endif // SPLITTING_S1_H
