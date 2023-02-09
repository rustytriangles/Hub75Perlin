#include <vector>

/* Implementation of Perlin's noise function.
 *
 * Based on http://adrianb.io/2014/08/09/perlinnoise.html
 *
 */
class Perlin
{
public:
    Perlin();

    // Evaluate at the specified location
    float eval(float x, float y, float z = 3.1415f) const;

private:
    int m_Repeat;

    std::vector<int> p; // Doubled permutation to avoid overflow

    static const int permutation[];

    int inc(int num) const;
};

// Sum n octaves
float octaves(Perlin &p, float x, float y, float z, int n);
