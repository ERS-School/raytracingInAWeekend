#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

float Hit_Sphere(const point3& _center, float _radius, const Ray& _r) {
    Vec3 oc = _r.Origin() - _center;
    auto a = Dot(_r.Direction(), _r.Direction());
    auto b = 2.0f * Dot(oc, _r.Direction());
    auto c = Dot(oc, oc) - _radius * _radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0f * a);
    }
}

/**
 * \brief Blend white and blue depending on the height of the y-coordinate after scaling the ray's direction to unit length
 */
colorRGB Ray_Color(const Ray& _r) {
	auto t = Hit_Sphere(point3(0, 0, -1), 0.5f, _r);

    if (t > 0.0f) // case where we have intersected the sphere somewhere along the + direction of the ray
    {
	    const Vec3 surfaceNormal = UnitVector(_r.At(t) - Vec3(0, 0, -1)); // Normal = surface point - sphere center (which we know is (0, 0, -1))
        return 0.5f * colorRGB(surfaceNormal.X() + 1.0f, surfaceNormal.Y() + 1.0f, surfaceNormal.Z() + 1.0f);
    }
	const Vec3 unitDir = UnitVector(_r.Direction());
    t = 0.5f * (unitDir.Y() + 1.0f);

    // linear interpolation (lerp):
    // blendedValue = 1 - t) * start value + t * endValue
    return (1.0f - t) * colorRGB(1.0f, 1.0f, 1.0f) + t * colorRGB(0.5f, 0.7f, 1.0f);
}

int main() {

    // Image Properties
    constexpr auto aspectRatio = 16.0f / 9.0f;
    constexpr int imgWidth = 400;  // pixels
    constexpr int imgHeight = static_cast<int>(imgWidth / aspectRatio); //pixels

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
	        const colorRGB pixelColor(Ray_Color(r));
            Write_Color(std::cout, pixelColor);
        }
    }
    std::cerr << "\nDone!\n";
}