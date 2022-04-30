#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

// Write (out stream) the translated [0,255] value of each color component
inline void Write_Color(std::ostream& _out, colorRGB _pixelColor) {
	_out << static_cast<int>(255.999 * _pixelColor.X()) << ' '
         << static_cast<int>(255.999 * _pixelColor.Y()) << ' '
         << static_cast<int>(255.999 * _pixelColor.Z()) << '\n';
}


#endif
