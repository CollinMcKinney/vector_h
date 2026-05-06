#if !defined(VECTORS_H)
#define VECTORS_H

#include <math.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Select best available STATIC_ASSERT implementation. */
#if defined(__cplusplus) && (__cplusplus >= 201103L)
    #define STATIC_ASSERT(expr, msg) static_assert((expr), #msg)
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
    #define STATIC_ASSERT(expr, msg) _Static_assert((expr), #msg)
#elif defined(_MSC_VER)
    #define STATIC_ASSERT(expr, msg) static_assert((expr), #msg)
#else
    #define CONCAT_(a, b) a##b
    #define CONCAT(a, b) CONCAT_(a, b)
    #define STATIC_ASSERT(expr, msg) \
        typedef char CONCAT(ERROR__, CONCAT(msg, CONCAT(__LINE_, __LINE__)))[((expr) ? 1 : -1)]
#endif

/* -------------------------------------------------------------------------
    User configuration - define ONE of these before including this header.
    By default we use 32‑bit float.
   ------------------------------------------------------------------------- */
#if defined(VECTORS_REAL32_IS_DOUBLE)
    #define VECTORS_REAL32 double
    #define VECTORS_REAL_IS_FLOAT 0
#else
    /* default to float if VECTORS_REAL32_IS_FLOAT is defined or nothing is defined */
    #define VECTORS_REAL32 float
    #define VECTORS_REAL_IS_FLOAT 1
#endif

typedef VECTORS_REAL32 real;
STATIC_ASSERT(sizeof(real) == 0x4, real_size_wrong);

/* -------------------------------------------------------------------------
   Generic math helpers - adapt to language standard and float/double
   ------------------------------------------------------------------------- */
#if defined(__cplusplus)
    #define REAL_MATH_1_ARG(func, x)      (func)(x)
    #define REAL_MATH_2_ARG(func, x, y)   (func)((x), (y))

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
    #if VECTORS_REAL_IS_FLOAT
        #define REAL_MATH_1_ARG(func, x)      func ## f(x)
        #define REAL_MATH_2_ARG(func, x, y)   func ## f((x), (y))
    #else
        #define REAL_MATH_1_ARG(func, x)      func(x)
        #define REAL_MATH_2_ARG(func, x, y)   func((x), (y))
    #endif

#else
    /* C89 - always cast through double */
    #define REAL_MATH_1_ARG(func, x)      ((real)func((double)(x)))
    #define REAL_MATH_2_ARG(func, x, y)   ((real)func((double)(x), (double)(y)))
#endif

/* Real math functions available in all standards. */
#define real_floor(x)  REAL_MATH_1_ARG(floor, x)
#define real_ceil(x)   REAL_MATH_1_ARG(ceil, x)
#define real_sin(x)    REAL_MATH_1_ARG(sin, x)
#define real_cos(x)    REAL_MATH_1_ARG(cos, x)
#define real_tan(x)    REAL_MATH_1_ARG(tan, x)
#define real_asin(x)   REAL_MATH_1_ARG(asin, x)
#define real_acos(x)   REAL_MATH_1_ARG(acos, x)
#define real_atan(x)   REAL_MATH_1_ARG(atan, x)
#define real_sinh(x)   REAL_MATH_1_ARG(sinh, x)
#define real_cosh(x)   REAL_MATH_1_ARG(cosh, x)
#define real_tanh(x)   REAL_MATH_1_ARG(tanh, x)
#define real_abs(x)    REAL_MATH_1_ARG(fabs, x)
#define real_sqrt(x)   REAL_MATH_1_ARG(sqrt, x)
#define real_pow(x,y)  REAL_MATH_2_ARG(pow, x, y)

/* C++ & C99+ - define macros to use the fmin, fmax, trunc library functions. */
#if defined(__cplusplus) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
    #define real_min(x,y)  REAL_MATH_2_ARG(fmin, x, y)
    #define real_max(x,y)  REAL_MATH_2_ARG(fmax, x, y)
    #define real_trunc(x)  REAL_MATH_1_ARG(trunc, x)
/* C89 - provide static functions definitions for min, max, trunc. */
#else
    static real real_min(real x, real y) { return (real)((x) < (y) ? (x) : (y)); }
    static real real_max(real x, real y) { return (real)((x) > (y) ? (x) : (y)); }
    static real real_trunc(real x)  { return (x) >= 0 ? real_floor(x) : real_ceil(x); }
#endif

/* Real constants. */
#define VECTORS_PI ((real)3.14159265358979323846)
static const real VECTORS_RAD2DEG = (real)(180.0 / VECTORS_PI);
static const real VECTORS_DEG2RAD = (real)(VECTORS_PI / 180.0);
static const real VECTORS_QUAT_EPSILON = (real)0.0001;

/* ================================================================== *
 *  Boolean - bool (use the BOOL(x) macro to set or check booleans)
 * ================================================================== */
#if !defined(__cplusplus) && !defined(__bool_true_false_are_defined)
    typedef int bool;
    #define true ((bool)1)
    #define false ((bool)0)
#endif
#define BOOL(x) ((x) ? true : false)
STATIC_ASSERT(BOOL(true)  == true && true == 1, bool_true_fails);
STATIC_ASSERT(BOOL(false) == false && false == 0, bool_false_fails);
STATIC_ASSERT(BOOL(0x00)  == 0, bool_zero_fails);
STATIC_ASSERT(BOOL(0xFF)  == 1, bool_nonzero_fails);
STATIC_ASSERT(BOOL(-1)    == 1, bool_negative_fails);

/* ================================================================== *
 *  8‑bit unsigned  -  u8
 * ================================================================== */
#if UCHAR_MAX == 0xFFU
    typedef unsigned char u8;
    #define U8_MAX  UCHAR_MAX      /* 0xFFU */
#else
    #error "No 8‑bit unsigned integer type found"
#endif
STATIC_ASSERT(sizeof(u8) == 0x1, u8_size_wrong);

/* ================================================================== *
 *  8‑bit signed  -  i8
 * ================================================================== */
#if SCHAR_MAX == 0x7F && SCHAR_MIN == (-0x7F - 1)
    /* most reliable: signed char */
    typedef signed char i8;
    #define I8_MAX  SCHAR_MAX      /* 0x7F */
    #define I8_MIN  SCHAR_MIN      /* (-0x7F - 1) */
#elif CHAR_MAX == 0x7F && CHAR_MIN == (-0x7F - 1)
    typedef char i8;
    #define I8_MAX  CHAR_MAX
    #define I8_MIN  CHAR_MIN
#else
    #error "No 8‑bit signed integer type found"
#endif
STATIC_ASSERT(sizeof(i8) == 0x1, i8_size_wrong);

/* ================================================================== *
 *  16‑bit unsigned  -  u16
 * ================================================================== */
#if USHRT_MAX == 0xFFFFU
    typedef unsigned short u16;
    #define U16_MAX  USHRT_MAX      /* 0xFFFFU */
#elif UINT_MAX == 0xFFFFU
    typedef unsigned int u16;
    #define U16_MAX  UINT_MAX       /* 0xFFFFU */
#elif ULONG_MAX == 0xFFFFUL
    typedef unsigned long u16;
    #define U16_MAX  ULONG_MAX      /* 0xFFFFUL */
#elif UCHAR_MAX == 0xFFFFU
    typedef unsigned char u16;
    #define U16_MAX  UCHAR_MAX      /* 0xFFFFU */
#else
    #error "No 16‑bit unsigned integer type found"
#endif
STATIC_ASSERT(sizeof(u16) == 0x2, u16_size_wrong);

/* ================================================================== *
 *  16‑bit signed  -  i16
 * ================================================================== */
#if SHRT_MAX == 0x7FFF
    typedef short i16;
    #define I16_MAX  SHRT_MAX       /* 0x7FFF */
    #define I16_MIN  SHRT_MIN       /* (-0x7FFF - 1) */
#elif INT_MAX == 0x7FFF
    typedef int i16;
    #define I16_MAX  INT_MAX
    #define I16_MIN  INT_MIN
#elif LONG_MAX == 0x7FFFL
    typedef long i16;
    #define I16_MAX  LONG_MAX
    #define I16_MIN  LONG_MIN
#elif SCHAR_MAX == 0x7FFF
    /* very unusual: 16‑bit signed char */
    typedef signed char i16;
    #define I16_MAX  SCHAR_MAX
    #define I16_MIN  SCHAR_MIN
#else
    #error "No 16‑bit signed integer type found"
#endif
STATIC_ASSERT(sizeof(i16) == 0x2, i16_size_wrong);

/* ================================================================== *
 *  32‑bit unsigned  -  u32
 *   Order: unsigned int, unsigned long, unsigned short, unsigned char
 * ================================================================== */
#if UINT_MAX == 0xFFFFFFFFU
    typedef unsigned int u32;
    #define U32_MAX  UINT_MAX       /* 0xFFFFFFFFU */
#elif ULONG_MAX == 0xFFFFFFFFUL
    typedef unsigned long u32;
    #define U32_MAX  ULONG_MAX      /* 0xFFFFFFFFUL */
#elif USHRT_MAX == 0xFFFFFFFFU
    typedef unsigned short u32;
    #define U32_MAX  USHRT_MAX      /* 0xFFFFFFFFU */
#elif UCHAR_MAX == 0xFFFFFFFFU
    typedef unsigned char u32;
    #define U32_MAX  UCHAR_MAX      /* 0xFFFFFFFFU */
#else
    #error "No 32‑bit unsigned integer type found"
#endif
STATIC_ASSERT(sizeof(u32) == 0x4, u32_size_wrong);
typedef u32 flags32;
STATIC_ASSERT(sizeof(flags32) == 0x4, flags32_size_wrong);
typedef u32 string_id;
STATIC_ASSERT(sizeof(string_id) == 0x4, string_id_size_wrong);

/* ================================================================== *
 *  32‑bit signed  -  i32
 * ================================================================== */
#if INT_MAX == 0x7FFFFFFF
    typedef int i32;
    #define I32_MAX  INT_MAX        /* 0x7FFFFFFF */
    #define I32_MIN  INT_MIN        /* (-0x7FFFFFFF - 1) */
#elif LONG_MAX == 0x7FFFFFFFL
    typedef long i32;
    #define I32_MAX  LONG_MAX
    #define I32_MIN  LONG_MIN
#elif SHRT_MAX == 0x7FFFFFFF
    typedef short i32;
    #define I32_MAX  SHRT_MAX
    #define I32_MIN  SHRT_MIN
#elif SCHAR_MAX == 0x7FFFFFFF
    typedef signed char i32;
    #define I32_MAX  SCHAR_MAX
    #define I32_MIN  SCHAR_MIN
#else
    #error "No 32‑bit signed integer type found"
#endif
STATIC_ASSERT(sizeof(i32)     == 0x4, i32_size_wrong);

/* ================================================================== *
 *  64‑bit unsigned  -  u64
 * ================================================================== */
#if ULONG_MAX == 0xFFFFFFFFFFFFFFFFUL
    typedef unsigned long u64;
    #define U64_MAX  ULONG_MAX
#elif UINT_MAX == 0xFFFFFFFFFFFFFFFFU
    typedef unsigned int u64;
    #define U64_MAX  UINT_MAX
#elif USHRT_MAX == 0xFFFFFFFFFFFFFFFFU
    typedef unsigned short u64;
    #define U64_MAX  USHRT_MAX
#elif UCHAR_MAX == 0xFFFFFFFFFFFFFFFFU
    typedef unsigned char u64;
    #define U64_MAX  UCHAR_MAX
#else
    #if defined(__GNUC__) || defined(__llvm__) || defined(_MSC_VER) || defined(__MWERKS__)
        typedef unsigned long long u64;
        #ifdef ULLONG_MAX
            #define U64_MAX  ULLONG_MAX
        #else
            #define U64_MAX  (~0ULL)   /* all bits set */
        #endif
    #else
        #error "No 64‑bit unsigned type found (need long long extension)"
    #endif
#endif
STATIC_ASSERT(sizeof(u64) == 0x8, u64_size_wrong);

/* ================================================================== *
 *  64‑bit signed  -  i64
 * ================================================================== */
#if LONG_MAX == 0x7FFFFFFFFFFFFFFFL
    typedef long i64;
    #define I64_MAX  LONG_MAX
    #define I64_MIN  LONG_MIN
#elif INT_MAX == 0x7FFFFFFFFFFFFFFFLL
    typedef int i64;
    #define I64_MAX  INT_MAX
    #define I64_MIN  INT_MIN
#elif SHRT_MAX == 0x7FFFFFFFFFFFFFFFLL
    typedef short i64;
    #define I64_MAX  SHRT_MAX
    #define I64_MIN  SHRT_MIN
#elif SCHAR_MAX == 0x7FFFFFFFFFFFFFFFLL
    typedef signed char i64;
    #define I64_MAX  SCHAR_MAX
    #define I64_MIN  SCHAR_MIN
#else
    #if defined(__GNUC__) || defined(__llvm__) || defined(_MSC_VER) || defined(__MWERKS__)
        typedef long long i64;
        #ifdef LLONG_MAX
            #define I64_MAX  LLONG_MAX
            #define I64_MIN  LLONG_MIN
        #else
            /* portable two’s complement computation (C89 without long long macros) */
            #define I64_MAX  (0x7FFFFFFFFFFFFFFFLL)
            #define I64_MIN  (-I64_MAX - 1)
        #endif
    #else
        #error "No 64‑bit signed type found (need long long extension)"
    #endif
#endif
STATIC_ASSERT(sizeof(i64) == 0x8, i64_size_wrong);

#define _0 (u32)(0)
#define _1 (u32)(1)
#define _2 (u32)(2)
#define _3 (u32)(3)

#define MASK_0      (u32)(1 << _0)
#define MASK_1      (u32)(1 << _1)
#define MASK_2      (u32)(1 << _2)
#define MASK_3      (u32)(1 << _3)
#define MASK_01     (u32)( MASK_0 | MASK_1 )
#define MASK_02     (u32)( MASK_0 | MASK_2 )
#define MASK_03     (u32)( MASK_0 | MASK_3 )
#define MASK_12     (u32)( MASK_1 | MASK_2 )
#define MASK_13     (u32)( MASK_1 | MASK_3 )
#define MASK_23     (u32)( MASK_2 | MASK_3 )
#define MASK_012    (u32)( MASK_0 | MASK_1 | MASK_2 )
#define MASK_013    (u32)( MASK_0 | MASK_1 | MASK_3 )
#define MASK_023    (u32)( MASK_0 | MASK_2 | MASK_3 )
#define MASK_123    (u32)( MASK_1 | MASK_2 | MASK_3 )
#define MASK_0123   (u32)( MASK_0 | MASK_1 | MASK_2 | MASK_3 )

#define X _0
#define Y _1
#define Z _2
#define W _3

#define MASK_X      MASK_0   
#define MASK_Y      MASK_1   
#define MASK_Z      MASK_2   
#define MASK_W      MASK_3   
#define MASK_XY     MASK_01  
#define MASK_XZ     MASK_02  
#define MASK_XW     MASK_03  
#define MASK_YZ     MASK_12  
#define MASK_YW     MASK_13  
#define MASK_ZW     MASK_23  
#define MASK_XYZ    MASK_012 
#define MASK_XYW    MASK_013 
#define MASK_XZW    MASK_023 
#define MASK_YZW    MASK_123 
#define MASK_XYZW   MASK_0123

#define I _0
#define J _1
#define K _2
/* #define W W */

#define MASK_I      MASK_0   
#define MASK_J      MASK_1   
#define MASK_K      MASK_2   
/* #define MASK_W   MASK_3 */
#define MASK_IJ     MASK_01  
#define MASK_IK     MASK_02  
#define MASK_IW     MASK_03  
#define MASK_JK     MASK_12  
#define MASK_JW     MASK_13  
#define MASK_KW     MASK_23  
#define MASK_IJK    MASK_012 
#define MASK_IJW    MASK_013 
#define MASK_IKW    MASK_023 
#define MASK_JKW    MASK_123 
#define MASK_IJKW   MASK_0123

#define R _0
#define G _1
#define B _2
#define A _3

#define MASK_R      MASK_0   
#define MASK_G      MASK_1   
#define MASK_B      MASK_2   
#define MASK_A      MASK_3   
#define MASK_RG     MASK_01  
#define MASK_RB     MASK_02  
#define MASK_RA     MASK_03  
#define MASK_GB     MASK_12  
#define MASK_GA     MASK_13  
#define MASK_BA     MASK_23  
#define MASK_RGB    MASK_012 
#define MASK_RGA    MASK_013 
#define MASK_RBA    MASK_023 
#define MASK_GBA    MASK_123 
#define MASK_RGBA   MASK_0123

#define S _0
#define T _1
#define P _2
#define Q _3

#define MASK_S      MASK_0   
#define MASK_T      MASK_1   
#define MASK_P      MASK_2   
#define MASK_Q      MASK_3   
#define MASK_ST     MASK_01  
#define MASK_SP     MASK_02  
#define MASK_SQ     MASK_03  
#define MASK_TP     MASK_12  
#define MASK_TQ     MASK_13  
#define MASK_PQ     MASK_23  
#define MASK_STP    MASK_012 
#define MASK_STQ    MASK_013 
#define MASK_SPQ    MASK_023 
#define MASK_TPQ    MASK_123 
#define MASK_STPQ   MASK_0123

/* 2-component realing point vector. */
typedef union vec2
{
    real components[2];
    struct { real x, y; } position;
    struct { real i, j; } rotation;
    struct { real r, g; } color;
    struct { real s, t; } textcoord;
} vec2;
STATIC_ASSERT(sizeof(vec2) == 0x8, vec2_size_wrong);

/* 3-component realing point vector. */
typedef union vec3
{
    real components[3];
    struct { real x, y, z; } position;
    struct { real i, j, k; } rotation;
    struct { real r, g, b; } color;
    struct { real s, t, p; } textcoord;
	vec2 vec2;
} vec3;
STATIC_ASSERT(sizeof(vec3) == 0xC, vec3_size_wrong);

/* 4-component realing point vector. */
typedef union vec4
{
    real components[4];
    struct { real x, y, z, w; } position;
    struct { real i, j, k, w; } rotation;
    struct { real r, g, b, a; } color;
    struct { real s, t, p, q; } textcoord;
	vec3 vec3;
} vec4;
STATIC_ASSERT(sizeof(vec4) == 0x10, vec4_size_wrong);

typedef union mat2
{
	real data[4];
	real transpose[2][2];
	vec2 columns[2];
} mat2;
STATIC_ASSERT(sizeof(mat2) == 0x10, mat2_size_wrong);

typedef union mat3
{
	real data[9];
	real transpose[3][3];
	vec3 columns[3];
} mat3;
STATIC_ASSERT(sizeof(mat3) == 0x24, mat3_size_wrong);

typedef union mat4
{
	real data[16];
	real transpose[4][4];
	vec4 columns[4];
} mat4;
STATIC_ASSERT(sizeof(mat4) == 0x40, mat4_size_wrong);

/* Swizzle (swap) the order of components */
static vec2 vec2_swizzle(vec2 src0, u32 a, u32 b)
{
    vec2 swizzled;
    swizzled.components[0] = src0.components[a & 0x1];
    swizzled.components[1] = src0.components[b & 0x1];
    return swizzled;
}

/* Selects components from src0 if the corresponding bit in the mask is set, otherwise selects from src1. */
static vec2 vec2_mask(vec2 src0, vec2 src1, u32 mask)
{
    vec2 masked;
    masked.components[0] = mask & MASK_0 ? src0.components[0] : src1.components[0];
    masked.components[1] = mask & MASK_1 ? src0.components[1] : src1.components[1];
    return masked;
}

/* Initialize a vec2 from 2 real's, where each component maps to an argument. */
static vec2 vec2_init_from_2(real src0, real src1)
{
    vec2 vector;
    vector.components[0] = src0;
    vector.components[1] = src1;
    return vector;
}

/* Initialize a vec2 from one real, where all components map to the argument. */
static vec2 vec2_init_from_1(real src0)
{
    vec2 vector;
    vector.components[0] = src0;
    vector.components[1] = src0;
    return vector;
}

/* Per-component negation (sign flip). */
static vec2 vec2_negate(vec2 src0)
{
    vec2 negative;
    negative.components[0] = -src0.components[0];
    negative.components[1] = -src0.components[1];
    return negative;
}

/* Per-component addition of two vec2. */
static vec2 vec2_add(vec2 augend, vec2 addend)
{
    vec2 sum;
    sum.components[0] = augend.components[0] + addend.components[0];
    sum.components[1] = augend.components[1] + addend.components[1];
    return sum;
}

/* Per-component addition of a vec2 and a scalar. */
static vec2 vec2_add_scalar(vec2 augend, real addend)
{
    vec2 sum;
    sum.components[0] = augend.components[0] + addend;
    sum.components[1] = augend.components[1] + addend;
    return sum;
}

/* Per-component subtraction of vec2. */
static vec2 vec2_sub(vec2 minuend, vec2 subtrahend)
{
    vec2 difference;
    difference.components[0] = minuend.components[0] - subtrahend.components[0];
    difference.components[1] = minuend.components[1] - subtrahend.components[1];
    return difference;
}

/* Per-component subtraction of a scalar from a vec2. */
static vec2 vec2_sub_scalar(vec2 minuend, real subtrahend)
{
    vec2 difference;
    difference.components[0] = minuend.components[0] - subtrahend;
    difference.components[1] = minuend.components[1] - subtrahend;
    return difference;
}

/* Per-component multiplication of a vec2 by a vec2. */
static vec2 vec2_mul(vec2 multiplicand, vec2 multiplier)
{
    vec2 product;
    product.components[0] = multiplicand.components[0] * multiplier.components[0];
    product.components[1] = multiplicand.components[1] * multiplier.components[1];
    return product;
}

/* Per-component multiplication of a vec2 and a scalar. */
static vec2 vec2_mul_scalar(vec2 multiplicand, real multiplier)
{
    vec2 product;
    product.components[0] = multiplicand.components[0] * multiplier;
    product.components[1] = multiplicand.components[1] * multiplier;
    return product;
}

/* Per-component division of a vec2 by a vec2. */
static vec2 vec2_div(vec2 dividend, vec2 divisor)
{
    vec2 quotient;
    quotient.components[0] = dividend.components[0] / divisor.components[0];
    quotient.components[1] = dividend.components[1] / divisor.components[1];
    return quotient;
}

/* Per-component division of a vec2 by a scalar. */
static vec2 vec2_div_scalar(vec2 dividend, real divisor)
{
    vec2 quotient;
    quotient.components[0] = dividend.components[0] / divisor;
    quotient.components[1] = dividend.components[1] / divisor;
    return quotient;
}

/* Per-component vec2 to the power of a vec2. */
static vec2 vec2_pow(vec2 base, vec2 power)
{
    vec2 yield;
    yield.components[0] = real_pow(base.components[0], power.components[0]);
    yield.components[1] = real_pow(base.components[1], power.components[1]);
    return yield;
}

/* Per-component vec2 to the power of a scalar. */
static vec2 vec2_pow_scalar(vec2 base, real power)
{
    vec2 yield;
    yield.components[0] = real_pow(base.components[0], power);
    yield.components[1] = real_pow(base.components[1], power);
    return yield;
}

/* Per-component principal square-root. */
static vec2 vec2_sqrt(vec2 radicand)
{
    vec2 principal;
    principal.components[0] = real_sqrt(radicand.components[0]);
    principal.components[1] = real_sqrt(radicand.components[1]);
    return principal;
}

/* Per-component reciprocal. */
static vec2 vec2_rcp(vec2 recipricand)
{
    vec2 ones        = vec2_init_from_1(1.0f);
    vec2 reciprocal = vec2_div(ones, recipricand);
    return reciprocal;
}

/* Per-component reciprocal square-root. */
static vec2 vec2_rsqrt(vec2 radicand)
{
    vec2 square_root    = vec2_sqrt(radicand);
    vec2 reciprocal     = vec2_rcp(square_root);
    return reciprocal;
}

/* Per-component absolute-value. */
static vec2 vec2_abs(vec2 src0)
{
    vec2 rets;
    rets.components[0] = real_abs(src0.components[0]);
    rets.components[1] = real_abs(src0.components[1]);
    return rets;
}

/* Per-component sine. */
static vec2 vec2_sin(vec2 theta)
{
    vec2 sine;
    sine.components[0] = real_sin(theta.components[0]);
    sine.components[1] = real_sin(theta.components[1]);
    return sine;
}

/* Per-component cosine. */
static vec2 vec2_cos(vec2 theta)
{
    vec2 cosine;
    cosine.components[0] = real_cos(theta.components[0]);
    cosine.components[1] = real_cos(theta.components[1]);
    return cosine;
}

/* Per-component tangent. */
static vec2 vec2_tan(vec2 theta)
{
    vec2 tangent;
    tangent.components[0] = real_tan(theta.components[0]);
    tangent.components[1] = real_tan(theta.components[1]);
    return tangent;
}

/* Per-component arc-sine. */
static vec2 vec2_asin(vec2 theta)
{
    vec2 arc_sine;
    arc_sine.components[0] = real_asin(theta.components[0]);
    arc_sine.components[1] = real_asin(theta.components[1]);
    return arc_sine;
}

/* Per-component arc-cosine. */
static vec2 vec2_acos(vec2 theta)
{
    vec2 arc_cosine;
    arc_cosine.components[0] = real_acos(theta.components[0]);
    arc_cosine.components[1] = real_acos(theta.components[1]);
    return arc_cosine;
}

/* Per-component arc-tangent. */
static vec2 vec2_atan(vec2 theta)
{
    vec2 arc_tangent;
    arc_tangent.components[0] = real_atan(theta.components[0]);
    arc_tangent.components[1] = real_atan(theta.components[1]);
    return arc_tangent;
}

/* Per-component cosecant. */
static vec2 vec2_csc(vec2 theta)
{
    vec2 sine = vec2_sin(theta);
    vec2 cosecant = vec2_rcp(sine);
    return cosecant;
}

/* Per-component secant. */
static vec2 vec2_sec(vec2 theta)
{
    vec2 cosine = vec2_cos(theta);
    vec2 secant = vec2_rcp(cosine);
    return secant;
}

/* Per-component cotangent. */
static vec2 vec2_cot(vec2 theta)
{
    vec2 tangent    = vec2_tan(theta);
    vec2 cotangent  = vec2_rcp(tangent);
    return cotangent;
}

/* Per-component hyperbolic-sine. */
static vec2 vec2_sinh(vec2 theta)
{
    vec2 hyperbolic_sine;
    hyperbolic_sine.components[0] = real_sinh(theta.components[0]);
    hyperbolic_sine.components[1] = real_sinh(theta.components[1]);
    return hyperbolic_sine;
}

/* Per-component hyperbolic-cosine. */
static vec2 vec2_cosh(vec2 theta)
{
    vec2 hyperbolic_cosine;
    hyperbolic_cosine.components[0] = real_cosh(theta.components[0]);
    hyperbolic_cosine.components[1] = real_cosh(theta.components[1]);
    return hyperbolic_cosine;
}

/* Per-component hyperbolic-tangent. */
static vec2 vec2_tanh(vec2 theta)
{
    vec2 hyperbolic_tangent;
    hyperbolic_tangent.components[0] = real_tanh(theta.components[0]);
    hyperbolic_tangent.components[1] = real_tanh(theta.components[1]);
    return hyperbolic_tangent;
}

/* Per-component hyperbolic-cosecant. */
static vec2 vec2_csch(vec2 theta)
{
    vec2 hyperbolic_sin          = vec2_sinh(theta);
    vec2 hyperbolic_cosecant    = vec2_rcp(hyperbolic_sin);
    return hyperbolic_cosecant;
}

/* Per-component hyperbolic-secant. */
static vec2 vec2_sech(vec2 theta)
{
    vec2 hyperbolic_cosine = vec2_cosh(theta);
    vec2 hyperbolic_secant = vec2_rcp(hyperbolic_cosine);
    return hyperbolic_secant;
}

/* Per-component hyperbolic-cotangent. */
static vec2 vec2_coth(vec2 theta)
{
    vec2 hyperbolic_tangent     = vec2_tanh(theta);
    vec2 hyperbolic_cotangent   = vec2_rcp(hyperbolic_tangent);
    return hyperbolic_cotangent;
}


/* True if *all* components are non-zero. */
static bool vec2_all(vec2 src0)
{
    bool rets = (
        (src0.components[0] != 0) &&
        (src0.components[1] != 0));
    return rets;
}

/* True if *any* components are non-zero. */
static bool vec2_any(vec2 src0)
{
    bool rets = (
        (src0.components[0] != 0) ||
        (src0.components[1] != 0));
    return rets;
}

/* 2-component dot product. */
static real vec2_dot(vec2 src0, vec2 src1)
{
    real dot_product;
    dot_product = (src0.components[0] * src1.components[0]) + (src0.components[1] * src1.components[1]);
    return dot_product;
}

/* Linear interpolation between two vec2 values. */
static vec2 vec2_lerp(vec2 src0, vec2 src1, real t)
{
    vec2 difference = vec2_sub(src1, src0);
    vec2 scaled = vec2_mul_scalar(difference, t);
    vec2 interpolated = vec2_add(src0, scaled);
    return interpolated;
}

/* Reflection vector through a normal (normal vector should be perpendicular to the surface, and cross
   through the intersection point.
          ____________________________________
         |                 normal            |
         | reflection  \   |   / incident    |
         |              \  |  /              |
         |               \ | /               |
         |                \|/                |
         |   surface ------*------           |
         |___________________________________|
*/
static vec2 vec2_reflect(vec2 incident, vec2 surface_normal)
{
    real dot_product    = 2.0f * vec2_dot(incident, surface_normal);
    vec2 product        = vec2_mul_scalar(surface_normal, dot_product);
    vec2 reflection     = vec2_sub(incident, product);
    return reflection;
}

/* Magnitude/Length */
static real vec2_magnitude(vec2 src0)
{
    real dot        = vec2_dot(src0, src0);
    real magnitude	= real_sqrt(dot);
    return magnitude;
}

/* Unit-vector */
static vec2 vec2_normalize(vec2 src0)
{
    real magnitude      = vec2_magnitude(src0);
    vec2 unit_vector    = vec2_div_scalar(src0, magnitude);
    return unit_vector;
}

/* Euclidean distance. */
static real vec2_distance(vec2 src0, vec2 src1)
{
    vec2 difference = vec2_sub(src0, src1);
    real distance   = vec2_magnitude(difference);
    return distance;
}

/* Angle between two vectors in radians. */
static real vec2_angle(vec2 src0, vec2 src1)
{
    real mag_a      = vec2_magnitude(src0);
    real mag_b      = vec2_magnitude(src1);
    real dot        = vec2_dot(src0, src1);
    real cos        = dot / (mag_a * mag_b);
    real radians    = real_acos(cos);
    return radians;
}

/* Per-component conversion from radians to degrees. */
static vec2 vec2_degrees(vec2 radians)
{
    vec2 degrees;
    degrees.components[0] = radians.components[0] * VECTORS_RAD2DEG;
    degrees.components[1] = radians.components[1] * VECTORS_RAD2DEG;
    return degrees;
}

/* Per-component conversion from degrees to radians. */
static vec2 vec2_radians(vec2 degrees)
{
    vec2 radians;
    radians.components[0] = degrees.components[0] * VECTORS_DEG2RAD;
    radians.components[1] = degrees.components[1] * VECTORS_DEG2RAD;
    return radians;
}

/* perp-product of two vec2. */
static real vec2_perp(vec2 src0, vec2 src1)
{
    return (src0.components[0] * src1.components[1]) - (src0.components[1] * src1.components[0]);
}

/* Per-component computation of closest integer rounded towards -inf. */
static vec2 vec2_floor(vec2 src0)
{
    vec2 floored;
    floored.components[0] = real_floor(src0.components[0]);
    floored.components[1] = real_floor(src0.components[1]);
    return floored;
}

/* Per-component computation of closest integer rounded towards +inf. */
static vec2 vec2_ceil(vec2 src0)
{
    vec2 ceiling;
    ceiling.components[0] = real_ceil(src0.components[0]);
    ceiling.components[1] = real_ceil(src0.components[1]);
    return ceiling;
}

/* Per-component computation of closest integer rounded towards 0. */
static vec2 vec2_trunc(vec2 src0)
{
    vec2 truncated;
    truncated.components[0] = real_trunc(src0.components[0]);
    truncated.components[1] = real_trunc(src0.components[1]);
    return truncated;
}

/* Per-component fractional component (src0 - floor(src0)). */
static vec2 vec2_frac(vec2 src0)
{
    vec2 rets;
    rets.components[0] = src0.components[0] - real_floor(src0.components[0]);
    rets.components[1] = src0.components[1] - real_floor(src0.components[1]);
    return rets;
}

/* Per-component maximum of two vec2. */
static vec2 vec2_max(vec2 src0, vec2 src1)
{
    vec2 maximum;
    maximum.components[0] = real_max(src0.components[0], src1.components[0]);
    maximum.components[1] = real_max(src0.components[1], src1.components[1]);
    return maximum;
}

/* Per-component maximum of a vec2 and a scalar. */
static vec2 vec2_max_scalar(vec2 src0, real src1)
{
    vec2 maximum;
    maximum.components[0] = real_max(src0.components[0], src1);
    maximum.components[1] = real_max(src0.components[1], src1);
    return maximum;
}

/* Per-component minimum of two vec2. */
static vec2 vec2_min(vec2 src0, vec2 src1)
{
    vec2 minimum;
    minimum.components[0] = real_min(src0.components[0], src1.components[0]);
    minimum.components[1] = real_min(src0.components[1], src1.components[1]);
    return minimum;
}

/* Per-component minimum of a vec2 and a scalar. */
static vec2 vec2_min_scalar(vec2 src0, real src1)
{
    vec2 minimum;
    minimum.components[0] = real_min(src0.components[0], src1);
    minimum.components[1] = real_min(src0.components[1], src1);
    return minimum;
}

/* Per-component clamp of src0 into the range of vectors (minimum..maximum). */
static vec2 vec2_clamp(vec2 src0, vec2 minimum, vec2 maximum)
{
    vec2 clamped_lower  = vec2_max(src0, minimum);
    vec2 clamped        = vec2_min(clamped_lower, maximum);
    return clamped;
}

/* Per-component clamp of src0 into the range of scalars (minimum..maximum). */
static vec2 vec2_clamp_scalar(vec2 src0, real minimum, real maximum)
{
    vec2 clamped_lower  = vec2_max_scalar(src0, minimum);
    vec2 clamped        = vec2_min_scalar(clamped_lower, maximum);
    return clamped;
}


/* Swizzle (swap) the order of components. */
static vec3 vec3_swizzle(vec3 src0, u32 a, u32 b, u32 c)
{
    vec3 swizzled;
    swizzled.components[0] = src0.components[a >= 3 ? 0 : a];
    swizzled.components[1] = src0.components[b >= 3 ? 0 : b];
    swizzled.components[2] = src0.components[c >= 3 ? 0 : c];
    return swizzled;
}

/* Selects components from src0 if the corresponding bit in the mask is set, otherwise selects from src1. */
static vec3 vec3_mask(vec3 src0, vec3 src1, u32 mask)
{
    vec3 masked;
    masked.components[0] = mask & MASK_0 ? src0.components[0] : src1.components[0];
    masked.components[1] = mask & MASK_1 ? src0.components[1] : src1.components[1];
    masked.components[2] = mask & MASK_2 ? src0.components[2] : src1.components[2];
    return masked;
}

/* Initialize a vec3 from 3 real's, where each component maps to an argument. */
static vec3 vec3_init_from_3(real src0, real src1, real src2)
{
    vec3 vector;
    vector.components[0] = src0;
    vector.components[1] = src1;
    vector.components[2] = src2;
    return vector;
}

/* Initialize a vec3 from one real, where all components map to the argument. */
static vec3 vec3_init_from_1(real src0)
{
    vec3 vector;
    vector.components[0] = src0;
    vector.components[1] = src0;
    vector.components[2] = src0;
    return vector;
}

/* Per-component negation (sign flip). */
static vec3 vec3_negate(vec3 src0)
{
    vec3 negative;
    negative.components[0] = -src0.components[0];
    negative.components[1] = -src0.components[1];
    negative.components[2] = -src0.components[2];
    return negative;
}

/* Per-component addition of two vec3. */
static vec3 vec3_add(vec3 augend, vec3 addend)
{
    vec3 sum;
    sum.components[0] = augend.components[0] + addend.components[0];
    sum.components[1] = augend.components[1] + addend.components[1];
    sum.components[2] = augend.components[2] + addend.components[2];
    return sum;
}

/* Per-component addition of a vec3 and a scalar. */
static vec3 vec3_add_scalar(vec3 augend, real addend)
{
    vec3 sum;
    sum.components[0] = augend.components[0] + addend;
    sum.components[1] = augend.components[1] + addend;
    sum.components[2] = augend.components[2] + addend;
    return sum;
}

/* Per-component subtraction of vec. */
static vec3 vec3_sub(vec3 minuend, vec3 subtrahend)
{
    vec3 difference;
    difference.components[0] = minuend.components[0] - subtrahend.components[0];
    difference.components[1] = minuend.components[1] - subtrahend.components[1];
    difference.components[2] = minuend.components[2] - subtrahend.components[2];
    return difference;
}

/* Per-component subtraction of a scalar from a vec3. */
static vec3 vec3_sub_scalar(vec3 minuend, real subtrahend)
{
    vec3 difference;
    difference.components[0] = minuend.components[0] - subtrahend;
    difference.components[1] = minuend.components[1] - subtrahend;
    difference.components[2] = minuend.components[2] - subtrahend;
    return difference;
}

/* Per-component multiplication of a vec3 by a vec3. */
static vec3 vec3_mul(vec3 multiplicand, vec3 multiplier)
{
    vec3 product;
    product.components[0] = multiplicand.components[0] * multiplier.components[0];
    product.components[1] = multiplicand.components[1] * multiplier.components[1];
    product.components[2] = multiplicand.components[2] * multiplier.components[2];
    return product;
}

/* Per-component multiplication of a vec3 and a scalar. */
static vec3 vec3_mul_scalar(vec3 multiplicand, real multiplier)
{
    vec3 product;
    product.components[0] = multiplicand.components[0] * multiplier;
    product.components[1] = multiplicand.components[1] * multiplier;
    product.components[2] = multiplicand.components[2] * multiplier;
    return product;
}

/* Per-component division of a vec3 by a vec3. */
static vec3 vec3_div(vec3 dividend, vec3 divisor)
{
    vec3 quotient;
    quotient.components[0] = dividend.components[0] / divisor.components[0];
    quotient.components[1] = dividend.components[1] / divisor.components[1];
    quotient.components[2] = dividend.components[2] / divisor.components[2];
    return quotient;
}

/* Per-component division of a vec3 by a scalar. */
static vec3 vec3_div_scalar(vec3 dividend, real divisor)
{
    vec3 quotient;
    quotient.components[0] = dividend.components[0] / divisor;
    quotient.components[1] = dividend.components[1] / divisor;
    quotient.components[2] = dividend.components[2] / divisor;
    return quotient;
}

/* Per-component vec3 to the power of a vec3. */
static vec3 vec3_pow(vec3 base, vec3 power)
{
    vec3 yield;
    yield.components[0] = real_pow(base.components[0], power.components[0]);
    yield.components[1] = real_pow(base.components[1], power.components[1]);
    yield.components[2] = real_pow(base.components[2], power.components[2]);
    return yield;
}

/* Per-component vec3 to the power of a scalar. */
static vec3 vec3_pow_scalar(vec3 base, real power)
{
    vec3 yield;
    yield.components[0] = real_pow(base.components[0], power);
    yield.components[1] = real_pow(base.components[1], power);
    yield.components[2] = real_pow(base.components[2], power);
    return yield;
}

/* Per-component principal square-root. */
static vec3 vec3_sqrt(vec3 radicand)
{
    vec3 principal;
    principal.components[0] = real_sqrt(radicand.components[0]);
    principal.components[1] = real_sqrt(radicand.components[1]);
    principal.components[2] = real_sqrt(radicand.components[2]);
    return principal;
}

/* Per-component reciprocal. */
static vec3 vec3_rcp(vec3 recipricand)
{
    vec3 ones        = vec3_init_from_1(1.f);
    vec3 reciprocal = vec3_div(ones, recipricand);
    return reciprocal;
}

/* Per-component reciprocal square-root. */
static vec3 vec3_rsqrt(vec3 radicand)
{
    vec3 square_root    = vec3_sqrt(radicand);
    vec3 reciprocal     = vec3_rcp(square_root);
    return reciprocal;
}

/* Per-component absolute-value. */
static vec3 vec3_abs(vec3 src0)
{
    vec3 rets;
    rets.components[0] = real_abs(src0.components[0]);
    rets.components[1] = real_abs(src0.components[1]);
    rets.components[2] = real_abs(src0.components[2]);
    return rets;
}

/* Per-component sine. */
static vec3 vec3_sin(vec3 theta)
{
    vec3 sine;
    sine.components[0] = real_sin(theta.components[0]);
    sine.components[1] = real_sin(theta.components[1]);
    sine.components[2] = real_sin(theta.components[2]);
    return sine;
}

/* Per-component cosine. */
static vec3 vec3_cos(vec3 theta)
{
    vec3 cosine;
    cosine.components[0] = real_cos(theta.components[0]);
    cosine.components[1] = real_cos(theta.components[1]);
    cosine.components[2] = real_cos(theta.components[2]);
    return cosine;
}

/* Per-component tangent. */
static vec3 vec3_tan(vec3 theta)
{
    vec3 tangent;
    tangent.components[0] = real_tan(theta.components[0]);
    tangent.components[1] = real_tan(theta.components[1]);
    tangent.components[2] = real_tan(theta.components[2]);
    return tangent;
}

/* Per-component arc-sine. */
static vec3 vec3_asin(vec3 theta)
{
    vec3 arc_sine;
    arc_sine.components[0] = real_asin(theta.components[0]);
    arc_sine.components[1] = real_asin(theta.components[1]);
    arc_sine.components[2] = real_asin(theta.components[2]);
    return arc_sine;
}

/* Per-component arc-cosine. */
static vec3 vec3_acos(vec3 theta)
{
    vec3 arc_cosine;
    arc_cosine.components[0] = real_acos(theta.components[0]);
    arc_cosine.components[1] = real_acos(theta.components[1]);
    arc_cosine.components[2] = real_acos(theta.components[2]);
    return arc_cosine;
}

/* Per-component arc-tangent. */
static vec3 vec3_atan(vec3 theta)
{
    vec3 arc_tangent;
    arc_tangent.components[0] = real_atan(theta.components[0]);
    arc_tangent.components[1] = real_atan(theta.components[1]);
    arc_tangent.components[2] = real_atan(theta.components[2]);
    return arc_tangent;
}

/* Per-component cosecant. */
static vec3 vec3_csc(vec3 theta)
{
    vec3 sine        = vec3_sin(theta);
    vec3 cosecant    = vec3_rcp(sine);
    return cosecant;
}

/* Per-component secant. */
static vec3 vec3_sec(vec3 theta)
{
    vec3 cosine = vec3_cos(theta);
    vec3 secant = vec3_rcp(cosine);
    return secant;
}

/* Per-component cotangent. */
static vec3 vec3_cot(vec3 theta)
{
    vec3 tangent    = vec3_tan(theta);
    vec3 cotangent  = vec3_rcp(tangent);
    return cotangent;
}

/* Per-component hyperbolic-sine. */
static vec3 vec3_sinh(vec3 theta)
{
    vec3 hyperbolic_sine;
    hyperbolic_sine.components[0] = real_sinh(theta.components[0]);
    hyperbolic_sine.components[1] = real_sinh(theta.components[1]);
    hyperbolic_sine.components[2] = real_sinh(theta.components[2]);
    return hyperbolic_sine;
}

/* Per-component hyperbolic-cosine. */
static vec3 vec3_cosh(vec3 theta)
{
    vec3 hyperbolic_cosine;
    hyperbolic_cosine.components[0] = real_cosh(theta.components[0]);
    hyperbolic_cosine.components[1] = real_cosh(theta.components[1]);
    hyperbolic_cosine.components[2] = real_cosh(theta.components[2]);
    return hyperbolic_cosine;
}

/* Per-component hyperbolic-tangent. */
static vec3 vec3_tanh(vec3 theta)
{
    vec3 hyperbolic_tangent;
    hyperbolic_tangent.components[0] = real_tanh(theta.components[0]);
    hyperbolic_tangent.components[1] = real_tanh(theta.components[1]);
    hyperbolic_tangent.components[2] = real_tanh(theta.components[2]);
    return hyperbolic_tangent;
}

/* Per-component hyperbolic-cosecant. */
static vec3 vec3_csch(vec3 theta)
{
    vec3 hyperbolic_sin          = vec3_sinh(theta);
    vec3 hyperbolic_cosecant    = vec3_rcp(hyperbolic_sin);
    return hyperbolic_cosecant;
}

/* Per-component hyperbolic-secant. */
static vec3 vec3_sech(vec3 theta)
{
    vec3 hyperbolic_cosine = vec3_cosh(theta);
    vec3 hyperbolic_secant = vec3_rcp(hyperbolic_cosine);
    return hyperbolic_secant;
}

/* Per-component hyperbolic-cotangent. */
static vec3 vec3_coth(vec3 theta)
{
    vec3 hyperbolic_tangent     = vec3_tanh(theta);
    vec3 hyperbolic_cotangent   = vec3_rcp(hyperbolic_tangent);
    return hyperbolic_cotangent;
}

/* True if *all* components are non-zero. */
static bool vec3_all(vec3 src0)
{
    bool rets = (
        (src0.components[0] != 0) &&
        (src0.components[1] != 0) &&
        (src0.components[2] != 0));
    return rets;
}

/* True if *any* components are non-zero. */
static bool vec3_any(vec3 src0)
{
    bool rets = (
        (src0.components[0] != 0) ||
        (src0.components[1] != 0) ||
        (src0.components[2] != 0));
    return rets;
}

/* 3-component dot product. */
static real vec3_dot(vec3 src0, vec3 src1)
{
    real dot_product;
    dot_product = (src0.components[0] * src1.components[0]) + (src0.components[1] * src1.components[1]) + (src0.components[2] * src1.components[2]);
    return dot_product;
}

/* Linear interpolation between two vec3 values. */
static vec3 vec3_lerp(vec3 src0, vec3 src1, real t)
{
    vec3 difference = vec3_sub(src1, src0);
    vec3 scaled = vec3_mul_scalar(difference, t);
    vec3 interpolated = vec3_add(src0, scaled);
    return interpolated;
}

/* Reflection vector through a normal (normal vector should be perpendicular to the surface, and cross
   through the intersection point. `surface_normal` must be normalized.
          ____________________________________
         |                 normal            |
         | reflection  \   |   / incident    |
         |              \  |  /              |
         |               \ | /               |
         |                \|/                |
         |   surface ------*------           |
         |___________________________________|
   http://developer.download.nvidia.com/CgTutorial/cg_tutorial_chapter07.html
*/
static vec3 vec3_reflect(vec3 incident, vec3 surface_normal)
{
    real dot_product    = 2.0f * vec3_dot(incident, surface_normal);
    vec3 product        = vec3_mul_scalar(surface_normal, dot_product);
    vec3 reflection     = vec3_sub(incident, product);
    return reflection;
}

/* Magnitude/Length */
static real vec3_magnitude(vec3 src0)
{
    real dot        = vec3_dot(src0, src0);
    real magnitude  = real_sqrt(dot);
    return magnitude;
}

/* Unit-vector */
static vec3 vec3_normalize(vec3 src0)
{
    real magnitude      = vec3_magnitude(src0);
    vec3 unit_vector    = vec3_div_scalar(src0, magnitude);
    return unit_vector;
}

/* Euclidean distance. */
static real vec3_distance(vec3 src0, vec3 src1)
{
    vec3 difference = vec3_sub(src0, src1);
    real distance   = vec3_magnitude(difference);
    return distance;
}

/* Angle between two vectors in radians. */
static real vec3_angle(vec3 src0, vec3 src1)
{
    real mag_a      = vec3_magnitude(src0);
    real mag_b      = vec3_magnitude(src1);
    real dot        = vec3_dot(src0, src1);
    real cos        = dot / (mag_a * mag_b);
    real radians    = real_acos(cos);
    return radians;
}

/* Per-component conversion from radians to degrees. */
static vec3 vec3_degrees(vec3 radians)
{
    vec3 degrees;
    degrees.components[0] = radians.components[0] * VECTORS_RAD2DEG;
    degrees.components[1] = radians.components[1] * VECTORS_RAD2DEG;
    degrees.components[2] = radians.components[2] * VECTORS_RAD2DEG;
    return degrees;
}

/* Per-component conversion from degrees to radians. */
static vec3 vec3_radians(vec3 degrees)
{
    vec3 radians;
    radians.components[0] = degrees.components[0] * VECTORS_DEG2RAD;
    radians.components[1] = degrees.components[1] * VECTORS_DEG2RAD;
    radians.components[2] = degrees.components[2] * VECTORS_DEG2RAD;
    return radians;
}

/* 3-component cross product of two vec3. */
static vec3 vec3_cross(vec3 src0, vec3 src1)
{
    vec3 cross_product;
    cross_product.components[0] = (src0.components[1] * src1.components[2]) - (src1.components[1] * src0.components[2]);
    cross_product.components[1] = (src0.components[2] * src1.components[0]) - (src1.components[2] * src0.components[0]);
    cross_product.components[2] = (src0.components[0] * src1.components[1]) - (src1.components[0] * src0.components[1]);
    return cross_product;
}

/* Per-component computation of closest integer rounded towards -inf. */
static vec3 vec3_floor(vec3 src0)
{
    vec3 floored;
    floored.components[0] = real_floor(src0.components[0]);
    floored.components[1] = real_floor(src0.components[1]);
    floored.components[2] = real_floor(src0.components[2]);
    return floored;
}

/* Per-component computation of closest integer rounded towards +inf. */
static vec3 vec3_ceil(vec3 src0)
{
    vec3 ceiling;
    ceiling.components[0] = real_ceil(src0.components[0]);
    ceiling.components[1] = real_ceil(src0.components[1]);
    ceiling.components[2] = real_ceil(src0.components[2]);
    return ceiling;
}

/* Per-component computation of closest integer rounded towards 0. */
static vec3 vec3_trunc(vec3 src0)
{
    vec3 truncated;
    truncated.components[0] = real_trunc(src0.components[0]);
    truncated.components[1] = real_trunc(src0.components[1]);
    truncated.components[2] = real_trunc(src0.components[2]);
    return truncated;
}

/* Per-component fractional component (src0 - floor(src0)). */
static vec3 vec3_frac(vec3 src0)
{
    vec3 rets;
    rets.components[0] = src0.components[0] - real_floor(src0.components[0]);
    rets.components[1] = src0.components[1] - real_floor(src0.components[1]);
    rets.components[2] = src0.components[2] - real_floor(src0.components[2]);
    return rets;
}

/* Per-component maximum of two vec3. */
static vec3 vec3_max(vec3 src0, vec3 src1)
{
    vec3 maximum;
    maximum.components[0] = real_max(src0.components[0], src1.components[0]);
    maximum.components[1] = real_max(src0.components[1], src1.components[1]);
    maximum.components[2] = real_max(src0.components[2], src1.components[2]);
    return maximum;
}

/* Per-component maximum of a vec3 and a scalar. */
static vec3 vec3_max_scalar(vec3 src0, real src1)
{
    vec3 maximum;
    maximum.components[0] = real_max(src0.components[0], src1);
    maximum.components[1] = real_max(src0.components[1], src1);
    maximum.components[2] = real_max(src0.components[2], src1);
    return maximum;
}

/* Per-component minimum of two vec3. */
static vec3 vec3_min(vec3 src0, vec3 src1)
{
    vec3 minimum;
    minimum.components[0] = real_min(src0.components[0], src1.components[0]);
    minimum.components[1] = real_min(src0.components[1], src1.components[1]);
    minimum.components[2] = real_min(src0.components[2], src1.components[2]);
    return minimum;
}

/* Per-component minimum of a vec3 and a scalar. */
static vec3 vec3_min_scalar(vec3 src0, real src1)
{
    vec3 minimum;
    minimum.components[0] = real_min(src0.components[0], src1);
    minimum.components[1] = real_min(src0.components[1], src1);
    minimum.components[2] = real_min(src0.components[2], src1);
    return minimum;
}

/* Per-component clamp of src0 into the range of vectors (minimum..maximum). */
static vec3 vec3_clamp(vec3 src0, vec3 minimum, vec3 maximum)
{
    vec3 clamped_lower  = vec3_max(src0, minimum);
    vec3 clamped        = vec3_min(clamped_lower, maximum);
    return clamped;
}

/* Per-component clamp of src0 into the range of scalars (minimum..maximum). */
static vec3 vec3_clamp_scalar(vec3 src0, real minimum, real maximum)
{
    vec3 clamped_lower  = vec3_max_scalar(src0, minimum);
    vec3 clamped        = vec3_min_scalar(clamped_lower, maximum);
    return clamped;
}


/* Swizzle (swap) the order of components. */
static vec4 vec4_swizzle(vec4 src0, u32 a, u32 b, u32 c, u32 d)
{
    vec4 swizzled;
    swizzled.components[0] = src0.components[a & 0x3];
    swizzled.components[1] = src0.components[b & 0x3];
    swizzled.components[2] = src0.components[c & 0x3];
    swizzled.components[3] = src0.components[d & 0x3];
    return swizzled;
}

/* Selects components from src0 if the corresponding bit in the mask is set, otherwise selects from src1. */
static vec4 vec4_mask(vec4 src0, vec4 src1, u32 mask)
{
    vec4 masked;
    masked.components[0] = mask & MASK_0 ? src0.components[0] : src1.components[0];
    masked.components[1] = mask & MASK_1 ? src0.components[1] : src1.components[1];
    masked.components[2] = mask & MASK_2 ? src0.components[2] : src1.components[2];
    masked.components[3] = mask & MASK_3 ? src0.components[3] : src1.components[3];
    return masked;
}

/* Initialize a vec4 from four real's, where each component maps to an argument. */
static vec4 vec4_init_from_4(real src0, real src1, real src2, real src3)
{
    vec4 vector;
    vector.components[0] = src0;
    vector.components[1] = src1;
    vector.components[2] = src2;
    vector.components[3] = src3;
    return vector;
}

/* Initialize a vec4 from one real, where all components map to the argument. */
static vec4 vec4_init_from_1(real src0)
{
    vec4 vector;
    vector.components[0] = src0;
    vector.components[1] = src0;
    vector.components[2] = src0;
    vector.components[3] = src0;
    return vector;
}

/* Per-component negation (sign flip). */
static vec4 vec4_negate(vec4 src0)
{
    vec4 negative;
    negative.components[0] = -src0.components[0];
    negative.components[1] = -src0.components[1];
    negative.components[2] = -src0.components[2];
    negative.components[3] = -src0.components[3];
    return negative;
}

/* Per-component addition of two vec4. */
static vec4 vec4_add(vec4 augend, vec4 addend)
{
    vec4 sum;
    sum.components[0] = augend.components[0] + addend.components[0];
    sum.components[1] = augend.components[1] + addend.components[1];
    sum.components[2] = augend.components[2] + addend.components[2];
    sum.components[3] = augend.components[3] + addend.components[3];
    return sum;
}

/* Per-component addition of a vec4 and a scalar. */
static vec4 vec4_add_scalar(vec4 augend, real addend)
{
    vec4 sum;
    sum.components[0] = augend.components[0] + addend;
    sum.components[1] = augend.components[1] + addend;
    sum.components[2] = augend.components[2] + addend;
    sum.components[3] = augend.components[3] + addend;
    return sum;
}

/* Per-component subtraction of vec. */
static vec4 vec4_sub(vec4 minuend, vec4 subtrahend)
{
    vec4 difference;
    difference.components[0] = minuend.components[0] - subtrahend.components[0];
    difference.components[1] = minuend.components[1] - subtrahend.components[1];
    difference.components[2] = minuend.components[2] - subtrahend.components[2];
    difference.components[3] = minuend.components[3] - subtrahend.components[3];
    return difference;
}

/* Per-component subtraction of a scalar from a vec4. */
static vec4 vec4_sub_scalar(vec4 minuend, real subtrahend)
{
    vec4 difference;
    difference.components[0] = minuend.components[0] - subtrahend;
    difference.components[1] = minuend.components[1] - subtrahend;
    difference.components[2] = minuend.components[2] - subtrahend;
    difference.components[3] = minuend.components[3] - subtrahend;
    return difference;
}

/* Per-component multiplication of a vec4 by a vec4. */
static vec4 vec4_mul(vec4 multiplicand, vec4 multiplier)
{
    vec4 product;
    product.components[0] = multiplicand.components[0] * multiplier.components[0];
    product.components[1] = multiplicand.components[1] * multiplier.components[1];
    product.components[2] = multiplicand.components[2] * multiplier.components[2];
    product.components[3] = multiplicand.components[3] * multiplier.components[3];
    return product;
}

/* Per-component multiplication of a vec4 and a scalar. */
static vec4 vec4_mul_scalar(vec4 multiplicand, real multiplier)
{
    vec4 product;
    product.components[0] = multiplicand.components[0] * multiplier;
    product.components[1] = multiplicand.components[1] * multiplier;
    product.components[2] = multiplicand.components[2] * multiplier;
    product.components[3] = multiplicand.components[3] * multiplier;
    return product;
}

/* Per-component division of a vec4 by a vec4. */
static vec4 vec4_div(vec4 dividend, vec4 divisor)
{
    vec4 quotient;
    quotient.components[0] = dividend.components[0] / divisor.components[0];
    quotient.components[1] = dividend.components[1] / divisor.components[1];
    quotient.components[2] = dividend.components[2] / divisor.components[2];
    quotient.components[3] = dividend.components[3] / divisor.components[3];
    return quotient;
}

/* Per-component division of a vec4 by a scalar. */
static vec4 vec4_div_scalar(vec4 dividend, real divisor)
{
    vec4 quotient;
    quotient.components[0] = dividend.components[0] / divisor;
    quotient.components[1] = dividend.components[1] / divisor;
    quotient.components[2] = dividend.components[2] / divisor;
    quotient.components[3] = dividend.components[3] / divisor;
    return quotient;
}

/* Per-component vec4 to the power of a vec4. */
static vec4 vec4_pow(vec4 base, vec4 power)
{
    vec4 yield;
    yield.components[0] = real_pow(base.components[0], power.components[0]);
    yield.components[1] = real_pow(base.components[1], power.components[1]);
    yield.components[2] = real_pow(base.components[2], power.components[2]);
    yield.components[3] = real_pow(base.components[3], power.components[3]);
    return yield;
}

/* Per-component vec4 to the power of a scalar. */
static vec4 vec4_pow_scalar(vec4 base, real power)
{
    vec4 yield;
    yield.components[0] = real_pow(base.components[0], power);
    yield.components[1] = real_pow(base.components[1], power);
    yield.components[2] = real_pow(base.components[2], power);
    yield.components[3] = real_pow(base.components[3], power);
    return yield;
}

/* Per-component principal square-root. */
static vec4 vec4_sqrt(vec4 radicand)
{
    vec4 principal;
    principal.components[0] = real_sqrt(radicand.components[0]);
    principal.components[1] = real_sqrt(radicand.components[1]);
    principal.components[2] = real_sqrt(radicand.components[2]);
    principal.components[3] = real_sqrt(radicand.components[3]);
    return principal;
}

/* Per-component reciprocal. */
static vec4 vec4_rcp(vec4 recipricand)
{
    vec4 one_vector = vec4_init_from_1(1.f);
    vec4 reciprocal = vec4_div(one_vector, recipricand);
    return reciprocal;
}

/* Per-component reciprocal square-root. */
static vec4 vec4_rsqrt(vec4 radicand)
{
    vec4 square_root = vec4_sqrt(radicand);
    vec4 reciprocal = vec4_rcp(square_root);
    return reciprocal;
}

/* Per-component absolute-value. */
static vec4 vec4_abs(vec4 src0)
{
    vec4 rets;
    rets.components[0] = real_abs(src0.components[0]);
    rets.components[1] = real_abs(src0.components[1]);
    rets.components[2] = real_abs(src0.components[2]);
    rets.components[3] = real_abs(src0.components[3]);
    return rets;
}

/* Per-component sine. */
static vec4 vec4_sin(vec4 theta)
{
    vec4 sine;
    sine.components[0] = real_sin(theta.components[0]);
    sine.components[1] = real_sin(theta.components[1]);
    sine.components[2] = real_sin(theta.components[2]);
    sine.components[3] = real_sin(theta.components[3]);
    return sine;
}

/* Per-component cosine. */
static vec4 vec4_cos(vec4 theta)
{
    vec4 cosine;
    cosine.components[0] = real_cos(theta.components[0]);
    cosine.components[1] = real_cos(theta.components[1]);
    cosine.components[2] = real_cos(theta.components[2]);
    cosine.components[3] = real_cos(theta.components[3]);
    return cosine;
}

/* Per-component tangent. */
static vec4 vec4_tan(vec4 theta)
{
    vec4 tangent;
    tangent.components[0] = real_tan(theta.components[0]);
    tangent.components[1] = real_tan(theta.components[1]);
    tangent.components[2] = real_tan(theta.components[2]);
    tangent.components[3] = real_tan(theta.components[3]);
    return tangent;
}

/* Per-component arc-sine. */
static vec4 vec4_asin(vec4 theta)
{
    vec4 arc_sine;
    arc_sine.components[0] = real_asin(theta.components[0]);
    arc_sine.components[1] = real_asin(theta.components[1]);
    arc_sine.components[2] = real_asin(theta.components[2]);
    arc_sine.components[3] = real_asin(theta.components[3]);
    return arc_sine;
}

/* Per-component arc-cosine. */
static vec4 vec4_acos(vec4 theta)
{
    vec4 arc_cosine;
    arc_cosine.components[0] = real_acos(theta.components[0]);
    arc_cosine.components[1] = real_acos(theta.components[1]);
    arc_cosine.components[2] = real_acos(theta.components[2]);
    arc_cosine.components[3] = real_acos(theta.components[3]);
    return arc_cosine;
}

/* Per-component arc-tangent. */
static vec4 vec4_atan(vec4 theta)
{
    vec4 arc_tangent;
    arc_tangent.components[0] = real_atan(theta.components[0]);
    arc_tangent.components[1] = real_atan(theta.components[1]);
    arc_tangent.components[2] = real_atan(theta.components[2]);
    arc_tangent.components[3] = real_atan(theta.components[3]);
    return arc_tangent;
}

/* Per-component cosecant. */
static vec4 vec4_csc(vec4 theta)
{
    vec4 sine = vec4_sin(theta);
    vec4 cosecant = vec4_rcp(sine);
    return cosecant;
}

/* Per-component secant. */
static vec4 vec4_sec(vec4 theta)
{
    vec4 cosine = vec4_cos(theta);
    vec4 secant = vec4_rcp(cosine);
    return secant;
}

/* Per-component cotangent. */
static vec4 vec4_cot(vec4 theta)
{
    vec4 tangent = vec4_tan(theta);
    vec4 cotangent = vec4_rcp(tangent);
    return cotangent;
}

/* Per-component hyperbolic-sine. */
static vec4 vec4_sinh(vec4 theta)
{
    vec4 hyperbolic_sine;
    hyperbolic_sine.components[0] = real_sinh(theta.components[0]);
    hyperbolic_sine.components[1] = real_sinh(theta.components[1]);
    hyperbolic_sine.components[2] = real_sinh(theta.components[2]);
    hyperbolic_sine.components[3] = real_sinh(theta.components[3]);
    return hyperbolic_sine;
}

/* Per-component hyperbolic-cosine. */
static vec4 vec4_cosh(vec4 theta)
{
    vec4 hyperbolic_cosine;
    hyperbolic_cosine.components[0] = real_cosh(theta.components[0]);
    hyperbolic_cosine.components[1] = real_cosh(theta.components[1]);
    hyperbolic_cosine.components[2] = real_cosh(theta.components[2]);
    hyperbolic_cosine.components[3] = real_cosh(theta.components[3]);
    return hyperbolic_cosine;
}

/* Per-component hyperbolic-tangent. */
static vec4 vec4_tanh(vec4 theta)
{
    vec4 hyperbolic_tangent;
    hyperbolic_tangent.components[0] = real_tanh(theta.components[0]);
    hyperbolic_tangent.components[1] = real_tanh(theta.components[1]);
    hyperbolic_tangent.components[2] = real_tanh(theta.components[2]);
    hyperbolic_tangent.components[3] = real_tanh(theta.components[3]);
    return hyperbolic_tangent;
}

/* Per-component hyperbolic-cosecant. */
static vec4 vec4_csch(vec4 theta)
{
    vec4 hyperbolic_sin = vec4_sinh(theta);
    vec4 hyperbolic_cosecant = vec4_rcp(hyperbolic_sin);
    return hyperbolic_cosecant;
}

/* Per-component hyperbolic-secant. */
static vec4 vec4_sech(vec4 theta)
{
    vec4 hyperbolic_cosine = vec4_cosh(theta);
    vec4 hyperbolic_secant = vec4_rcp(hyperbolic_cosine);
    return hyperbolic_secant;
}

/* Per-component hyperbolic-cotangent. */
static vec4 vec4_coth(vec4 theta)
{
    vec4 hyperbolic_tangent = vec4_tanh(theta);
    vec4 hyperbolic_cotangent = vec4_rcp(hyperbolic_tangent);
    return hyperbolic_cotangent;
}

/* True if *all* components are non-zero. */
static bool vec4_all(vec4 src0)
{
    bool rets = (
        (src0.components[0] != 0) &&
        (src0.components[1] != 0) &&
        (src0.components[2] != 0) &&
        (src0.components[3] != 0));
    return rets;
}

/* True if *any* components are non-zero. */
static bool vec4_any(vec4 src0)
{
    bool rets = (
        (src0.components[0] != 0) ||
        (src0.components[1] != 0) ||
        (src0.components[2] != 0) ||
        (src0.components[3] != 0));
    return rets;
}

/* Four-component dot product. */
static real vec4_dot(vec4 src0, vec4 src1)
{
    real dot_product = 0.0f;
    dot_product += (src0.components[0] * src1.components[0]);
    dot_product += (src0.components[1] * src1.components[1]);
    dot_product += (src0.components[2] * src1.components[2]);
    dot_product += (src0.components[3] * src1.components[3]);
    return dot_product;
}

/* Linear interpolation between two vec4 values. */
static vec4 vec4_lerp(vec4 src0, vec4 src1, real t)
{
    vec4 difference = vec4_sub(src1, src0);
    vec4 scaled = vec4_mul_scalar(difference, t);
    vec4 interpolated = vec4_add(src0, scaled);
    return interpolated;
}

/* Reflection vector through a normal (normal vector should be perpendicular to the surface, and cross
   through the intersection point.
          ____________________________________
         |                 normal            |
         | reflection  \   |   / incident    |
         |              \  |  /              |
         |               \ | /               |
         |                \|/                |
         |   surface ------*------           |
         |___________________________________|
*/
static vec4 vec4_reflect(vec4 incident, vec4 surface_normal)
{
    real dot_product    = 2.0f * vec4_dot(incident, surface_normal);
    vec4 product        = vec4_mul_scalar(surface_normal, dot_product);
    vec4 reflection     = vec4_sub(incident, product);
    return reflection;
}

/* Magnitude/Length */
static real vec4_magnitude(vec4 src0)
{
    real dot        = vec4_dot(src0, src0);
    real magnitude  = real_sqrt(dot);
    return magnitude;
}

/* Unit-vector */
static vec4 vec4_normalize(vec4 src0)
{
    real magnitude      = vec4_magnitude(src0);
    vec4 unit_vector    = vec4_div_scalar(src0, magnitude);
    return unit_vector;
}

/* Euclidean distance. */
static real vec4_distance(vec4 src0, vec4 src1)
{
    vec4 difference = vec4_sub(src0, src1);
    real distance   = vec4_magnitude(difference);
    return distance;
}

/* Angle between two vectors in radians. */
static real vec4_angle(vec4 src0, vec4 src1)
{
    real mag_a      = vec4_magnitude(src0);
    real mag_b      = vec4_magnitude(src1);
    real dot        = vec4_dot(src0, src1);
    real cos        = dot / (mag_a * mag_b);
    real radians    = real_acos(cos);
    return radians;
}

/* Per-component conversion from radians to degrees. */
static vec4 vec4_degrees(vec4 radians)
{
    vec4 degrees;
    degrees.components[0] = radians.components[0] * VECTORS_RAD2DEG;
    degrees.components[1] = radians.components[1] * VECTORS_RAD2DEG;
    degrees.components[2] = radians.components[2] * VECTORS_RAD2DEG;
    degrees.components[3] = radians.components[3] * VECTORS_RAD2DEG;
    return degrees;
}

/* Per-component conversion from degrees to radians. */
static vec4 vec4_radians(vec4 degrees)
{
    vec4 radians;
    radians.components[0] = degrees.components[0] * VECTORS_DEG2RAD;
    radians.components[1] = degrees.components[1] * VECTORS_DEG2RAD;
    radians.components[2] = degrees.components[2] * VECTORS_DEG2RAD;
    radians.components[3] = degrees.components[3] * VECTORS_DEG2RAD;
    return radians;
}

/* 3-component cross product of two vec4. */
static vec4 vec4_cross(vec4 src0, vec4 src1)
{
    vec4 cross_product;
    cross_product.components[0] = (src0.components[1] * src1.components[2]) - (src1.components[1] * src0.components[2]);
    cross_product.components[1] = (src0.components[2] * src1.components[0]) - (src1.components[2] * src0.components[0]);
    cross_product.components[2] = (src0.components[0] * src1.components[1]) - (src1.components[0] * src0.components[1]);
    cross_product.components[3] = 1.0f;
    return cross_product;
}

/* Per-component computation of closest integer rounded towards -inf. */
static vec4 vec4_floor(vec4 src0)
{
    vec4 floored;
    floored.components[0] = real_floor(src0.components[0]);
    floored.components[1] = real_floor(src0.components[1]);
    floored.components[2] = real_floor(src0.components[2]);
    floored.components[3] = real_floor(src0.components[3]);
    return floored;
}

/* Per-component computation of closest integer rounded towards +inf. */
static vec4 vec4_ceil(vec4 src0)
{
    vec4 ceiling;
    ceiling.components[0] = real_ceil(src0.components[0]);
    ceiling.components[1] = real_ceil(src0.components[1]);
    ceiling.components[2] = real_ceil(src0.components[2]);
    ceiling.components[3] = real_ceil(src0.components[3]);
    return ceiling;
}

/* Per-component computation of closest integer rounded towards 0. */
static vec4 vec4_trunc(vec4 src0)
{
    vec4 truncated;
    truncated.components[0] = real_trunc(src0.components[0]);
    truncated.components[1] = real_trunc(src0.components[1]);
    truncated.components[2] = real_trunc(src0.components[2]);
    truncated.components[3] = real_trunc(src0.components[3]);
    return truncated;
}

/* Per-component fractional component (src0 - floor(src0)). */
static vec4 vec4_frac(vec4 src0)
{
    vec4 rets;
    rets.components[0] = src0.components[0] - real_floor(src0.components[0]);
    rets.components[1] = src0.components[1] - real_floor(src0.components[1]);
    rets.components[2] = src0.components[2] - real_floor(src0.components[2]);
    rets.components[3] = src0.components[3] - real_floor(src0.components[3]);
    return rets;
}

/* Per-component maximum of two vec4. */
static vec4 vec4_max(vec4 src0, vec4 src1)
{
    vec4 maximum;
    maximum.components[0] = real_max(src0.components[0], src1.components[0]);
    maximum.components[1] = real_max(src0.components[1], src1.components[1]);
    maximum.components[2] = real_max(src0.components[2], src1.components[2]);
    maximum.components[3] = real_max(src0.components[3], src1.components[3]);
    return maximum;
}

/* Per-component maximum of a vec4 and a scalar. */
static vec4 vec4_max_scalar(vec4 src0, real src1)
{
    vec4 maximum;
    maximum.components[0] = real_max(src0.components[0], src1);
    maximum.components[1] = real_max(src0.components[1], src1);
    maximum.components[2] = real_max(src0.components[2], src1);
    maximum.components[3] = real_max(src0.components[3], src1);
    return maximum;
}

/* Per-component minimum of two vec4. */
static vec4 vec4_min(vec4 src0, vec4 src1)
{
    vec4 minimum;
    minimum.components[0] = real_min(src0.components[0], src1.components[0]);
    minimum.components[1] = real_min(src0.components[1], src1.components[1]);
    minimum.components[2] = real_min(src0.components[2], src1.components[2]);
    minimum.components[3] = real_min(src0.components[3], src1.components[3]);
    return minimum;
}

/* Per-component minimum of a vec4 and a scalar. */
static vec4 vec4_min_scalar(vec4 src0, real src1)
{
    vec4 minimum;
    minimum.components[0] = real_min(src0.components[0], src1);
    minimum.components[1] = real_min(src0.components[1], src1);
    minimum.components[2] = real_min(src0.components[2], src1);
    minimum.components[3] = real_min(src0.components[3], src1);
    return minimum;
}

/* Per-component clamp of src0 into the range of vectors (minimum..maximum). */
static vec4 vec4_clamp(vec4 src0, vec4 minimum, vec4 maximum)
{
    vec4 clamped_lower  = vec4_max(src0, minimum);
    vec4 clamped        = vec4_min(clamped_lower, maximum);
    return clamped;
}

/* Per-component clamp of src0 into the range of scalars (minimum..maximum). */
static vec4 vec4_clamp_scalar(vec4 src0, real minimum, real maximum)
{
    vec4 clamped_lower  = vec4_max_scalar(src0, minimum);
    vec4 clamped        = vec4_min_scalar(clamped_lower, maximum);
    return clamped;
}

/* Inverts a color stored in a vector (color channels must be scaled to 0..1) */
static vec4 vec4_invert_color(vec4 color)
{
    vec4 inverted_color;
    inverted_color.color.r = 1.0f - color.color.r;
    inverted_color.color.g = 1.0f - color.color.g;
    inverted_color.color.b = 1.0f - color.color.b;
    inverted_color.color.a = color.color.a;
    return inverted_color;
}

/* -------------------------------------------------------------------------
   3x3 matrix operations
   ------------------------------------------------------------------------- */

/* Construct a mat3 from a quaternion. */
static mat3 mat3_from_quat(vec4 q)
{
    real xx = q.position.x * q.position.x;
    real yy = q.position.y * q.position.y;
    real zz = q.position.z * q.position.z;
    real xy = q.position.x * q.position.y;
    real xz = q.position.x * q.position.z;
    real yz = q.position.y * q.position.z;
    real wx = q.rotation.w * q.position.x;
    real wy = q.rotation.w * q.position.y;
    real wz = q.rotation.w * q.position.z;
    mat3 m;
    m.data[0] = 1.0f - 2.0f * (yy + zz);
    m.data[1] = 2.0f * (xy - wz);
    m.data[2] = 2.0f * (xz + wy);
    m.data[3] = 2.0f * (xy + wz);
    m.data[4] = 1.0f - 2.0f * (xx + zz);
    m.data[5] = 2.0f * (yz - wx);
    m.data[6] = 2.0f * (xz - wy);
    m.data[7] = 2.0f * (yz + wx);
    m.data[8] = 1.0f - 2.0f * (xx + yy);
    return m;
}

/* Transpose a mat3 (swap rows and columns). */
static mat3 mat3_transpose(mat3 m)
{
    mat3 t;
    t.data[0] = m.data[0];
    t.data[1] = m.data[3];
    t.data[2] = m.data[6];
    t.data[3] = m.data[1];
    t.data[4] = m.data[4];
    t.data[5] = m.data[7];
    t.data[6] = m.data[2];
    t.data[7] = m.data[5];
    t.data[8] = m.data[8];
    return t;
}

/* Multiply two mat3 matrices. */
static mat3 mat3_mul(mat3 a, mat3 b)
{
    mat3 r;
    i32 i, j, k;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            real sum = 0;
            for (k = 0; k < 3; k++)
            {
                sum += a.data[i * 3 + k] * b.data[k * 3 + j];
            }
            r.data[i * 3 + j] = sum;
        }
    }
    return r;
}

/* Multiply a mat3 by a vec3. */
static vec3 mat3_mul_vec3(mat3 m, vec3 v)
{
    vec3 result;
    result.position.x = m.data[0] * v.position.x + m.data[1] * v.position.y + m.data[2] * v.position.z;
    result.position.y = m.data[3] * v.position.x + m.data[4] * v.position.y + m.data[5] * v.position.z;
    result.position.z = m.data[6] * v.position.x + m.data[7] * v.position.y + m.data[8] * v.position.z;
    return result;
}

/* Inverse of a diagonal 3x3 matrix.
   Assumes data[1],data[2],data[3],data[5],data[6],data[7] are zero.
   Returns a mat3 with reciprocals on the diagonal (or zero where original is zero). */
static mat3 mat3_inverse_diagonal(mat3 m) {
    mat3 r;
    r.data[0] = m.data[0] != 0.0f ? 1.0f / m.data[0] : 0.0f;
    r.data[1] = 0.0f; r.data[2] = 0.0f;
    r.data[3] = 0.0f;
    r.data[4] = m.data[4] != 0.0f ? 1.0f / m.data[4] : 0.0f;
    r.data[5] = 0.0f;
    r.data[6] = 0.0f; r.data[7] = 0.0f;
    r.data[8] = m.data[8] != 0.0f ? 1.0f / m.data[8] : 0.0f;
    return r;
}

/* -------------------------------------------------------------------------
   4x4 matrix operations
   ------------------------------------------------------------------------- */

/* Create an identity mat4 (1's on diagonal, 0's elsewhere). */
static mat4 mat4_identity(void)
{
    mat4 r;
    i32 i;
    for (i = 0; i < 16; i++)
    {
        r.data[i] = 0;
    }
    r.transpose[0][0] = 1;
    r.transpose[1][1] = 1;
    r.transpose[2][2] = 1;
    r.transpose[3][3] = 1;
    return r;
}

/* Multiply two mat4 matrices. */
static mat4 mat4_mul(mat4 a, mat4 b)
{
    mat4 r;
    i32 i, j, k;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            r.transpose[i][j] = 0;
            for (k = 0; k < 4; k++)
            {
                r.transpose[i][j] += a.transpose[i][k] * b.transpose[k][j];
            }
        }
    }
    return r;
}

/* Multiply a mat4 by a vec4. */
static vec4 mat4_mul_vec4(mat4 m, vec4 v)
{
    vec4 result;
    result.position.x = m.transpose[0][0] * v.position.x + m.transpose[0][1] * v.position.y + m.transpose[0][2] * v.position.z + m.transpose[0][3] * v.rotation.w;
    result.position.y = m.transpose[1][0] * v.position.x + m.transpose[1][1] * v.position.y + m.transpose[1][2] * v.position.z + m.transpose[1][3] * v.rotation.w;
    result.position.z = m.transpose[2][0] * v.position.x + m.transpose[2][1] * v.position.y + m.transpose[2][2] * v.position.z + m.transpose[2][3] * v.rotation.w;
    result.rotation.w = m.transpose[3][0] * v.position.x + m.transpose[3][1] * v.position.y + m.transpose[3][2] * v.position.z + m.transpose[3][3] * v.rotation.w;
    return result;
}

/* Create a perspective projection mat4. */
static mat4 mat4_perspective(real fov_y, real aspect, real near_plane, real far_plane)
{
    mat4 r;
    real tan_half_fov;
    i32 i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            r.transpose[i][j] = 0;
        }
    }
    tan_half_fov = real_tan(fov_y * 0.5f);
    r.transpose[0][0] = 1.0f / (aspect * tan_half_fov);
    r.transpose[1][1] = 1.0f / tan_half_fov;
    r.transpose[2][2] = (far_plane + near_plane) / (near_plane - far_plane);
    r.transpose[2][3] = (2.0f * far_plane * near_plane) / (near_plane - far_plane);
    r.transpose[3][2] = -1.0f;
    return r;
}

/* Create a view matrix looking at a target. */
static mat4 mat4_lookat(vec3 eye, vec3 center, vec3 up) {
    vec3 forward, side, up_cross;
    mat4 r;
    real forward_len;

    forward = vec3_sub(center, eye);
    forward_len = vec3_magnitude(forward);
    if (forward_len < VECTORS_QUAT_EPSILON) {
        forward = vec3_init_from_3(0.0f, 0.0f, -1.0f);
    } else {
        forward = vec3_div_scalar(forward, forward_len);
    }

    side = vec3_cross(forward, up);
    side = vec3_normalize(side);
    up_cross = vec3_cross(side, forward);   /* already unit length */

    r.transpose[0][0] = side.position.x;
    r.transpose[0][1] = side.position.y;
    r.transpose[0][2] = side.position.z;
    r.transpose[0][3] = -vec3_dot(side, eye);      /* <-- translation X */

    r.transpose[1][0] = up_cross.position.x;
    r.transpose[1][1] = up_cross.position.y;
    r.transpose[1][2] = up_cross.position.z;
    r.transpose[1][3] = -vec3_dot(up_cross, eye);   /* <-- translation Y */

    r.transpose[2][0] = -forward.position.x;
    r.transpose[2][1] = -forward.position.y;
    r.transpose[2][2] = -forward.position.z;
    r.transpose[2][3] =  vec3_dot(forward, eye);     /* <-- translation Z */

    r.transpose[3][0] = 0.0f;
    r.transpose[3][1] = 0.0f;
    r.transpose[3][2] = 0.0f;
    r.transpose[3][3] = 1.0f;

    return r;
}

/* Identity quaternion representing no rotation. */
static vec4 quat_identity(void)
{
    return vec4_init_from_4(0.0f, 0.0f, 0.0f, 1.0f);
}

/* Quaternion conjugate. */
static vec4 quat_conjugate(vec4 src0)
{
    return vec4_init_from_4(-src0.rotation.i, -src0.rotation.j, -src0.rotation.k, src0.rotation.w);
}

/* Multiplicative inverse of a quaternion. */
static vec4 quat_inverse(vec4 src0)
{
    real magnitude_squared = vec4_dot(src0, src0);
    vec4 conjugate = quat_conjugate(src0);
    vec4 inverse = vec4_div_scalar(conjugate, magnitude_squared);
    return inverse;
}

/* Hamilton product of two quaternions. */
static vec4 quat_mul(vec4 multiplicand, vec4 multiplier)
{
    vec4 product;
    product.rotation.i = (multiplicand.rotation.w * multiplier.rotation.i) + (multiplicand.rotation.i * multiplier.rotation.w) + (multiplicand.rotation.j * multiplier.rotation.k) - (multiplicand.rotation.k * multiplier.rotation.j);
    product.rotation.j = (multiplicand.rotation.w * multiplier.rotation.j) - (multiplicand.rotation.i * multiplier.rotation.k) + (multiplicand.rotation.j * multiplier.rotation.w) + (multiplicand.rotation.k * multiplier.rotation.i);
    product.rotation.k = (multiplicand.rotation.w * multiplier.rotation.k) + (multiplicand.rotation.i * multiplier.rotation.j) - (multiplicand.rotation.j * multiplier.rotation.i) + (multiplicand.rotation.k * multiplier.rotation.w);
    product.rotation.w = (multiplicand.rotation.w * multiplier.rotation.w) - (multiplicand.rotation.i * multiplier.rotation.i) - (multiplicand.rotation.j * multiplier.rotation.j) - (multiplicand.rotation.k * multiplier.rotation.k);
    return product;
}

/* Construct a quaternion from an axis and an angle in radians. */
static vec4 quat_from_axis_angle(vec3 axis, real radians)
{
    real half_angle = radians * 0.5f;
    real sin_half = real_sin(half_angle);
    real cos_half = real_cos(half_angle);
    vec3 unit_axis = vec3_normalize(axis);
    return vec4_init_from_4(unit_axis.rotation.i * sin_half, unit_axis.rotation.j * sin_half, unit_axis.rotation.k * sin_half, cos_half);
}

/* Extract the axis and angle in radians from a quaternion, returned as (i, j, k, radians). */
static vec4 quat_to_axis_angle(vec4 rotation)
{
    vec4 normalized = vec4_normalize(rotation);
    real half_angle = real_acos(normalized.rotation.w);
    real sin_half = real_sqrt(real_max(0.0f, 1.0f - (normalized.rotation.w * normalized.rotation.w)));

    if (sin_half <= VECTORS_QUAT_EPSILON)
    {
        return vec4_init_from_4(1.0f, 0.0f, 0.0f, half_angle * 2.0f);
    }

    return vec4_init_from_4(
        normalized.rotation.i / sin_half,
        normalized.rotation.j / sin_half,
        normalized.rotation.k / sin_half,
        half_angle * 2.0f);
}

/* True if a quaternion has unit length within a small epsilon. */
static bool quat_is_normalized(vec4 rotation)
{
    real magnitude_squared = vec4_dot(rotation, rotation);
    return real_abs(magnitude_squared - 1.0f) <= VECTORS_QUAT_EPSILON;
}

/* Construct the shortest-arc quaternion rotating one vector onto another. */
static vec4 quat_between_vec3(vec3 from, vec3 to)
{
    vec3 from_normalized = vec3_normalize(from);
    vec3 to_normalized = vec3_normalize(to);
    real dot = vec3_dot(from_normalized, to_normalized);
    vec3 axis;
    vec4 rotation;

    if (dot >= (1.0f - VECTORS_QUAT_EPSILON))
    {
        return quat_identity();
    }

    if (dot <= (-1.0f + VECTORS_QUAT_EPSILON))
    {
        axis = vec3_cross(vec3_init_from_3(1.0f, 0.0f, 0.0f), from_normalized);
        if (vec3_magnitude(axis) <= VECTORS_QUAT_EPSILON)
        {
            axis = vec3_cross(vec3_init_from_3(0.0f, 1.0f, 0.0f), from_normalized);
        }
        return quat_from_axis_angle(axis, VECTORS_PI);
    }

    axis = vec3_cross(from_normalized, to_normalized);
    rotation = vec4_init_from_4(axis.rotation.i, axis.rotation.j, axis.rotation.k, 1.0f + dot);
    return vec4_normalize(rotation);
}

/* Normalized linear interpolation between two quaternions. */
static vec4 quat_nlerp(vec4 src0, vec4 src1, real factor)
{
    vec4 end = src1;
    vec4 inverse_factor;
    vec4 scaled_factor;
    vec4 blended;

    if (vec4_dot(src0, src1) < 0.0f)
    {
        end = vec4_negate(src1);
    }

    inverse_factor = vec4_mul_scalar(src0, 1.0f - factor);
    scaled_factor = vec4_mul_scalar(end, factor);
    blended = vec4_add(inverse_factor, scaled_factor);
    return vec4_normalize(blended);
}

/* Spherical linear interpolation between two quaternions. */
static vec4 quat_slerp(vec4 src0, vec4 src1, real factor)
{
    vec4 end = src1;
    real dot = vec4_dot(src0, src1);
    real theta;
    real sin_theta;
    real scale0;
    real scale1;

    if (dot < 0.0f)
    {
        end = vec4_negate(src1);
        dot = -dot;
    }

    if (dot >= (1.0f - (VECTORS_QUAT_EPSILON * 5.0f)))
    {
        return quat_nlerp(src0, end, factor);
    }

    dot = real_min(real_max(dot, -1.0f), 1.0f);
    theta = real_acos(dot);
    sin_theta = real_sin(theta);
    scale0 = real_sin((1.0f - factor) * theta) / sin_theta;
    scale1 = real_sin(factor * theta) / sin_theta;
    return vec4_add(vec4_mul_scalar(src0, scale0), vec4_mul_scalar(end, scale1));
}

/* Rotate a vec3 by a quaternion. */
static vec3 quat_rotate_vec3(vec4 rotation, vec3 vector)
{
    vec4 normalized = vec4_normalize(rotation);
    vec3 qv = normalized.vec3;
    vec3 uv = vec3_cross(qv, vector);
    vec3 uuv = vec3_cross(qv, uv);
    vec3 rotated = vec3_add(vector, vec3_mul_scalar(vec3_add(vec3_mul_scalar(uv, normalized.rotation.w), uuv), 2.0f));
    return rotated;
}

/* Rotate a vec4 by a quaternion, preserving the incoming w component. */
static vec4 quat_rotate_vec4(vec4 rotation, vec4 vector)
{
    vec4 rotated;
	rotated.vec3 = quat_rotate_vec3(rotation, vector.vec3);
    rotated.rotation.w = vector.rotation.w;
    return rotated;
}

/* Undefine internal helper macros */
#undef CONCAT_
#undef CONCAT
#undef STATIC_ASSERT

#ifdef __cplusplus
}
#endif

#endif /* VECTORS_H */
