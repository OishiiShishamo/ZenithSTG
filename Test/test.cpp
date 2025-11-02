#include "gtest/gtest.h"
#include <chrono>
#include <random>
#include "color.h"
#include "utility.h"

using namespace zenithstg;

// ( ﾉ´ •ω•`)ﾉ━━━━━━━━━━━━━━━━
// Color Class Tests
// ( ﾉ´ •ω•`)ﾉ━━━━━━━━━━━━━━━━
TEST(ColorTest, BasicGetterSetter) {
    Color c = Color255(255, 128, 0, 64);

    EXPECT_NEAR(c.GetR255(), 255.0f, 1e-3);
    EXPECT_NEAR(c.GetG255(), 128.0f, 1e-3);
    EXPECT_NEAR(c.GetB255(), 0.0f, 1e-3);
    EXPECT_NEAR(c.GetA255(), 64.0f, 1e-3);

    c.Set255(0, 255, 0);
    EXPECT_NEAR(c.GetR255(), 0.0f, 1e-3);
    EXPECT_NEAR(c.GetG255(), 255.0f, 1e-3);
    EXPECT_NEAR(c.GetB255(), 0.0f, 1e-3);
}

TEST(ColorTest, OperatorAddSub) {
    Color c1 = Color255(255, 0, 0);
    Color c2 = Color255(0, 255, 0);
    Color c3 = c1 + c2;

    EXPECT_NEAR(c3.GetR255(), 255.0f, 1e-3);
    EXPECT_NEAR(c3.GetG255(), 255.0f, 1e-3);
    EXPECT_NEAR(c3.GetB255(), 0.0f, 1e-3);

    c3 -= Color255(128, 128, 0);
    EXPECT_NEAR(c3.GetR255(), 127.0f, 1e-3);
    EXPECT_NEAR(c3.GetG255(), 127.0f, 1e-3);
    EXPECT_NEAR(c3.GetB255(), 0.0f, 1e-3);
}

TEST(ColorTest, SaturationClamp) {
    Color c = Color255(9999, -100, 500);
    EXPECT_NEAR(c.GetR255(), 255.0f, 1e-3);
    EXPECT_NEAR(c.GetG255(), 0.0f, 1e-3);
    EXPECT_NEAR(c.GetB255(), 255.0f, 1e-3);
}

TEST(ColorTest, MultiplyScalar) {
    Color c = Color255(100, 50, 25);
    c *= 2.0f;
    EXPECT_NEAR(c.GetR255(), 200.0f, 1e-3);
    EXPECT_NEAR(c.GetG255(), 100.0f, 1e-3);
    EXPECT_NEAR(c.GetB255(), 50.0f, 1e-3);
}

TEST(ColorTest, LerpFunction_Static) {
    Color red = Color255(255, 0, 0);
    Color blue = Color255(0, 0, 255);
    Color purple = Lerp(red, blue, 0.5f);

    EXPECT_NEAR(purple.GetR255(), 127.5f, 1.0f);
    EXPECT_NEAR(purple.GetG255(), 0.0f, 1.0f);
    EXPECT_NEAR(purple.GetB255(), 127.5f, 1.0f);

    Color lerp0 = Lerp(red, blue, 0.0f);
    Color lerp1 = Lerp(red, blue, 1.0f);

    EXPECT_NEAR(lerp0.GetR255(), red.GetR255(), 1e-3);
    EXPECT_NEAR(lerp0.GetG255(), red.GetG255(), 1e-3);
    EXPECT_NEAR(lerp0.GetB255(), red.GetB255(), 1e-3);

    EXPECT_NEAR(lerp1.GetR255(), blue.GetR255(), 1e-3);
    EXPECT_NEAR(lerp1.GetG255(), blue.GetG255(), 1e-3);
    EXPECT_NEAR(lerp1.GetB255(), blue.GetB255(), 1e-3);

    Color below = Lerp(red, blue, -0.5f);
    Color above = Lerp(red, blue, 1.5f);

    EXPECT_NEAR(below.GetR255(), red.GetR255(), 1e-3);
    EXPECT_NEAR(above.GetB255(), blue.GetB255(), 1e-3);
}


// ( ﾉ´ •ω•`)ﾉ━━━━━━━━━━━━━━━━
// Gaming Color Tests
// ( ﾉ´ •ω•`)ﾉ━━━━━━━━━━━━━━━━
long long gaming_t = 0;

TEST(ColorTest, GetColorHsv_PrimaryColors) {
    Color red = GetColorHsv(0.0f, 1.0f, 1.0f);
    EXPECT_NEAR(red.GetR(), 1.0f, 0.001f);
    EXPECT_NEAR(red.GetG(), 0.0f, 0.001f);
    EXPECT_NEAR(red.GetB(), 0.0f, 0.001f);

    Color green = GetColorHsv(120.0f, 1.0f, 1.0f);
    EXPECT_NEAR(green.GetR(), 0.0f, 0.001f);
    EXPECT_NEAR(green.GetG(), 1.0f, 0.001f);
    EXPECT_NEAR(green.GetB(), 0.0f, 0.001f);

    Color blue = GetColorHsv(240.0f, 1.0f, 1.0f);
    EXPECT_NEAR(blue.GetR(), 0.0f, 0.001f);
    EXPECT_NEAR(blue.GetG(), 0.0f, 0.001f);
    EXPECT_NEAR(blue.GetB(), 1.0f, 0.001f);
}

TEST(ColorTest, GetColorHsv_SaturationAndValue) {
    Color gray = GetColorHsv(120.0f, 0.0f, 0.5f);
    EXPECT_NEAR(gray.GetR(), 0.5f, 0.001f);
    EXPECT_NEAR(gray.GetG(), 0.5f, 0.001f);
    EXPECT_NEAR(gray.GetB(), 0.5f, 0.001f);

    Color black = GetColorHsv(240.0f, 1.0f, 0.0f);
    EXPECT_NEAR(black.GetR(), 0.0f, 0.001f);
    EXPECT_NEAR(black.GetG(), 0.0f, 0.001f);
    EXPECT_NEAR(black.GetB(), 0.0f, 0.001f);
}

TEST(ColorTest, GamingColor_CycleBehavior) {
    gaming_t = 0;
    Color c1 = GamingColorTest(gaming_t, 0, 1.0f);

    gaming_t = 60;
    Color c2 = GamingColorTest(gaming_t, 0, 1.0f);

    gaming_t = 120;
    Color c3 = GamingColorTest(gaming_t, 0, 1.0f);

    EXPECT_FALSE(
        std::fabs(c1.GetR() - c2.GetR()) < 0.001f &&
        std::fabs(c1.GetG() - c2.GetG()) < 0.001f &&
        std::fabs(c1.GetB() - c2.GetB()) < 0.001f
    );

    gaming_t = 0;
    Color c4 = GamingColorTest(gaming_t, 180, 1.0f);
    EXPECT_FALSE(
        std::fabs(c1.GetR() - c4.GetR()) < 0.001f &&
        std::fabs(c1.GetG() - c4.GetG()) < 0.001f &&
        std::fabs(c1.GetB() - c4.GetB()) < 0.001f
    );
}

TEST(ColorTest, GamingColor_Periodicity) {
    gaming_t = 0;
    Color c1 = GamingColorTest(gaming_t, 0, 1.0f);

    gaming_t = 360;
    Color c2 = GamingColorTest(gaming_t, 0, 1.0f);

    EXPECT_NEAR(c1.GetR(), c2.GetR(), 0.001f);
    EXPECT_NEAR(c1.GetG(), c2.GetG(), 0.001f);
    EXPECT_NEAR(c1.GetB(), c2.GetB(), 0.001f);
}