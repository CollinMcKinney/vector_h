#if !defined(VECTORS_H)
#define VECTORS_H

#include <math.h>

typedef __UINTPTR_TYPE__ mask_t;
static_assert(sizeof(mask_t) == __SIZEOF_POINTER__, "");

#pragma region Component Masks
#define X (mask_t)(0)
#define Y (mask_t)(1)
#define Z (mask_t)(2)
#define W (mask_t)(3)

#define MASK_X		(mask_t)(1 << X)
#define MASK_Y		(mask_t)(1 << Y)
#define MASK_Z		(mask_t)(1 << Z)
#define MASK_W		(mask_t)(1 << W)
#define MASK_XY		(mask_t)( MASK_X | MASK_Y )
#define MASK_XZ		(mask_t)( MASK_X | MASK_Z )
#define MASK_XW		(mask_t)( MASK_X | MASK_W )
#define MASK_YZ		(mask_t)( MASK_Y | MASK_Z )
#define MASK_YW		(mask_t)( MASK_Y | MASK_W )
#define MASK_ZW		(mask_t)( MASK_Z | MASK_W )
#define MASK_XYZ	(mask_t)( MASK_X | MASK_Y | MASK_Z )
#define MASK_XYW	(mask_t)( MASK_X | MASK_Y | MASK_W )
#define MASK_XZW	(mask_t)( MASK_X | MASK_Z | MASK_W )
#define MASK_YZW	(mask_t)( MASK_Y | MASK_Z | MASK_W )
#define MASK_XYZW	(mask_t)( MASK_X | MASK_Y | MASK_Z | MASK_W )
#pragma endregion

#pragma region Vector Typedefs
// 2-component floating point vector.
typedef union vec2
{
	float components[2];
	struct { float x, y; };
	struct { float i, j; };
	struct { float r, g; };
	struct { float s, t; };
} vec2;
static_assert(sizeof(vec2) == 0x8, "");

// 3-component floating point vector.
typedef union vec3
{
	float components[3];
	struct { float x, y, z; };
	struct { float i, j, k; };
	struct { float r, g, b; };
	struct { float s, t, p; };
} vec3;
static_assert(sizeof(vec3) == 0xC, "");

// 4-component floating point vector.
typedef union vec4
{
	float components[4];
	struct { float x, y, z, w; };
	struct { float i, j, k; /*w*/ };
	struct { float r, g, b, a; };
	struct { float s, t, p, q; };
} vec4;
static_assert(sizeof(vec4) == 0x10, "");

#pragma endregion

#pragma region Vec2 Functions

// Swizzle (swap) the order of components
static inline vec2 vec2_swizzle(vec2 src0, mask_t a, mask_t b)
{
	vec2 swizzled;
	swizzled.x = src0.components[a & 0x1];
	swizzled.y = src0.components[b & 0x1];
	return swizzled;
}

// Selects components from src0 if the corresponding bit in the mask is set, otherwise selects from src1.
static inline vec2 vec2_mask(vec2 src0, vec2 src1, mask_t mask)
{
	vec2 masked;
	masked.x = mask & MASK_X ? src0.x : src1.x;
	masked.y = mask & MASK_Y ? src0.y : src1.y;
	return masked;
}

// Initialize a vec2 from 2 float's, where each component maps to an argument.
static inline vec2 vec2_init_from_2(float x, float y)
{
	vec2 vector;
	vector.x = x;
	vector.y = y;
	return vector;
}

// Initialize a vec2 from one float, where all components map to the argument.
static inline vec2 vec2_init_from_1(float xy)
{
	vec2 vector;
	vector.x = xy;
	vector.y = xy;
	return vector;
}

// Per-component negation (sign flip).
static inline vec2 vec2_negate(vec2 src0)
{
	vec2 negative;
	negative.x = -src0.x;
	negative.y = -src0.y;
	return negative;
}

// Per-component addition of two vec2.
static inline vec2 vec2_add(vec2 augend, vec2 addend)
{
	vec2 sum;
	sum.x = augend.x + addend.x;
	sum.y = augend.y + addend.y;
	return sum;
}

// Per-component addition of a vec2 and a scalar.
static inline vec2 vec2_add_scalar(vec2 augend, float addend)
{
	vec2 sum;
	sum.x = augend.x + addend;
	sum.y = augend.y + addend;
	return sum;
}

// Per-component subtraction of vec2.
static inline vec2 vec2_sub(vec2 minuend, vec2 subtrahend)
{
	vec2 difference;
	difference.x = minuend.x - subtrahend.x;
	difference.y = minuend.y - subtrahend.y;
	return difference;
}

// Per-component subtraction of a scalar from a vec2.
static inline vec2 vec2_sub_scalar(vec2 minuend, float subtrahend)
{
	vec2 difference;
	difference.x = minuend.x - subtrahend;
	difference.y = minuend.y - subtrahend;
	return difference;
}

// Per-component multiplication of a vec2 by a vec2.
static inline vec2 vec2_mul(vec2 multiplicand, vec2 multiplier)
{
	vec2 product;
	product.x = multiplicand.x * multiplier.x;
	product.y = multiplicand.y * multiplier.y;
	return product;
}

// Per-component multiplication of a vec2 and a scalar.
static inline vec2 vec2_mul_scalar(vec2 multiplicand, float multiplier)
{
	vec2 product;
	product.x = multiplicand.x * multiplier;
	product.y = multiplicand.y * multiplier;
	return product;
}

// Per-component division of a vec2 by a vec2.
static inline vec2 vec2_div(vec2 dividend, vec2 divisor)
{
	vec2 quotient;
	quotient.x = dividend.x / divisor.x;
	quotient.y = dividend.y / divisor.y;
	return quotient;
}

// Per-component division of a vec2 by a scalar.
static inline vec2 vec2_div_scalar(vec2 dividend, float divisor)
{
	vec2 quotient;
	quotient.x = dividend.x / divisor;
	quotient.y = dividend.y / divisor;
	return quotient;
}

// Per-component vec2 to the power of a vec2.
static inline vec2 vec2_pow(vec2 base, vec2 power)
{
	vec2 yield;
	yield.x = powf(base.x, power.x);
	yield.y = powf(base.y, power.y);
	return yield;
}

// Per-component vec2 to the power of a scalar.
static inline vec2 vec2_pow_scalar(vec2 base, float power)
{
	vec2 yield;
	yield.x = powf(base.x, power);
	yield.y = powf(base.y, power);
	return yield;
}

// Per-component principal square-root.
static inline vec2 vec2_sqrt(vec2 radicand)
{
	vec2 principal;
	principal.x = sqrtf(radicand.x);
	principal.y = sqrtf(radicand.y);
	return principal;
}

// Per-component reciprocal.
static inline vec2 vec2_rcp(vec2 recipricand)
{
	vec2 ones		= vec2_init_from_1(1.f);
	vec2 reciprocal = vec2_div(ones, recipricand);
	return reciprocal;
}

// Per-component reciprocal  square-root.
static inline vec2 vec2_rsqrt(vec2 radicand)
{
	vec2 square_root	= vec2_sqrt(radicand);
	vec2 reciprocal		= vec2_rcp(square_root);
	return reciprocal;
}

// Per-component absolute-value.
static inline vec2 vec2_abs(vec2 src0)
{
	vec2 rets;
	rets.x = fabsf(src0.x);
	rets.y = fabsf(src0.y);
	return rets;
}

// Per-component sine.
static inline vec2 vec2_sin(vec2 theta)
{
	vec2 sine;
	sine.x = sinf(theta.x);
	sine.y = sinf(theta.y);
	return sine;
}

// Per-component cosine.
static inline vec2 vec2_cos(vec2 theta)
{
	vec2 cosine;
	cosine.x = cosf(theta.x);
	cosine.y = cosf(theta.y);
	return cosine;
}

// Per-component tangent.
static inline vec2 vec2_tan(vec2 theta)
{
	vec2 tagent;
	tagent.x = tanf(theta.x);
	tagent.y = tanf(theta.y);
	return tagent;
}

// Per-component arc-sine.
static inline vec2 vec2_asin(vec2 theta)
{
	vec2 arc_sine;
	arc_sine.x = asinf(theta.x);
	arc_sine.y = asinf(theta.y);
	return arc_sine;
}

// Per-component arc-cosine.
static inline vec2 vec2_acos(vec2 theta)
{
	vec2 arc_cosine;
	arc_cosine.x = acosf(theta.x);
	arc_cosine.y = acosf(theta.y);
	return arc_cosine;
}

// Per-component arc-tangent.
static inline vec2 vec2_atan(vec2 theta)
{
	vec2 arc_tangent;
	arc_tangent.x = atanf(theta.x);
	arc_tangent.y = atanf(theta.y);
	return arc_tangent;
}

// Per-component cosecant.
static inline vec2 vec2_csc(vec2 theta)
{
	vec2 sine = vec2_sin(theta);
	vec2 cosecant = vec2_rcp(sine);
	return cosecant;
}

// Per-component secant.
static inline vec2 vec2_sec(vec2 theta)
{
	vec2 cosine = vec2_cos(theta);
	vec2 secant = vec2_rcp(cosine);
	return secant;
}

// Per-component cotangent.
static inline vec2 vec2_cot(vec2 theta)
{
	vec2 tangent	= vec2_tan(theta);
	vec2 cotangent	= vec2_rcp(tangent);
	return cotangent;
}

// Per-component hyperbolic-sine.
static inline vec2 vec2_sinh(vec2 theta)
{
	vec2 hyperbolic_sine;
	hyperbolic_sine.x = sinhf(theta.x);
	hyperbolic_sine.y = sinhf(theta.y);
	return hyperbolic_sine;
}

// Per-component hyperbolic-cosine.
static inline vec2 vec2_cosh(vec2 theta)
{
	vec2 hyperbolic_cosine;
	hyperbolic_cosine.x = coshf(theta.x);
	hyperbolic_cosine.y = coshf(theta.y);
	return hyperbolic_cosine;
}

// Per-component hyperbolic-tangent.
static inline vec2 vec2_tanh(vec2 theta)
{
	vec2 hyperbolic_tangent;
	hyperbolic_tangent.x = tanhf(theta.x);
	hyperbolic_tangent.y = tanhf(theta.y);
	return hyperbolic_tangent;
}

// Per-component hyperbolic-cosecant.
static inline vec2 vec2_csch(vec2 theta)
{
	vec2 hyperbolic_sin			= vec2_sinh(theta);
	vec2 hyperbolic_cosecant	= vec2_rcp(hyperbolic_sin);
	return hyperbolic_cosecant;
}

// Per-component hyperbolic-secant.
static inline vec2 vec2_sech(vec2 theta)
{
	vec2 hyperbolic_cosine = vec2_cosh(theta);
	vec2 hyperbolic_secant = vec2_rcp(hyperbolic_cosine);
	return hyperbolic_secant;
}

// Per-component hyperbolic-cotangent.
static inline vec2 vec2_coth(vec2 theta)
{
	vec2 hyperbolic_tangent		= vec2_tanh(theta);
	vec2 hyperbolic_cotangent	= vec2_rcp(hyperbolic_tangent);
	return hyperbolic_cotangent;
}


// True if *all* components are non-zero.
static inline bool vec2_all(vec2 src0)
{
	bool rets = (
		(src0.x != 0) &&
		(src0.y != 0));
	return rets;
}

// True if *any* components are non-zero.
static inline bool vec2_any(vec2 src0)
{
	bool rets = (
		(src0.x != 0) ||
		(src0.y != 0));
	return rets;
}

// 2-component dot product.
static inline float vec2_dot(vec2 src0, vec2 src1)
{
	float dot_product;
	dot_product = (src0.x * src1.x) + (src0.y * src1.y);
	return dot_product;
}

// Reflection vector through a normal (normal vector should be perpendicular to the surface, and cross
// through the intersection point.
//	   ____________________________________
//	  |				  normal			   |
//	  |	reflection  \	|   / incident 	   |
//	  |	             \	|  /			   |
//	  |	              \ | /				   |
//	  |	               \|/				   |
//	  |	  surface ------*------    		   |
//	  |____________________________________|
static inline vec2 vec2_reflect(vec2 incident, vec2 surface_normal)
{
	float dot_product	= 2.0f * vec2_dot(incident, surface_normal);
	vec2 product		= vec2_mul_scalar(surface_normal, dot_product);
	vec2 reflection		= vec2_sub(incident, product);
	return reflection;
}

// Magnitude/Length 
static inline float vec2_magnitude(vec2 src0)
{
	float dot		= vec2_dot(src0, src0);
	float magnitude = sqrtf(dot);
	return magnitude;
}

// Unit-vector
static inline vec2 vec2_normalize(vec2 src0)
{
	float magnitude		= vec2_magnitude(src0);
	vec2 unit_vector	= vec2_div_scalar(src0, magnitude);
	return unit_vector;
}

// Euclidean distance.
static inline float vec2_distance(vec2 src0, vec2 src1)
{
	vec2 difference = vec2_sub(src0, src1);
	float distance	= vec2_magnitude(difference);
	return distance;
}

// Angle between two vectors in radians.
static inline float vec2_angle(vec2 src0, vec2 src1)
{
	float mag_a		= vec2_magnitude(src0);
	float mag_b		= vec2_magnitude(src1);
	float dot		= vec2_dot(src0, src1);
	float cos		= dot / (mag_a * mag_b);
	float radians	= acosf(cos);
	return radians;
}

// Per-component conversion from radians to degrees.
static inline vec2 vec2_degrees(vec2 radians)
{
	vec2 degrees;
	degrees.x = (float)(radians.x * 57.29577951308232157827); // multiply by 180/pi.
	degrees.y = (float)(radians.y * 57.29577951308232157827); // multiply by 180/pi.
	return degrees;
}

// Per-component conversion from degrees to radians.
static inline vec2 vec2_radians(vec2 degrees)
{
	vec2 radians;
	radians.x = (float)(degrees.x * 0.01745329251994329556); // multiply by pi/180.
	radians.y = (float)(degrees.y * 0.01745329251994329556); // multiply by pi/180.
	return radians;
}

// perp-product of two vec2.
static inline float vec2_perp(vec2 src0, vec2 src1)
{
	return (src0.x * src1.y) - (src0.y * src1.x);
}

// Per-component computation of closest integer rounded towards -∞.
static inline vec2 vec2_floor(vec2 src0)
{
	vec2 floor;
	floor.x = floorf(src0.x);
	floor.y = floorf(src0.y);
	return floor;
}

// Per-component computation of closest integer rounded towards ∞.
static inline vec2 vec2_ceil(vec2 src0)
{
	vec2 ceiling;
	ceiling.x = ceilf(src0.x);
	ceiling.y = ceilf(src0.y);
	return ceiling;
}

// Per-component computation of closest integer rounded towards 0.
static inline vec2 vec2_trunc(vec2 src0)
{
	vec2 truncated;
	truncated.x = truncf(src0.x);
	truncated.y = truncf(src0.y);
	return truncated;
}

// Per-component fractional component (src0 - floor(src0)).
static inline vec2 vec2_frac(vec2 src0)
{
	vec2 rets;
	rets.x = src0.x - floorf(src0.x);
	rets.y = src0.y - floorf(src0.y);
	return rets;
}

// Per-component maximum of two vec2.
static inline vec2 vec2_max(vec2 src0, vec2 src1)
{
	vec2 maximum;
	maximum.x = fmaxf(src0.x, src1.x);
	maximum.y = fmaxf(src0.y, src1.y);
	return maximum;
}

// Per-component maximum of a vec2 and a scalar.
static inline vec2 vec2_max_scalar(vec2 src0, float src1)
{
	vec2 maximum;
	maximum.x = fmaxf(src0.x, src1);
	maximum.y = fmaxf(src0.y, src1);
	return maximum;
}

// Per-component minimum of two vec2.
static inline vec2 vec2_min(vec2 src0, vec2 src1)
{
	vec2 minimum;
	minimum.x = fminf(src0.x, src1.x);
	minimum.y = fminf(src0.y, src1.y);
	return minimum;
}

// Per-component minimum of a vec2 and a scalar.
static inline vec2 vec2_min_scalar(vec2 src0, float src1)
{
	vec2 minimum;
	minimum.x = fminf(src0.x, src1);
	minimum.y = fminf(src0.y, src1);
	return minimum;
}

// Per-component clamp of src0 into the range of vectors (minimum..maximum).
static inline vec2 vec2_clamp(vec2 src0, vec2 minimum, vec2 maximum)
{
	vec2 clamped_lower	= vec2_max(src0, minimum);
	vec2 clamped		= vec2_min(clamped_lower, maximum);
	return clamped;
}

// Per-component clamp of src0 into the range of scalars (minimum..maximum).
static inline vec2 vec2_clamp_scalar(vec2 src0, float minimum, float maximum)
{
	vec2 clamped_lower	= vec2_max_scalar(src0, minimum);
	vec2 clamped		= vec2_min_scalar(clamped_lower, maximum);
	return clamped;
}
#pragma endregion

#pragma region Vec3 Functions
// Swizzle (swap) the order of components.
static inline vec3 vec3_swizzle(vec3 src0, mask_t a, mask_t b, mask_t c)
{
	vec3 swizzled;
	swizzled.x = src0.components[a >= 3 ? 0 : a];
	swizzled.y = src0.components[b >= 3 ? 0 : b];
	swizzled.z = src0.components[c >= 3 ? 0 : c];
	return swizzled;
}

// Selects components from src0 if the corresponding bit in the mask is set, otherwise selects from src1.
static inline vec3 vec3_mask(vec3 src0, vec3 src1, mask_t mask)
{
	vec3 masked;
	masked.x = mask & MASK_X ? src0.x : src1.x;
	masked.y = mask & MASK_Y ? src0.y : src1.y;
	masked.z = mask & MASK_Z ? src0.z : src1.z;
	return masked;
}

// Initialize a vec3 from 3 float's, where each component maps to an argument.
static inline vec3 vec3_init_from_3(float x, float y, float z)
{
	vec3 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}

// Initialize a vec3 from one float, where all components map to the argument.
static inline vec3 vec3_init_from_1(float xyz)
{
	vec3 vector;
	vector.x = xyz;
	vector.y = xyz;
	vector.z = xyz;
	return vector;
}

// Per-component negation (sign flip).
static inline vec3 vec3_negate(vec3 src0)
{
	vec3 negative;
	negative.x = -src0.x;
	negative.y = -src0.y;
	negative.z = -src0.z;
	return negative;
}

// Per-component addition of two vec3.
static inline vec3 vec3_add(vec3 augend, vec3 addend)
{
	vec3 sum;
	sum.x = augend.x + addend.x;
	sum.y = augend.y + addend.y;
	sum.z = augend.z + addend.z;
	return sum;
}

// Per-component addition of a vec3 and a scalar.
static inline vec3 vec3_add_scalar(vec3 augend, float addend)
{
	vec3 sum;
	sum.x = augend.x + addend;
	sum.y = augend.y + addend;
	sum.z = augend.z + addend;
	return sum;
}

// Per-component subtraction of vec.
static inline vec3 vec3_sub(vec3 minuend, vec3 subtrahend)
{
	vec3 difference;
	difference.x = minuend.x - subtrahend.x;
	difference.y = minuend.y - subtrahend.y;
	difference.z = minuend.z - subtrahend.z;
	return difference;
}

// Per-component subtraction of a scalar from a vec3.
static inline vec3 vec3_sub_scalar(vec3 minuend, float subtrahend)
{
	vec3 difference;
	difference.x = minuend.x - subtrahend;
	difference.y = minuend.y - subtrahend;
	difference.z = minuend.z - subtrahend;
	return difference;
}

// Per-component multiplication of a vec3 by a vec3.
static inline vec3 vec3_mul(vec3 multiplicand, vec3 multiplier)
{
	vec3 product;
	product.x = multiplicand.x * multiplier.x;
	product.y = multiplicand.y * multiplier.y;
	product.z = multiplicand.z * multiplier.z;
	return product;
}

// Per-component multiplication of a vec3 and a scalar.
static inline vec3 vec3_mul_scalar(vec3 multiplicand, float multiplier)
{
	vec3 product;
	product.x = multiplicand.x * multiplier;
	product.y = multiplicand.y * multiplier;
	product.z = multiplicand.z * multiplier;
	return product;
}

// Per-component division of a vec3 by a vec3.
static inline vec3 vec3_div(vec3 dividend, vec3 divisor)
{
	vec3 quotient;
	quotient.x = dividend.x / divisor.x;
	quotient.y = dividend.y / divisor.y;
	quotient.z = dividend.z / divisor.z;
	return quotient;
}

// Per-component division of a vec3 by a scalar.
static inline vec3 vec3_div_scalar(vec3 dividend, float divisor)
{
	vec3 quotient;
	quotient.x = dividend.x / divisor;
	quotient.y = dividend.y / divisor;
	quotient.z = dividend.z / divisor;
	return quotient;
}

// Per-component vec3 to the power of a vec3.
static inline vec3 vec3_pow(vec3 base, vec3 power)
{
	vec3 yield;
	yield.x = powf(base.x, power.x);
	yield.y = powf(base.y, power.y);
	yield.z = powf(base.z, power.z);
	return yield;
}

// Per-component vec3 to the power of a scalar.
static inline vec3 vec3_pow_scalar(vec3 base, float power)
{
	vec3 yield;
	yield.x = powf(base.x, power);
	yield.y = powf(base.y, power);
	yield.z = powf(base.z, power);
	return yield;
}

// Per-component principal square-root.
static inline vec3 vec3_sqrt(vec3 radicand)
{
	vec3 principal;
	principal.x = sqrtf(radicand.x);
	principal.y = sqrtf(radicand.y);
	principal.z = sqrtf(radicand.z);
	return principal;
}

// Per-component reciprocal.
static inline vec3 vec3_rcp(vec3 recipricand)
{
	vec3 ones		= vec3_init_from_1(1.f);
	vec3 reciprocal = vec3_div(ones, recipricand);
	return reciprocal;
}

// Per-component reciprocal  square-root.
static inline vec3 vec3_rsqrt(vec3 radicand)
{
	vec3 square_root	= vec3_sqrt(radicand);
	vec3 reciprocal		= vec3_rcp(square_root);
	return reciprocal;
}

// Per-component absolute-value.
static inline vec3 vec3_abs(vec3 src0)
{
	vec3 rets;
	rets.x = fabsf(src0.x);
	rets.y = fabsf(src0.y);
	rets.z = fabsf(src0.z);
	return rets;
}

// Per-component sine.
static inline vec3 vec3_sin(vec3 theta)
{
	vec3 sine;
	sine.x = sinf(theta.x);
	sine.y = sinf(theta.y);
	sine.z = sinf(theta.z);
	return sine;
}

// Per-component cosine.
static inline vec3 vec3_cos(vec3 theta)
{
	vec3 cosine;
	cosine.x = cosf(theta.x);
	cosine.y = cosf(theta.y);
	cosine.z = cosf(theta.z);
	return cosine;
}

// Per-component tangent.
static inline vec3 vec3_tan(vec3 theta)
{
	vec3 tagent;
	tagent.x = tanf(theta.x);
	tagent.y = tanf(theta.y);
	tagent.z = tanf(theta.z);
	return tagent;
}

// Per-component arc-sine.
static inline vec3 vec3_asin(vec3 theta)
{
	vec3 arc_sine;
	arc_sine.x = asinf(theta.x);
	arc_sine.y = asinf(theta.y);
	arc_sine.z = asinf(theta.z);
	return arc_sine;
}

// Per-component arc-cosine.
static inline vec3 vec3_acos(vec3 theta)
{
	vec3 arc_cosine;
	arc_cosine.x = acosf(theta.x);
	arc_cosine.y = acosf(theta.y);
	arc_cosine.z = acosf(theta.z);
	return arc_cosine;
}

// Per-component arc-tangent.
static inline vec3 vec3_atan(vec3 theta)
{
	vec3 arc_tangent;
	arc_tangent.x = atanf(theta.x);
	arc_tangent.y = atanf(theta.y);
	arc_tangent.z = atanf(theta.z);
	return arc_tangent;
}

// Per-component cosecant.
static inline vec3 vec3_csc(vec3 theta)
{
	vec3 sine		= vec3_sin(theta);
	vec3 cosecant	= vec3_rcp(sine);
	return cosecant;
}

// Per-component secant.
static inline vec3 vec3_sec(vec3 theta)
{
	vec3 cosine = vec3_cos(theta);
	vec3 secant = vec3_rcp(cosine);
	return secant;
}

// Per-component cotangent.
static inline vec3 vec3_cot(vec3 theta)
{
	vec3 tangent	= vec3_tan(theta);
	vec3 cotangent	= vec3_rcp(tangent);
	return cotangent;
}

// Per-component hyperbolic-sine.
static inline vec3 vec3_sinh(vec3 theta)
{
	vec3 hyperbolic_sine;
	hyperbolic_sine.x = sinhf(theta.x);
	hyperbolic_sine.y = sinhf(theta.y);
	hyperbolic_sine.z = sinhf(theta.z);
	return hyperbolic_sine;
}

// Per-component hyperbolic-cosine.
static inline vec3 vec3_cosh(vec3 theta)
{
	vec3 hyperbolic_cosine;
	hyperbolic_cosine.x = coshf(theta.x);
	hyperbolic_cosine.y = coshf(theta.y);
	hyperbolic_cosine.z = coshf(theta.z);
	return hyperbolic_cosine;
}

// Per-component hyperbolic-tangent.
static inline vec3 vec3_tanh(vec3 theta)
{
	vec3 hyperbolic_tangent;
	hyperbolic_tangent.x = tanhf(theta.x);
	hyperbolic_tangent.y = tanhf(theta.y);
	hyperbolic_tangent.z = tanhf(theta.z);
	return hyperbolic_tangent;
}

// Per-component hyperbolic-cosecant.
static inline vec3 vec3_csch(vec3 theta)
{
	vec3 hyperbolic_sin			= vec3_sinh(theta);
	vec3 hyperbolic_cosecant	= vec3_rcp(hyperbolic_sin);
	return hyperbolic_cosecant;
}

// Per-component hyperbolic-secant.
static inline vec3 vec3_sech(vec3 theta)
{
	vec3 hyperbolic_cosine = vec3_cosh(theta);
	vec3 hyperbolic_secant = vec3_rcp(hyperbolic_cosine);
	return hyperbolic_secant;
}

// Per-component hyperbolic-cotangent.
static inline vec3 vec3_coth(vec3 theta)
{
	vec3 hyperbolic_tangent		= vec3_tanh(theta);
	vec3 hyperbolic_cotangent	= vec3_rcp(hyperbolic_tangent);
	return hyperbolic_cotangent;
}

// True if *all* components are non-zero.
static inline bool vec3_all(vec3 src0)
{
	bool rets = (
		(src0.x != 0) &&
		(src0.y != 0) &&
		(src0.z != 0));
	return rets;
}

// True if *any* components are non-zero.
static inline bool vec3_any(vec3 src0)
{
	bool rets = (
		(src0.x != 0) ||
		(src0.y != 0) ||
		(src0.z != 0));
	return rets;
}

// 3-component dot product.
static inline float vec3_dot(vec3 src0, vec3 src1)
{
	float dot_product;
	dot_product = (src0.x * src1.x) + (src0.y * src1.y) + (src0.z * src1.z);
	return dot_product;
}

// Reflection vector through a normal (normal vector should be perpendicular to the surface, and cross
// through the intersection point. `surface_normal` must be normalized.
//	   ____________________________________
//	  |				  normal			   |
//	  |	reflection  \	|   / incident 	   |
//	  |	             \	|  /			   |
//	  |	              \ | /				   |
//	  |	               \|/				   |
//	  |	  surface ------*------    		   |
//	  |____________________________________|
// http://developer.download.nvidia.com/CgTutorial/cg_tutorial_chapter07.html
static inline vec3 vec3_reflect(vec3 incident, vec3 surface_normal)
{
	float dot_product	= 2.0f * vec3_dot(incident, surface_normal);
	vec3 product		= vec3_mul_scalar(surface_normal, dot_product);
	vec3 reflection		= vec3_sub(incident, product);
	return reflection;
}

// Magnitude/Length 
static inline float vec3_magnitude(vec3 src0)
{
	float dot		= vec3_dot(src0, src0);
	float magnitude = sqrtf(dot);
	return magnitude;
}

// Unit-vector
static inline vec3 vec3_normalize(vec3 src0)
{
	float magnitude		= vec3_magnitude(src0);
	vec3 unit_vector	= vec3_div_scalar(src0, magnitude);
	return unit_vector;
}

// Euclidean distance.
static inline float vec3_distance(vec3 src0, vec3 src1)
{
	vec3 difference = vec3_sub(src0, src1);
	float distance	= vec3_magnitude(difference);
	return distance;
}

// Angle between two vectors in radians.
static inline float vec3_angle(vec3 src0, vec3 src1)
{
	float mag_a		= vec3_magnitude(src0);
	float mag_b		= vec3_magnitude(src1);
	float dot		= vec3_dot(src0, src1);
	float cos		= dot / (mag_a * mag_b);
	float radians	= acosf(cos);
	return radians;
}

// Per-component conversion from radians to degrees.
static inline vec3 vec3_degrees(vec3 radians)
{
	vec3 degrees;
	degrees.x = (float)(radians.x * 57.29577951308232157827); // multiply by 180/pi.
	degrees.y = (float)(radians.y * 57.29577951308232157827); // multiply by 180/pi.
	degrees.z = (float)(radians.z * 57.29577951308232157827); // multiply by 180/pi.
	return degrees;
}

// Per-component conversion from degrees to radians.
static inline vec3 vec3_radians(vec3 degrees)
{
	vec3 radians;
	radians.x = (float)(degrees.x * 0.01745329251994329556); // multiply by pi/180.
	radians.y = (float)(degrees.y * 0.01745329251994329556); // multiply by pi/180.
	radians.z = (float)(degrees.z * 0.01745329251994329556); // multiply by pi/180.
	return radians;
}

// 3-component cross product of two vec3.
static inline vec3 vec3_cross(vec3 src0, vec3 src1)
{
	vec3 cross_product;
	cross_product.x = (src0.y * src1.z) - (src1.y * src0.z);
	cross_product.y = (src0.z * src1.x) - (src1.z * src0.x);
	cross_product.z = (src0.x * src1.y) - (src1.x * src0.y);
	return cross_product;
}

// Per-component computation of closest integer rounded towards -∞.
static inline vec3 vec3_floor(vec3 src0)
{
	vec3 floor;
	floor.x = floorf(src0.x);
	floor.y = floorf(src0.y);
	floor.z = floorf(src0.z);
	return floor;
}

// Per-component computation of closest integer rounded towards ∞.
static inline vec3 vec3_ceil(vec3 src0)
{
	vec3 ceiling;
	ceiling.x = ceilf(src0.x);
	ceiling.y = ceilf(src0.y);
	ceiling.z = ceilf(src0.z);
	return ceiling;
}

// Per-component computation of closest integer rounded towards 0.
static inline vec3 vec3_trunc(vec3 src0)
{
	vec3 truncated;
	truncated.x = truncf(src0.x);
	truncated.y = truncf(src0.y);
	truncated.z = truncf(src0.z);
	return truncated;
}

// Per-component fractional component (src0 - floor(src0)).
static inline vec3 vec3_frac(vec3 src0)
{
	vec3 rets;
	rets.x = src0.x - floorf(src0.x);
	rets.y = src0.y - floorf(src0.y);
	rets.z = src0.z - floorf(src0.z);
	return rets;
}

// Per-component maximum of two vec3.
static inline vec3 vec3_max(vec3 src0, vec3 src1)
{
	vec3 maximum;
	maximum.x = fmaxf(src0.x, src1.x);
	maximum.y = fmaxf(src0.y, src1.y);
	maximum.z = fmaxf(src0.z, src1.z);
	return maximum;
}

// Per-component maximum of a vec3 and a scalar.
static inline vec3 vec3_max_scalar(vec3 src0, float src1)
{
	vec3 maximum;
	maximum.x = fmaxf(src0.x, src1);
	maximum.y = fmaxf(src0.y, src1);
	maximum.z = fmaxf(src0.z, src1);
	return maximum;
}

// Per-component minimum of two vec3.
static inline vec3 vec3_min(vec3 src0, vec3 src1)
{
	vec3 minimum;
	minimum.x = fminf(src0.x, src1.x);
	minimum.y = fminf(src0.y, src1.y);
	minimum.z = fminf(src0.z, src1.z);
	return minimum;
}

// Per-component minimum of a vec3 and a scalar.
static inline vec3 vec3_min_scalar(vec3 src0, float src1)
{
	vec3 minimum;
	minimum.x = fminf(src0.x, src1);
	minimum.y = fminf(src0.y, src1);
	minimum.z = fminf(src0.z, src1);
	return minimum;
}

// Per-component clamp of src0 into the range of vectors (minimum..maximum).
static inline vec3 vec3_clamp(vec3 src0, vec3 minimum, vec3 maximum)
{
	vec3 clamped_lower	= vec3_max(src0, minimum);
	vec3 clamped		= vec3_min(clamped_lower, maximum);
	return clamped;
}

// Per-component clamp of src0 into the range of scalars (minimum..maximum).
static inline vec3 vec3_clamp_scalar(vec3 src0, float minimum, float maximum)
{
	vec3 clamped_lower	= vec3_max_scalar(src0, minimum);
	vec3 clamped		= vec3_min_scalar(clamped_lower, maximum);
	return clamped;
}
#pragma endregion

#pragma region Vec4 Functions
// Swizzle (swap) the order of components.
static inline vec4 vec4_swizzle(vec4 src0, mask_t a, mask_t b, mask_t c, mask_t d)
{
	vec4 swizzled;
	swizzled.x = src0.components[a & 0x3];
	swizzled.y = src0.components[b & 0x3];
	swizzled.z = src0.components[c & 0x3];
	swizzled.w = src0.components[d & 0x3];
	return swizzled;
}

// Selects components from src0 if the corresponding bit in the mask is set, otherwise selects from src1.
static inline vec4 vec4_mask(vec4 src0, vec4 src1, mask_t mask)
{
	vec4 masked;
	masked.x = mask & MASK_X ? src0.x : src1.x;
	masked.y = mask & MASK_Y ? src0.y : src1.y;
	masked.z = mask & MASK_Z ? src0.z : src1.z;
	masked.w = mask & MASK_W ? src0.w : src1.w;
	return masked;
}

// Initialize a vec4 from four float's, where each component maps to an argument.
static inline vec4 vec4_init_from_4(float x, float y, float z, float w)
{
	vec4 vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return vector;
}

// Initialize a vec4 from one float, where all components map to the argument.
static inline vec4 vec4_init_from_1(float xyzw)
{
	vec4 vector;
	vector.x = xyzw;
	vector.y = xyzw;
	vector.z = xyzw;
	vector.w = xyzw;
	return vector;
}

// Per-component negation (sign flip).
static inline vec4 vec4_negate(vec4 src0)
{
	vec4 negative;
	negative.x = -src0.x;
	negative.y = -src0.y;
	negative.z = -src0.z;
	negative.w = -src0.w;
	return negative;
}

// Per-component addition of two vec4.
static inline vec4 vec4_add(vec4 augend, vec4 addend)
{
	vec4 sum;
	sum.x = augend.x + addend.x;
	sum.y = augend.y + addend.y;
	sum.z = augend.z + addend.z;
	sum.w = augend.w + addend.w;
	return sum;
}

// Per-component addition of a vec4 and a scalar.
static inline vec4 vec4_add_scalar(vec4 augend, float addend)
{
	vec4 sum;
	sum.x = augend.x + addend;
	sum.y = augend.y + addend;
	sum.z = augend.z + addend;
	sum.w = augend.w + addend;
	return sum;
}

// Per-component subtraction of vec.
static inline vec4 vec4_sub(vec4 minuend, vec4 subtrahend)
{
	vec4 difference;
	difference.x = minuend.x - subtrahend.x;
	difference.y = minuend.y - subtrahend.y;
	difference.z = minuend.z - subtrahend.z;
	difference.w = minuend.w - subtrahend.w;
	return difference;
}

// Per-component subtraction of a scalar from a vec4.
static inline vec4 vec4_sub_scalar(vec4 minuend, float subtrahend)
{
	vec4 difference;
	difference.x = minuend.x - subtrahend;
	difference.y = minuend.y - subtrahend;
	difference.z = minuend.z - subtrahend;
	difference.w = minuend.w - subtrahend;
	return difference;
}

// Per-component multiplication of a vec4 by a vec4.
static inline vec4 vec4_mul(vec4 multiplicand, vec4 multiplier)
{
	vec4 product;
	product.x = multiplicand.x * multiplier.x;
	product.y = multiplicand.y * multiplier.y;
	product.z = multiplicand.z * multiplier.z;
	product.w = multiplicand.w * multiplier.w;
	return product;
}

// Per-component multiplication of a vec4 and a scalar.
static inline vec4 vec4_mul_scalar(vec4 multiplicand, float multiplier)
{
	vec4 product;
	product.x = multiplicand.x * multiplier;
	product.y = multiplicand.y * multiplier;
	product.z = multiplicand.z * multiplier;
	product.w = multiplicand.w * multiplier;
	return product;
}

// Per-component division of a vec4 by a vec4.
static inline vec4 vec4_div(vec4 dividend, vec4 divisor)
{
	vec4 quotient;
	quotient.x = dividend.x / divisor.x;
	quotient.y = dividend.y / divisor.y;
	quotient.z = dividend.z / divisor.z;
	quotient.w = dividend.w / divisor.w;
	return quotient;
}

// Per-component division of a vec4 by a scalar.
static inline vec4 vec4_div_scalar(vec4 dividend, float divisor)
{
	vec4 quotient;
	quotient.x = dividend.x / divisor;
	quotient.y = dividend.y / divisor;
	quotient.z = dividend.z / divisor;
	quotient.w = dividend.w / divisor;
	return quotient;
}

// Per-component vec4 to the power of a vec4.
static inline vec4 vec4_pow(vec4 base, vec4 power)
{
	vec4 yield;
	yield.x = powf(base.x, power.x);
	yield.y = powf(base.y, power.y);
	yield.z = powf(base.z, power.z);
	yield.w = powf(base.w, power.w);
	return yield;
}

// Per-component vec4 to the power of a scalar.
static inline vec4 vec4_pow_scalar(vec4 base, float power)
{
	vec4 yield;
	yield.x = powf(base.x, power);
	yield.y = powf(base.y, power);
	yield.z = powf(base.z, power);
	yield.w = powf(base.w, power);
	return yield;
}

// Per-component principal square-root.
static inline vec4 vec4_sqrt(vec4 radicand)
{
	vec4 principal;
	principal.x = sqrtf(radicand.x);
	principal.y = sqrtf(radicand.y);
	principal.z = sqrtf(radicand.z);
	principal.w = sqrtf(radicand.w);
	return principal;
}

// Per-component reciprocal.
static inline vec4 vec4_rcp(vec4 recipricand)
{
	vec4 one_vector = vec4_init_from_1(1.f);
	vec4 reciprocal = vec4_div(one_vector, recipricand);
	return reciprocal;
}

// Per-component reciprocal  square-root.
static inline vec4 vec4_rsqrt(vec4 radicand)
{
	vec4 square_root = vec4_sqrt(radicand);
	vec4 reciprocal = vec4_rcp(square_root);
	return reciprocal;
}

// Per-component absolute-value.
static inline vec4 vec4_abs(vec4 src0)
{
	vec4 rets;
	rets.x = fabsf(src0.x);
	rets.y = fabsf(src0.y);
	rets.z = fabsf(src0.z);
	rets.w = fabsf(src0.w);
	return rets;
}

// Per-component sine.
static inline vec4 vec4_sin(vec4 theta)
{
	vec4 sine;
	sine.x = sinf(theta.x);
	sine.y = sinf(theta.y);
	sine.z = sinf(theta.z);
	sine.w = sinf(theta.w);
	return sine;
}

// Per-component cosine.
static inline vec4 vec4_cos(vec4 theta)
{
	vec4 cosine;
	cosine.x = cosf(theta.x);
	cosine.y = cosf(theta.y);
	cosine.z = cosf(theta.z);
	cosine.w = cosf(theta.w);
	return cosine;
}

// Per-component tangent.
static inline vec4 vec4_tan(vec4 theta)
{
	vec4 tagent;
	tagent.x = tanf(theta.x);
	tagent.y = tanf(theta.y);
	tagent.z = tanf(theta.z);
	tagent.w = tanf(theta.w);
	return tagent;
}

// Per-component arc-sine.
static inline vec4 vec4_asin(vec4 theta)
{
	vec4 arc_sine;
	arc_sine.x = asinf(theta.x);
	arc_sine.y = asinf(theta.y);
	arc_sine.z = asinf(theta.z);
	arc_sine.w = asinf(theta.w);
	return arc_sine;
}

// Per-component arc-cosine.
static inline vec4 vec4_acos(vec4 theta)
{
	vec4 arc_cosine;
	arc_cosine.x = acosf(theta.x);
	arc_cosine.y = acosf(theta.y);
	arc_cosine.z = acosf(theta.z);
	arc_cosine.w = acosf(theta.w);
	return arc_cosine;
}

// Per-component arc-tangent.
static inline vec4 vec4_atan(vec4 theta)
{
	vec4 arc_tangent;
	arc_tangent.x = atanf(theta.x);
	arc_tangent.y = atanf(theta.y);
	arc_tangent.z = atanf(theta.z);
	arc_tangent.w = atanf(theta.w);
	return arc_tangent;
}

// Per-component cosecant.
static inline vec4 vec4_csc(vec4 theta)
{
	vec4 sine = vec4_sin(theta);
	vec4 cosecant = vec4_rcp(sine);
	return cosecant;
}

// Per-component secant.
static inline vec4 vec4_sec(vec4 theta)
{
	vec4 cosine = vec4_cos(theta);
	vec4 secant = vec4_rcp(cosine);
	return secant;
}

// Per-component cotangent.
static inline vec4 vec4_cot(vec4 theta)
{
	vec4 tangent = vec4_tan(theta);
	vec4 cotangent = vec4_rcp(tangent);
	return cotangent;
}

// Per-component hyperbolic-sine.
static inline vec4 vec4_sinh(vec4 theta)
{
	vec4 hyperbolic_sine;
	hyperbolic_sine.x = sinhf(theta.x);
	hyperbolic_sine.y = sinhf(theta.y);
	hyperbolic_sine.z = sinhf(theta.z);
	hyperbolic_sine.w = sinhf(theta.w);
	return hyperbolic_sine;
}

// Per-component hyperbolic-cosine.
static inline vec4 vec4_cosh(vec4 theta)
{
	vec4 hyperbolic_cosine;
	hyperbolic_cosine.x = coshf(theta.x);
	hyperbolic_cosine.y = coshf(theta.y);
	hyperbolic_cosine.z = coshf(theta.z);
	hyperbolic_cosine.w = coshf(theta.w);
	return hyperbolic_cosine;
}

// Per-component hyperbolic-tangent.
static inline vec4 vec4_tanh(vec4 theta)
{
	vec4 hyperbolic_tangent;
	hyperbolic_tangent.x = tanhf(theta.x);
	hyperbolic_tangent.y = tanhf(theta.y);
	hyperbolic_tangent.z = tanhf(theta.z);
	hyperbolic_tangent.w = tanhf(theta.w);
	return hyperbolic_tangent;
}

// Per-component hyperbolic-cosecant.
static inline vec4 vec4_csch(vec4 theta)
{
	vec4 hyperbolic_sin = vec4_sinh(theta);
	vec4 hyperbolic_cosecant = vec4_rcp(hyperbolic_sin);
	return hyperbolic_cosecant;
}

// Per-component hyperbolic-secant.
static inline vec4 vec4_sech(vec4 theta)
{
	vec4 hyperbolic_cosine = vec4_cosh(theta);
	vec4 hyperbolic_secant = vec4_rcp(hyperbolic_cosine);
	return hyperbolic_secant;
}

// Per-component hyperbolic-cotangent.
static inline vec4 vec4_coth(vec4 theta)
{
	vec4 hyperbolic_tangent = vec4_tanh(theta);
	vec4 hyperbolic_cotangent = vec4_rcp(hyperbolic_tangent);
	return hyperbolic_cotangent;
}

// True if *all* components are non-zero.
static inline bool vec4_all(vec4 src0)
{
	bool rets = (
		(src0.x != 0) &&
		(src0.y != 0) &&
		(src0.z != 0) &&
		(src0.w != 0));
	return rets;
}

// True if *any* components are non-zero.
static inline bool vec4_any(vec4 src0)
{
	bool rets = (
		(src0.x != 0) ||
		(src0.y != 0) ||
		(src0.z != 0) ||
		(src0.w != 0));
	return rets;
}

// Four-component dot product.
static inline float vec4_dot(vec4 src0, vec4 src1)
{
	float dot_product = 0.0f;
	dot_product += (src0.x * src1.x);
	dot_product += (src0.y * src1.y);
	dot_product += (src0.z * src1.z);
	dot_product += (src0.w * src1.w);
	return dot_product;
}

// Reflection vector through a normal (normal vector should be perpendicular to the surface, and cross
// through the intersection point.
//	   ____________________________________
//	  |				  normal			   |
//	  |	reflection  \	|   / incident 	   |
//	  |	             \	|  /			   |
//	  |	              \ | /				   |
//	  |	               \|/				   |
//	  |	  surface ------*------    		   |
//	  |____________________________________|
static inline vec4 vec4_reflect(vec4 incident, vec4 surface_normal)
{
	float dot_product	= 2.0f * vec4_dot(incident, surface_normal);
	vec4 product		= vec4_mul_scalar(surface_normal, dot_product);
	vec4 reflection		= vec4_sub(incident, product);
	return reflection;
}

// Magnitude/Length 
static inline float vec4_magnitude(vec4 src0)
{
	float dot		= vec4_dot(src0, src0);
	float magnitude = sqrtf(dot);
	return magnitude;
}

// Unit-vector
static inline vec4 vec4_normalize(vec4 src0)
{
	float magnitude		= vec4_magnitude(src0);
	vec4 unit_vector	= vec4_div_scalar(src0, magnitude);
	return unit_vector;
}

// Euclidean distance.
static inline float vec4_distance(vec4 src0, vec4 src1)
{
	vec4 difference = vec4_sub(src0, src1);
	float distance	= vec4_magnitude(difference);
	return distance;
}

// Angle between two vectors in radians.
static inline float vec4_angle(vec4 src0, vec4 src1)
{
	float mag_a		= vec4_magnitude(src0);
	float mag_b		= vec4_magnitude(src1);
	float dot		= vec4_dot(src0, src1);
	float cos		= dot / (mag_a * mag_b);
	float radians	= acosf(cos);
	return radians;
}

// Per-component conversion from radians to degrees.
static inline vec4 vec4_degrees(vec4 radians)
{
	vec4 degrees;
	degrees.x = (float)(radians.x * 57.29577951308232157827); // multiply by 180/pi.
	degrees.y = (float)(radians.y * 57.29577951308232157827); // multiply by 180/pi.
	degrees.z = (float)(radians.z * 57.29577951308232157827); // multiply by 180/pi.
	degrees.w = (float)(radians.w * 57.29577951308232157827); // multiply by 180/pi.
	return degrees;
}

// Per-component conversion from degrees to radians.
static inline vec4 vec4_radians(vec4 degrees)
{
	vec4 radians;
	radians.x = (float)(degrees.x * 0.01745329251994329556); // multiply by pi/180.
	radians.y = (float)(degrees.y * 0.01745329251994329556); // multiply by pi/180.
	radians.z = (float)(degrees.z * 0.01745329251994329556); // multiply by pi/180.
	radians.w = (float)(degrees.w * 0.01745329251994329556); // multiply by pi/180.
	return radians;
}

// 3-component cross product of two vec4.
static inline vec4 vec4_cross(vec4 src0, vec4 src1)
{
	vec4 cross_product;
	cross_product.x = (src0.y * src1.z) - (src1.y * src0.z);
	cross_product.y = (src0.z * src1.x) - (src1.z * src0.x);
	cross_product.z = (src0.x * src1.y) - (src1.x * src0.y);
	cross_product.w = 1.0f;
	return cross_product;
}

// Per-component computation of closest integer rounded towards -∞.
static inline vec4 vec4_floor(vec4 src0)
{
	vec4 floor;
	floor.x = floorf(src0.x);
	floor.y = floorf(src0.y);
	floor.z = floorf(src0.z);
	floor.w = floorf(src0.w);
	return floor;
}

// Per-component computation of closest integer rounded towards ∞.
static inline vec4 vec4_ceil(vec4 src0)
{
	vec4 ceiling;
	ceiling.x = ceilf(src0.x);
	ceiling.y = ceilf(src0.y);
	ceiling.z = ceilf(src0.z);
	ceiling.w = ceilf(src0.w);
	return ceiling;
}

// Per-component computation of closest integer rounded towards 0.
static inline vec4 vec4_trunc(vec4 src0)
{
	vec4 truncated;
	truncated.x = truncf(src0.x);
	truncated.y = truncf(src0.y);
	truncated.z = truncf(src0.z);
	truncated.w = truncf(src0.w);
	return truncated;
}

// Per-component fractional component (src0 - floor(src0)).
static inline vec4 vec4_frac(vec4 src0)
{
	vec4 rets;
	rets.x = src0.x - floorf(src0.x);
	rets.y = src0.y - floorf(src0.y);
	rets.z = src0.z - floorf(src0.z);
	rets.w = src0.w - floorf(src0.w);
	return rets;
}

// Per-component maximum of two vec4.
static inline vec4 vec4_max(vec4 src0, vec4 src1)
{
	vec4 maximum;
	maximum.x = fmaxf(src0.x, src1.x);
	maximum.y = fmaxf(src0.y, src1.y);
	maximum.z = fmaxf(src0.z, src1.z);
	maximum.w = fmaxf(src0.w, src1.w);
	return maximum;
}

// Per-component maximum of a vec4 and a scalar.
static inline vec4 vec4_max_scalar(vec4 src0, float src1)
{
	vec4 maximum;
	maximum.x = fmaxf(src0.x, src1);
	maximum.y = fmaxf(src0.y, src1);
	maximum.z = fmaxf(src0.z, src1);
	maximum.w = fmaxf(src0.w, src1);
	return maximum;
}

// Per-component minimum of two vec4.
static inline vec4 vec4_min(vec4 src0, vec4 src1)
{
	vec4 minimum;
	minimum.x = fminf(src0.x, src1.x);
	minimum.y = fminf(src0.y, src1.y);
	minimum.z = fminf(src0.z, src1.z);
	minimum.w = fminf(src0.w, src1.w);
	return minimum;
}

// Per-component minimum of a vec4 and a scalar.
static inline vec4 vec4_min_scalar(vec4 src0, float src1)
{
	vec4 minimum;
	minimum.x = fminf(src0.x, src1);
	minimum.y = fminf(src0.y, src1);
	minimum.z = fminf(src0.z, src1);
	minimum.w = fminf(src0.w, src1);
	return minimum;
}

// Per-component clamp of src0 into the range of vectors (minimum..maximum).
static inline vec4 vec4_clamp(vec4 src0, vec4 minimum, vec4 maximum)
{
	vec4 clamped_lower	= vec4_max(src0, minimum);
	vec4 clamped		= vec4_min(clamped_lower, maximum);
	return clamped;
}

// Per-component clamp of src0 into the range of scalars (minimum..maximum).
static inline vec4 vec4_clamp_scalar(vec4 src0, float minimum, float maximum)
{
	vec4 clamped_lower	= vec4_max_scalar(src0, minimum);
	vec4 clamped		= vec4_min_scalar(clamped_lower, maximum);
	return clamped;
}

// Inverts a color stored in a vector (color channels must be scaled to `0..1`
static inline vec4 vec4_invert_color(vec4 color)
{
	vec4 inverted_color;
	inverted_color.r = 1.0f - color.r;
	inverted_color.g = 1.0f - color.g;
	inverted_color.b = 1.0f - color.b;
	inverted_color.a = color.a;
	return inverted_color;
}
#pragma endregion

#pragma region Test Functions
static inline void vec2_test_all()
{
	vec2 a = vec2_init_from_1(1.0f);
	vec2 b = vec2_init_from_2(1.0f, 1.0f);
	vec2 c = vec2_swizzle(a, X, Y);

	a = vec2_mask(a, b, MASK_XY);
	a = vec2_negate(a);
	a = vec2_add(a, b);
	a = vec2_add_scalar(a, 1.0f);
	a = vec2_sub(a, b);
	a = vec2_sub_scalar(a, 1.0f);
	a = vec2_mul(a, b);
	a = vec2_mul_scalar(a, 1.0f);
	a = vec2_div(a, b);
	a = vec2_div_scalar(a, 1.0f);
	a = vec2_pow(a, b);
	a = vec2_pow_scalar(a, 1.0f);
	a = vec2_sqrt(a);
	a = vec2_rcp(a);
	a = vec2_rsqrt(a);
	a = vec2_abs(a);
	a = vec2_sin(a);
	a = vec2_cos(a);
	a = vec2_tan(a);
	a = vec2_asin(a);
	a = vec2_acos(a);
	a = vec2_atan(a);
	a = vec2_csc(a);
	a = vec2_sec(a);
	a = vec2_cot(a);
	a = vec2_sinh(a);
	a = vec2_cosh(a);
	a = vec2_tanh(a);
	a = vec2_csch(a);
	a = vec2_sech(a);
	a = vec2_coth(a);

	bool	v = vec2_all(a);
	v = vec2_any(a);

	float	f = vec2_dot(a, b);

	a = vec2_reflect(a, b);
	f = vec2_magnitude(a);
	a = vec2_normalize(a);
	f = vec2_distance(a, b);
	f = vec2_angle(a, b);
	a = vec2_degrees(a);
	a = vec2_radians(a);
	f = vec2_perp(a, b);
	a = vec2_floor(a);
	a = vec2_ceil(a);
	a = vec2_trunc(a);
	a = vec2_frac(a);
	a = vec2_max(a, b);
	a = vec2_max_scalar(a, 1.0f);
	a = vec2_min(a, b);
	a = vec2_min_scalar(a, 1.0f);
	a = vec2_clamp(a, b, c);
	a = vec2_clamp_scalar(a, 1.0f, 1.0f);
}

static inline void vec3_test_all()
{
	vec3 a = vec3_init_from_1(1.0f);
	vec3 b = vec3_init_from_3(1.0f, 1.0f, 1.0f);
	vec3 c = vec3_swizzle(a, X, Y, Z);

	a = vec3_mask(a, b, MASK_XY);
	a = vec3_negate(a);
	a = vec3_add(a, b);
	a = vec3_add_scalar(a, 1.0f);
	a = vec3_sub(a, b);
	a = vec3_sub_scalar(a, 1.0f);
	a = vec3_mul(a, b);
	a = vec3_mul_scalar(a, 1.0f);
	a = vec3_div(a, b);
	a = vec3_div_scalar(a, 1.0f);
	a = vec3_pow(a, b);
	a = vec3_pow_scalar(a, 1.0f);
	a = vec3_sqrt(a);
	a = vec3_rcp(a);
	a = vec3_rsqrt(a);
	a = vec3_abs(a);
	a = vec3_sin(a);
	a = vec3_cos(a);
	a = vec3_tan(a);
	a = vec3_asin(a);
	a = vec3_acos(a);
	a = vec3_atan(a);
	a = vec3_csc(a);
	a = vec3_sec(a);
	a = vec3_cot(a);
	a = vec3_sinh(a);
	a = vec3_cosh(a);
	a = vec3_tanh(a);
	a = vec3_csch(a);
	a = vec3_sech(a);
	a = vec3_coth(a);

	bool	v = vec3_all(a);
	v = vec3_any(a);

	float	f = vec3_dot(a, b);

	a = vec3_reflect(a, b);
	f = vec3_magnitude(a);
	a = vec3_normalize(a);
	f = vec3_distance(a, b);
	f = vec3_angle(a, b);
	a = vec3_degrees(a);
	a = vec3_radians(a);
	a = vec3_cross(a, b);
	a = vec3_floor(a);
	a = vec3_ceil(a);
	a = vec3_trunc(a);
	a = vec3_frac(a);
	a = vec3_max(a, b);
	a = vec3_max_scalar(a, 1.0f);
	a = vec3_min(a, b);
	a = vec3_min_scalar(a, 1.0f);
	a = vec3_clamp(a, b, c);
	a = vec3_clamp_scalar(a, 1.0f, 1.0f);
}

static inline void vec4_test_all()
{
	vec4 a = vec4_init_from_1(1.0f);
	vec4 b = vec4_init_from_4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 c = vec4_swizzle(a, X, Y, Z, W);

	a = vec4_mask(a, b, MASK_XY);
	a = vec4_negate(a);
	a = vec4_add(a, b);
	a = vec4_add_scalar(a, 1.0f);
	a = vec4_sub(a, b);
	a = vec4_sub_scalar(a, 1.0f);
	a = vec4_mul(a, b);
	a = vec4_mul_scalar(a, 1.0f);
	a = vec4_div(a, b);
	a = vec4_div_scalar(a, 1.0f);
	a = vec4_pow(a, b);
	a = vec4_pow_scalar(a, 1.0f);
	a = vec4_sqrt(a);
	a = vec4_rcp(a);
	a = vec4_rsqrt(a);
	a = vec4_abs(a);
	a = vec4_sin(a);
	a = vec4_cos(a);
	a = vec4_tan(a);
	a = vec4_asin(a);
	a = vec4_acos(a);
	a = vec4_atan(a);
	a = vec4_csc(a);
	a = vec4_sec(a);
	a = vec4_cot(a);
	a = vec4_sinh(a);
	a = vec4_cosh(a);
	a = vec4_tanh(a);
	a = vec4_csch(a);
	a = vec4_sech(a);
	a = vec4_coth(a);

	bool	v = vec4_all(a);
	v = vec4_any(a);

	float	f = vec4_dot(a, b);

	a = vec4_reflect(a, b);
	f = vec4_magnitude(a);
	a = vec4_normalize(a);
	f = vec4_distance(a, b);
	f = vec4_angle(a, b);
	a = vec4_degrees(a);
	a = vec4_radians(a);
	a = vec4_cross(a, b);
	a = vec4_floor(a);
	a = vec4_ceil(a);
	a = vec4_trunc(a);
	a = vec4_frac(a);
	a = vec4_max(a, b);
	a = vec4_max_scalar(a, 1.0f);
	a = vec4_min(a, b);
	a = vec4_min_scalar(a, 1.0f);
	a = vec4_clamp(a, b, c);
	a = vec4_clamp_scalar(a, 1.0f, 1.0f);
}
#pragma endregion

#endif /* VECTORS_H */