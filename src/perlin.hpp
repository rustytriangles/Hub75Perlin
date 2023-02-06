#include <vector>

/* Implementation of Perlin's noise function.
 *
 * Based on http://adrianb.io/2014/08/09/perlinnoise.html
 *
 */
class Perlin {
public:

	Perlin();

    // Evaluate at the specified location
	double eval(double x, double y, double z = 3.1415) const;

private:
	int m_Repeat;

	std::vector<int> p; 													// Doubled permutation to avoid overflow

	static const int permutation[];

	int inc(int num) const;

};

// Sum n octaves
double octaves(Perlin& p, double x, double y, double z, int n);
