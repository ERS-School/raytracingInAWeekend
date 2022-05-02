#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittableList.h"
#include "material.h"
#include "sphere.h"

#include <iostream>

/**
 * \brief Determine the color a ray returns after its bouncy journey
 */
colorRGB Ray_Color_OldLambert(const Ray& _r, const Hittable& _world, int _depth) {
    HitInfo info;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (_depth <= 0)
        return {0, 0, 0};
    
    if (_world.Hit(_r, 0.001f, static_cast<float>(infinity), info))
    {
	    const point3 target = info.P_ + info.Normal_ + RandomInUnitSphere();
			// bounce the ray in direction of target and recursively check color again
	    const auto c = Ray_Color_OldLambert(Ray(info.P_, target - info.P_), _world, _depth - 1);
    	return 0.5 * c;
    }
    
    // linear interpolation (lerp):
    // blendedValue = (1 - t) * start value + t * endValue
    const Vec3 unitDir = UnitVector(_r.Direction());
    const auto t = 0.5f * (unitDir.Y() + 1.0f);
    return (1.0f - t) * colorRGB(1.0f, 1.0f, 1.0f) + t * colorRGB(0.5f, 0.7f, 1.0f);
}
colorRGB Ray_Color_Lambert(const Ray& _r, const Hittable& _world, int _depth) {
    HitInfo info;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (_depth <= 0)
        return { 0, 0, 0 };

    if (_world.Hit(_r, 0.001f, static_cast<float>(infinity), info))
    {
        const point3 target = info.P_ + info.Normal_ + RandomUnitVector();
        // bounce the ray in direction of target and recursively check color again
        const auto c = Ray_Color_Lambert(Ray(info.P_, target - info.P_), _world, _depth - 1);
        return 0.5 * c;
    }

    // linear interpolation (lerp):
    // blendedValue = (1 - t) * start value + t * endValue
    const Vec3 unitDir = UnitVector(_r.Direction());
    const auto t = 0.5f * (unitDir.Y() + 1.0f);
    return (1.0f - t) * colorRGB(1.0f, 1.0f, 1.0f) + t * colorRGB(0.5f, 0.7f, 1.0f);
}
colorRGB Ray_Color_LambertHemisphere(const Ray& _r, const Hittable& _world, int _depth) {
    HitInfo info;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (_depth <= 0)
        return { 0, 0, 0 };

    if (_world.Hit(_r, 0.001f, static_cast<float>(infinity), info))
    {
        Ray scattered;
        colorRGB attenuation;
        if (info.MaterialPtr_->Scatter(_r, info, attenuation, scattered))
            return attenuation * Ray_Color_LambertHemisphere(scattered, _world, _depth - 1);
        return {0, 0, 0};
    }

    // linear interpolation (lerp):
    // blendedValue = (1 - t) * start value + t * endValue
    const Vec3 unitDir = UnitVector(_r.Direction());
    const auto t = 0.5f * (unitDir.Y() + 1.0f);
    return (1.0f - t) * colorRGB(1.0f, 1.0f, 1.0f) + t * colorRGB(0.5f, 0.7f, 1.0f);
}


HittableList RandomScene() {
    HittableList world;

    auto groundMaterial = make_shared<Lambertian>(colorRGB(0.5f, 0.5f, 0.5f));
    world.Add(make_shared<Sphere>(point3(0, -1000, 0), 1000.0f, groundMaterial));
    
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
	        const auto chooseMat = RandomFloat();
            point3 center(static_cast<float>(a) + 0.9f * RandomFloat(), 0.2f, static_cast<float>(b) + 0.9f * RandomFloat());
    
            if ((center - point3(4, 0.2f, 0)).Length() > 0.9f) {
                shared_ptr<Material> sphereMaterial;
    
                if (chooseMat < 0.8f) {
                    // diffuse
                    auto albedo = colorRGB::Random() * colorRGB::Random();
                    sphereMaterial = make_shared<Lambertian>(albedo);
                    world.Add(make_shared<Sphere>(center, 0.2f, sphereMaterial));
                }
                else if (chooseMat < 0.95f) {
                    // metal
                    auto albedo = colorRGB::Random(0.5f, 1.0f);
                    auto fuzz = RandomFloat(0, 0.5f);
                    sphereMaterial = make_shared<Metal>(albedo, fuzz);
                    world.Add(make_shared<Sphere>(center, 0.2f, sphereMaterial));
                }
                else {
                    // glass
                    sphereMaterial = make_shared<Dielectric>(1.5f);
                    world.Add(make_shared<Sphere>(center, 0.2f, sphereMaterial));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5f);
    world.Add(make_shared<Sphere>(point3(0, 1, 0), 1.0f, material1));
    
    auto material2 = make_shared<Lambertian>(colorRGB(0.4f, 0.2f, 0.1f));
    world.Add(make_shared<Sphere>(point3(-4, 1, 0), 1.0f, material2));
    
    auto material3 = make_shared<Metal>(colorRGB(0.7f, 0.6f, 0.5f), 0.0f);
    world.Add(make_shared<Sphere>(point3(4.0f, 1.0f, 0.0f), 1.0f, material3));

    return world;
}

void DepthOfField_TestScene() {

    // Image Properties
    constexpr auto aspectRatio = 16.0f / 9.0f;
    constexpr int imgWidth = 400;  // pixels
    constexpr int imgHeight = static_cast<int>(imgWidth / aspectRatio); //pixels
    constexpr int samplesPerPixel = 100;
    constexpr int maxDepth = 50;

    // World
    auto R = cos(pi / 4);
    HittableList world;

    auto materialGround = make_shared<Lambertian>(colorRGB(0.8f, 0.8f, 0.0));
    auto materialCenter = make_shared<Lambertian>(colorRGB(0.1f, 0.2f, 0.5));
    auto materialLeft = make_shared<Dielectric>(1.5f);
    auto materialRight = make_shared<Metal>(colorRGB(0.8f, 0.6f, 0.2f), 0.0f);

    world.Add(make_shared<Sphere>(point3( 0.0f, -100.5f, -1.0f)  ,  100.0f,   materialGround));
    world.Add(make_shared<Sphere>(point3( 0.0f, 0.0f, -1.0f)     ,  0.5f,     materialCenter));
    world.Add(make_shared<Sphere>(point3(-1.0f, 0.0f, -1.0f)    ,  0.5f,     materialLeft));
    world.Add(make_shared<Sphere>(point3(-1.0,  0.0f, -1.0f)     , -0.45f,   materialLeft));
    world.Add(make_shared<Sphere>(point3( 1.0f, 0.0f, -1.0f)     ,  0.5f,     materialRight));

    // Camera
    point3 lookfrom(3, 3, 2);
    point3 lookat(0, 0, -1);
    Vec3 vup(0, 1, 0);
    auto dist_to_focus = (lookfrom - lookat).Length();
    auto aperture = 2.0f;

    Camera cam(lookfrom, lookat, vup, 20, aspectRatio, aperture, dist_to_focus);
    //Camera cam(point3(-2, 2, 1), point3(0, 0, -1), Vec3(0, 1, 0), 90, aspectRatio);

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
	            const auto u = (col + RandomFloat()) / (imgWidth - 1.0f);
	            const auto v = (row + RandomFloat()) / (imgHeight - 1.0f);
                Ray r = cam.GetRay(u, v);
                pixelColor += Ray_Color_LambertHemisphere(r, world, maxDepth);
            }
            Write_Color(std::cout, pixelColor, samplesPerPixel);
        }
    }
    std::cerr << "\nDone!\n";
}


int main() {
    // Image Properties
    constexpr auto aspectRatio = 3.0f / 2.0f;
    constexpr int imgWidth = 1200;  // pixels
    constexpr int imgHeight = static_cast<int>(imgWidth / aspectRatio); //pixels
    constexpr int samplesPerPixel = 500;
    constexpr int maxDepth = 50;

    // World
    HittableList world = RandomScene();

    // Camera
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0f;
    auto aperture = 0.1f;

    Camera cam(lookfrom, lookat, vup, 20, aspectRatio, aperture, dist_to_focus);
    //Camera cam(point3(-2, 2, 1), point3(0, 0, -1), Vec3(0, 1, 0), 90, aspectRatio);

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
                const auto u = (col + RandomFloat()) / (imgWidth - 1.0f);
                const auto v = (row + RandomFloat()) / (imgHeight - 1.0f);
                Ray r = cam.GetRay(u, v);
                pixelColor += Ray_Color_LambertHemisphere(r, world, maxDepth);
            }
            Write_Color(std::cout, pixelColor, samplesPerPixel);
        }
    }
    std::cerr << "\nDone!\n";
}