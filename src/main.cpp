#include "color.h"
#include "ray.h"

#include <png.h>

#include <iostream>
#include <vector>

#include <cmath>
#include <cstdio>

using namespace ray_tracing;

static constexpr std::size_t num_channels{4};

static Color::ValueType scale_256(Color::ValueType value) {
    return std::floor(value == 1 ? 255 : value * 256);
}

static bool write_png(const char* filename,
                      std::size_t width,
                      std::size_t height,
                      std::uint8_t* buffer) {
    auto fp{fopen(filename, "wb")};
    if (!fp) {
        std::cerr << "Failed to open file: " << filename << ".\n";
        return false;
    }

    auto png_ptr{png_create_write_struct(PNG_LIBPNG_VER_STRING,
                                         nullptr,
                                         nullptr,
                                         nullptr)};
    if (!png_ptr) {
        std::cerr << "Failed to create PNG write struct.\n";
        fclose(fp);
        return false;
    }

    auto info_ptr{png_create_info_struct(png_ptr)};
    if (!info_ptr) {
        std::cerr << "Failed to create PNG info struct.\n";
        png_destroy_write_struct(&png_ptr, nullptr);
        fclose(fp);
        return false;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        std::cerr << "Failed to set PNG jump buffer.\n";
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return false;
    }

    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr,
                 info_ptr,
                 width,
                 height,
                 8,
                 PNG_COLOR_TYPE_RGBA,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);
    auto row{new png_byte[num_channels * width]};

    for (auto y{decltype(height){0}}; y < height; ++y) {
        for (auto x{decltype(width){0}}; x < width; ++x) {
            for (auto i{decltype(num_channels){0}}; i < num_channels; ++i) {
                row[x * num_channels + i]
                    = buffer[(y * width + x) * num_channels + i];
            }
        }
        png_write_row(png_ptr, row);
    }
    png_write_end(png_ptr, nullptr);

    delete[] row;
    png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

    return true;
}

static Color background_color(const Ray& ray) {
    return Color::lerp(Color{0.5, 0.7, 1, 1},
                       Color::white,
                       0.5 * (ray.direction.y + 1));
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <output.png>\n";
        return 1;
    }

    const char* output_filename = argv[1];

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

    std::vector<std::uint8_t> buffer(num_channels * image_width * image_height);

    for (auto row{decltype(image_height){0}}; row < image_height; ++row) {
        for (auto col{decltype(image_width){0}}; col < image_width; ++col) {
            auto u{static_cast<Vector3::ValueType>(col) / (image_width - 1)};
            auto v{static_cast<Vector3::ValueType>(row) / (image_height - 1)};
            Ray ray{origin,
                    lower_left_corner + u * horizontal + v * vertical - origin};
            auto color{background_color(ray)};
            auto index{num_channels * (row * image_width + col)};
            buffer[index] = scale_256(color.r);
            buffer[index + 1] = scale_256(color.g);
            buffer[index + 2] = scale_256(color.b);
            buffer[index + 3] = scale_256(color.a);
        }
    }

    if (write_png(output_filename, image_width, image_height, buffer.data())) {
        std::cout << "PNG file '" << output_filename
                  << "' created successfully.\n";
    } else {
        std::cerr << "Failed to create PNG file.\n";
        return 1;
    }

    return 0;
}
