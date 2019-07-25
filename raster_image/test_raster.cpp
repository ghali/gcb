/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "raster_image/array2.h"
#include "raster_image/image.h"
#include "raster_image/image_color_4.h"

#include <cassert>
#include <iostream>

void test_array_bool()
{
    // Simple test 
    Array2<bool> A(5,6);
    A(2,3) = true;
    A(4,5) = false;

    assert( A(2,3) == true );
    assert( A(4,5) == false );
    assert( A(3,4) == false );

    // Test operator=
    Array2<bool> B(2,2);
    B = A;

    assert( B(2,3) == true );
    assert( B(4,5) == false );
    assert( B(3,4) == false );

    // Test copy constructor
    Array2<bool> C(A);

    assert( C(2,3) == true );
    assert( C(4,5) == false );
    assert( C(3,4) == false );
}

void test_array_int()
{
    // Simple test 
    Array2<int> A(5,6);
    A(2,3) = 4;
    A(4,5) = 7;

    assert( A(2,3) == 4 );
    assert( A(4,5) == 7 );
    assert( A(3,4) == 0 );

    // Test operator=
    Array2<int> B(2,2);
    B = A;

    assert( B(2,3) == 4 );
    assert( B(4,5) == 7 );
    assert( B(3,4) == 0 );

    // Test copy constructor
    Array2<int> C(A);

    assert( C(2,3) == 4 );
    assert( C(4,5) == 7 );
    assert( C(3,4) == 0 );

    assert( A(2,3) == 4 );
    assert( A(4,5) == 7 );
    assert( A(3,4) == 0 );
}

void test_array_copy()
{
    Array2<int> A(3,2,5);
    assert( A(2,1) == 5 );
    Array2<int> B = A;
    B(1,1) = 9;
    assert( A(1,1) == 5 );

    Array2<int> C(A);
    assert( C.getNrows() == 3 );
    assert( C.getNcols() == 2 );
    C(2,1) = 7;
    assert( A(2,1) == 5 );
    assert( C(2,1) == 7 );
}

void test_image_bool()
{
    Image<bool> I(2,3);
    I(0,0) = false;
    I(1,0) = true;
    assert( !I(0,0) && I(1,0) );

    Image<bool> D;
    assert( D(0,0) == false && D(1,1) == false );
}

#if 0
void test_grayimage()
{
    Image<unsigned char> I(2,3);
    I(0,0) = 129;
    I(1,0) = 255;
    assert( I(0,0) == 129 && I(1,0) == 255 );

    Image<unsigned char> D;
    assert( D(0,0) == 0 && D(1,1) == 0 );
}
#endif

void test_grayimage()
{
    Image<unsigned char> I("testimage_3_2.pgm");
    assert( I.ncols() == 3 );
    assert( I.nrows() == 2 );
    assert( I(0,0) == 0 );
    assert( I(1,0) == 1 );
    assert( I(2,0) == 2 );
    assert( I(0,1) == 3 );
    assert( I(1,1) == 4 );
    assert( I(2,1) == 5 );
}

void test_colorimage()
{
    typedef Color_4<unsigned char> MyColor;
    Image<MyColor> I("testimage_4_4.ppm");
    assert( I(0,0) == MyColor(10,11,12,0) );
    assert( I(3,3) == MyColor(15,12,9,0) );
    assert( I(0,3) == MyColor(1,2,3,0) );

    Image<MyColor> I2(I);
    assert( I(0,0) == I2(0,0) );
    assert( I(3,3) == I2(3,3) );
}

int main()
{
    test_array_bool();
    test_array_int();
    test_array_copy();
    test_image_bool();
    test_grayimage();
    test_colorimage();
}
