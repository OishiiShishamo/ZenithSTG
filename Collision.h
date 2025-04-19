#pragma once
#ifndef COLLISION_H
#define COLLISION_H

#include "Main.h"

int colCircleAndCircle(const Vec2D& v1, const Vec2D& v2, double r);
int colPointAndRect(const Vec2D& v, const Vec2D& r1, const Vec2D& r2, const Vec2D& r3, const Vec2D& r4);

#endif