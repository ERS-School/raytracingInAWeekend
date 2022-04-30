#include "vec3.h"
#include "color.h"

#include <iostream>

int main() {

    // Image properties
    constexpr int imgWidth = 256;  // pixels
    constexpr int imgHeight = 256; // pixels

    // Render the image:
    std::cout << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";
    for (int row = imgHeight; row >= 0; --row)
    {
        // Progress indicator
        std::cerr << "\rScan lines remaining: " << row << ' ' << std::flush;

        // Create the image pixel-by-pixel
        for (int col = 0; col < imgWidth; ++col)
        {
	        const colorRGB pixelColor(static_cast<float>(col) / (imgWidth - 1.0f), static_cast<float>(row) / (imgHeight - 1.0f), 0.25f);
            Write_Color(std::cout, pixelColor);

            //std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cerr << "\nDone!\n";
}