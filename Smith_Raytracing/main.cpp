#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittableList.h"
#include "sphere.h"

#include <iostream>

/**
 * \brief Determine the color a ray returns after its bouncy journey
 */
colorRGB Ray_Color(const Ray& _r, const Hittable& _world, int _depth) {
    HitInfo info;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (_depth <= 0)
        return {0, 0, 0};
    
    if (_world.Hit(_r, 0.001f, static_cast<float>(infinity), info))
    {
        point3 target = info.P_ + info.Normal_ + RandomInUnitSphere();
        auto c = Ray_Color(Ray(info.P_, target - info.P_), _world, _depth - 1); // bounce the ray in direction of target and recursively check color again
    	return 0.5f * c;
    }
    
    // linear interpolation (lerp):
    // blendedValue = (1 - t) * start value + t * endValue
    const Vec3 unitDir = UnitVector(_r.Direction());
    const auto t = 0.5f * (unitDir.Y() + 1.0f);
    return (1.0f - t) * colorRGB(1.0f, 1.0f, 1.0f) + t * colorRGB(0.5f, 0.7f, 1.0f);

    //// If we've exceeded the ray bounce limit, no more light is gathered.
    //if (_depth <= 0)
    //    return colorRGB(0, 0, 0);
    //
    //if (_world.Hit(_r, 0, infinity, info)) {
    //    point3 target = info.P_ + info.Normal_ + RandomInUnitSphere();
    //    return 0.5 * Ray_Color(Ray(info.P_, target - info.P_), _world, _depth - 1);
    //}
    //
    //Vec3 unit_direction = UnitVector(_r.Direction());
    //auto t = 0.5f * (unit_direction.Y() + 1.0f);
    //return (1.0f - t) * colorRGB(1.0f, 1.0f, 1.0f) + t * colorRGB(0.5f, 0.7f, 1.0f);
}

int main() {

    // Image Properties
    constexpr auto aspectRatio = 16.0f / 9.0f;
    constexpr int imgWidth = 400;  // pixels
    constexpr int imgHeight = static_cast<int>(imgWidth / aspectRatio); //pixels
    constexpr int samplesPerPixel = 100;
    constexpr int maxDepth = 50;

    // World Properties
    HittableList world;
    world.Add(make_shared<Sphere>(point3(0, 0, -1), 0.5f));
    world.Add(make_shared<Sphere>(point3(0, -100.5, -1), 100.0f));

    // Camera
    Camera cam;

    // Render the image:
    std::cout << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";
    for (int row = imgHeight; row >= 0; --row)
    {
        // Progress indicator
        std::cerr << "\rScan lines remaining: " << row << ' ' << std::flush;

        // Create the image pixel-by-pixel
        for (int col = 0; col < imgWidth; ++col)
        {
            colorRGB pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s)
            {
                auto u = (col + RandomDouble()) / (imgWidth - 1.0);
                auto v = (row + RandomDouble()) / (imgHeight - 1.0);
                Ray r = cam.GetRay(u, v);
                pixelColor += Ray_Color(r, world, maxDepth);
            }
            Write_Color(std::cout, pixelColor, samplesPerPixel);
        }
    }
    std::cerr << "\nDone!\n";
}