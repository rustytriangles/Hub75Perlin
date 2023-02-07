#include "util.hpp"

double grad(int hash, double x, double y, double z)
{
    int h = hash & 15;                     // Take the hashed value and take the first 4 bits of it (15 == 0b1111)
    double u = h < 8 /* 0b1000 */ ? x : y; // If the most significant bit (MSB) of the hash is 0 then set u = x.  Otherwise y.

    double v; // In Ken Perlin's original implementation this was another conditional operator (?:).  I
              // expanded it for readability.

    if (h < 4 /* 0b0100 */) // If the first and second significant bits are 0 set v = y
        v = y;
    else if (h == 12 /* 0b1100 */ || h == 14 /* 0b1110*/) // If the first and second significant bits are 1 set v = x
        v = x;
    else // If the first and second significant bits are not equal (0/1, 1/0) set v = z
        v = z;

    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v); // Use the last 2 bits to decide if u and v are positive or negative.  Then return their addition.
}

double fade(double t)
{
    // Fade function as defined by Ken Perlin.  This eases coordinate values
    // so that they will "ease" towards integral values.  This ends up smoothing
    // the final output.
    return t * t * t * (t * (t * 6 - 15) + 10); // 6t^5 - 15t^4 + 10t^3
}

double lerp(double a, double b, double x)
{
    return a + x * (b - a);
}