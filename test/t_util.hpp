#include "../src/util.hpp"

BOOST_AUTO_TEST_SUITE(t_util)

BOOST_AUTO_TEST_CASE(test_grad) {
    BOOST_TEST(grad(3, 1.f, 1.f, 1.f) == -2.f);
}

BOOST_AUTO_TEST_CASE(test_fade) {
    BOOST_TEST(fade(0.f) == 0.f);
    BOOST_TEST(fade(1.f) == 1.f);
    BOOST_TEST(fade(0.5f) == 0.5f);
    BOOST_TEST(fade(0.25f) < 0.125f);
    BOOST_TEST(fade(0.75f) > 0.875f);
}

BOOST_AUTO_TEST_CASE(test_lerp) {
    const float a = 10.f;
    const float b = 100.f;
    BOOST_TEST(lerp(a, b, 0.f) == a);
    BOOST_TEST(lerp(a, b, 1.f) == b);
    BOOST_TEST(lerp(a, b, 0.5f) == (a + b) / 2.f);
    BOOST_TEST(lerp(a, b, 0.25f) == (3.f * a + b) / 4.f);
    BOOST_TEST(lerp(a, b, 0.75f) == (a + 3.f * b) / 4.f);
}

BOOST_AUTO_TEST_SUITE_END()
