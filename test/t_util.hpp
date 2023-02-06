#include "../src/util.hpp"

BOOST_AUTO_TEST_SUITE(t_util)

BOOST_AUTO_TEST_CASE(test_grad) {
    BOOST_TEST(grad(3,1.,1.,1.) == -2.);
}

BOOST_AUTO_TEST_CASE(test_fade) {
    BOOST_TEST(fade(0.) == 0.);
    BOOST_TEST(fade(1.) == 1.);
    BOOST_TEST(fade(0.5) == 0.5);
    BOOST_TEST(fade(0.25) < 0.125);
    BOOST_TEST(fade(0.75) > 0.875);
}

BOOST_AUTO_TEST_CASE(test_lerp) {
    const double a = 10.;
    const double b = 100.;
    BOOST_TEST(lerp(a,b, 0.) == a);
    BOOST_TEST(lerp(a,b, 1.) == b);
    BOOST_TEST(lerp(a,b, 0.5) == (a+b)/2.);
    BOOST_TEST(lerp(a,b, 0.25) == (3.*a + b)/4.);
    BOOST_TEST(lerp(a,b, 0.75) == (a + 3.*b)/4.);    
}

BOOST_AUTO_TEST_SUITE_END()
