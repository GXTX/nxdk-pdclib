/* _PDCLIB_realpath( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an implementation of _PDCLIB_realpath() for use with nxdk
 */

#include <stdio.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#include <stdlib.h>
#include <string.h>

char * _PDCLIB_realpath( const char * path )
{
    /* The path is not canonicalized, it is stored as given. */
    char * rc = malloc( strlen( path ) + 1 );

    if ( rc != NULL )
    {
        strcpy( rc, path );
    }

    return rc;
}

#endif
