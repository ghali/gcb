/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef IMAGE_GRAYSCALE_H
#define IMAGE_GRAYSCALE_H

#include <iostream>
#include <fstream>

#include "raster_image/array2.h"

template<typename Grayscale_type>
std::ostream &
operator<< (std::ostream & os,
            const Image<Grayscale_type> & p);

//----------------------------------------------------------------
template<typename Grayscale_type>
class Image
{
    int _ncols, _nrows;
    Array2<Grayscale_type> H;
    unsigned int _maxval;

public:
    int ncols() const { return _ncols; }
    int nrows() const { return _nrows; }
    const Grayscale_type & operator()(int col, int row) const
    {
        return H(col,row);
    }
    Grayscale_type & operator()(int col, int row)
    {
        return H(col,row);
    }

    unsigned int get_maxval() const { return _maxval; }

    const void* getData() const { return H.table; }

    Image() : _ncols(2), _nrows(2),
              H( _ncols,_nrows,Grayscale_type() ),
              _maxval(0)
    {}

    Image(int ncols, int nrows, int maxval = 255)
        : _ncols(ncols), _nrows(nrows), H(ncols, nrows), _maxval(maxval)
    {}

    Image<Grayscale_type>(const char* pgmfilename)
    {
        std::ifstream IS(pgmfilename);
        if(!IS) {
            std::cerr << "Cannot open pgm file: " << pgmfilename << " for reading\n";
            exit(1);
        }
        char pgmTypechars[500];
        IS >> pgmTypechars;
        std::string pgmType(pgmTypechars);

        // P2 is ascii. P5 is binary
        if( !( pgmType == "P2" || pgmType == "P5" ) ) {
            std::cerr << "Signature of " << pgmfilename << " indicates it is not a pgm file\n";
            exit(1);
        }
        bool pgmTypeP2 = pgmType == "P2";

        // handle up to 2 lines of comments
        char tokenchars[500];
        IS >> tokenchars;
        std::string token(tokenchars);
        if(token == "#") {
            IS.ignore(1000, '\n');
            IS >> tokenchars;
            token = std::string(tokenchars);
            if(token =="#") {
                IS.ignore(1000, '\n');
                IS >> tokenchars;
                token = std::string(tokenchars);
            }
        }
        _ncols = atoi(token.c_str());
        IS >> _nrows;
    
        // check size
        if(_ncols<2 || _nrows<2) {
            std::cerr << "Image " << pgmfilename << " is too small\n";
            exit(1);
        }

        // Create array
        H = Array2<Grayscale_type>(_ncols, _nrows);

        // read maximum height
        IS >> _maxval;
        char dummy;
        IS.get(dummy);          // read the end of line
        if(_maxval<1 || _maxval>65535) {
            std::cerr << _maxval << "is illegal as Maxval for file " << pgmfilename << std::endl;
            exit(1);
        }

        // Read the file:
        //   coordinates:
        //     (0,1) (1,1) (2,1)
        //     (0,0) (1,0) (2,0)
        //   reading order:
        //       0     1     2
        //       3     4     5
        //
        //    ^j
        //    |
        //    |    . (*H)(i,j)
        //    |
        //    |          i
        //  --+---------->
        //    |
        for(int row=_nrows-1; row>=0; row--)
            for(int col=0; col<_ncols; col++) {
                if(pgmTypeP2) { // P2: ascii file
                    int v;
                    IS >> v;  // read into an integer
                    H(col,row) = (Grayscale_type)(v);  // cast
                    // H(col,row).set_a( (Grayscale_type)(0) );  // pgm files don't store an alpha channel
                }
                else {               // pgmType is P5: binary file
                    if(_maxval<256) { // fits in one byte
                        unsigned char v;
                        v = IS.get();

                        H(col,row) = (Grayscale_type)(v);
                        // H(col,row).set_a( (Grayscale_type)(0) );
                    }
                    else {      // fits in two bytes
                        char v1, v2;
                        IS.get(v1);
                        IS.get(v2);
                        H(col,row) = (Grayscale_type)(int(v1) >> 8 + int(v2)); // The most significant byte is first
                        H(col,row) = (Grayscale_type)(0);
                    }                    
                }                    
                if(H(col,row) > _maxval) {  // || H(col,row).a() > _maxval) {
                    std::cerr << "Value read is larger than the max value of " << _maxval << std::endl;
                    exit(1);
                }
            }
    }

    void write(const char* pgmfilename, const bool ASCII_P2 = false)
    {
        std::ofstream OS(pgmfilename);
        if(!OS) {
            std::cerr << "Cannot open pgm file " << pgmfilename << " for output\n";
            exit(1);
        }
        OS << (ASCII_P2 ? "P2" : "P5") << std::endl
           << "# Created by Image<Grayscale_Type>" << std::endl
           << _nrows << " " << _ncols << std::endl
           << _maxval << std::endl;

        for(int col=_ncols-1; col>=0; col--) // write in English-reading order
            for(int row=0; row<_nrows; row++)
                if(ASCII_P2)
                    OS << H(row,col);
                else if(_maxval<256)
                    OS << char(H(row,col));
                else // "The most significant byte is first."
                    OS << char(int(H(row,col)) >> 8) << char(int(H(row,col)) && 0xFF);
        // In P5, there can be no CR/LF at the end of each raster line.
        OS.close();
    }

    friend std::ostream &
    operator<< <>(std::ostream & os, const Image<bool> & I);
};

template<typename Grayscale_type>
std::ostream &
operator<< (std::ostream & os,
            const Image<Grayscale_type> & I)
{
    for(int row=I.nrows()-1; row>=0; --row) {
        for(int col=0; col<I.ncols(); ++col)
            os << I(col,row);
        os << std::endl;
    }
    return os;
}

#endif // IMAGE_GRAYSCALE_H
