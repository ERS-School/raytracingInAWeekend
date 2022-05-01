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

    // Divide the color by the number of samples
    auto scale = 1.0f / samplesPerPixel;
    r *= scale;
    g *= scale;
    b *= scale;

	_out << static_cast<int>(255.999f * Clamp(r, 0.0F, 0.999f)) << ' '
         << static_cast<int>(255.999f * Clamp(g, 0.0F, 0.999f)) << ' '
         << static_cast<int>(255.999f * Clamp(b, 0.0F, 0.999f)) << '\n';
}


#endif
