/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <sys/time.h>
#include <string>
#include <sstream>

//----------------FPScounter_1_Begin----------------
class FPScounter
{
protected:
    timeval start_time;
    std::string str;

public:
    FPScounter() : str("")
    {
        gettimeofday(&start_time, NULL);
    }

    std::string
    getFrameRate()
    {
        static int number_of_frames = 0;
        static timeval current_time;
        float elapsedTime; 

        gettimeofday(&current_time, NULL);
//----------------FPScounter_1_End----------------

//----------------FPScounter_2_Begin----------------
        elapsedTime =
            current_time.tv_sec -
            start_time.tv_sec +
            ( (current_time.tv_usec -
               start_time.tv_usec) / 1.0E6 );

        number_of_frames++;
    
        if(elapsedTime >= 1.0) {
            start_time = current_time;

            std::ostringstream os;
            os << number_of_frames << " fps";
            str = os.str();

            number_of_frames = 0;
        }
        return str;
    }
};
//----------------FPScounter_2_End----------------

#endif // FPSCOUNTER_H
