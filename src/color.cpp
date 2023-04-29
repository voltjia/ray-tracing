#include "color.h"

#include <algorithm>
#include <cmath>

namespace ray_tracing {

Color::Color(ValueType r, ValueType g, ValueType b, ValueType a)
    : r{std::max(0.0, std::min(1.0, r))},
      g{std::max(0.0, std::min(1.0, g))},
      b{std::max(0.0, std::min(1.0, b))},
      a{std::max(0.0, std::min(1.0, a))} {}

Color Color::lerp_unclamped(const Color& c0, const Color& c1, ValueType t) {
    return (1 - t) * c0 + t * c1;
}

Color Color::lerp(const Color& c0, const Color& c1, ValueType t) {
    return lerp_unclamped(c0, c1, std::max(0.0, std::min(1.0, t)));
}

Color Color::gamma() const {
    return Color{std::sqrt(r), std::sqrt(g), std::sqrt(b), std::sqrt(a)};
}

Color operator-(const Color& color) {
    return Color{-color.r, -color.g, -color.b, -color.a};
}

Color operator+(const Color& lhs, const Color& rhs) {
    return Color{lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b, lhs.a + rhs.a};
}

Color operator-(const Color& lhs, const Color& rhs) {
    return lhs + -rhs;
}

Color operator*(Color::ValueType lhs, const Color& rhs) {
    return Color{lhs * rhs.r, lhs * rhs.g, lhs * rhs.b, lhs * rhs.a};
}

Color operator*(const Color& lhs, Color::ValueType rhs) {
    return rhs * lhs;
}

Color operator/(const Color& lhs, Color::ValueType rhs) {
    return (1 / rhs) * lhs;
}

Color& operator+=(Color& lhs, const Color& rhs) {
    lhs.r += rhs.r;
    lhs.g += rhs.g;
    lhs.b += rhs.b;
    lhs.a += rhs.a;
    return lhs;
}

Color& operator-=(Color& lhs, const Color& rhs) {
    lhs += -rhs;
    return lhs;
}

Color& operator*=(Color& lhs, Color::ValueType rhs) {
    lhs.r *= rhs;
    lhs.g *= rhs;
    lhs.b *= rhs;
    lhs.a *= rhs;
    return lhs;
}

Color& operator/=(Color& lhs, Color::ValueType rhs) {
    lhs *= (1 / rhs);
    return lhs;
}

const Color Color::clear{0, 0, 0, 0};

const Color Color::black{0, 0, 0, 1};

const Color Color::white{1, 1, 1, 1};

const Color Color::gray{0.5, 0.5, 0.5, 1};

const Color Color::red{1, 0, 0, 1};

const Color Color::green{0, 1, 0, 1};

const Color Color::blue{0, 0, 1, 1};

const Color Color::cyan{0, 1, 1, 1};

const Color Color::magenta{1, 0, 1, 1};

const Color Color::yellow{1, 1, 0, 1};

}
