#pragma once

/** How many 4D vectors fit in the QuadReg */
#define VECS_QUAD_NUM (VECS_SIZE / 4 / sizeof (float))

#if defined(__x86_64__)

#include <immintrin.h>

/** Size in bytes of the underlying type. */
#define VECS_SIZE 32

/** Opaque dedicated type that can store `VECS_QUAD_NUM` 4D vectors */
typedef __m256 VECS_Quad;

#define VECS_QuadSplat(x) ((VECS_QuadReg)(_mm256_set1_ps(x)))
/** Set all */
#define VECS_QuadSetEach(x, y, z, w) ((VECS_QuadReg)(_mm256_set_ps(w, y, z, x, w, y, z, x)))

/** `ptr` must be aligned to `VECS_SIZE`. */
#define VECS_QuadLoad(ptr) ((VECS_QuadReg)(_mm256_load_ps(ptr)))
#define VECS_QuadLoadUnaligned(ptr) ((VECS_QuadReg)(_mm256_loadu_ps(ptr)))  
/** `ptr` must be aligned to `VECS_SIZE`. */
#define VECS_QuadStore(ptr, a) (_mm256_store_ps(ptr, a))
#define VECS_QuadStoreUnaligned(ptr, a) (_mm256_storeu_ps(ptr, a))

#define VECS_QuadAdd(a, b) ((VECS_QuadReg)(_mm256_add_ps(a, b)))
#define VECS_QuadSub(a, b) ((VECS_QuadReg)(_mm256_sub_ps(a, b)))
#define VECS_QuadMul(a, b) ((VECS_QuadReg)(_mm256_mul_ps(a, b)))
#define VECS_QuadDiv(a, b) ((VECS_QuadReg)(_mm256_div_ps(a, b)))

/** Fused Multiply-Add: (a * b) + c */
#define VECS_QuadMulAdd(a, b, c) ((VECS_QuadReg)(_mm256_fmadd_ps(a, b, c)))
#define VECS_QuadSqrt(a) ((VECS_QuadReg)(_mm256_sqrt_ps(a)))
/** Fast but lower precision approximation */
#define VECS_QuadRcp(a) ((VECS_QuadReg)(_mm256_rcp_ps(a)))

#define VECS_QuadBlend(a, b, mask) ((VECS_QuadReg)(_mm256_blendv_ps(a, b, mask)))

#define VECS_QuadMin(a, b) ((VECS_QuadReg)(_mm256_min_ps(a, b)))
#define VECS_QuadMax(a, b) ((VECS_QuadReg)(_mm256_max_ps(a, b)))
#define VECS_QuadAbs(a) ((VECS_QuadReg)(_mm256_andnot_ps(_mm256_set1_ps(-0.0f), a)))

#endif

