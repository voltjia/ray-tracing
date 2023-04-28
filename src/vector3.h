#ifndef VECTOR3_H
#define VECTOR3_H

namespace ray_tracing {

struct Vector3 {
    using ValueType = float;

    Vector3() = default;

    Vector3(ValueType x, ValueType y, ValueType z);

    static ValueType dot(const Vector3& lhs, const Vector3& rhs);

    ValueType magnitude_sqaured() const;

    ValueType magnitude() const;

    Vector3 normalized() const;

    static const Vector3 zero;

    static const Vector3 one;

    static const Vector3 up;

    static const Vector3 down;

    static const Vector3 left;

    static const Vector3 right;

    static const Vector3 forward;

    static const Vector3 back;

    ValueType x;

    ValueType y;

    ValueType z;
};

Vector3 operator-(const Vector3& vec);

Vector3 operator+(const Vector3& lhs, const Vector3& rhs);

Vector3 operator-(const Vector3& lhs, const Vector3& rhs);

Vector3 operator*(Vector3::ValueType lhs, const Vector3& rhs);

Vector3 operator*(const Vector3& lhs, Vector3::ValueType rhs);

Vector3 operator/(const Vector3& lhs, Vector3::ValueType rhs);

Vector3& operator+=(Vector3& lhs, const Vector3& rhs);

Vector3& operator-=(Vector3& lhs, const Vector3& rhs);

Vector3& operator*=(Vector3& lhs, Vector3::ValueType rhs);

Vector3& operator/=(Vector3& lhs, Vector3::ValueType rhs);

}

#endif
