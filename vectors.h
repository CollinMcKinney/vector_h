#if !defined(VECTORS_H)
#define VECTORS_H

#include <math.h>
#include <limits.h>
#include <float.h>

#define CONCAT_(a, b) a##b
#define CONCAT(a, b) CONCAT_(a, b)
#define STATIC_ASSERT(expr) typedef char CONCAT(static_assert_at_line_, __LINE__)[(expr) ? 1 : -1]

#if !defined(__cplusplus) && !defined(__bool_true_false_are_defined)
    typedef int bool;
    #define true 1
    #define false 0
#endif

#ifndef VECTORS_REAL_TYPE
    #define VECTORS_REAL_TYPE float
#endif
typedef VECTORS_REAL_TYPE real;
STATIC_ASSERT(sizeof(real) == 0x4);

static real real_max(real src0, real src1) { return src0 > src1 ? src0 : src1; }
static real real_min(real src0, real src1) { return src0 < src1 ? src0 : src1; }
static real real_trunc(real src0) { return src0 >= 0 ? (real)floor(src0) : (real)ceil(src0); }

#define VECTORS_PI ((real)3.14159265358979323846)
static const real VECTORS_RAD2DEG = (real)(180.0 / VECTORS_PI);
static const real VECTORS_DEG2RAD = (real)(VECTORS_PI / 180.0);
static const real VECTORS_QUAT_EPSILON = (real)0.0001;

/* Try each unsigned type in order of preference (int first, then long, short, char) */
#if UINT_MAX == 0xFFFFFFFFU
    typedef unsigned int mask_t;
#elif ULONG_MAX == 0xFFFFFFFFUL
    typedef unsigned long mask_t;
#elif USHRT_MAX == 0xFFFFFFFFU
    typedef unsigned short mask_t;
#elif UCHAR_MAX == 0xFFFFFFFFU
    typedef unsigned char mask_t;
#else
    #error "No 32-bit unsigned integer type found"
#endif
STATIC_ASSERT(sizeof(mask_t) == 0x4);

#define X (mask_t)(0)
#define Y (mask_t)(1)
#define Z (mask_t)(2)
#define W (mask_t)(3)

#define MASK_X      (mask_t)(1 << X)
#define MASK_Y      (mask_t)(1 << Y)
#define MASK_Z      (mask_t)(1 << Z)
#define MASK_W      (mask_t)(1 << W)
#define MASK_XY     (mask_t)( MASK_X | MASK_Y )
#define MASK_XZ     (mask_t)( MASK_X | MASK_Z )
#define MASK_XW     (mask_t)( MASK_X | MASK_W )
#define MASK_YZ     (mask_t)( MASK_Y | MASK_Z )
#define MASK_YW     (mask_t)( MASK_Y | MASK_W )
#define MASK_ZW     (mask_t)( MASK_Z | MASK_W )
#define MASK_XYZ    (mask_t)( MASK_X | MASK_Y | MASK_Z )
#define MASK_XYW    (mask_t)( MASK_X | MASK_Y | MASK_W )
#define MASK_XZW    (mask_t)( MASK_X | MASK_Z | MASK_W )
#define MASK_YZW    (mask_t)( MASK_Y | MASK_Z | MASK_W )
#define MASK_XYZW   (mask_t)( MASK_X | MASK_Y | MASK_Z | MASK_W )

#define I X
#define J Y
#define K Z
/* #define W W */

#define MASK_I      MASK_X  
#define MASK_J      MASK_Y  
#define MASK_K      MASK_Z  
/* #define MASK_W      MASK_W */
#define MASK_IJ     MASK_XY 
#define MASK_IK     MASK_XZ 
#define MASK_IW     MASK_XW 
#define MASK_JK     MASK_YZ 
#define MASK_JW     MASK_YW 
#define MASK_KW     MASK_ZW 
#define MASK_IJK    MASK_XYZ
#define MASK_IJW    MASK_XYW
#define MASK_IKW    MASK_XZW
#define MASK_JKW    MASK_YZW
#define MASK_IJKW   MASK_XYZW

#define R X
#define G Y
#define B Z
#define A W

#define MASK_R      MASK_X  
#define MASK_G      MASK_Y  
#define MASK_B      MASK_Z  
#define MASK_A      MASK_W  
#define MASK_RG     MASK_XY 
#define MASK_RB     MASK_XZ 
#define MASK_RA     MASK_XW 
#define MASK_GB     MASK_YZ 
#define MASK_GA     MASK_YW 
#define MASK_BA     MASK_ZW 
#define MASK_RGB    MASK_XYZ
#define MASK_RGA    MASK_XYW
#define MASK_RBA    MASK_XZW
#define MASK_GBA    MASK_YZW
#define MASK_RGBA   MASK_XYZW

#define S X
#define T Y
#define P Z
#define Q W

#define MASK_S      MASK_X  
#define MASK_T      MASK_Y  
#define MASK_P      MASK_Z  
#define MASK_Q      MASK_W  
#define MASK_ST     MASK_XY 
#define MASK_SP     MASK_XZ 
#define MASK_SQ     MASK_XW 
#define MASK_TP     MASK_YZ 
#define MASK_TQ     MASK_YW 
#define MASK_PQ     MASK_ZW 
#define MASK_STP    MASK_XYZ
#define MASK_STQ    MASK_XYW
#define MASK_SPQ    MASK_XZW
#define MASK_TPQ    MASK_YZW
#define MASK_STPQ   MASK_XYZW

/* 2-component realing point vector. */
typedef union vec2
{
    real components[2];
    struct { real x, y; } position;
    struct { real i, j; } rotation;
    struct { real r, g; } color;
    struct { real s, t; } textcoord;
} vec2;
STATIC_ASSERT(sizeof(vec2) == 0x8);

/* 3-component realing point vector. */
typedef union vec3
{
    real components[3];
    struct { real x, y, z; } position;
    struct { real i, j, k; } rotation;
    struct { real r, g, b; } color;
    struct { real s, t, p; } textcoord;
} vec3;
STATIC_ASSERT(sizeof(vec3) == 0xC);

/* 4-component realing point vector. */
typedef union vec4
{
    real components[4];
    struct { real x, y, z, w; } position;
    struct { real i, j, k, w; } rotation;
    struct { real r, g, b, a; } color;
    struct { real s, t, p, q; } textcoord;
} vec4;
STATIC_ASSERT(sizeof(vec4) == 0x10);

/* Swizzle (swap) the order of components */
static vec2 vec2_swizzle(vec2 src0, mask_t a, mask_t b)
{
    vec2 swizzled;
    swizzled.components[0] = src0.components[a & 0x1];
    swizzled.components[1] = src0.components[b & 0x1];
    return swizzled;
}

/* Selects components from src0 if the corresponding bit in the mask is set, otherwise selects from src1. */
static vec2 vec2_mask(vec2 src0, vec2 src1, mask_t mask)
{
    vec2 masked;
    masked.components[0] = mask & MASK_X ? src0.components[0] : src1.components[0];
    masked.components[1] = mask & MASK_Y ? src0.components[1] : src1.components[1];
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
    yield.components[0] = (real)pow((double)base.components[0], (double)power.components[0]);
    yield.components[1] = (real)pow((double)base.components[1], (double)power.components[1]);
    return yield;
}

/* Per-component vec2 to the power of a scalar. */
static vec2 vec2_pow_scalar(vec2 base, real power)
{
    vec2 yield;
    yield.components[0] = (real)pow((double)base.components[0], (double)power);
    yield.components[1] = (real)pow((double)base.components[1], (double)power);
    return yield;
}

/* Per-component principal square-root. */
static vec2 vec2_sqrt(vec2 radicand)
{
    vec2 principal;
    principal.components[0] = (real)sqrt((double)radicand.components[0]);
    principal.components[1] = (real)sqrt((double)radicand.components[1]);
    return principal;
}

/* Per-component reciprocal. */
static vec2 vec2_rcp(vec2 recipricand)
{
    vec2 ones        = vec2_init_from_1(1.f);
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
    rets.components[0] = (real)fabs((double)src0.components[0]);
    rets.components[1] = (real)fabs((double)src0.components[1]);
    return rets;
}

/* Per-component sine. */
static vec2 vec2_sin(vec2 theta)
{
    vec2 sine;
    sine.components[0] = (real)sin((double)theta.components[0]);
    sine.components[1] = (real)sin((double)theta.components[1]);
    return sine;
}

/* Per-component cosine. */
static vec2 vec2_cos(vec2 theta)
{
    vec2 cosine;
    cosine.components[0] = (real)cos((double)theta.components[0]);
    cosine.components[1] = (real)cos((double)theta.components[1]);
    return cosine;
}

/* Per-component tangent. */
static vec2 vec2_tan(vec2 theta)
{
    vec2 tagent;
    tagent.components[0] = (real)tan((double)theta.components[0]);
    tagent.components[1] = (real)tan((double)theta.components[1]);
    return tagent;
}

/* Per-component arc-sine. */
static vec2 vec2_asin(vec2 theta)
{
    vec2 arc_sine;
    arc_sine.components[0] = (real)asin((double)theta.components[0]);
    arc_sine.components[1] = (real)asin((double)theta.components[1]);
    return arc_sine;
}

/* Per-component arc-cosine. */
static vec2 vec2_acos(vec2 theta)
{
    vec2 arc_cosine;
    arc_cosine.components[0] = (real)acos((double)theta.components[0]);
    arc_cosine.components[1] = (real)acos((double)theta.components[1]);
    return arc_cosine;
}

/* Per-component arc-tangent. */
static vec2 vec2_atan(vec2 theta)
{
    vec2 arc_tangent;
    arc_tangent.components[0] = (real)atan((double)theta.components[0]);
    arc_tangent.components[1] = (real)atan((double)theta.components[1]);
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
    hyperbolic_sine.components[0] = (real)sinh((double)theta.components[0]);
    hyperbolic_sine.components[1] = (real)sinh((double)theta.components[1]);
    return hyperbolic_sine;
}

/* Per-component hyperbolic-cosine. */
static vec2 vec2_cosh(vec2 theta)
{
    vec2 hyperbolic_cosine;
    hyperbolic_cosine.components[0] = (real)cosh((double)theta.components[0]);
    hyperbolic_cosine.components[1] = (real)cosh((double)theta.components[1]);
    return hyperbolic_cosine;
}

/* Per-component hyperbolic-tangent. */
static vec2 vec2_tanh(vec2 theta)
{
    vec2 hyperbolic_tangent;
    hyperbolic_tangent.components[0] = (real)tanh((double)theta.components[0]);
    hyperbolic_tangent.components[1] = (real)tanh((double)theta.components[1]);
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
    real magnitude = (real)sqrt((double)dot);
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
    real radians    = (real)acos((double)cos);
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
    floored.components[0] = (real)floor((double)src0.components[0]);
    floored.components[1] = (real)floor((double)src0.components[1]);
    return floored;
}

/* Per-component computation of closest integer rounded towards +inf. */
static vec2 vec2_ceil(vec2 src0)
{
    vec2 ceiling;
    ceiling.components[0] = (real)ceil((double)src0.components[0]);
    ceiling.components[1] = (real)ceil((double)src0.components[1]);
    return ceiling;
}

/* Per-component computation of closest integer rounded towards 0. */
static vec2 vec2_trunc(vec2 src0)
{
    vec2 truncated;
    truncated.components[0] = (real)real_trunc((double)src0.components[0]);
    truncated.components[1] = (real)real_trunc((double)src0.components[1]);
    return truncated;
}

/* Per-component fractional component (src0 - floor(src0)). */
static vec2 vec2_frac(vec2 src0)
{
    vec2 rets;
    rets.components[0] = src0.components[0] - (real)floor((double)src0.components[0]);
    rets.components[1] = src0.components[1] - (real)floor((double)src0.components[1]);
    return rets;
}

/* Per-component maximum of two vec2. */
static vec2 vec2_max(vec2 src0, vec2 src1)
{
    vec2 maximum;
    maximum.components[0] = (real)real_max((double)src0.components[0], (double)src1.components[0]);
    maximum.components[1] = (real)real_max((double)src0.components[1], (double)src1.components[1]);
    return maximum;
}

/* Per-component maximum of a vec2 and a scalar. */
static vec2 vec2_max_scalar(vec2 src0, real src1)
{
    vec2 maximum;
    maximum.components[0] = (real)real_max((double)src0.components[0], (double)src1);
    maximum.components[1] = (real)real_max((double)src0.components[1], (double)src1);
    return maximum;
}

/* Per-component minimum of two vec2. */
static vec2 vec2_min(vec2 src0, vec2 src1)
{
    vec2 minimum;
    minimum.components[0] = (real)real_min((double)src0.components[0], (double)src1.components[0]);
    minimum.components[1] = (real)real_min((double)src0.components[1], (double)src1.components[1]);
    return minimum;
}

/* Per-component minimum of a vec2 and a scalar. */
static vec2 vec2_min_scalar(vec2 src0, real src1)
{
    vec2 minimum;
    minimum.components[0] = (real)real_min((double)src0.components[0], (double)src1);
    minimum.components[1] = (real)real_min((double)src0.components[1], (double)src1);
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
static vec3 vec3_swizzle(vec3 src0, mask_t a, mask_t b, mask_t c)
{
    vec3 swizzled;
    swizzled.components[0] = src0.components[a >= 3 ? 0 : a];
    swizzled.components[1] = src0.components[b >= 3 ? 0 : b];
    swizzled.components[2] = src0.components[c >= 3 ? 0 : c];
    return swizzled;
}

/* Selects components from src0 if the corresponding bit in the mask is set, otherwise selects from src1. */
static vec3 vec3_mask(vec3 src0, vec3 src1, mask_t mask)
{
    vec3 masked;
    masked.components[0] = mask & MASK_X ? src0.components[0] : src1.components[0];
    masked.components[1] = mask & MASK_Y ? src0.components[1] : src1.components[1];
    masked.components[2] = mask & MASK_Z ? src0.components[2] : src1.components[2];
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
    yield.components[0] = (real)pow((double)base.components[0], (double)power.components[0]);
    yield.components[1] = (real)pow((double)base.components[1], (double)power.components[1]);
    yield.components[2] = (real)pow((double)base.components[2], (double)power.components[2]);
    return yield;
}

/* Per-component vec3 to the power of a scalar. */
static vec3 vec3_pow_scalar(vec3 base, real power)
{
    vec3 yield;
    yield.components[0] = (real)pow((double)base.components[0], (double)power);
    yield.components[1] = (real)pow((double)base.components[1], (double)power);
    yield.components[2] = (real)pow((double)base.components[2], (double)power);
    return yield;
}

/* Per-component principal square-root. */
static vec3 vec3_sqrt(vec3 radicand)
{
    vec3 principal;
    principal.components[0] = (real)sqrt((double)radicand.components[0]);
    principal.components[1] = (real)sqrt((double)radicand.components[1]);
    principal.components[2] = (real)sqrt((double)radicand.components[2]);
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
    rets.components[0] = (real)fabs((double)src0.components[0]);
    rets.components[1] = (real)fabs((double)src0.components[1]);
    rets.components[2] = (real)fabs((double)src0.components[2]);
    return rets;
}

/* Per-component sine. */
static vec3 vec3_sin(vec3 theta)
{
    vec3 sine;
    sine.components[0] = (real)sin((double)theta.components[0]);
    sine.components[1] = (real)sin((double)theta.components[1]);
    sine.components[2] = (real)sin((double)theta.components[2]);
    return sine;
}

/* Per-component cosine. */
static vec3 vec3_cos(vec3 theta)
{
    vec3 cosine;
    cosine.components[0] = (real)cos((double)theta.components[0]);
    cosine.components[1] = (real)cos((double)theta.components[1]);
    cosine.components[2] = (real)cos((double)theta.components[2]);
    return cosine;
}

/* Per-component tangent. */
static vec3 vec3_tan(vec3 theta)
{
    vec3 tagent;
    tagent.components[0] = (real)tan((double)theta.components[0]);
    tagent.components[1] = (real)tan((double)theta.components[1]);
    tagent.components[2] = (real)tan((double)theta.components[2]);
    return tagent;
}

/* Per-component arc-sine. */
static vec3 vec3_asin(vec3 theta)
{
    vec3 arc_sine;
    arc_sine.components[0] = (real)asin((double)theta.components[0]);
    arc_sine.components[1] = (real)asin((double)theta.components[1]);
    arc_sine.components[2] = (real)asin((double)theta.components[2]);
    return arc_sine;
}

/* Per-component arc-cosine. */
static vec3 vec3_acos(vec3 theta)
{
    vec3 arc_cosine;
    arc_cosine.components[0] = (real)acos((double)theta.components[0]);
    arc_cosine.components[1] = (real)acos((double)theta.components[1]);
    arc_cosine.components[2] = (real)acos((double)theta.components[2]);
    return arc_cosine;
}

/* Per-component arc-tangent. */
static vec3 vec3_atan(vec3 theta)
{
    vec3 arc_tangent;
    arc_tangent.components[0] = (real)atan((double)theta.components[0]);
    arc_tangent.components[1] = (real)atan((double)theta.components[1]);
    arc_tangent.components[2] = (real)atan((double)theta.components[2]);
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
    hyperbolic_sine.components[0] = (real)sinh((double)theta.components[0]);
    hyperbolic_sine.components[1] = (real)sinh((double)theta.components[1]);
    hyperbolic_sine.components[2] = (real)sinh((double)theta.components[2]);
    return hyperbolic_sine;
}

/* Per-component hyperbolic-cosine. */
static vec3 vec3_cosh(vec3 theta)
{
    vec3 hyperbolic_cosine;
    hyperbolic_cosine.components[0] = (real)cosh((double)theta.components[0]);
    hyperbolic_cosine.components[1] = (real)cosh((double)theta.components[1]);
    hyperbolic_cosine.components[2] = (real)cosh((double)theta.components[2]);
    return hyperbolic_cosine;
}

/* Per-component hyperbolic-tangent. */
static vec3 vec3_tanh(vec3 theta)
{
    vec3 hyperbolic_tangent;
    hyperbolic_tangent.components[0] = (real)tanh((double)theta.components[0]);
    hyperbolic_tangent.components[1] = (real)tanh((double)theta.components[1]);
    hyperbolic_tangent.components[2] = (real)tanh((double)theta.components[2]);
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
    real magnitude  = (real)sqrt((double)dot);
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
    real radians    = (real)acos((double)cos);
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
    floored.components[0] = (real)floor((double)src0.components[0]);
    floored.components[1] = (real)floor((double)src0.components[1]);
    floored.components[2] = (real)floor((double)src0.components[2]);
    return floored;
}

/* Per-component computation of closest integer rounded towards +inf. */
static vec3 vec3_ceil(vec3 src0)
{
    vec3 ceiling;
    ceiling.components[0] = (real)ceil((double)src0.components[0]);
    ceiling.components[1] = (real)ceil((double)src0.components[1]);
    ceiling.components[2] = (real)ceil((double)src0.components[2]);
    return ceiling;
}

/* Per-component computation of closest integer rounded towards 0. */
static vec3 vec3_trunc(vec3 src0)
{
    vec3 truncated;
    truncated.components[0] = (real)real_trunc((double)src0.components[0]);
    truncated.components[1] = (real)real_trunc((double)src0.components[1]);
    truncated.components[2] = (real)real_trunc((double)src0.components[2]);
    return truncated;
}

/* Per-component fractional component (src0 - floor(src0)). */
static vec3 vec3_frac(vec3 src0)
{
    vec3 rets;
    rets.components[0] = src0.components[0] - (real)floor((double)src0.components[0]);
    rets.components[1] = src0.components[1] - (real)floor((double)src0.components[1]);
    rets.components[2] = src0.components[2] - (real)floor((double)src0.components[2]);
    return rets;
}

/* Per-component maximum of two vec3. */
static vec3 vec3_max(vec3 src0, vec3 src1)
{
    vec3 maximum;
    maximum.components[0] = (real)real_max((double)src0.components[0], (double)src1.components[0]);
    maximum.components[1] = (real)real_max((double)src0.components[1], (double)src1.components[1]);
    maximum.components[2] = (real)real_max((double)src0.components[2], (double)src1.components[2]);
    return maximum;
}

/* Per-component maximum of a vec3 and a scalar. */
static vec3 vec3_max_scalar(vec3 src0, real src1)
{
    vec3 maximum;
    maximum.components[0] = (real)real_max((double)src0.components[0], (double)src1);
    maximum.components[1] = (real)real_max((double)src0.components[1], (double)src1);
    maximum.components[2] = (real)real_max((double)src0.components[2], (double)src1);
    return maximum;
}

/* Per-component minimum of two vec3. */
static vec3 vec3_min(vec3 src0, vec3 src1)
{
    vec3 minimum;
    minimum.components[0] = (real)real_min((double)src0.components[0], (double)src1.components[0]);
    minimum.components[1] = (real)real_min((double)src0.components[1], (double)src1.components[1]);
    minimum.components[2] = (real)real_min((double)src0.components[2], (double)src1.components[2]);
    return minimum;
}

/* Per-component minimum of a vec3 and a scalar. */
static vec3 vec3_min_scalar(vec3 src0, real src1)
{
    vec3 minimum;
    minimum.components[0] = (real)real_min((double)src0.components[0], (double)src1);
    minimum.components[1] = (real)real_min((double)src0.components[1], (double)src1);
    minimum.components[2] = (real)real_min((double)src0.components[2], (double)src1);
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
static vec4 vec4_swizzle(vec4 src0, mask_t a, mask_t b, mask_t c, mask_t d)
{
    vec4 swizzled;
    swizzled.components[0] = src0.components[a & 0x3];
    swizzled.components[1] = src0.components[b & 0x3];
    swizzled.components[2] = src0.components[c & 0x3];
    swizzled.components[3] = src0.components[d & 0x3];
    return swizzled;
}

/* Selects components from src0 if the corresponding bit in the mask is set, otherwise selects from src1. */
static vec4 vec4_mask(vec4 src0, vec4 src1, mask_t mask)
{
    vec4 masked;
    masked.components[0] = mask & MASK_X ? src0.components[0] : src1.components[0];
    masked.components[1] = mask & MASK_Y ? src0.components[1] : src1.components[1];
    masked.components[2] = mask & MASK_Z ? src0.components[2] : src1.components[2];
    masked.components[3] = mask & MASK_W ? src0.components[3] : src1.components[3];
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
    yield.components[0] = (real)pow((double)base.components[0], (double)power.components[0]);
    yield.components[1] = (real)pow((double)base.components[1], (double)power.components[1]);
    yield.components[2] = (real)pow((double)base.components[2], (double)power.components[2]);
    yield.components[3] = (real)pow((double)base.components[3], (double)power.components[3]);
    return yield;
}

/* Per-component vec4 to the power of a scalar. */
static vec4 vec4_pow_scalar(vec4 base, real power)
{
    vec4 yield;
    yield.components[0] = (real)pow((double)base.components[0], (double)power);
    yield.components[1] = (real)pow((double)base.components[1], (double)power);
    yield.components[2] = (real)pow((double)base.components[2], (double)power);
    yield.components[3] = (real)pow((double)base.components[3], (double)power);
    return yield;
}

/* Per-component principal square-root. */
static vec4 vec4_sqrt(vec4 radicand)
{
    vec4 principal;
    principal.components[0] = (real)sqrt((double)radicand.components[0]);
    principal.components[1] = (real)sqrt((double)radicand.components[1]);
    principal.components[2] = (real)sqrt((double)radicand.components[2]);
    principal.components[3] = (real)sqrt((double)radicand.components[3]);
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
    rets.components[0] = (real)fabs((double)src0.components[0]);
    rets.components[1] = (real)fabs((double)src0.components[1]);
    rets.components[2] = (real)fabs((double)src0.components[2]);
    rets.components[3] = (real)fabs((double)src0.components[3]);
    return rets;
}

/* Per-component sine. */
static vec4 vec4_sin(vec4 theta)
{
    vec4 sine;
    sine.components[0] = (real)sin((double)theta.components[0]);
    sine.components[1] = (real)sin((double)theta.components[1]);
    sine.components[2] = (real)sin((double)theta.components[2]);
    sine.components[3] = (real)sin((double)theta.components[3]);
    return sine;
}

/* Per-component cosine. */
static vec4 vec4_cos(vec4 theta)
{
    vec4 cosine;
    cosine.components[0] = (real)cos((double)theta.components[0]);
    cosine.components[1] = (real)cos((double)theta.components[1]);
    cosine.components[2] = (real)cos((double)theta.components[2]);
    cosine.components[3] = (real)cos((double)theta.components[3]);
    return cosine;
}

/* Per-component tangent. */
static vec4 vec4_tan(vec4 theta)
{
    vec4 tagent;
    tagent.components[0] = (real)tan((double)theta.components[0]);
    tagent.components[1] = (real)tan((double)theta.components[1]);
    tagent.components[2] = (real)tan((double)theta.components[2]);
    tagent.components[3] = (real)tan((double)theta.components[3]);
    return tagent;
}

/* Per-component arc-sine. */
static vec4 vec4_asin(vec4 theta)
{
    vec4 arc_sine;
    arc_sine.components[0] = (real)asin((double)theta.components[0]);
    arc_sine.components[1] = (real)asin((double)theta.components[1]);
    arc_sine.components[2] = (real)asin((double)theta.components[2]);
    arc_sine.components[3] = (real)asin((double)theta.components[3]);
    return arc_sine;
}

/* Per-component arc-cosine. */
static vec4 vec4_acos(vec4 theta)
{
    vec4 arc_cosine;
    arc_cosine.components[0] = (real)acos((double)theta.components[0]);
    arc_cosine.components[1] = (real)acos((double)theta.components[1]);
    arc_cosine.components[2] = (real)acos((double)theta.components[2]);
    arc_cosine.components[3] = (real)acos((double)theta.components[3]);
    return arc_cosine;
}

/* Per-component arc-tangent. */
static vec4 vec4_atan(vec4 theta)
{
    vec4 arc_tangent;
    arc_tangent.components[0] = (real)atan((double)theta.components[0]);
    arc_tangent.components[1] = (real)atan((double)theta.components[1]);
    arc_tangent.components[2] = (real)atan((double)theta.components[2]);
    arc_tangent.components[3] = (real)atan((double)theta.components[3]);
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
    hyperbolic_sine.components[0] = (real)sinh((double)theta.components[0]);
    hyperbolic_sine.components[1] = (real)sinh((double)theta.components[1]);
    hyperbolic_sine.components[2] = (real)sinh((double)theta.components[2]);
    hyperbolic_sine.components[3] = (real)sinh((double)theta.components[3]);
    return hyperbolic_sine;
}

/* Per-component hyperbolic-cosine. */
static vec4 vec4_cosh(vec4 theta)
{
    vec4 hyperbolic_cosine;
    hyperbolic_cosine.components[0] = (real)cosh((double)theta.components[0]);
    hyperbolic_cosine.components[1] = (real)cosh((double)theta.components[1]);
    hyperbolic_cosine.components[2] = (real)cosh((double)theta.components[2]);
    hyperbolic_cosine.components[3] = (real)cosh((double)theta.components[3]);
    return hyperbolic_cosine;
}

/* Per-component hyperbolic-tangent. */
static vec4 vec4_tanh(vec4 theta)
{
    vec4 hyperbolic_tangent;
    hyperbolic_tangent.components[0] = (real)tanh((double)theta.components[0]);
    hyperbolic_tangent.components[1] = (real)tanh((double)theta.components[1]);
    hyperbolic_tangent.components[2] = (real)tanh((double)theta.components[2]);
    hyperbolic_tangent.components[3] = (real)tanh((double)theta.components[3]);
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
    real magnitude  = (real)sqrt((double)dot);
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
    real radians    = (real)acos((double)cos);
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
    floored.components[0] = (real)floor((double)src0.components[0]);
    floored.components[1] = (real)floor((double)src0.components[1]);
    floored.components[2] = (real)floor((double)src0.components[2]);
    floored.components[3] = (real)floor((double)src0.components[3]);
    return floored;
}

/* Per-component computation of closest integer rounded towards +inf. */
static vec4 vec4_ceil(vec4 src0)
{
    vec4 ceiling;
    ceiling.components[0] = (real)ceil((double)src0.components[0]);
    ceiling.components[1] = (real)ceil((double)src0.components[1]);
    ceiling.components[2] = (real)ceil((double)src0.components[2]);
    ceiling.components[3] = (real)ceil((double)src0.components[3]);
    return ceiling;
}

/* Per-component computation of closest integer rounded towards 0. */
static vec4 vec4_trunc(vec4 src0)
{
    vec4 truncated;
    truncated.components[0] = (real)real_trunc((double)src0.components[0]);
    truncated.components[1] = (real)real_trunc((double)src0.components[1]);
    truncated.components[2] = (real)real_trunc((double)src0.components[2]);
    truncated.components[3] = (real)real_trunc((double)src0.components[3]);
    return truncated;
}

/* Per-component fractional component (src0 - floor(src0)). */
static vec4 vec4_frac(vec4 src0)
{
    vec4 rets;
    rets.components[0] = src0.components[0] - (real)floor((double)src0.components[0]);
    rets.components[1] = src0.components[1] - (real)floor((double)src0.components[1]);
    rets.components[2] = src0.components[2] - (real)floor((double)src0.components[2]);
    rets.components[3] = src0.components[3] - (real)floor((double)src0.components[3]);
    return rets;
}

/* Per-component maximum of two vec4. */
static vec4 vec4_max(vec4 src0, vec4 src1)
{
    vec4 maximum;
    maximum.components[0] = (real)real_max((double)src0.components[0], (double)src1.components[0]);
    maximum.components[1] = (real)real_max((double)src0.components[1], (double)src1.components[1]);
    maximum.components[2] = (real)real_max((double)src0.components[2], (double)src1.components[2]);
    maximum.components[3] = (real)real_max((double)src0.components[3], (double)src1.components[3]);
    return maximum;
}

/* Per-component maximum of a vec4 and a scalar. */
static vec4 vec4_max_scalar(vec4 src0, real src1)
{
    vec4 maximum;
    maximum.components[0] = (real)real_max((double)src0.components[0], (double)src1);
    maximum.components[1] = (real)real_max((double)src0.components[1], (double)src1);
    maximum.components[2] = (real)real_max((double)src0.components[2], (double)src1);
    maximum.components[3] = (real)real_max((double)src0.components[3], (double)src1);
    return maximum;
}

/* Per-component minimum of two vec4. */
static vec4 vec4_min(vec4 src0, vec4 src1)
{
    vec4 minimum;
    minimum.components[0] = (real)real_min((double)src0.components[0], (double)src1.components[0]);
    minimum.components[1] = (real)real_min((double)src0.components[1], (double)src1.components[1]);
    minimum.components[2] = (real)real_min((double)src0.components[2], (double)src1.components[2]);
    minimum.components[3] = (real)real_min((double)src0.components[3], (double)src1.components[3]);
    return minimum;
}

/* Per-component minimum of a vec4 and a scalar. */
static vec4 vec4_min_scalar(vec4 src0, real src1)
{
    vec4 minimum;
    minimum.components[0] = (real)real_min((double)src0.components[0], (double)src1);
    minimum.components[1] = (real)real_min((double)src0.components[1], (double)src1);
    minimum.components[2] = (real)real_min((double)src0.components[2], (double)src1);
    minimum.components[3] = (real)real_min((double)src0.components[3], (double)src1);
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

/* Undefine internal helper macros */
#undef CONCAT_
#undef CONCAT
#undef STATIC_ASSERT

#endif /* VECTORS_H */
