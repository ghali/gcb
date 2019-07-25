/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef IFS_READER_H
#define IFS_READER_H

#include <fstream>
#include <string>
#include <list>

template<typename NT>
struct IFS_reader
{
    // return false if file is read successfully
    static bool read(Indexed_face_set<NT>& ifs,
                     const std::string& filename,
                     bool invert = false // by default polygons are not reversed
                     )
    {
        std::ifstream IS(filename.c_str());
        if(!IS) {
            std::cerr << "Cannot open " << filename << std::endl;
            return true;
        }

        std::string rtoken;
        IS >> rtoken;
        if(rtoken != std::string("OFF")) {
            std::cerr << "OFF file does not start with keyword 'OFF'\n";
            return true;
        }
        int numV, numP, unusedEdgeNumber;
        IS >> numV >> numP >> unusedEdgeNumber;

        for(int i=0; i<numV; i++) {
            double x, y, z;
            IS >> x >> y >> z;
            ifs.push_back_vertex(Point_E3<NT>(static_cast<NT>(x),
                                              static_cast<NT>(y),
                                              static_cast<NT>(z)));
        }

        for(int j=0; j<numP; j++)
        {
            int numSides;
            IS >> numSides;
            if(IS.eof()) {
                std::cerr << "Error: too few polygons in OFF file\n";
                return true;
            }

            int vindex;
            std::list<int> L;

            for(int k=0; k<numSides; k++)
                if(invert)
                { IS >> vindex; L.push_front(vindex); }
                else
                { IS >> vindex; L.push_back(vindex); }

            typename Indexed_face_set<NT>::Polygon myPolygon(L);

            ifs.push_back_polygon(myPolygon);

            L.clear();
        }
        return false;
    }
};

#endif // IFS_READER_H
