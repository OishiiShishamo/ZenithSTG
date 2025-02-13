#pragma once
#ifndef COLLISION_H
#define COLLISION_H

#include "Main.h"

int colCircleAndCircle(Vector v1, Vector v2, double r);
int colPointAndRect(Vector v, Vector r1, Vector r2, Vector r3, Vector r4);

#endif