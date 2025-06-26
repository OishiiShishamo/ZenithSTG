#pragma once
#ifndef EFFECT_H
#define EFFECT_H

#include "Object.h"
#include <memory>
#include <array>
#include <vector>
#include <mutex>

/**
* @class Effect
* @brief �G�t�F�N�g�֘A / Effect Related.
* @extends Object
*/
class Effect : public Object {
public:
	double startPal = 0;
	int palEaseTime = 0;
	int palEaseType = 0;
	double palT = 0;
	long long order = 0; // ���я�
	int index = 0;       // �����̃C���f�b�N�X

	Effect() = default;
	Effect(int alive, int isCol, const Vec2D& pos, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, const Color& color, int style, int blend, int pal, int palEaseTime, int palEaseType, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popT, int ID = 0, const std::vector<std::any>& params = {})
		: Object(alive, isCol, OBJECT_EFFECT, pos, startAngle, endAngle, angleEaseType, angleEaseTime, startShowAngle, endShowAngle, showAngleEaseType, showAngleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, popT, 0, 0, 0, 0, 0, 0, 0, ID, params) {
	}

	/**
	* @brief �I�u�W�F�N�g�̓���ȂǁB / Object behavior, etc.
	*
	* @param Index ����p�r�Ȃ� / No current use
	*/
	void UpdateObject(long long Index = 0) override;

	/**
	* @brief �C�[�W���O�ɂ��p�����[�^�̍X�V�B / Updating parameters by easing.
	*/
	void UpdateEase() override;

	/**
	* @brief �G�t�F�N�g�̕`�� / Effect Drawing.
	*/
	void ShowEffect();
	void MoveFunc() override;
};

/**
* @brief �󂫃C���f�b�N�X���Ǘ����邽�߂̊֐� / Function to manage blank indices.
*
* @param idx �󂫃C���f�b�N�X / Blank index
*/
void PushBlankEffects(int idx);

/**
* @brief �G�t�F�N�g�̐��� / Create Effect.
*
* @see objectParams �����̏ڍׂ͂�������Q�� / See here for details of the argument.
*/
int CreateEffect(const Vec2D& pos, const Color& color, int style, int blend, double pal, int palEaseType, int palEaseTime, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID = 0, const std::vector<std::any>& params = {});

/**
* @brief �G�t�F�N�g�̓���ƕ`�� / Effect Movement and Drawing.
*/
void MoveEffects();

/**
* @brief �G�t�F�N�g�̕���X�V / Parallel update of effects.
*
* @param effects �G�t�F�N�g�z�� / Array of effects
*/
void ParallelUpdateEffects(std::array<Effect, MAX_EFFECT>& effects);

void GrazeEffect(const Vec2D& pos);

#endif