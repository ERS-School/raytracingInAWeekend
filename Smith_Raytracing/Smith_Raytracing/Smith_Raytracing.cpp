#include <iostream>

int main() {

    // Image properties
    const int img_width = 256;  // pixels
    const int img_height = 256; // pixels

    // Render the image:
    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";
    for (int row = img_height; row >= 0; --row)
    {
        // Progress indicator
        std::cerr << "\rScanlines remaining: " << row << ' ' << std::flush;

        // Create the image pixel-by-pixel
        for (int col = 0; col < img_width; ++col)
        {
            auto r = double(col) / (img_width - 1.0);
            auto g = double(row) / (img_height - 1.0);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            //std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cerr << "\nDone!\n";
}