#include "../src/perlin.hpp"

BOOST_AUTO_TEST_SUITE(t_perlin)
BOOST_AUTO_TEST_CASE(test_2D) {
    Perlin p;
    BOOST_TEST(p.eval(0.,0.) == 0.5691469123734284);
    BOOST_TEST(p.eval(1.,0.) == 0.57887306592404197);
    BOOST_TEST(p.eval(0.,1.) == 0.5);
    BOOST_TEST(p.eval(1.,1.) == 0.50972615355061357);
}
BOOST_AUTO_TEST_SUITE_END()
