/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "raster_image/image.h"

typedef Image<Color_4<float> > ColorImage; // floats range from 0 to 1
typedef Image<char> GrayscaleImage;

std::ostream &
operator<< (std::ostream & os, const Image<bool> & I)
{
    for(int row=I.nrows()-1; row>=0; --row) {
        for(int col=0; col<I.ncols(); ++col)
            os << (I(row,col) ? 'x' : '.');
        os << std::endl;
    }
    return os;
}
