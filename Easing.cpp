#include "Easing.h"

// ���`���
double
Linear(double t, double start, double end) {
	return start + (end - start) * t;
}

// �C�[�W�C�� (����) - �񎟋Ȑ�
double
EaseInQuad(double t, double start, double end) {
	return start + (end - start) * (t * t);
}

// �C�[�W�A�E�g (����) - �񎟋Ȑ�
double
EaseOutQuad(double t, double start, double end) {
	return start + (end - start) * (t * (2 - t));
}

// �C�[�W�C���A�E�g (�����ƌ���) - �񎟋Ȑ�
double
EaseInOutQuad(double t, double start, double end) {
	if (t < 0.5f) return start + (end - start) * (2 * t * t);
	return start + (end - start) * (-1 + (4 - 2 * t) * t);
}

// �C�[�W�C�� (����) - �O���Ȑ�
double
EaseInCubic(double t, double start, double end) {
	return start + (end - start) * (t * t * t);
}

// �C�[�W�A�E�g (����) - �O���Ȑ�
double
EaseOutCubic(double t, double start, double end) {
	t -= 1;
	return start + (end - start) * (t * t * t + 1);
}

// �C�[�W�C���A�E�g (�����ƌ���) - �O���Ȑ�
double
EaseInOutCubic(double t, double start, double end) {
	if (t < 0.5f) return start + (end - start) * (4 * t * t * t);
	t -= 1;
	return start + (end - start) * (t * t * t * 4 + 1);
}