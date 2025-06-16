#include "gtest/gtest.h"
#include "Vec2D.h"
#include "Main.h"
#include "Easing.h"
#include "Global.h"
#include <cmath>

const double EPSILON = 1e-9;

bool almostEqual(double a, double b) {
    return std::fabs(a - b) < EPSILON;
}

bool vecAlmostEqual(const Vec2D& a, const Vec2D& b) {
    return almostEqual(a.GetX(), b.GetX()) && almostEqual(a.GetY(), b.GetY());
}

//Vec2D Zone
TEST(Vec2DTest, ConstructorTest) {
    Vec2D v1;
    EXPECT_DOUBLE_EQ(0.0, v1.GetX());
    EXPECT_DOUBLE_EQ(0.0, v1.GetY());

    Vec2D v2(1.5, -2.5);
    EXPECT_DOUBLE_EQ(1.5, v2.GetX());
    EXPECT_DOUBLE_EQ(-2.5, v2.GetY());
}

TEST(Vec2DTest, ArithmeticOperators) {
    Vec2D a(3.0, 4.0);
    Vec2D b(1.0, 2.0);

    Vec2D add = a + b;
    EXPECT_DOUBLE_EQ(4.0, add.GetX());
    EXPECT_DOUBLE_EQ(6.0, add.GetY());

    Vec2D sub = a - b;
    EXPECT_DOUBLE_EQ(2.0, sub.GetX());
    EXPECT_DOUBLE_EQ(2.0, sub.GetY());

    Vec2D mul_scalar = a * 2.0;
    EXPECT_DOUBLE_EQ(6.0, mul_scalar.GetX());
    EXPECT_DOUBLE_EQ(8.0, mul_scalar.GetY());

    Vec2D div_scalar = a / 2.0;
    EXPECT_DOUBLE_EQ(1.5, div_scalar.GetX());
    EXPECT_DOUBLE_EQ(2.0, div_scalar.GetY());

    Vec2D mul = a * b;
    EXPECT_DOUBLE_EQ(3.0, mul.GetX());
    EXPECT_DOUBLE_EQ(8.0, mul.GetY());

    Vec2D div = a / b;
    EXPECT_DOUBLE_EQ(3.0, div.GetX());
    EXPECT_DOUBLE_EQ(2.0, div.GetY());
}

TEST(Vec2DTest, CompoundAssignmentOperators) {
    Vec2D a(3.0, 4.0);
    Vec2D b(1.0, 2.0);

    a += b;
    EXPECT_DOUBLE_EQ(4.0, a.GetX());
    EXPECT_DOUBLE_EQ(6.0, a.GetY());

    a -= b;
    EXPECT_DOUBLE_EQ(3.0, a.GetX());
    EXPECT_DOUBLE_EQ(4.0, a.GetY());

    a *= 2.0;
    EXPECT_DOUBLE_EQ(6.0, a.GetX());
    EXPECT_DOUBLE_EQ(8.0, a.GetY());

    a /= 2.0;
    EXPECT_DOUBLE_EQ(3.0, a.GetX());
    EXPECT_DOUBLE_EQ(4.0, a.GetY());

    a *= b;
    EXPECT_DOUBLE_EQ(3.0, a.GetX());
    EXPECT_DOUBLE_EQ(8.0, a.GetY());

    a /= b;
    EXPECT_DOUBLE_EQ(3.0, a.GetX());
    EXPECT_DOUBLE_EQ(4.0, a.GetY());
}

TEST(Vec2DTest, SettersTest) {
    Vec2D v;
    v.SetX(10.0);
    v.SetY(-20.0);
    EXPECT_DOUBLE_EQ(10.0, v.GetX());
    EXPECT_DOUBLE_EQ(-20.0, v.GetY());
}

TEST(Vec2DTest, NormalizationTest) {
    Vec2D v(3.0, 4.0);
    v.VecNorm();

    double len = std::sqrt(v.GetX() * v.GetX() + v.GetY() * v.GetY());
    EXPECT_TRUE(almostEqual(len, 1.0));
    EXPECT_TRUE(almostEqual(v.GetX(), 0.6));
    EXPECT_TRUE(almostEqual(v.GetY(), 0.8));
}

TEST(Vec2DTest, NormalizationZeroVectorTest) {
    Vec2D v(0.0, 0.0);
    v.VecNorm();
    EXPECT_DOUBLE_EQ(0.0, v.GetX());
    EXPECT_DOUBLE_EQ(0.0, v.GetY());
}

TEST(Vec2DTest, EqualityOperatorsSanity) {
    Vec2D a(1.0, 2.0);
    Vec2D b(1.0, 2.0);
    Vec2D c(2.0, 3.0);

    // カスタム比較関数が必要
    EXPECT_TRUE(vecAlmostEqual(a, b));
    EXPECT_FALSE(vecAlmostEqual(a, c));
}


TEST(Vec2DTest, CrossProductBasicTest) {
    Vec2D v1(0.0, 0.0);
    Vec2D v2(1.0, 0.0);
    Vec2D v3(0.0, 1.0);

    // クロス積の結果は1
    EXPECT_NEAR(crossProduct(v1, v2, v3), 1.0, EPSILON);
}

TEST(Vec2DTest, CrossProductColinear) {
    Vec2D v1(1.0, 1.0);
    Vec2D v2(2.0, 2.0);
    Vec2D v3(3.0, 3.0);

    // 直線上の3点 → クロス積は0
    EXPECT_NEAR(crossProduct(v1, v2, v3), 0.0, EPSILON);
}

TEST(Vec2DTest, RangeTest) {
    Vec2D a(0.0, 0.0);
    Vec2D b(3.0, 4.0);

    EXPECT_NEAR(Range(a, b), 5.0, EPSILON); // 3-4-5 の直角三角形
}

TEST(Vec2DTest, AngleToVec2DTest) {
    double angle = pi / 2; // 90度
    Vec2D result = AngleToVec2D(angle);

    EXPECT_NEAR(result.GetX(), std::cos(angle), EPSILON);
    EXPECT_NEAR(result.GetY(), -std::sin(angle), EPSILON); // 実装が -sin
}

TEST(Vec2DTest, RotatePointTest90Degrees) {
    Vec2D original(1.0, 0.0);
    double angle = pi / 2;

    Vec2D rotated = RotatePoint(original, angle);

    EXPECT_NEAR(rotated.GetX(), 0.0, EPSILON);
    EXPECT_NEAR(rotated.GetY(), -1.0, EPSILON);
}

TEST(Vec2DTest, RotatePointTest180Degrees) {
    Vec2D original(1.0, 0.0);
    double angle = pi;

    Vec2D rotated = RotatePoint(original, angle);

    EXPECT_NEAR(rotated.GetX(), -1.0, EPSILON);
    EXPECT_NEAR(rotated.GetY(), 0.0, EPSILON);
}

TEST(EasingTest, Linear) {
    EXPECT_TRUE(almostEqual(Linear(0.0, 0, 10), 0));
    EXPECT_TRUE(almostEqual(Linear(0.5, 0, 10), 5));
    EXPECT_TRUE(almostEqual(Linear(1.0, 0, 10), 10));
}

TEST(EasingTest, EaseInQuad) {
    EXPECT_TRUE(almostEqual(EaseInQuad(0.0, 0, 10), 0));
    EXPECT_TRUE(almostEqual(EaseInQuad(0.5, 0, 10), 10 * 0.25));
    EXPECT_TRUE(almostEqual(EaseInQuad(1.0, 0, 10), 10));
}

TEST(EasingTest, EaseOutQuad) {
    EXPECT_TRUE(almostEqual(EaseOutQuad(0.0, 0, 10), 0));
    EXPECT_TRUE(almostEqual(EaseOutQuad(0.5, 0, 10), 10 * 0.75));
    EXPECT_TRUE(almostEqual(EaseOutQuad(1.0, 0, 10), 10));
}

TEST(EasingTest, EaseInOutQuad) {
    EXPECT_TRUE(almostEqual(EaseInOutQuad(0.0, 0, 10), 0));
    EXPECT_TRUE(almostEqual(EaseInOutQuad(0.25, 0, 10), 10 * (2 * 0.25 * 0.25))); // 2*t*t = 0.125
    EXPECT_TRUE(almostEqual(EaseInOutQuad(0.75, 0, 10), 10 * (-1 + (4 - 2 * 0.75) * 0.75)));
    EXPECT_TRUE(almostEqual(EaseInOutQuad(1.0, 0, 10), 10));
}

TEST(EasingTest, EaseInCubic) {
    EXPECT_TRUE(almostEqual(EaseInCubic(0.0, 0, 10), 0));
    EXPECT_TRUE(almostEqual(EaseInCubic(0.5, 0, 10), 10 * 0.125)); // 0.5^3 = 0.125
    EXPECT_TRUE(almostEqual(EaseInCubic(1.0, 0, 10), 10));
}

TEST(EasingTest, EaseOutCubic) {
    EXPECT_TRUE(almostEqual(EaseOutCubic(0.0, 0, 10), 0));
    EXPECT_TRUE(almostEqual(EaseOutCubic(0.5, 0, 10), 10 * ((-0.5) * (-0.5) * (-0.5) + 1))); // t=0.5, t-1 = -0.5
    EXPECT_TRUE(almostEqual(EaseOutCubic(1.0, 0, 10), 10));
}

TEST(EasingTest, EaseInOutCubic) {
    EXPECT_TRUE(almostEqual(EaseInOutCubic(0.0, 0, 10), 0));
    EXPECT_TRUE(almostEqual(EaseInOutCubic(0.25, 0, 10), 10 * (4 * 0.25 * 0.25 * 0.25))); // 4 * t^3
    EXPECT_TRUE(almostEqual(EaseInOutCubic(0.75, 0, 10), 10 * (((0.75 - 1) * (0.75 - 1) * (0.75 - 1) * 4) + 1)));
    EXPECT_TRUE(almostEqual(EaseInOutCubic(1.0, 0, 10), 10));
}

TEST(EasingTest, EasingWrapperLinear) {
    EXPECT_TRUE(almostEqual(Easing(LINEAR, 0.5, 0, 10), 5));
}

TEST(EasingTest, EasingWrapperInvalidType) {
    // invalid type should fallback to Linear
    EXPECT_TRUE(almostEqual(Easing(-1, 0.5, 0, 10), 5));
}