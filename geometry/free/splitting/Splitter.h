#ifndef SPLITTER_H
#define SPLITTER_H

template<typename Geometry>
void
split(const typename Geometry::Convex_polytope & polytope,
      const typename Geometry::Hyperplane & hyperplane,
      typename Geometry::Convex_polytope & positive_part,
      typename Geometry::Convex_polytope & negative_part)
{
    Splitter<typename Geometry::NumberType, Geometry>::split(polytope,
                                                             hyperplane,
                                                             positive_part,        
                                                             negative_part);
}

#endif // SPLITTER_H
