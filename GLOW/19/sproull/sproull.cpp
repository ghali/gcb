/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <iostream>
using std::cout;
using std::endl;
#include <cmath>
#include "raster_image/image.h"
#include "misc/clock.h"

//----------------Point_E2i_Begin----------------
struct Point_E2i {
    int x, y;
    Point_E2i(int x, int y) : x(x), y(y) {}
};
//----------------Point_E2i_End----------------

//----------------B1_Begin----------------
void B1(Image<bool>& I, const Point_E2i& P)
{
    float yt;
    int xi = 0, yi;

    float Py_by_Px = float(P.y) / float(P.x);
    while(xi <= P.x) {
        yt = Py_by_Px * float(xi);
        yi = int(std::floor(yt + 0.5)); // floor returns float
        I(xi, yi) = true;
        ++xi;
    }
}
//----------------B1_End----------------

//----------------B2_Begin----------------
void B2(Image<bool>& I, const Point_E2i& P)
{
    float yt = 0;
    int xi = 0, yi;

    float Py_by_Px = float(P.y) / float(P.x);
    while(xi <= P.x) {
        yi = int(std::floor(yt + 0.5));
        I(xi, yi) = true;
        yt += Py_by_Px;
        ++xi;
    }
}
//----------------B2_End----------------

//----------------B3_Begin----------------
void B3(Image<bool>& I, const Point_E2i& P)
{
    float ys = 0.5;
    int xi = 0, yi;

    float Py_by_Px = float(P.y) / float(P.x);
    while(xi <= P.x) {
        yi = int(std::floor(ys));
        I(xi, yi) = true;
        ys += Py_by_Px;
        ++xi;
    }
}
//----------------B3_End----------------

//----------------B4_Begin----------------
void B4(Image<bool>& I, const Point_E2i& P)
{
    float ysf = 0.5;
    int xi = 0, ysi = 0;

    float Py_by_Px = float(P.y) / float(P.x);
    while(xi <= P.x) {
        I(xi, ysi) = true;
        if(ysf + Py_by_Px >= 1) {
            ++ysi;
            ysf += Py_by_Px - 1;
        }
        else
            ysf += Py_by_Px;
        ++xi;
    }
}
//----------------B4_End----------------

// scale by 2 * P.x
//----------------B5_Begin----------------
void B5(Image<bool>& I, const Point_E2i& P)
{
    float r = float(P.x);
    int xi = 0, ysi = 0;

    float v1 = 2.0 * float(P.x) - 2 * float(P.y);
    float v2 = 2.0 * float(P.y);
    while(xi <= P.x) {
        I(xi, ysi) = true;
        if(r + v2 >= 2 * P.x) {
            ++ysi;
            r -= v1;
        }
        else
            r += v2;
        ++xi;
    }
}
//----------------B5_End----------------

// use integers instead
//----------------B6_Begin----------------
void B6(Image<bool>& I, const Point_E2i& P)
{
    int r = P.x;
    int xi = 0, ysi = 0;

    int v1 = 2 * P.x - 2 * P.y;
    int v2 = 2 * P.y;
    while(xi <= P.x) {
        I(xi, ysi) = true;
        if(r + v2 >= 2 * P.x) {
            ++ysi;
            r -= v1;
        }
        else
            r += v2;
        ++xi;
    }
}
//----------------B6_End----------------

// compare with zero ==> subtract 2 * P.x
//----------------B7_Begin----------------
void B7(Image<bool>& I, const Point_E2i& P)
{
    int r = - P.x;
    int xi = 0, ysi = 0;

    int v1 = 2 * P.x - 2 * P.y;
    int v2 = 2 * P.y;
    while(xi <= P.x) {
        I(xi, ysi) = true;
        if(r + v2 >= 0) {
            ++ysi;
            r -= v1;
        }
        else
            r += v2;
        ++xi;
    }
}
//----------------B7_End----------------

// avoid adding v2 inside the loop
//----------------B8_Begin----------------
void B8(Image<bool>& I, const Point_E2i& P)
{
    int r = 2 * P.y - P.x;
    int xi = 0, ysi = 0;

    int v1 = 2 * P.x - 2 * P.y;
    int v2 = 2 * P.y;
    while(xi <= P.x) {
        I(xi, ysi) = true;
        if(r >= 0) {
            ++ysi;
            r -= v1;
        }
        else
            r += v2;
        ++xi;
    }
}
//----------------B8_End----------------

void run_once()
{
    Point_E2i P(11,7);

    Image<bool> I1(12,12); B1(I1, P); cout << I1 << endl << endl;
    Image<bool> I2(12,12); B2(I2, P); cout << I2 << endl << endl;
    Image<bool> I3(12,12); B3(I3, P); cout << I3 << endl << endl;
    Image<bool> I4(12,12); B4(I4, P); cout << I4 << endl << endl;
    Image<bool> I5(12,12); B5(I5, P); cout << I5 << endl << endl;
    Image<bool> I6(12,12); B6(I6, P); cout << I6 << endl << endl;
    Image<bool> I7(12,12); B7(I7, P); cout << I7 << endl << endl;
    Image<bool> I8(12,12); B8(I8, P); cout << I8 << endl << endl;
}

void run_many()
{
    Point_E2i P(11,7);

    const int N = 10000000;
    Image<bool> I1(12,12); int n1=N; Clock c1; while(n1--) B1(I1, P); cout << c1.getSecondsSinceStart() << " & ";
    Image<bool> I2(12,12); int n2=N; Clock c2; while(n2--) B2(I2, P); cout << c2.getSecondsSinceStart() << " & ";
    Image<bool> I3(12,12); int n3=N; Clock c3; while(n3--) B3(I3, P); cout << c3.getSecondsSinceStart() << " & ";
    Image<bool> I4(12,12); int n4=N; Clock c4; while(n4--) B4(I4, P); cout << c4.getSecondsSinceStart() << " & ";
    Image<bool> I5(12,12); int n5=N; Clock c5; while(n5--) B5(I5, P); cout << c5.getSecondsSinceStart() << " & ";
    Image<bool> I6(12,12); int n6=N; Clock c6; while(n6--) B6(I6, P); cout << c6.getSecondsSinceStart() << " & ";
    Image<bool> I7(12,12); int n7=N; Clock c7; while(n7--) B7(I7, P); cout << c7.getSecondsSinceStart() << " & ";
    Image<bool> I8(12,12); int n8=N; Clock c8; while(n8--) B8(I8, P); cout << c8.getSecondsSinceStart() << endl;
}

int main()
{
    run_once();
    run_many();
}
