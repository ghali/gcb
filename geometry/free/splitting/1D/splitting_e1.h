// splitting_e1.h

#ifndef SPLITTING_E1_H
#define SPLITTING_E1_H

#include "geometry/E1/geometry_e1.h"
#include "geometry/E1/predicates_E1.h"

// We include the (generic between S2 and E2) splitting in 2D class
// to define a partial template specialization on the 2D case.
#include "geometry/free/splitting/2D/splitting_2.h"


template<typename NT>
struct Splitter<NT, Geometry_E1<NT> >
{
    static
    void
    split(const typename Geometry_E1<NT>::Convex_polytope & I,
          const typename Geometry_E1<NT>::Hyperplane & hyperplane,
          typename Geometry_E1<NT>::Convex_polytope & positive_part,
          typename Geometry_E1<NT>::Convex_polytope & negative_part)

    // template<>
    // void
    // split(const Geometry_E1<NT>::Convex_polytope & I,
    //       const Geometry_E1<NT>::Hyperplane  hyperplane,
    //       Geometry_E1<NT>::Convex_polytope & positive_part,
    //       Geometry_E1<NT>::Convex_polytope & negative_part)
    // split(const typename Geometry::Convex_polytope & I,
    //       const typename Geometry::Hyperplane  hyperplane,
    //       typename Geometry::Convex_polytope & positive_part,
    //       typename Geometry::Convex_polytope & negative_part)
    {
        //    typedef typename Geometry_E1::Point            Point;
        //    typedef typename Geometry_E1::Hyperplane       Hyperplane;
        //    typedef typename Geometry_E1::Convex_polytope  Convex_polytope;

        const Oriented_side source_of_segment = oriented_side( hyperplane, I.source() );
        const Oriented_side target_of_segment = oriented_side( hyperplane, I.target() );

        // Case (1)
        if( target_of_segment != ON_POSITIVE_SIDE )
        {
            positive_part.set_empty( true );
            negative_part = I;
            // Case (1s)
            if( target_of_segment == ON_ORIENTED_BOUNDARY )
                negative_part.set_target_closed( false );
            return;
        }

        // Case (2)
        if( source_of_segment != ON_NEGATIVE_SIDE )
        {
            negative_part.set_empty( true );
            positive_part = I;
            // case (2s)
            if( source_of_segment == ON_ORIENTED_BOUNDARY )
                positive_part.set_source_closed( false );
            return;
        }

        // Case (split)
        if( source_of_segment == ON_NEGATIVE_SIDE
            && target_of_segment == ON_POSITIVE_SIDE )
        {
            negative_part = Convex_polytope_E1d( I.source(), hyperplane, true, false ); // closed, open
            positive_part = Convex_polytope_E1d( hyperplane, I.target(), false, true ); // open, closed
            return;
        }

        assert(false);          // We should never be here.
    }
};

// We include this convenience function definition to make it possible
// for clients to call the split function above by using
//     split<Geometry_E1<double> >(..)
// instead of 
//     Splitter<double, Geometry_E1<double> >:: split(..)
#include "geometry/free/splitting/Splitter.h"

#endif // SPLITTING_E1_H
