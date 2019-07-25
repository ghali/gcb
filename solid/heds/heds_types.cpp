/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "heds_types.h"

//----------------------------------------------------------------
std::ostream &
operator<< (std::ostream & os, const Vertex & J)
{
    return os << "  coords: " << J.coords;
}

std::ostream &
operator<< (std::ostream & os, const Arc)
{
    return os;                  // do nothing
}

std::ostream&
operator<< (std::ostream & os, const Polygon & P)
{
    return os << "  normal: " << P.normal
              << "  color: " << P.color;
}

