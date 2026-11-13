/* time( time_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <time.h>

#ifndef REGTEST

#include <xboxkrnl/xboxkrnl.h>
#include "pdclib/_PDCLIB_xbox_time.h"

time_t time( time_t * timer )
{
    time_t result;
    LARGE_INTEGER cur_time;

    KeQuerySystemTime(&cur_time);

    result = (time_t)((cur_time.QuadPart / 10000000) - _PDCLIB_XBOX_EPOCH_OFFSET);

    if (timer != NULL)
    {
        *timer = result;
    }

    return result;
}

#endif
