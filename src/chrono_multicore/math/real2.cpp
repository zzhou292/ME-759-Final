#include "chrono_multicore/math/real2.h"
#include <iostream>

namespace chrono {

CUDA_HOST_DEVICE real2 operator+(const real2& a, real b) {
    return real2(a.x + b, a.y + b);
}
CUDA_HOST_DEVICE real2 operator-(const real2& a, real b) {
    return real2(a.x - b, a.y - b);
}
CUDA_HOST_DEVICE real2 operator*(const real2& a, real b) {
    return real2(a.x * b, a.y * b);
}
CUDA_HOST_DEVICE real2 operator/(const real2& a, real b) {
    return real2(a.x / b, a.y / b);
}

CUDA_HOST_DEVICE real2 operator+(const real2& a, const real2& b) {
    return real2(a.x + b.x, a.y + b.y);
}
CUDA_HOST_DEVICE real2 operator-(const real2& a, const real2& b) {
    return real2(a.x - b.x, a.y - b.y);
}
CUDA_HOST_DEVICE real2 operator*(const real2& a, const real2& b) {
    return real2(a.x * b.x, a.y * b.y);
}
CUDA_HOST_DEVICE real2 operator/(const real2& a, const real2& b) {
    return real2(a.x / b.x, a.y / b.y);
}
CUDA_HOST_DEVICE real2 operator-(const real2& a) {
    return real2(-a.x, -a.y);
}

CUDA_HOST_DEVICE OPERATOR_EQUALS_IMPL(*, real, real2);
CUDA_HOST_DEVICE OPERATOR_EQUALS_IMPL(/, real, real2);
CUDA_HOST_DEVICE OPERATOR_EQUALS_IMPL(+, real, real2);
CUDA_HOST_DEVICE OPERATOR_EQUALS_IMPL(-, real, real2);

CUDA_HOST_DEVICE OPERATOR_EQUALS_IMPL(*, real2, real2);
CUDA_HOST_DEVICE OPERATOR_EQUALS_IMPL(/, real2, real2);
CUDA_HOST_DEVICE OPERATOR_EQUALS_IMPL(+, real2, real2);
CUDA_HOST_DEVICE OPERATOR_EQUALS_IMPL(-, real2, real2);

CUDA_HOST_DEVICE real2 operator*(real lhs, const real2& rhs) {
    real2 r(rhs);
    r *= lhs;
    return r;
}

CUDA_HOST_DEVICE bool operator==(const real2& lhs, const real2& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

CUDA_HOST_DEVICE real2 Max(const real2& a, const real2& b) {
    return real2(Max(a.x, b.x), Max(a.y, b.y));
}

CUDA_HOST_DEVICE real2 Min(const real2& a, const real2& b) {
    return real2(Min(a.x, b.x), Min(a.y, b.y));
}

CUDA_HOST_DEVICE real Dot(const real2& v1, const real2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

CUDA_HOST_DEVICE real Dot(const real2& v) {
    return v.x * v.x + v.y * v.y;
}

CUDA_HOST_DEVICE real Length2(const real2& v1) {
    return v1.x * v1.x + v1.y * v1.y;
}
CUDA_HOST_DEVICE real2 Normalize(const real2& v1) {
    return v1 / Sqrt(Dot(v1));
}
CUDA_HOST_DEVICE void Print(real2 v, const char* name) {
    printf("%s\n", name);
    printf("%f %f\n", v.x, v.y);
}
}
