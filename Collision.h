#pragma once
#ifndef COLLISION_H
#define COLLISION_H

#include "Main.h"

int colCircleAndCircle(Vec2D v1, Vec2D v2, double r);
int colPointAndRect(Vec2D v, Vec2D r1, Vec2D r2, Vec2D r3, Vec2D r4);

#endif