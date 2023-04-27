#ifndef COLOR_H
#define COLOR_H

#include <iostream>

namespace ray_tracing {

struct Color {
    using ValueType = double;

    Color(ValueType r, ValueType g, ValueType b, ValueType a);

    static Color lerp_unclamped(const Color& c0, const Color& c1, ValueType t);

    static Color lerp(const Color& c0, const Color& c1, ValueType t);

    static const Color clear;

    static const Color black;

    static const Color white;

    static const Color gray;

    static const Color red;

    static const Color green;

    static const Color blue;

    static const Color cyan;

    static const Color magenta;

    static const Color yellow;

    ValueType r;

    ValueType g;

    ValueType b;

    ValueType a;
};

Color operator-(const Color& color);

Color operator+(const Color& lhs, const Color& rhs);

Color operator-(const Color& lhs, const Color& rhs);

Color operator*(Color::ValueType lhs, const Color& rhs);

Color operator*(const Color& lhs, Color::ValueType rhs);

Color operator/(const Color& lhs, Color::ValueType rhs);

Color& operator+=(Color& lhs, const Color& rhs);

Color& operator-=(Color& lhs, const Color& rhs);

Color& operator*=(Color& lhs, Color::ValueType rhs);

Color& operator/=(Color& lhs, Color::ValueType rhs);

}

#endif
