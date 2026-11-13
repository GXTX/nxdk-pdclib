/* _PDCLIB_changemode( struct _PDCLIB_file_t *, unsigned int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an implementation of _PDCLIB_changemode() for use with nxdk
 */

#include <stdio.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

int _PDCLIB_changemode( struct _PDCLIB_file_t * stream, unsigned int mode )
{
    /* Not supported, freopen() closes and reopens the stream instead. */
    return 0;
}

#endif
