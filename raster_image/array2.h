/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef ARRAY2_H
#define ARRAY2_H

// comment out the next line to avoid bounds checking
// #define NDEBUG
#include <cassert>
#include <utility>
#include <typeinfo>
#include <limits>

template<typename Color_unit> struct Color_4;
template<typename PixelType> class Image;

//----------------Array2_1_Begin----------------
template<class Type>
class Array2 {
    typedef Color_4<unsigned char> Color_4uc;
    friend class Image<Color_4uc>;
    int nrows, ncols;
    Type* table;
public:
    void* getTable() const
    { return (void*) table; }

    void init(const Type& t)
    {
        table = new Type[nrows * ncols];
        for(int i=0; i< nrows * ncols; ++i)
            table[i] = t;
    }

    Array2() : nrows(2), ncols(2)
    { init(Type()); }

    Array2(
           int nrowsin,
           int ncolsin,
           const Type& t = Type())
        : nrows(nrowsin), ncols(ncolsin)
    { init(t); }

    virtual ~Array2()
    {
        delete[] table;
    }

    Array2(const Array2& rhs)
        : nrows(rhs.nrows), ncols(rhs.ncols)
    {
        table = new Type[nrows * ncols];
        for(int i=0; i<nrows*ncols; ++i)
            table[i] = rhs.table[i];
    }
//----------------Array2_1_End----------------

    Type * begin() { return & table[0]; }
    Type * end()   { return & table[nrows * ncols]; }

//----------------Array2_2_Begin----------------
    Array2& operator=(const Array2& rhs)
    {
        if(this != &rhs) {
            delete[] table;
            nrows = rhs.nrows;
            ncols = rhs.ncols;
            table = new Type[nrows * ncols];
            for(int i=0; i<nrows*ncols; ++i)
                table[i] = rhs.table[i];
        }
        return *this;
    }

    int getNrows() const { return nrows; }
    int getNcols() const { return ncols; }
    bool withinBounds(int row, int col) const
    {
        return
            row>=0 && row<nrows &&
            col>=0 && col<ncols;
    }
    // matrix is stored in row-order
    const Type&
    operator()(int row, int col) const
    {
        assert( withinBounds(row,col) );
        return table[col + row * ncols];
    }
    Type&
    operator()(int row, int col)
    {
        assert( withinBounds(row,col) );
        return table[col + row * ncols];
    }
};
//----------------Array2_2_End----------------

// Return the minimum and maximum values in the array A.
template<typename T>
std::pair<T,T>
find_bounds(const Array2<T> & A)
{
    T min = + std::numeric_limits<T>::max();
    T max = - std::numeric_limits<T>::max();

    for(int row = 0; row < A.getNrows(); ++row)
        for(int col = 0; col < A.getNcols(); ++col) {
            if(A(row,col) < min) min = A(row,col);
            if(A(row,col) > max) max = A(row,col);
        }
    return std::make_pair(min, max);
}

#endif // ARRAY2_H
