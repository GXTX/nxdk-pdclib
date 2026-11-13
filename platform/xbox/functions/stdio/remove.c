/* unlink( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* The generic remove() calls unlink(). This is that function for nxdk.
*/

#include <stdio.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

int unlink( const char * pathname )
{
    return _PDCLIB_remove( pathname );
}

#endif
