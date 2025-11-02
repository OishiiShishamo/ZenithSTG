#include "utility.h"

#include <cmath>
#include <cstdint>
#include <DirectXMath.h>

#include "DxLib.h"

#include "color.h"
#include "property.h"
#include "time_utl.h"

namespace zenithstg {
	void ApplyWindowSize() {
		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);
		if (properties_.window_size_ == 2 && width - height <= 839) {
			properties_.window_size_ = 1;
		}
		if (properties_.window_size_ == 1 && width - height <= 699) {
			properties_.window_size_ = 0;
		}
		return;
	}

	void DrawRotaGraph4(int x, int y, float rate, float angle_x, float angle_y, float angle_z, int handle, int tran_flag, int x_turn_flag, int y_turn_flag) {
		int sx = 0, sy = 0;
		if (handle < 0) return;
		GetGraphSize(handle, &sx, &sy);
		if (sx <= 0 || sy <= 0) return;

		DirectX::XMMATRIX rot_x = DirectX::XMMatrixRotationX(static_cast<float>(angle_x));
		DirectX::XMMATRIX rot_y = DirectX::XMMatrixRotationY(static_cast<float>(angle_y));
		DirectX::XMMATRIX rot_z = DirectX::XMMatrixRotationZ(static_cast<float>(angle_z));
		DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(static_cast<float>(rate), static_cast<float>(rate), static_cast<float>(rate));
		DirectX::XMMATRIX m = scale * rot_z * rot_y * rot_x;

		float hw = sx * 0.5f;
		float hh = sy * 0.5f;

		float sign_x = x_turn_flag ? -1.0f : 1.0f;
		float sign_y = y_turn_flag ? -1.0f : 1.0f;

		DirectX::XMVECTOR p1 = DirectX::XMVectorSet(-hw * sign_x, -hh * sign_y, 0.0f, 1.0f); // 左上
		DirectX::XMVECTOR p2 = DirectX::XMVectorSet(hw * sign_x, -hh * sign_y, 0.0f, 1.0f);  // 右上
		DirectX::XMVECTOR p3 = DirectX::XMVectorSet(hw * sign_x, hh * sign_y, 0.0f, 1.0f);   // 右下
		DirectX::XMVECTOR p4 = DirectX::XMVectorSet(-hw * sign_x, hh * sign_y, 0.0f, 1.0f);  // 左下

		p1 = DirectX::XMVector3TransformCoord(p1, m);
		p2 = DirectX::XMVector3TransformCoord(p2, m);
		p3 = DirectX::XMVector3TransformCoord(p3, m);
		p4 = DirectX::XMVector3TransformCoord(p4, m);

		int lux = x + static_cast<int>(DirectX::XMVectorGetX(p1));
		int luy = y + static_cast<int>(DirectX::XMVectorGetY(p1));
		int rux = x + static_cast<int>(DirectX::XMVectorGetX(p2));
		int ruy = y + static_cast<int>(DirectX::XMVectorGetY(p2));
		int rdx = x + static_cast<int>(DirectX::XMVectorGetX(p3));
		int rdy = y + static_cast<int>(DirectX::XMVectorGetY(p3));
		int ldx = x + static_cast<int>(DirectX::XMVectorGetX(p4));
		int ldy = y + static_cast<int>(DirectX::XMVectorGetY(p4));

		DrawModiGraph(lux, luy, rux, ruy, rdx, rdy, ldx, ldy, handle, tran_flag);
	}

	Color GetColorHsv(float h, float s, float v) {
		h = std::fmod(h, 360.0f);
		if (h < 0.0f) h += 360.0f;

		float c = v * s;
		float x = c * (1.0f - std::fabs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
		float m = v - c;

		float r, g, b;

		if (h < 60.0f) {
			r = c; g = x; b = 0.0f;
		}
		else if (h < 120.0f) {
			r = x; g = c; b = 0.0f;
		}
		else if (h < 180.0f) {
			r = 0.0f; g = c; b = x;
		}
		else if (h < 240.0f) {
			r = 0.0f; g = x; b = c;
		}
		else if (h < 300.0f) {
			r = x; g = 0.0f; b = c;
		}
		else {
			r = c; g = 0.0f; b = x;
		}

		return Color(r + m, g + m, b + m);
	}

	Color GamingColor(int offset, float mul) {
		return GetColorHsv(std::fmod((t + offset) * mul, 360), 1, 1);
	}

	Color GamingColorTest(long long gaming_t, int offset, float mul) {
		return GetColorHsv(std::fmod((gaming_t + offset) * mul, 360), 1, 1);
	}

	void SmartSetDrawBlendMode(int blend_mode, int pal) {
		GetDrawBlendMode(&current_blend_mode, &current_blend_pal);
		if (!(current_blend_mode == blend_mode && current_blend_pal == pal)) {
			SetDrawBlendMode(blend_mode, pal);
		}
	}

	double Rad(double angle) {
		return (kPi / 180) * angle;
	}

	long long Beat2Frame(double bpm, double beat, int offset_frame) {
		double secondsPerBeat = 60.0 / bpm;
		double timeInSeconds = beat * secondsPerBeat;
		long long frame = static_cast<int>(std::round(timeInSeconds * fps));
		return frame + offset_frame;
	}

	void CameraMove(Vec2D pos) {
		screen_pos_offset = kCenter * screen_size_rate - pos * screen_size_rate;
	}
	void CameraMove(int x, int y) {
		screen_pos_offset = kCenter * screen_size_rate - Vec2D(x, y) * screen_size_rate;
	}
}