/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "solid/ifs/indexed_face_set.h"
#include "solid/ifs/ifs_reader.h"

#include <cassert>

typedef double MyDouble;
typedef Indexed_face_set<MyDouble> Indexed_face_set_d;
typedef IFS_reader<MyDouble> IFS_reader_d;

int main()
{
    Indexed_face_set_d ifs;

    assert( !IFS_reader_d::read(ifs, "../../objects/cube.off") );

    assert( ifs.number_of_vertices() == 8 );
    assert( ifs.number_of_polygons() == 6 );
}
