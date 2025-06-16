#include "pch.h"
#include "Vec2D.h"
#include "Main.h"

TEST(Vec2DTest, Vec2DMoveTest) {
	Vec2D vec1 = Vec2D(0.0f, 0.0f);
	Vec2D vec2 = Vec2D(5.0f, 0.0f);
	Vec2D vec = vec1 + vec2;
	EXPECT_EQ(5.0f, vec.GetX());
}