#include "../src/perlin.hpp"

BOOST_AUTO_TEST_SUITE(t_perlin)
BOOST_AUTO_TEST_CASE(test_2D)
{
    Perlin p;
    BOOST_TEST(p.eval(0., 0.) == 0.569146931f);
    BOOST_TEST(p.eval(1., 0.) == 0.578873038f);
    BOOST_TEST(p.eval(0., 1.) == 0.5f);
    BOOST_TEST(p.eval(1., 1.) == 0.509726167f);
}
BOOST_AUTO_TEST_SUITE_END()
