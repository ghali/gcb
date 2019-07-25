/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef CLOCK_H
#define CLOCK_H

//----------------clock_Begin----------------
#include <sys/time.h>
class Clock
{
protected:
    timeval startTime;

public:
    Clock()
    {
        // gettimeofday assumes we're on POSIX.
        gettimeofday(&startTime, NULL);
    }

    float
    getSecondsSinceStart()
    {
        timeval currentTime;
        gettimeofday(&currentTime, NULL);
        float elapsedTime =
            currentTime.tv_sec - startTime.tv_sec +
            ((currentTime.tv_usec - startTime.tv_usec) / 1.0E6);
        return elapsedTime;
    }
};
//----------------clock_End----------------

#endif // CLOCK_H
