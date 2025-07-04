#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include "Object.h"

/**
* @class Particle
* @brief �p�[�e�B�N���֘A / Particle Related.
* @extends Object
*/
class Particle : public Object {
public:
	double startPal = 0;
	int palEaseTime = 0;
	int palEaseType = 0;
	double palT = 0;
	long long order = 0; // ���я�
	int index = 0;       // �����̃C���f�b�N�X

	Particle() = default;
	Particle(int alive, int isCol, const Vec2D& pos, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startShowAngle, double endShowAngle, int showAngleEaseType, int showAngleEaseTime, const Color& color, int style, int blend, int pal, int palEaseTime, int palEaseType, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int popT, int ID = 0, const std::vector<std::any>& params = {})
		: Object(alive, isCol, OBJECT_PARTICLE, pos, startAngle, endAngle, angleEaseType, angleEaseTime, startShowAngle, endShowAngle, showAngleEaseType, showAngleEaseTime, color, style, blend, pal, startColSize, endColSize, colSizeEaseType, colSizeEaseTime, startSize, endSize, sizeEaseType, sizeEaseTime, startSpeed, endSpeed, speedEaseType, speedEaseTime, popT, 0, 0, 0, 0, 0, 0, 0, ID, params) {
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
	* @brief �p�[�e�B�N���̕`�� / Particle Drawing.
	*/
	void ShowParticle();
	void MoveFunc() override;
};

/**
* @brief �󂫃C���f�b�N�X���Ǘ����邽�߂̊֐� / Function to manage blank indices.
*
* @param idx �󂫃C���f�b�N�X / Blank index
*/
void PushBlankParticles(int idx);

/**
* @brief �p�[�e�B�N���̐��� / Create Particle.
*
* @see objectParams �����̏ڍׂ͂�������Q�� / See here for details of the argument.
*/
int CreateParticle(const Vec2D& pos, const Color& color, int style, int blend, double pal, int palEaseType, int palEaseTime, int isCol, double startColSize, double endColSize, int colSizeEaseType, int colSizeEaseTime, double startSize, double endSize, int sizeEaseType, int sizeEaseTime, int aim, double startAngle, double endAngle, int angleEaseType, int angleEaseTime, double startSpeed, double endSpeed, int speedEaseType, int speedEaseTime, int ID = 0, const std::vector<std::any>& params = {});

/**
* @brief �p�[�e�B�N���̓���ƕ`�� / Particle Movement and Drawing.
*/
void MoveParticles();

/**
* @brief �p�[�e�B�N���̕���X�V / Parallel update of particles.
*
* @param particles �p�[�e�B�N���z�� / Array of particles
*/
void ParallelUpdateParticles(std::array<Particle, MAX_PARTICLE>& particles);

void GrazeParticle(const Vec2D& pos);

#endif