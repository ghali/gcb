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
#include <iomanip>
using namespace std;

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

void print(int x)
{
    char  *ix = reinterpret_cast<char*>(&x);
    float *f  = reinterpret_cast<float*>(&x);

    int n = 4;
    while(n--)
        binary_print(n, ix[n]);
    cout << setprecision(99);
    cout << "   " << *f << endl;
}

int one_bit[] = {
    0x3F800000,
    0x3F800001,
    0x3F800002,
    0x3F800003,
    0x3F800004,
    0x3F800005,
    0x3F800006,
    0x3F800007,
    0x3F800008,
    0x3F800009,
    0x3F80000a,
    0x3F80000b,
    0x3F80000c,
    0x3F80000d,
    0x3F80000e,
    0x3F80000f
};

int main()
{
    int n=0;
    while(n<16)
        print(one_bit[n++]);
}

//     x = 1.00000011920928955078f; print(x); // 1 + 1/2^23 =(0.00000011920928955078)
// 0 01111111 00000000000000000000001 = 00111111 10000000 00000000 00000001 = 0x3F800001

