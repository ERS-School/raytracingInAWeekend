#include "rtweekend.h"

#include "color.h"
#include "hittableList.h"
#include "sphere.h"

#include <iostream>

/**
 * \brief Blend white and blue depending on the height of the y-coordinate after scaling the ray's direction to unit length
 */
colorRGB Ray_Color(const Ray& _r, const Hittable& _world) {
    HitInfo info;
    if (_world.Hit(_r, 0, INFINITY, info))
        return 0.5f * (info.Normal_ + colorRGB(1.0f, 1.0f, 1.0f));

    // linear interpolation (lerp):
    // blendedValue = 1 - t) * start value + t * endValue
    const Vec3 unitDir = UnitVector(_r.Direction());
    const auto t = 0.5f * (unitDir.Y() + 1.0f);
    return (1.0f - t) * colorRGB(1.0f, 1.0f, 1.0f) + t * colorRGB(0.5f, 0.7f, 1.0f);
}

int main() {

    // Image Properties
    constexpr auto aspectRatio = 16.0f / 9.0f;
    constexpr int imgWidth = 400;  // pixels
    constexpr int imgHeight = static_cast<int>(imgWidth / aspectRatio); //pixels

    // World Properties
    HittableList world;
    world.Add(make_shared<Sphere>(point3(0, 0, -1), 0.5f));
    world.Add(make_shared<Sphere>(point3(0, -100.5, -1), 100.0f));

    // Camera Properties
    constexpr auto viewportHeight = 2.0f;
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focalLength = 1.0f;

    auto origin = point3(0, 0, 0);
    auto horizontalAxis = Vec3(viewportWidth, 0, 0);
    auto verticalAxis = Vec3(0, viewportHeight, 0);
    auto lowerLeftCorner = origin - horizontalAxis / 2 - verticalAxis / 2 - Vec3(0, 0, focalLength);

    // Render the image:
    std::cout << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";
    for (int row = imgHeight; row >= 0; --row)
    {
        // Progress indicator
        std::cerr << "\rScan lines remaining: " << row << ' ' << std::flush;

        // Create the image pixel-by-pixel
        for (int col = 0; col < imgWidth; ++col)
        {
            float u = static_cast<float>(col) / (imgWidth / 1.0f);
            float v = static_cast<float>(row) / (imgHeight / 1.0f);
            Ray r(origin, lowerLeftCorner + u * horizontalAxis + v * verticalAxis - origin);
	        const colorRGB pixelColor(Ray_Color(r, world));
            Write_Color(std::cout, pixelColor);
        }
    }
    std::cerr << "\nDone!\n";
}