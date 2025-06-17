#pragma once
#ifndef PARAMS_H
#define PARAMS_H

#define UI_POS_OFFSET Vec2D(1400, 50)

#define MAX_BULLET 9000
#define MAX_LASER 8192
#define MAX_ENEMY 8192
#define MAX_PLAYER_SHOT 8192
#define MAX_EFFECT 8192

#define GRAZE_ENABLED 1
#define BULLET_GRAZE_EVERY_FRAME 0
#define LASER_GRAZE_EVERY_FRAME 1

inline constexpr long long GrazeScore = 1;

inline constexpr int GrazeRange = 16;

#endif