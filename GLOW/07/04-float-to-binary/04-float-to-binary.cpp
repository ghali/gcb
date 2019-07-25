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

void print(float x)
{
    char *ix = reinterpret_cast<char*>(&x);

    int n = 4;
    while(n--)
        binary_print(n, ix[n]);
    cout << endl;
}

int main()
{
    float x;
    x =    4.0f ; print(x);
    x =    2.0f ; print(x);
    x =    1.0f ; print(x);
    x =    0.5f ; print(x);
    x =    0.25f; print(x);
    cout << endl;
    x =  - 0.25f; print(x);
    x =  - 0.5f ; print(x);
    x =  - 1.0f ; print(x);
    x =  - 2.0f ; print(x);
    x =  - 4.0f ; print(x);
    cout << endl;

    x = 1.0625000f; print(x); // 1 + 1/16 (0.0625000)
    x = 1.0312500f; print(x); // 1 + 1/32 (0.0312500)
    x = 1.0156250f; print(x); // 1 + 1/64 (0.0156250)
    x = 1.0078125f; print(x); // 1 + 1/128 (0.0078125)

    x = 1.00000047683715820312f; print(x); // 1 + 1/2^21 (0.00000047683715820312)
    x = 1.00000023841857910156f; print(x); // 1 + 1/2^22 (0.00000023841857910156)
    x = 1.00000011920928955078f; print(x); // 1 + 1/2^23 (0.00000011920928955078)
    x = 1.00000005960464477539f; print(x); // 1 + 1/2^24 (0.00000005960464477539)
}
