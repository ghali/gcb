/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geometry/E2/point_e2.h"
#include "geometry/E2/segment_e2.h"

#include "geometry/E2/intersection_e2.h"

typedef float FloatType;
typedef Point_E2<FloatType>     Point_E2f;
typedef Segment_E2<FloatType> Segment_E2f;

void binary_print(int n, char c)
{
    cout << ((c & 0x80) ? 1 : 0);
    if(n>=2) cout << " ";
    cout << ((c & 0x40) ? 1 : 0)
         << ((c & 0x20) ? 1 : 0)
         << ((c & 0x10) ? 1 : 0)
         << ((c & 0x08) ? 1 : 0)
         << ((c & 0x04) ? 1 : 0)
         << ((c & 0x02) ? 1 : 0)
         << ((c & 0x01) ? 1 : 0);
}

void print(float x)
{
    char *ix = reinterpret_cast<char*>(&x);

    int n = 4;
    while(n--)
        binary_print(n, ix[n]);
    cout << endl;
}

//----------------main_Begin----------------
int main()
{
    const Point_E2f A(2,2), B(9,5);
    const Point_E2f C(8,2), D(6,5);
    const Point_E2f E(4,1), F(5,6);
    const Segment_E2f AB(A,B), CD(C,D), EF(E,F);

    const Point_E2f Gd = intersection_of_lines(AB, EF);
    const Point_E2f H = intersection_of_lines(AB, CD);

    const Segment_E2f AH(A,H);
    const Point_E2f Gi = intersection_of_lines(AH, EF);

    // assert( Gd == Gi ); // fails

    print( Gd.x() );
    print( Gi.x() );

    print( Gd.y() );
    print( Gi.y() );
}
//----------------main_End----------------
