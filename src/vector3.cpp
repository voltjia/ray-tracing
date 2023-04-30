#include "vector3.h"

#include "utils.h"

#include <cmath>

namespace ray_tracing {

Vector3::Vector3(ValueType x, ValueType y, ValueType z) : x{x}, y{y}, z{z} {}

Vector3::ValueType Vector3::dot(const Vector3& lhs, const Vector3& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::cross(const Vector3& lhs, const Vector3& rhs) {
    return Vector3{lhs.y * rhs.z - lhs.z * rhs.y,
                   lhs.z * rhs.x - lhs.x * rhs.z,
                   lhs.x * rhs.y - lhs.y * rhs.x};
}

Vector3 Vector3::random(ValueType min, ValueType max) {
    return Vector3{random_float(min, max),
                   random_float(min, max),
                   random_float(min, max)};
}

Vector3::ValueType Vector3::magnitude_sqaured() const {
    return x * x + y * y + z * z;
}

Vector3::ValueType Vector3::magnitude() const {
    return std::sqrt(magnitude_sqaured());
}

Vector3 Vector3::normalized() const {
    return *this / magnitude();
}

Vector3 operator-(const Vector3& vec) {
    return Vector3{-vec.x, -vec.y, -vec.z};
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
    return Vector3{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
    return lhs + -rhs;
}

Vector3 operator*(Vector3::ValueType lhs, const Vector3& rhs) {
    return Vector3{lhs * rhs.x, lhs * rhs.y, lhs * rhs.z};
}

Vector3 operator*(const Vector3& lhs, Vector3::ValueType rhs) {
    return rhs * lhs;
}

Vector3 operator/(const Vector3& lhs, Vector3::ValueType rhs) {
    return (1 / rhs) * lhs;
}

Vector3& operator+=(Vector3& lhs, const Vector3& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}

Vector3& operator-=(Vector3& lhs, const Vector3& rhs) {
    lhs += -rhs;
    return lhs;
}

Vector3& operator*=(Vector3& lhs, Vector3::ValueType rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    return lhs;
}

Vector3& operator/=(Vector3& lhs, Vector3::ValueType rhs) {
    lhs *= (1 / rhs);
    return lhs;
}

const Vector3 Vector3::zero{0, 0, 0};

const Vector3 Vector3::one{1, 1, 1};

const Vector3 Vector3::up{0, 1, 0};

const Vector3 Vector3::down{0, -1, 0};

const Vector3 Vector3::left{-1, 0, 0};

const Vector3 Vector3::right{1, 0, 0};

const Vector3 Vector3::forward{0, 0, 1};

const Vector3 Vector3::back{0, 0, -1};

}
