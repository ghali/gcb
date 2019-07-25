/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef DETERMINANT_H
#define DETERMINANT_H

template<typename T>
T
determinant(const T& a, const T& b,
            const T& c, const T& d)
{
    return a * d - b * c;
}

template<typename T>
T
determinant(const T& a, const T& b, const T& c,
            const T& d, const T& e, const T& f,
            const T& g, const T& h, const T& i)
{
    return a * determinant(e,f,h,i)
        -  b * determinant(d,f,g,i)
        +  c * determinant(d,e,g,h);
}

template<typename T>
T
determinant(const T& a, const T& b, const T& c, const T& d,
            const T& e, const T& f, const T& g, const T& h,
            const T& i, const T& j, const T& k, const T& l,
            const T& m, const T& n, const T& o, const T& p)
{
    return a * determinant(f,g,h, j,k,l, n,o,p)
        -  b * determinant(e,g,h, i,k,l, m,o,p)
        +  c * determinant(e,f,h, i,j,l, m,n,p)
        -  d * determinant(e,f,g, i,j,k, m,n,o);
}

#endif // DETERMINANT_H
