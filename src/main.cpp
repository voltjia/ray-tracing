#include "camera.h"
#include "color.h"
#include "dielectric.h"
#include "hittable-list.h"
#include "lambertian.h"
#include "metal.h"
#include "ray.h"
#include "sphere.h"
#include "utils.h"
#include "vector3.h"

#include <png.h>

#include <iomanip>
#include <iostream>
#include <string>
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
    return Color::lerp(Color::white,
                       Color{0.5, 0.7, 1, 1},
                       0.5 * (ray.direction.y + 1));
}

static Color hit_color(const Ray& ray,
                       const Hittable& world,
                       std::size_t depth) {
    if (depth == -1) {
        return Color::black;
    }

    Hittable::HitInfo hit_info;
    if (world.hit(ray, hit_info)) {
        Ray scattered;
        Color attenuation;
        if (hit_info.material_ptr->scatter(ray,
                                           hit_info,
                                           scattered,
                                           attenuation)) {
            auto color{hit_color(scattered, world, depth - 1)};
            return Color{attenuation.r * color.r,
                         attenuation.g * color.g,
                         attenuation.b * color.b,
                         attenuation.a * color.a};
        }
        return Color::black;
    }
    return background_color(ray);
}

HittableList random_scene() {
    HittableList scene;

    auto ground_material{std::make_shared<Lambertian>(Color::gray)};
    scene.add(std::make_shared<Sphere>(Vector3{0, -1000, 0},
                                       1000,
                                       ground_material));

    for (auto a{-10}; a < 10; ++a) {
        for (auto b{-10}; b < 10; ++b) {
            auto center{Vector3{static_cast<Vector3::ValueType>(
                                        a + 0.9 * random_double()),
                                0.2,
                                static_cast<Vector3::ValueType>(
                                        b + 0.9 * random_double())}};
            auto material_choice{random_double()};

            if ((center - Vector3{4, 0.2, 0}).magnitude() > 0.9) {
                std::shared_ptr<Material> material;

                if (material_choice < 0.6) {
                    auto albedo{Color{random_double() * random_double(),
                                      random_double() * random_double(),
                                      random_double() * random_double(),
                                      random_double() * random_double()}};
                    material = std::make_shared<Lambertian>(albedo);
                } else if (material_choice < 0.9) {
                    auto albedo{Color{random_double(0.5, 1),
                                      random_double(0.5, 1),
                                      random_double(0.5, 1),
                                      random_double(0.5, 1)}};
                    auto fuzz{random_double(0, 0.5)};
                    material = std::make_shared<Metal>(albedo, fuzz);
                } else {
                    material = std::make_shared<Dielectric>(1.5);
                }

                scene.add(std::make_shared<Sphere>(center, 0.2, material));
            }
        }
    }

    auto dielectric_material{std::make_shared<Dielectric>(1.5)};
    scene.add(
            std::make_shared<Sphere>(Vector3{0, 1, 0}, 1, dielectric_material));

    auto lambertian_material{
            std::make_shared<Lambertian>(Color{0.4, 0.2, 0.1, 1})};
    scene.add(std::make_shared<Sphere>(Vector3{-4, 1, 0},
                                       1,
                                       lambertian_material));

    auto metal_material{std::make_shared<Metal>(Color{0.7, 0.6, 0.5, 1}, 0)};
    scene.add(std::make_shared<Sphere>(Vector3{4, 1, 0}, 1, metal_material));

    return scene;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <output.png>\n";
        return 1;
    }

    const char* output_filename = argv[1];

    constexpr auto aspect_ratio{16.0 / 9.0};
    constexpr auto image_height{1080};
    constexpr auto image_width{aspect_ratio * image_height};
    constexpr auto samples_per_pixel{500};
    constexpr auto max_depth{50};

    const auto lookfrom{Vector3{13, 2, -3}};
    const auto lookat{Vector3::zero};
    const auto viewup{Vector3::up};
    const auto focus_distance{10};
    constexpr auto aperture{0.1};

    Camera camera(lookfrom,
                  lookat,
                  viewup,
                  degrees_to_radians(20),
                  aspect_ratio,
                  focus_distance,
                  aperture);

    auto world{random_scene()};

    std::vector<std::uint8_t> buffer;
    for (auto row{decltype(image_height){image_height}}; row != -1; --row) {
        for (auto col{decltype(image_width){0}}; col < image_width; ++col) {
            Color::ValueType r_sum{0};
            Color::ValueType g_sum{0};
            Color::ValueType b_sum{0};
            Color::ValueType a_sum{0};
            for (auto i{samples_per_pixel}; i != -1; --i) {
                auto u{(static_cast<Vector3::ValueType>(col) + random_double())
                       / (image_width - 1)};
                auto v{(static_cast<Vector3::ValueType>(row) + random_double())
                       / (image_height - 1)};
                auto ray{camera.generate_ray(u, v)};
                auto color{hit_color(ray, world, max_depth)};
                r_sum += color.r;
                g_sum += color.g;
                b_sum += color.b;
                a_sum += color.a;
            }
            Color color{r_sum / samples_per_pixel,
                        g_sum / samples_per_pixel,
                        b_sum / samples_per_pixel,
                        a_sum / samples_per_pixel};
            Color color_gamma_corrected{color.gamma()};
            buffer.emplace_back(scale_256(color_gamma_corrected.r));
            buffer.emplace_back(scale_256(color_gamma_corrected.g));
            buffer.emplace_back(scale_256(color_gamma_corrected.b));
            buffer.emplace_back(scale_256(color_gamma_corrected.a));
        }

        constexpr auto progress_bar_width{50};
        auto progress{100.0 * (image_height - row) / image_height};
        auto num_progress_chars{progress_bar_width * (image_height - row)
                                / image_height};
        std::string progress_bar;
        for (decltype(num_progress_chars) i{0}; i < num_progress_chars; ++i) {
            progress_bar += u8"█";
        }
        std::string empty_space(progress_bar_width - num_progress_chars, ' ');
        std::cerr << "\rRendering: [" << progress_bar << empty_space << "] "
                  << std::fixed << std::setprecision(2) << progress
                  << " % completed.";
    }
    std::cerr << '\n';

    if (write_png(output_filename, image_width, image_height, buffer.data())) {
        std::cerr << "PNG file '" << output_filename
                  << "' created successfully.\n";
    } else {
        std::cerr << "Failed to create PNG file.\n";
        return 1;
    }

    return 0;
}
