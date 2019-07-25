/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "misc/epsilon_double.h"
#include "misc/color_3.h"
#include "misc/random_e3.h"
#include "orientation.h"
#include "misc/conversions.h"
#include <cassert>

typedef Direction_E3<double> Direction_E3d;

//----------------test_epsilon_double_Begin----------------
void test_epsilon_double()
{
    Epsilon_double a(2.0);
    Epsilon_double b(2.0 + EPSILON);

    assert( (a < b) != (a == b) );
    assert( (b > a) != (a == b) );
}
//----------------test_epsilon_double_End----------------

void test_Color_3()
{
    Color_3<float> color1(0.2, 0.4, 0.6);
    Color_3<float> color2 = color1;
    assert( color1 == color2 );
}

void test_conversions()
{
    int i = 789;
    std::string si = integer_to_zero_padded_string(i);
    assert( si == std::string("0789") );

    double d1 = 7.89;
    std::string sd1 = double_to_string(d1);
    assert( sd1 == std::string("7.9") );

    double d2 = 7.89;
    std::string sd2 = double_to_string_fn(d2);
    assert( sd2 == std::string("+7p9") );

    float d3 = 135.7913;
    std::string sd3 = double_to_string_fn(d3, 6, 2);
    assert( sd3 == std::string("+135p79") );
}

void test_random()
{
    int N = 20;
    while(N--) {
        Direction_E3d d;
        set_to_random(d);
        // weak test:
        assert(d.x() > -1.0 && d.x() < 1.0
               && d.y() > -1.0 && d.y() < 1.0
               && d.z() > -1.0 && d.z() < 1.0);
    }
}

int main()
{
    test_epsilon_double();
    test_Color_3();
    test_conversions();
    test_random();
    // ...
}
