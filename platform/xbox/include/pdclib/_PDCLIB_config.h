/* Internal PDCLib configuration <_PDCLIB_config.h>
   ("Example" platform target, for PDCLib development)

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _PDCLIB_CONFIG_H
#define _PDCLIB_CONFIG_H _PDCLIB_CONFIG_H

/* -------------------------------------------------------------------------- */
/* Misc                                                                       */
/* -------------------------------------------------------------------------- */

/* Helper macros also documented in _PDCLIB_internal.h, but defined here as   */
/* they are needed in this file already.                                      */
/* _PDCLIB_cc( x, y ) concatenates two preprocessor tokens without extending. */
/* _PDCLIB_concat( x, y ) concatenates two preprocessor tokens with extending */
#define _PDCLIB_cc( x, y )     x ## y
#define _PDCLIB_concat( x, y ) _PDCLIB_cc( x, y )

/* exit() can signal success to the host environment by the value of zero or  */
/* the constant EXIT_SUCCESS. Failure is signaled by EXIT_FAILURE. Note that  */
/* any other return value is "implementation-defined", i.e. your environment  */
/* is not required to handle it gracefully. Set your definitions here.        */
#define _PDCLIB_SUCCESS 0
#define _PDCLIB_FAILURE -1

/* qsort() in <stdlib.h> requires a function that swaps two memory areas.     */
/* Below is a naive implementation that can be improved significantly for     */
/* specific platforms, e.g. by swapping int instead of char.                  */
#define _PDCLIB_memswp( i, j, size ) char tmp; do { tmp = *i; *i++ = *j; *j++ = tmp; } while ( --size );

/* Define this to some compiler directive that can be written after the       */
/* parameter list of a function declaration to indicate the function does     */
/* never return. If your compiler does not support such a directive, define   */
/* to nothing. (This is to avoid warnings with the exit functions under GCC   */
/* when compiling with C99/C++ settings, where C11 _Noreturn is unavailable.) */
#define _PDCLIB_NORETURN __attribute__(( noreturn ))

/* -------------------------------------------------------------------------- */
/* Symbol Visibility                                                          */
/* -------------------------------------------------------------------------- */
#define _PDCLIB_PUBLIC
#define _PDCLIB_LOCAL

/* -------------------------------------------------------------------------- */
/* Integers                                                                   */
/* -------------------------------------------------------------------------- */
/* The defines below make use of predefines offered by GCC and clang. If you  */
/* adapt PDCLib for a different compiler family, you will have to use what    */
/* that compiler provides, or enter actual values.                            */
/* -------------------------------------------------------------------------- */

/* At the point of writing, PDCLib makes no provisions for, nor has it been   */
/* tested, on a platform that uses signed magnitude or one's complement to    */
/* encode its integers. Most importantly, there are no guarantees that the    */
/* negative zero of those encodings is in any form handled gracefully.        */
#define _PDCLIB_TWOS_COMPLEMENT 1

/* 1234 for little endian, 4321 for big endian; other types not supported.    */
#define _PDCLIB_ENDIANESS __BYTE_ORDER__

/* Calculation of a minimum value from a given maximum for two's complement.  */
/* (For convenience only, used only in this header file below.)               */
#define _PDCLIB_MIN_CALC( max ) ( ( - max ) - 1 )

/* Now, introducting the various predefines to the _PDCLIB_* namespace, so    */
/* the rest of PDCLib can work with that and adapting to a different compiler */
/* will require changes only in this one file.                                */

/* Bits in a char */
#define _PDCLIB_CHAR_BIT __CHAR_BIT__

/* Maximum and minimum values of signed / unsigned char                       */
#define _PDCLIB_SCHAR_MAX __SCHAR_MAX__
#define _PDCLIB_SCHAR_MIN _PDCLIB_MIN_CALC( __SCHAR_MAX__ )
#define _PDCLIB_UCHAR_MAX ( __SCHAR_MAX__ * 2 + 1 )

/* Whether the 'char' type is unsigned                                        */
#ifdef __CHAR_UNSIGNED__
#define _PDCLIB_CHAR_MAX _PDCLIB_UCHAR_MAX
#define _PDCLIB_CHAR_MIN 0
#else
#define _PDCLIB_CHAR_MAX _PDCLIB_SCHAR_MAX
#define _PDCLIB_CHAR_MIN _PDCLIB_SCHAR_MIN
#endif

/* Maximum and minimum values of signed / unsigned short                      */
#define _PDCLIB_SHRT_MAX __SHRT_MAX__
#define _PDCLIB_SHRT_MIN _PDCLIB_MIN_CALC( __SHRT_MAX__ )
#define _PDCLIB_USHRT_MAX ( __SHRT_MAX__ * 2u + 1 )

/* Maximum and minimum values of signed / unsigned int                        */
#define _PDCLIB_INT_MAX __INT_MAX__
#define _PDCLIB_INT_MIN _PDCLIB_MIN_CALC( __INT_MAX__ )
#define _PDCLIB_UINT_MAX ( __INT_MAX__ * 2u + 1 )

/* Maximum and minimum values of signed / unsigned long                       */
#define _PDCLIB_LONG_MAX __LONG_MAX__
#define _PDCLIB_LONG_MIN _PDCLIB_MIN_CALC( __LONG_MAX__ )
#define _PDCLIB_ULONG_MAX ( __LONG_MAX__ * 2ul + 1 )

/* Maximum and minimum values of signed / unsigned long long                  */
#define _PDCLIB_LLONG_MAX __LONG_LONG_MAX__
#define _PDCLIB_LLONG_MIN _PDCLIB_MIN_CALC( __LONG_LONG_MAX__ )
#define _PDCLIB_ULLONG_MAX ( __LONG_LONG_MAX__ * 2ull + 1 )

/* -------------------------------------------------------------------------- */
/* <stdint.h> defines a set of integer types that are of a minimum width, and */
/* "usually fastest" on the system. (If, for example, accessing a single char */
/* requires the CPU to access a complete int and then mask out the char, the  */
/* "usually fastest" type of at least 8 bits would be int, not char.)         */
/* If you do not have information on the relative performance of the types,   */
/* the standard allows you to define any type that meets minimum width and    */
/* signedness requirements.                                                   */
/* The first define is the appropriate basic type (e.g. "long int"), second   */
/* its max value, the third its min value (both expressed in the given type). */
/* The same follows for the unsigned type (for which the minimum value is     */
/* obviously zero and need not be defined).                                   */
/* There *are* predefines provided for the printf()/scanf() length specifiers */
/* but tunneling them through here would have added many lines of repetitive  */
/* and mostly redundant defines. They are determined in <_PDCLIB_internal.h>. */
/* -------------------------------------------------------------------------- */

/* int_fast8_t / uint_fast8_t                                                 */
#define _PDCLIB_int_fast8_t        int
#define _PDCLIB_INT_FAST8_MAX      _PDCLIB_INT_MAX
#define _PDCLIB_INT_FAST8_MIN      _PDCLIB_INT_MIN
#define _PDCLIB_uint_fast8_t       unsigned int
#define _PDCLIB_UINT_FAST8_MAX     _PDCLIB_UINT_MAX

/* int_least8_t / uint_least8_t                                               */
#define _PDCLIB_int_least8_t       signed char
#define _PDCLIB_INT_LEAST8_MAX     _PDCLIB_SCHAR_MAX
#define _PDCLIB_INT_LEAST8_MIN     _PDCLIB_SCHAR_MIN
#define _PDCLIB_uint_least8_t      unsigned char
#define _PDCLIB_UINT_LEAST8_MAX    _PDCLIB_UCHAR_MAX

/* int_fast16_t / uint_fast16_t                                               */
#define _PDCLIB_int_fast16_t       int
#define _PDCLIB_INT_FAST16_MAX     _PDCLIB_INT_MAX
#define _PDCLIB_INT_FAST16_MIN     _PDCLIB_INT_MIN
#define _PDCLIB_uint_fast16_t      unsigned int
#define _PDCLIB_UINT_FAST16_MAX    _PDCLIB_UINT_MAX

/* int_least16_t / uint_least16_t                                             */
#define _PDCLIB_int_least16_t      short
#define _PDCLIB_INT_LEAST16_MAX    _PDCLIB_SHRT_MAX
#define _PDCLIB_INT_LEAST16_MIN    _PDCLIB_SHRT_MIN
#define _PDCLIB_uint_least16_t     unsigned short
#define _PDCLIB_UINT_LEAST16_MAX   _PDCLIB_USHRT_MAX

/* int_fast32_t / uint_fast32_t                                               */
#define _PDCLIB_int_fast32_t       int
#define _PDCLIB_INT_FAST32_MAX     _PDCLIB_INT_MAX
#define _PDCLIB_INT_FAST32_MIN     _PDCLIB_INT_MIN
#define _PDCLIB_uint_fast32_t      unsigned int
#define _PDCLIB_UINT_FAST32_MAX    _PDCLIB_UINT_MAX

/* int_least32_t / uint_least32_t                                             */
#define _PDCLIB_int_least32_t      int
#define _PDCLIB_INT_LEAST32_MAX    _PDCLIB_INT_MAX
#define _PDCLIB_INT_LEAST32_MIN    _PDCLIB_INT_MIN
#define _PDCLIB_uint_least32_t     unsigned int
#define _PDCLIB_UINT_LEAST32_MAX   _PDCLIB_UINT_MAX

/* int_fast64_t / uint_fast64_t                                               */
#define _PDCLIB_int_fast64_t       long long
#define _PDCLIB_INT_FAST64_MAX     _PDCLIB_LLONG_MAX
#define _PDCLIB_INT_FAST64_MIN     _PDCLIB_LLONG_MIN
#define _PDCLIB_uint_fast64_t      unsigned long long
#define _PDCLIB_UINT_FAST64_MAX    _PDCLIB_ULLONG_MAX

/* int_least64_t / uint_least64_t                                             */
#define _PDCLIB_int_least64_t      long long
#define _PDCLIB_INT_LEAST64_MAX    _PDCLIB_LLONG_MAX
#define _PDCLIB_INT_LEAST64_MIN    _PDCLIB_LLONG_MIN
#define _PDCLIB_uint_least64_t     unsigned long long
#define _PDCLIB_UINT_LEAST64_MAX   _PDCLIB_ULLONG_MAX

/* Exact-width integer types. These are *optional*. If your platform does not */
/* support types of these exact widths in two's complement encoding, just     */
/* leave them undefined.                                                      */
#define _PDCLIB_int8_t   signed char
#define _PDCLIB_int16_t  short
#define _PDCLIB_int32_t  int
#define _PDCLIB_int64_t  long long
#define _PDCLIB_uint8_t  unsigned char
#define _PDCLIB_uint16_t unsigned short
#define _PDCLIB_uint32_t unsigned int
#define _PDCLIB_uint64_t unsigned long long

/* INTn_C / UINTn_C macros to define int_leastN_t / uint_leastN_t literals.   */
#define _PDCLIB_INT_LEAST8_C( c )   c
#define _PDCLIB_UINT_LEAST8_C( c )  c
#define _PDCLIB_INT_LEAST16_C( c )  c
#define _PDCLIB_UINT_LEAST16_C( c ) c
#define _PDCLIB_INT_LEAST32_C( c )  c
#define _PDCLIB_UINT_LEAST32_C( c ) c##u
#define _PDCLIB_INT_LEAST64_C( c )  c##ll
#define _PDCLIB_UINT_LEAST64_C( c ) c##ull

/* <stdlib.h> defines the div() function family that allows taking quotient   */
/* and remainder of an integer division in one operation. Many platforms      */
/* support this in hardware / opcode, and the standard permits ordering of    */
/* the return structure in any way to fit the hardware. That is why those     */
/* structs can be configured here.                                            */

struct _PDCLIB_div_t
{
    int quot;
    int rem;
};

struct _PDCLIB_ldiv_t
{
    long int quot;
    long int rem;
};

struct _PDCLIB_lldiv_t
{
    long long int quot;
    long long int rem;
};

/* -------------------------------------------------------------------------- */
/* What follows are a couple of "special" typedefs and their limits.          */
/* -------------------------------------------------------------------------- */

/* The result type of substracting two pointers                               */
#define _PDCLIB_ptrdiff_t   int
#define _PDCLIB_PTRDIFF_MAX _PDCLIB_INT_MAX
#define _PDCLIB_PTRDIFF_MIN _PDCLIB_INT_MIN

/* An integer type that can be accessed as atomic entity (think asynchronous  */
/* interrupts). In a freestanding environment, the type itself need not be    */
/* defined, but its limits must. (Don't ask.)                                 */
#define _PDCLIB_sig_atomic_t   int
#define _PDCLIB_SIG_ATOMIC_MAX _PDCLIB_INT_MAX
#define _PDCLIB_SIG_ATOMIC_MIN _PDCLIB_INT_MIN

/* Result type of the 'sizeof' operator (must be unsigned).                   */
/* Note: In <stdint.h>, this is taken as the base for RSIZE_MAX, the limit    */
/* for the bounds-checking interfaces of Annex K. The recommendation by the   */
/* standard is to use ( SIZE_MAX >> 1 ) when "targeting machines with large   */
/* addess spaces", whereas small address spaces should use SIZE_MAX directly. */
#define _PDCLIB_size_t   unsigned int
#define _PDCLIB_SIZE_MAX _PDCLIB_UINT_MAX

/* Large enough an integer to hold all character codes of the widest          */
/* supported locale.                                                          */
#define _PDCLIB_wchar_t   unsigned short
#define _PDCLIB_WCHAR_MAX _PDCLIB_USHRT_MAX
#define _PDCLIB_WCHAR_MIN 0

/* Large enough an integer to hold all character codes of the widest          */
/* supported locale plus WEOF (which needs not to be equal to EOF, nor needs  */
/* to be of negative value).                                                  */
#define _PDCLIB_wint_t   unsigned short
#define _PDCLIB_WINT_MAX _PDCLIB_USHRT_MAX
#define _PDCLIB_WINT_MIN 0

/* Integer types capable of taking the (cast) value of a void *, and having   */
/* the value cast back to void *, comparing equal to the original.            */
#define _PDCLIB_intptr_t     long
#define _PDCLIB_INTPTR_MAX   _PDCLIB_LONG_MAX
#define _PDCLIB_INTPTR_MIN   _PDCLIB_LONG_MIN
#define _PDCLIB_uintptr_t    unsigned long
#define _PDCLIB_UINTPTR_MAX  _PDCLIB_ULONG_MAX

/* Largest supported integer type. Implementation note: see _PDCLIB_atomax(). */
#define _PDCLIB_intmax_t     long long int
#define _PDCLIB_INTMAX_MAX   _PDCLIB_LLONG_MAX
#define _PDCLIB_INTMAX_MIN   _PDCLIB_LLONG_MIN
#define _PDCLIB_INTMAX_C( c ) c##ll
#define _PDCLIB_uintmax_t    unsigned long long int
#define _PDCLIB_UINTMAX_MAX  _PDCLIB_ULLONG_MAX
#define _PDCLIB_UINTMAX_C( c ) c##ull

/* <inttypes.h> defines imaxdiv(), which is equivalent to the div() function  */
/* family (see further above) with intmax_t as basis.                         */

struct _PDCLIB_imaxdiv_t
{
    _PDCLIB_intmax_t quot;
    _PDCLIB_intmax_t rem;
};

/* -------------------------------------------------------------------------- */
/* Time types, limits, constants, and paths                                   */
/* -------------------------------------------------------------------------- */

/* _PDCLIB_time is the type for type_t; _PDCLIB_clock for clock_t. Both types */
/* are defined as "real types capable of representing times". The "range and  */
/* precision of times representable" is implementation-defined.               */

/* For clock_t, the standard defines that dividing the result of clock() by   */
/* CLOCKS_PER_SEC gives the seconds elapsed.                                  */
#define _PDCLIB_clock_t unsigned int
#define _PDCLIB_CLOCKS_PER_SEC 1000

/* For time_t, no such divider exists. Most implementations use a count of    */
/* seconds since a specified epoch. While PDCLib really should support other  */
/* encodings as well, for now "count of seconds" is the only supported one.   */
/* MIN / MAX values for time_t are not required by the standard (and they are */
/* not "exported" from the _PDCLIB namespace), but they are useful in support */
/* of the _tzcode implementation.                                             */
#define _PDCLIB_time_t long
#define _PDCLIB_TIME_MAX _PDCLIB_LONG_MAX
#define _PDCLIB_TIME_MIN _PDCLIB_LONG_MIN

/* "Unix time" uses 1970-01-01T00:00:00 as "epoch". If your system uses a     */
/* different "zero point" for its timestamps, set this to the offset between  */
/* your epoch and Unix epoch. (For example, NTP uses 1900-01-01T00:00:00 as   */
/* epoch, giving an offset of (70 * 365 + 17) * 86400 = 220898800 seconds.)   */
#define _PDCLIB_EPOCH_BIAS INT64_C( 0 )

/* Leave this alone for now.                                                  */
#define _PDCLIB_TIME_UTC 1

/* Path to TZ data.                                                           */
/* There is no time zone database on the Xbox. With empty paths the lookup    */
/* fails right away and UTC is used.                                          */
#define _PDCLIB_TZDIR ""

/* Path to default (local) timezone                                           */
#define _PDCLIB_TZDEFAULT ""

/* -------------------------------------------------------------------------- */
/* Floating Point                                                             */
/* -------------------------------------------------------------------------- */

/* Whether the implementation rounds toward zero (0), to nearest (1), toward
   positive infinity (2), or toward negative infinity (3). (-1) signifies
   indeterminable rounding, any other value implementation-specific rounding.
*/
#define _PDCLIB_FLT_ROUNDS -1

/* Check <float.h> for explanations on each of these values.                  */
#define _PDCLIB_FLT_EVAL_METHOD   __FLT_EVAL_METHOD__

#define _PDCLIB_FLT_HAS_SUBNORM   __FLT_HAS_DENORM__
#define _PDCLIB_DBL_HAS_SUBNORM   __DBL_HAS_DENORM__
#define _PDCLIB_LDBL_HAS_SUBNORM  __LDBL_HAS_DENORM__

#define _PDCLIB_FLT_RADIX         __FLT_RADIX__

#define _PDCLIB_FLT_MANT_DIG      __FLT_MANT_DIG__
#define _PDCLIB_DBL_MANT_DIG      __DBL_MANT_DIG__
#define _PDCLIB_LDBL_MANT_DIG     __LDBL_MANT_DIG__

#define _PDCLIB_FLT_DECIMAL_DIG   __FLT_DECIMAL_DIG__
#define _PDCLIB_DBL_DECIMAL_DIG   __DBL_DECIMAL_DIG__
#define _PDCLIB_LDBL_DECIMAL_DIG  __LDBL_DECIMAL_DIG__

#define _PDCLIB_DECIMAL_DIG       __DECIMAL_DIG__

#define _PDCLIB_FLT_DIG           __FLT_DIG__
#define _PDCLIB_DBL_DIG           __DBL_DIG__
#define _PDCLIB_LDBL_DIG          __LDBL_DIG__

#define _PDCLIB_FLT_MIN_EXP       __FLT_MIN_EXP__
#define _PDCLIB_DBL_MIN_EXP       __DBL_MIN_EXP__
#define _PDCLIB_LDBL_MIN_EXP      __LDBL_MIN_EXP__

#define _PDCLIB_FLT_MIN_10_EXP    __FLT_MIN_10_EXP__
#define _PDCLIB_DBL_MIN_10_EXP    __DBL_MIN_10_EXP__
#define _PDCLIB_LDBL_MIN_10_EXP   __LDBL_MIN_10_EXP__

#define _PDCLIB_FLT_MAX_EXP       __FLT_MAX_EXP__
#define _PDCLIB_DBL_MAX_EXP       __DBL_MAX_EXP__
#define _PDCLIB_LDBL_MAX_EXP      __LDBL_MAX_EXP__

#define _PDCLIB_FLT_MAX_10_EXP    __FLT_MAX_10_EXP__
#define _PDCLIB_DBL_MAX_10_EXP    __DBL_MAX_10_EXP__
#define _PDCLIB_LDBL_MAX_10_EXP   __LDBL_MAX_10_EXP__

#define _PDCLIB_FLT_MAX           __FLT_MAX__
#define _PDCLIB_DBL_MAX           __DBL_MAX__
#define _PDCLIB_LDBL_MAX          __LDBL_MAX__

#define _PDCLIB_FLT_EPSILON       __FLT_EPSILON__
#define _PDCLIB_DBL_EPSILON       __DBL_EPSILON__
#define _PDCLIB_LDBL_EPSILON      __LDBL_EPSILON__

#define _PDCLIB_FLT_MIN           __FLT_MIN__
#define _PDCLIB_DBL_MIN           __DBL_MIN__
#define _PDCLIB_LDBL_MIN          __LDBL_MIN__

#define _PDCLIB_FLT_TRUE_MIN      __FLT_DENORM_MIN__
#define _PDCLIB_DBL_TRUE_MIN      __DBL_DENORM_MIN__
#define _PDCLIB_LDBL_TRUE_MIN     __LDBL_DENORM_MIN__

#if __FLT_HAS_INFINITY__ == 1
#define _PDCLIB_HUGE_VALF         (__FLT_MAX__ * 2)
#else
#define _PDCLIB_HUGE_VALF         __FLT_MAX__
#endif

#if __DBL_HAS_INFINITY__ == 1
#define _PDCLIB_HUGE_VAL          (__DBL_MAX__ * 2)
#else
#define _PDCLIB_HUGE_VAL          __DBL_MAX__
#endif

#if __LDBL_HAS_INFINITY__ == 1
#define _PDCLIB_HUGE_VALL         (__LDBL_MAX__ * 2)
#else
#define _PDCLIB_HUGE_VALL         __LDBL_MAX__
#endif

/* Macros for deconstructing floating point values                            */
/* This assumes that the floating point value has been memcpy'd into an array */
/* of _PDCLIB_bigint_digit_t (see _PDCLIB_bigint_from_*dbl.c with the array   */
/* passed to the macro as parameter.                                          */
#define _PDCLIB_FLT_SIGN( data ) ( ( data[1] & 0x8000 ) >> 15 )
#define _PDCLIB_FLT_EXP( data ) ( ( data[1] & 0x7f80 ) >> 7 )
#define _PDCLIB_FLT_SIZE( data ) ( data[1] &= 0x007f, 2 )

#define _PDCLIB_DBL_SIGN( data ) ( ( data[3] & 0x8000 ) >> 15 )
#define _PDCLIB_DBL_EXP( data ) ( ( data[3] & 0x7ff0u ) >> 4 )
#define _PDCLIB_DBL_SIZE( data ) ( data[3] &= 0x000fu, 4 )

/* Most platforms today use IEEE 754 single precision for 'float', and double */
/* precision for 'double'. But type 'long double' varies. We use what the     */
/* compiler states about LDBL_MANT_DIG to determine the type.                 */
#if _PDCLIB_LDBL_MANT_DIG == 64

/* Intel "Extended Precision" format, using 80 bits (64bit mantissa) */
#define _PDCLIB_LDBL_SIGN( data ) ( ( data[4] & 0x8000u ) >> 15 )
#define _PDCLIB_LDBL_EXP( data ) ( data[4] & 0x7fffu )
#define _PDCLIB_LDBL_SIZE( data ) ( data[3] &= 0x7fffu, 4 )

#elif _PDCLIB_LDBL_MANT_DIG == 113

/* IEEE "Quadruple Precision" format, using 128 bits (113bit mantissa) */
#define _PDCLIB_LDBL_SIGN( data ) ( ( data[7] & 0x8000u ) >> 15 )
#define _PDCLIB_LDBL_EXP( data ) ( data[7] & 0x7fffu )
#define _PDCLIB_LDBL_SIZE( data ) 7

#else

/* IEEE "Double Precision" format, using 64 bits (53bit mantissa) */
/* (Same as DBL above) */
#define _PDCLIB_LDBL_SIGN( data ) ( ( data[3] & 0x8000 ) >> 15 )
#define _PDCLIB_LDBL_EXP( data ) ( ( data[3] & 0x7ff0u ) >> 4 )
#define _PDCLIB_LDBL_SIZE( data ) ( data[3] &= 0x000fu, 4 )

#endif

/* Given the definitions for *_MANT_START above, which resolve to "pointer
   to most dignificant byte of mantissa", the operand to use to get at the
   less significant bytes. (That would be - for i386, x86_64, and ARM.)
*/
#define _PDCLIB_FLT_OP -

/* -------------------------------------------------------------------------- */
/* Big Integer Arithmetic                                                     */
/* -------------------------------------------------------------------------- */
/* In support of the floating point converstions required by printf() etc.,   */
/* PDCLib provides rudimentary big integer arithmetics. The _PDCLIB_bigint_t  */
/* type stores values in a sequence of integer "digits", which may be of any  */
/* uint_leastN_t type with N being 32 or 16. Note that multiplication and     */
/* division require the help of the next larger type. So set the define to    */
/* 32 if efficient 64bit integer arithmetics are available on your platform,  */
/* and to 16 otherwise.                                                       */
/* (The value range of _PDCLIB_bigint_t is not affected by this setting.)     */

#define _PDCLIB_BIGINT_DIGIT_BITS 16

/* -------------------------------------------------------------------------- */
/* Platform-dependent macros defined by the standard headers.                 */
/* -------------------------------------------------------------------------- */

/* The offsetof macro
   Contract: Expand to an integer constant expression of type size_t, which
   represents the offset in bytes to the structure member from the beginning
   of the structure. If the specified member is a bitfield, behaviour is
   undefined.
   There is no standard-compliant way to do this.
   This implementation casts an integer zero to 'pointer to type', and then
   takes the address of member. This is undefined behaviour but should work on
   most compilers.
*/
#define _PDCLIB_offsetof( type, member ) __builtin_offsetof( type, member )

/* Variable Length Parameter List Handling (<stdarg.h>)
   The macros defined by <stdarg.h> are highly dependent on the calling
   conventions used, and you probably have to replace them with builtins of
   your compiler.
*/

typedef __builtin_va_list _PDCLIB_va_list;
#define _PDCLIB_va_arg __builtin_va_arg
#define _PDCLIB_va_copy __builtin_va_copy
#define _PDCLIB_va_end __builtin_va_end
#define _PDCLIB_va_start __builtin_va_start

/* -------------------------------------------------------------------------- */
/* OS "glue", part 1                                                          */
/* These are values and data type definitions that you would have to adapt to */
/* the capabilities and requirements of your OS.                              */
/* The actual *functions* of the OS interface are declared in _PDCLIB_glue.h. */
/* -------------------------------------------------------------------------- */

/* Memory management -------------------------------------------------------- */

/* Set this to the page size of your OS. If your OS does not support paging, set
   to an appropriate value. (Too small, and malloc() will call the kernel too
   often. Too large, and you will waste memory.)
*/
#define _PDCLIB_PAGESIZE 4096

/* Set this to the minimum memory node size. Any malloc() for a smaller size
   will be satisfied by a malloc() of this size instead (to avoid excessive
   fragmentation).
*/
#define _PDCLIB_MINALLOC 8

/* I/O ---------------------------------------------------------------------- */

/* The type of the file descriptor returned by _PDCLIB_open(). */
/* It has to match the winapi HANDLE type                      */
typedef void *_PDCLIB_fd_t;

/* The value (of type _PDCLIB_fd_t) returned by _PDCLIB_open() if the operation
   failed.
*/
#define _PDCLIB_NOHANDLE ( (_PDCLIB_fd_t) -1 )

/* The default size for file buffers. Must be at least 256. */
#define _PDCLIB_BUFSIZ 1024

/* The minimum number of files the implementation can open simultaneously. Must
   be at least 8. Depends largely on how the bookkeeping is done by fopen() /
   freopen() / fclose(). The example implementation limits the number of open
   files only by available memory.
*/
#define _PDCLIB_FOPEN_MAX 8

/* Length of the longest filename the implementation guarantees to support. */
#define _PDCLIB_FILENAME_MAX 128

/* Maximum length of filenames generated by tmpnam(). (See tmpfile.c.) */
#define _PDCLIB_L_tmpnam 46

/* Number of distinct file names that can be generated by tmpnam(). */
#define _PDCLIB_TMP_MAX 50

/* The values of SEEK_SET, SEEK_CUR and SEEK_END, used by fseek().
   Since at least one platform (POSIX) uses the same symbols for its own "seek"
   function, we use whatever the host defines (if it does define them).
*/
#define _PDCLIB_SEEK_SET 0
#define _PDCLIB_SEEK_CUR 1
#define _PDCLIB_SEEK_END 2

/* The number of characters that can be buffered with ungetc(). The standard
   guarantees only one (1); anything larger would make applications relying on
   this capability dependent on implementation-defined behaviour (not good).
*/
#define _PDCLIB_UNGETCBUFSIZE 1

/* The number of functions that can be registered with atexit(). Needs to be  */
/* at least 33 (32 guaranteed by the standard, plus _PDCLIB_closeall() which  */
/* is used internally by PDCLib to close all open streams).                   */
/* TODO: Should expand dynamically.                                           */
#define _PDCLIB_ATEXIT_SLOTS 40

/* errno -------------------------------------------------------------------- */

/* These are the values that _PDCLIB_errno can be set to by the library.

   By keeping PDCLib's errno in the _PDCLIB_* namespace, the library is capable
   to "translate" between errno values used by the hosting operating system and
   those used and passed out by the library.

   Example: In the example platform, the remove() function uses the unlink()
   system call as backend. Linux sets its errno to EISDIR if you try to unlink()
   a directory, but POSIX demands EPERM. Within the remove() function, you can
   catch the 'errno == EISDIR', and set '_PDCLIB_errno = _PDCLIB_EPERM'. Anyone
   using PDCLib's <errno.h> will "see" EPERM instead of EISDIR (the _PDCLIB_*
   prefix removed by <errno.h> mechanics).

   If you do not want that kind of translation, you might want to "match" the
   values used by PDCLib with those used by the host OS, as to avoid confusion.

   The standard only defines three distinct errno values: ERANGE, EDOM, and
   EILSEQ. The standard leaves it up to "the implementation" whether there are
   any more beyond those three. There is some controversy as to whether errno is
   such a good idea at all, so you might want to come up with a different error
   reporting facility for your platform.
*/

/* Argument list too long */
#define _PDCLIB_E2BIG             7
/* Permission denied */
#define _PDCLIB_EACCES           13
/* Address in use */
#define _PDCLIB_EADDRINUSE      100
/* Address not available */
#define _PDCLIB_EADDRNOTAVAIL   101
/* Address family not supported */
#define _PDCLIB_EAFNOSUPPORT    102
/* Resource unavailable, try again */
#define _PDCLIB_EAGAIN           11
/* Connection already in progress */
#define _PDCLIB_EALREADY        103
/* Bad file descriptor */
#define _PDCLIB_EBADF             9
/* Bad message */
#define _PDCLIB_EBADMSG         104
/* Device or resource busy */
#define _PDCLIB_EBUSY            16
/* Operation canceled */
#define _PDCLIB_ECANCELED       105
/* No child processes */
#define _PDCLIB_ECHILD           10
/* Connection aborted */
#define _PDCLIB_ECONNABORTED    106
/* Connection refused */
#define _PDCLIB_ECONNREFUSED    107
/* Connection reset */
#define _PDCLIB_ECONNRESET      108
/* Resource deadlock would occur */
#define _PDCLIB_EDEADLK          36
/* Destination address required */
#define _PDCLIB_EDESTADDRREQ    109
/* Mathematics argument out of domain of function */
#define _PDCLIB_EDOM             33
/* File exists */
#define _PDCLIB_EEXIST           17
/* Bad address */
#define _PDCLIB_EFAULT           14
/* File too large */
#define _PDCLIB_EFBIG            27
/* Host is unreachable */
#define _PDCLIB_EHOSTUNREACH    110
/* Identifier removed */
#define _PDCLIB_EIDRM           111
/* Illegal byte sequence */
#define _PDCLIB_EILSEQ           42
/* Operation in progress */
#define _PDCLIB_EINPROGRESS     112
/* Interrupted function */
#define _PDCLIB_EINTR             4
/* Invalid argument */
#define _PDCLIB_EINVAL           22
/* I/O error */
#define _PDCLIB_EIO               5
/* Socket is connected */
#define _PDCLIB_EISCONN         113
/* Is a directory */
#define _PDCLIB_EISDIR           21
/* Too many levels of symbolic links */
#define _PDCLIB_ELOOP           114
/* File descriptor value too large */
#define _PDCLIB_EMFILE           24
/* Too many links */
#define _PDCLIB_EMLINK           31
/* Message too large */
#define _PDCLIB_EMSGSIZE        115
/* Filename too long */
#define _PDCLIB_ENAMETOOLONG     38
/* Network is down */
#define _PDCLIB_ENETDOWN        116
/* Connection aborted by network */
#define _PDCLIB_ENETRESET       117
/* Network unreachable */
#define _PDCLIB_ENETUNREACH     118
/* Too many files open in system */
#define _PDCLIB_ENFILE           23
/* No buffer space available */
#define _PDCLIB_ENOBUFS         119
/* No message is available on the STREAM head read queue */
#define _PDCLIB_ENODATA         120
/* No such device */
#define _PDCLIB_ENODEV           19
/* No such file or directory */
#define _PDCLIB_ENOENT            2
/* Executable file format error */
#define _PDCLIB_ENOEXEC           8
/* No locks available */
#define _PDCLIB_ENOLCK           39
/* Link has been severed */
#define _PDCLIB_ENOLINK         121
/* Not enough space */
#define _PDCLIB_ENOMEM           12
/* No message of the desired type */
#define _PDCLIB_ENOMSG          122
/* Protocol not available */
#define _PDCLIB_ENOPROTOOPT     123
/* No space left on device */
#define _PDCLIB_ENOSPC           28
/* No STREAM resources */
#define _PDCLIB_ENOSR           124
/* Not a STREAM */
#define _PDCLIB_ENOSTR          125
/* Function not supported */
#define _PDCLIB_ENOSYS           40
/* The socket is not connected */
#define _PDCLIB_ENOTCONN        126
/* Not a directory */
#define _PDCLIB_ENOTDIR          20
/* Directory not empty */
#define _PDCLIB_ENOTEMPTY        41
/* State not recoverable */
#define _PDCLIB_ENOTRECOVERABLE 127
/* Not a socket */
#define _PDCLIB_ENOTSOCK        128
/* Not supported */
#define _PDCLIB_ENOTSUP         129
/* Inappropriate I/O control operation */
#define _PDCLIB_ENOTTY           25
/* No such device or address */
#define _PDCLIB_ENXIO             6
/* Operation not supported on socket */
#define _PDCLIB_EOPNOTSUPP      130
/* Value too large to be stored in data type */
#define _PDCLIB_EOVERFLOW       132
/* Previous owner died */
#define _PDCLIB_EOWNERDEAD      133
/* Operation not permitted */
#define _PDCLIB_EPERM             1
/* Broken pipe */
#define _PDCLIB_EPIPE            32
/* Protocol error */
#define _PDCLIB_EPROTO          134
/* Protocol not supported */
#define _PDCLIB_EPROTONOSUPPORT 135
/* Protocol wrong type for socket */
#define _PDCLIB_EPROTOTYPE      136
/* Result too large */
#define _PDCLIB_ERANGE           34
/* Read-only file system */
#define _PDCLIB_EROFS            30
/* Invalid seek */
#define _PDCLIB_ESPIPE           29
/* No such process */
#define _PDCLIB_ESRCH             3
/* Stream ioctl() timeout */
#define _PDCLIB_ETIME           137
/* Connection timed out */
#define _PDCLIB_ETIMEDOUT       138
/* Text file busy */
#define _PDCLIB_ETXTBSY         139
/* Operation would block */
#define _PDCLIB_EWOULDBLOCK     140
/* Cross-device link */
#define _PDCLIB_EXDEV            18

/* The highest defined errno value, plus one. This is used to set the size    */
/* of the array in struct _PDCLIB_lc_text_t holding error messages for the    */
/* strerror() and perror() functions. (If you change this value because you   */
/* are using additional errno values, you *HAVE* to provide appropriate error */
/* messages for *ALL* locales.)                                               */
#define _PDCLIB_ERRNO_MAX 141

/* The error message used for unknown error codes (generated by errno_readout */
/* for consistency between the 'holes' in the list of defined error messages  */
/* and the text generated by e.g. strerror() for out-of-range error values.)  */
#define _PDCLIB_EUNKNOWN_TEXT (char*)"unknown error"

/* locale data -------------------------------------------------------------- */

/* The default path where PDCLib should look for its locale data.             */
/* Must end with the appropriate separator character.                         */
#define _PDCLIB_LOCALE_PATH "/usr/share/pdclib/i18n/"

/* The name of the environment variable that can be used to override that     */
/* path setting.                                                              */
#define _PDCLIB_LOCALE_PATH_ENV PDCLIB_I18N

/* threads ------------------------------------------------------------------ */
typedef void *_PDCLIB_thrd_t;
typedef struct __PDCLIB_cnd_t
{
    void *eventHandles[2]; // [0] single-receiver signal, [1] broadcast signal
    _Atomic int waitCount;
} _PDCLIB_cnd_t;
typedef struct __PDCLIB_mtx_t
{
    void *handle;
} _PDCLIB_mtx_t;
typedef unsigned int _PDCLIB_tss_t;
typedef int _PDCLIB_once_flag;
#define _PDCLIB_ONCE_FLAG_INIT 0
#define _PDCLIB_TSS_DTOR_ITERATIONS 4

#if __has_include(<assert_ext_.h>)
#define _PDCLIB_EXTEND_ASSERT_H <assert_ext_.h>
#endif

#if __has_include(<ctype_ext_.h>)
#define _PDCLIB_EXTEND_CTYPE_H <ctype_ext_.h>
#endif

#if __has_include(<errno_ext_.h>)
#define _PDCLIB_EXTEND_ERRNO_H <errno_ext_.h>
#endif

#if __has_include(<float_ext_.h>)
#define _PDCLIB_EXTEND_FLOAT_H <float_ext_.h>
#endif

#if __has_include(<inttypes_ext_.h>)
#define _PDCLIB_EXTEND_INTTYPES_H <inttypes_ext_.h>
#endif

#if __has_include(<iso646_ext_.h>)
#define _PDCLIB_EXTEND_ISO646_H <iso646_ext_.h>
#endif

#if __has_include(<limits_ext_.h>)
#define _PDCLIB_EXTEND_LIMITS_H <limits_ext_.h>
#endif

#if __has_include(<locale_ext_.h>)
#define _PDCLIB_EXTEND_LOCALE_H <locale_ext_.h>
#endif

#if __has_include(<signal_ext_.h>)
#define _PDCLIB_EXTEND_SIGNAL_H <signal_ext_.h>
#endif

#if __has_include(<stdalign_ext_.h>)
#define _PDCLIB_EXTEND_STDALIGN_H <stdalign_ext_.h>
#endif

#if __has_include(<stdarg_ext_.h>)
#define _PDCLIB_EXTEND_STDARG_H <stdarg_ext_.h>
#endif

#if __has_include(<stdbool_ext_.h>)
#define _PDCLIB_EXTEND_STDBOOL_H <stdbool_ext_.h>
#endif

#if __has_include(<stddef_ext_.h>)
#define _PDCLIB_EXTEND_STDDEF_H <stddef_ext_.h>
#endif

#if __has_include(<stdint_ext_.h>)
#define _PDCLIB_EXTEND_STDINT_H <stdint_ext_.h>
#endif

#if __has_include(<stdio_ext_.h>)
#define _PDCLIB_EXTEND_STDIO_H <stdio_ext_.h>
#endif

#if __has_include(<stdlib_ext_.h>)
#define _PDCLIB_EXTEND_STDLIB_H <stdlib_ext_.h>
#endif

#if __has_include(<stdnoreturn_ext_.h>)
#define _PDCLIB_EXTEND_STDNORETURN_H <stdnoreturn_ext_.h>
#endif

#if __has_include(<string_ext_.h>)
#define _PDCLIB_EXTEND_STRING_H <string_ext_.h>
#endif

#if __has_include(<threads_ext_.h>)
#define _PDCLIB_EXTEND_THREADS_H <threads_ext_.h>
#endif

#if __has_include(<time_ext_.h>)
#define _PDCLIB_EXTEND_TIME_H <time_ext_.h>
#endif

#if __has_include(<wctype_ext_.h>)
#define _PDCLIB_EXTEND_WCTYPE_H <wctype_ext_.h>
#endif


#endif
