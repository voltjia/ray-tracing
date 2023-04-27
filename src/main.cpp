#include "color.h"
#include "ray.h"

#include <iostream>

using namespace ray_tracing;

static Color background_color(const Ray& ray) {
    return Color::lerp(Color{0.5, 0.7, 1, 1},
                       Color::white,
                       0.5 * (ray.direction.y + 1));
}

static Color::ValueType scale_256(Color::ValueType value) {
    return std::floor(value == 1 ? 255 : value * 256);
}

int main() {
    constexpr auto aspect_radio{16.0 / 9.0};
    constexpr std::size_t image_width{400};
    constexpr auto image_height{
        static_cast<decltype(image_width)>(image_width / aspect_radio)};

    constexpr auto viewport_height{2.0};
    constexpr auto viewport_width{aspect_radio * viewport_height};
    constexpr auto focal_length{1.0};

    auto origin{Vector3::zero};
    auto horizontal{Vector3::right * viewport_width};
    auto vertical{Vector3::up * viewport_height};
    auto lower_left_corner{origin - vertical / 2 - horizontal / 2
                           + Vector3::forward * focal_length};

    // Output PPM format. See https://en.wikipedia.org/wiki/Netpbm.
    // TODO: Consider writing to a file directly.
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (auto row{decltype(image_height){0}}; row < image_height; ++row) {
        for (auto col{decltype(image_width){0}}; col < image_width; ++col) {
            auto u{static_cast<Vector3::ValueType>(col) / (image_width - 1)};
            auto v{static_cast<Vector3::ValueType>(row) / (image_height - 1)};
            Ray ray{origin,
                    lower_left_corner + u * horizontal + v * vertical - origin};
            Color color{background_color(ray)};

            std::cout << scale_256(color.r) << ' ';
            std::cout << scale_256(color.g) << ' ';
            std::cout << scale_256(color.b) << '\n';
        }
    }

    return 0;
}
