#include <vector>
class Perlin {
public:

	Perlin();

	double OctavePerlin(double x, double y, double z, int octaves, double persistence);

	double eval(double x, double y, double z = 3.1415) const;

private:
	int m_Repeat;

	std::vector<int> p; 													// Doubled permutation to avoid overflow

	static const int permutation[];

	int inc(int num) const;


};

