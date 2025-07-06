#pragma once
#ifndef ZENITHSTG_SRC_PARTICLE_H_
#define ZENITHSTG_SRC_PARTICLE_H_

#include "object.h"

/**
* @class Particle
* @brief �p�[�e�B�N���֘A / Particle Related.
* @extends Object
*/
class Particle : public Object {
public:
	double start_pal_ = 0;
	int pal_ease_time_ = 0;
	int pal_ease_type_ = 0;
	double pal_t_ = 0;
	long long order_ = 0; // ���я�
	int index_ = 0;       // �����̃C���f�b�N�X

	Particle() = default;
	Particle(int alive, int is_col, const Vec2D& pos, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_show_angle, double end_show_angle, int show_angle_ease_type, int show_angle_ease_time, const zenithstg::Color& color, int style, int blend, int pal, int palEaseTime, int palEaseType, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int pop_t, int id = 0, const std::vector<std::any>& params = {})
		: Object(alive, is_col, kObjectParticle, pos, start_angle, end_angle, angle_ease_type, angle_ease_time, start_show_angle, end_show_angle, show_angle_ease_type, show_angle_ease_time, color, style, blend, pal, start_col_size, end_col_size, col_size_ease_type, col_size_ease_time, start_size, end_size, size_ease_type, size_ease_time, start_speed, end_speed, speed_ease_type, speed_ease_time, pop_t, 0, 0, 0, 0, 0, 0, 0, id, params) {
	}

	/**
	* @brief �I�u�W�F�N�g�̓���ȂǁB / Object behavior, etc.
	*/
	void UpdateObject() override;

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
* @see ObjectParams �����̏ڍׂ͂�������Q�� / See here for details of the argument.
*/
int CreateParticle(const Vec2D& pos, const zenithstg::Color& color, int style, int blend, double pal, int palEaseType, int palEaseTime, int is_col, double start_col_size, double end_col_size, int col_size_ease_type, int col_size_ease_time, double start_size, double end_size, int size_ease_type, int size_ease_time, int aim, double start_angle, double end_angle, int angle_ease_type, int angle_ease_time, double start_speed, double end_speed, int speed_ease_type, int speed_ease_time, int id = 0, const std::vector<std::any>& params = {});

/**
* @brief �p�[�e�B�N���̓���ƕ`�� / Particle Movement and Drawing.
*/
void MoveParticles();

/**
* @brief �p�[�e�B�N���̕���X�V / Parallel update of particles.
*
* @param particles �p�[�e�B�N���z�� / Array of particles
*/
void ParallelUpdateParticles(std::array<Particle, kMaxParticle>& particles);

void GrazeParticle(const Vec2D& pos);

#endif