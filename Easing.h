#pragma once
#ifndef EASING_H
#define EASING_H

#define LINEAR 0
#define EASEINQUAD 1
#define EASEOUTQUAD 2
#define EASEINOUTQUAD 3
#define EASEINCUBIC 4
#define EASEOUTCUBIC 5
#define EASEINOUTCUBIC 6

#include "main.h"

// ���`���
double Linear(double t, double start, double end);

// �C�[�W�C�� (����) - �񎟋Ȑ�
double EaseInQuad(double t, double start, double end);

// �C�[�W�A�E�g (����) - �񎟋Ȑ�
double EaseOutQuad(double t, double start, double end);

// �C�[�W�C���A�E�g (�����ƌ���) - �񎟋Ȑ�
double EaseInOutQuad(double t, double start, double end);

// �C�[�W�C�� (����) - �O���Ȑ�
double EaseInCubic(double t, double start, double end);

// �C�[�W�A�E�g (����) - �O���Ȑ�
double EaseOutCubic(double t, double start, double end);

// �C�[�W�C���A�E�g (�����ƌ���) - �O���Ȑ�
double EaseInOutCubic(double t, double start, double end);

#endif