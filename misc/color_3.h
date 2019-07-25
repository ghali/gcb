/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef COLOR_3_H
#define COLOR_3_H

#include <iostream>

template<typename Color_unit>
class Color_3;

template<typename Color_unit>
std::ostream &
operator<< (std::ostream & os, const Color_3<Color_unit> & c);

template<typename Color_unit>
class Color_3
{
    Color_unit _r, _g, _b;

public:
    Color_3(const Color_unit rr = Color_unit(),
            const Color_unit gg = Color_unit(),
            const Color_unit bb = Color_unit())
        : _r(rr), _g(gg), _b(bb)
    {}

    Color_unit r() const { return _r; }
    Color_unit g() const { return _g; }
    Color_unit b() const { return _b; }

    void set_r(const Color_unit& u) { _r = u; }
    void set_g(const Color_unit& u) { _g = u; }
    void set_b(const Color_unit& u) { _b = u; }

    Color_3<Color_unit>&
    operator=(const Color_3<Color_unit>& c)
    {
        if(this != &c) {
            _r = c._r;
            _g = c._g;
            _b = c._b;
        }

        return *this;
    }

    Color_3<Color_unit>
    operator + (const Color_3<Color_unit> & c) const
    {
        typedef Color_3<Color_unit> mycolor;
        return mycolor(_r + c.r(), _g + c.g(), _b + c.b());
    }

    Color_3<Color_unit>
    operator * (const Color_unit & t) const
    {
        typedef Color_3<Color_unit> mycolor;
        return mycolor(_r * t, _g * t, _b * t);
    }

    bool
    operator==(const Color_3<Color_unit>& c) const
    {
        return (this == &c) || (_r == c._r && _g == c._g && _b == c._b);
    }

    friend std::ostream& operator<< <>(std::ostream& os, const Color_3<Color_unit>& c);
};

template<typename Color_unit>
std::ostream & operator<< (std::ostream & os, const Color_3<Color_unit> & c)
{
    return os << int(c._r) << " " << int(c._g) << " " << int(c._b);
}

#endif // COLOR_3_H
