#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

#include "rtweekend.h"

// Write (out stream) the translated [0,255] value of each color component
inline void Write_Color(std::ostream& _out, colorRGB _pixelColor, int samplesPerPixel) {
    auto r = _pixelColor.X();
    auto g = _pixelColor.Y();
    auto b = _pixelColor.Z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    const auto scale = 1.0f / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

	_out << static_cast<int>(256 * Clamp(r, 0.0f, 0.999f)) << ' '
         << static_cast<int>(256 * Clamp(g, 0.0f, 0.999f)) << ' '
         << static_cast<int>(256 * Clamp(b, 0.0f, 0.999f)) << '\n';
}


#endif
