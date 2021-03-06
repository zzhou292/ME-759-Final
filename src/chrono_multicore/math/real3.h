// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2016 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Hammad Mazhar
// =============================================================================
//
// Description: Vectorized implementation of a 3d vector
// =============================================================================

#pragma once

#include "chrono_multicore/math/real.h"
#include "chrono_multicore/math/real2.h"

#if !defined(__CUDACC__)
#include "chrono_multicore/math/sse.h"
#endif

namespace chrono {

/// @addtogroup multicore_math
/// @{

/// Chrono::Multicore triplet (3-dimensional vector).
class CH_MULTICORE_API real3 {
  public:
    CUDA_HOST_DEVICE inline real3() { array[3] = 0; }
    CUDA_HOST_DEVICE inline explicit real3(real a) {
        array[0] = a;
        array[1] = a;
        array[2] = a;
        array[3] = 0;
    }
    CUDA_HOST_DEVICE inline real3(real a, real b, real c) {
        array[0] = a;
        array[1] = b;
        array[2] = c;
        array[3] = 0;
    }
    CUDA_HOST_DEVICE inline real3(const real3& v) {
        array[0] = v.x;
        array[1] = v.y;
        array[2] = v.z;
        array[3] = 0;
    }
    CUDA_HOST_DEVICE inline real operator[](unsigned int i) const { return array[i]; }
    CUDA_HOST_DEVICE inline real& operator[](unsigned int i) { return array[i]; }
    CUDA_HOST_DEVICE inline real3& operator=(const real3& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = 0;
        return *this;  // Return a reference to myself.
    }

#if defined(USE_AVX)
    inline real3(__m256d m) { _mm256_storeu_pd(&array[0], m); }
    inline operator __m256d() const { return _mm256_loadu_pd(&array[0]); }
    inline real3& operator=(const __m256d& rhs) {
        _mm256_storeu_pd(&array[0], rhs);
        return *this;
    }
    static inline __m256d Set(real x) { return _mm256_set1_pd(x); }
    static inline __m256d Set(real x, real y, real z) { return _mm256_setr_pd(x, y, z, 0.0); }

#elif defined(USE_SSE)
    inline real3(__m128 m) { _mm_storeu_ps(&array[0], m); }
    inline operator __m128() const { return _mm_loadu_ps(&array[0]); }
    inline real3& operator=(const __m128& rhs) {
        _mm_storeu_ps(&array[0], rhs);
        return *this;
    }
    static inline __m128 Set(real x) { return _mm_set1_ps(x); }
    static inline __m128 Set(real x, real y, real z) { return _mm_setr_ps(x, y, z, 0.0f); }
#else

#endif

    // ========================================================================================
    union {
        real array[4];
        struct {
            real x, y, z, w;
        };
    };
};

CUDA_HOST_DEVICE CH_MULTICORE_API real3 Set3(real x);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 Set3(real x, real y, real z);

CUDA_HOST_DEVICE CH_MULTICORE_API real3 operator+(const real3& a, real b);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 operator-(const real3& a, real b);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 operator*(const real3& a, real b);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 operator/(const real3& a, real b);

CUDA_HOST_DEVICE CH_MULTICORE_API real3 operator+(const real3& a, const real3& b);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 operator-(const real3& a, const real3& b);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 operator*(const real3& a, const real3& b);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 operator/(const real3& a, const real3& b);

CUDA_HOST_DEVICE CH_MULTICORE_API OPERATOR_EQUALS_PROTO(*, real, real3);
CUDA_HOST_DEVICE CH_MULTICORE_API OPERATOR_EQUALS_PROTO(/, real, real3);
CUDA_HOST_DEVICE CH_MULTICORE_API OPERATOR_EQUALS_PROTO(+, real, real3);
CUDA_HOST_DEVICE CH_MULTICORE_API OPERATOR_EQUALS_PROTO(-, real, real3);

CUDA_HOST_DEVICE CH_MULTICORE_API OPERATOR_EQUALS_PROTO(*, real3, real3);
CUDA_HOST_DEVICE CH_MULTICORE_API OPERATOR_EQUALS_PROTO(/, real3, real3);
CUDA_HOST_DEVICE CH_MULTICORE_API OPERATOR_EQUALS_PROTO(+, real3, real3);
CUDA_HOST_DEVICE CH_MULTICORE_API OPERATOR_EQUALS_PROTO(-, real3, real3);

CUDA_HOST_DEVICE CH_MULTICORE_API real3 operator-(const real3& a);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 operator*(real lhs, const real3& rhs);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 operator/(real lhs, const real3& rhs);

CUDA_HOST_DEVICE CH_MULTICORE_API bool operator<(const real3& lhs, const real3& rhs);
CUDA_HOST_DEVICE CH_MULTICORE_API bool operator>(const real3& lhs, const real3& rhs);
CUDA_HOST_DEVICE CH_MULTICORE_API bool operator==(const real3& lhs, const real3& rhs);

CUDA_HOST_DEVICE CH_MULTICORE_API real3 Cross(const real3& b, const real3& c);
CUDA_HOST_DEVICE CH_MULTICORE_API real Dot(const real3& v1, const real3& v2);
CUDA_HOST_DEVICE CH_MULTICORE_API real Dot(const real3& v);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 Normalize(const real3& v);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 Sqrt(const real3& v);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 Round(const real3& v);
CUDA_HOST_DEVICE CH_MULTICORE_API real Length(const real3& v);
CUDA_HOST_DEVICE CH_MULTICORE_API real Length2(const real3& v1);
CUDA_HOST_DEVICE CH_MULTICORE_API real SafeLength(const real3& v);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 SafeNormalize(const real3& v, const real3& safe = real3(0));
CUDA_HOST_DEVICE CH_MULTICORE_API real Max(const real3& a);
CUDA_HOST_DEVICE CH_MULTICORE_API real Min(const real3& a);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 Max(const real3& a, const real3& b);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 Min(const real3& a, const real3& b);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 Max(const real3& a, const real& b);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 Min(const real3& a, const real& b);
CUDA_HOST_DEVICE CH_MULTICORE_API bool IsZero(const real3& v);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 Abs(const real3& v);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 Sign(const real3& v);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 Clamp(const real3& v, real max_length);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 Clamp(const real3& a, const real3& clamp_min, const real3& clamp_max);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 OrthogonalVector(const real3& v);
CUDA_HOST_DEVICE CH_MULTICORE_API real3 UnitOrthogonalVector(const real3& v);
CUDA_HOST_DEVICE CH_MULTICORE_API void Sort(real& a, real& b, real& c);
CUDA_HOST_DEVICE CH_MULTICORE_API void Print(real3 v, const char* name);

/// @} multicore_math

} // end namespace chrono
