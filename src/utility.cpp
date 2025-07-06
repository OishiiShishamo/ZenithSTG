#include "main.h"

#include "utility.h"

bool debuging = true;

void ApplyWindowSize() {
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	if (width - height < 560 - 1) {
		properties_.window_size_ = 0;
	}
	else if (width - height < 700 - 1) {
		properties_.window_size_ = 1;
	}
	else if (width - height < 840 - 1) {
		properties_.window_size_ = 2;
	}
	else {
		properties_.window_size_ = 1;
	}

	if (debuging) properties_.window_size_ = 1;

	return;
}

void
DrawRotaGraph4(int x, int y, double rate, double angle_x, double angle_y, double angle_z, int handle, int tran_flag, int x_turn_flag, int y_turn_flag) {
	int sx = 0, sy = 0;
	if (handle < 0) return;
	GetGraphSize(handle, &sx, &sy);
	if (sx <= 0 || sy <= 0) return;

	DirectX::XMMATRIX rot_x = DirectX::XMMatrixRotationX(static_cast<double>(angle_x));
	DirectX::XMMATRIX rot_y = DirectX::XMMatrixRotationY(static_cast<double>(angle_y));
	DirectX::XMMATRIX rot_z = DirectX::XMMatrixRotationZ(static_cast<double>(angle_z));
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(static_cast<double>(rate), static_cast<double>(rate), static_cast<double>(rate));
	DirectX::XMMATRIX m = scale * rot_z * rot_y * rot_x;

	double hw = sx * 0.5f;
	double hh = sy * 0.5f;

	double sign_x = x_turn_flag ? -1.0f : 1.0f;
	double sign_y = y_turn_flag ? -1.0f : 1.0f;

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

zenithstg::Color
GetColorHsv(double H, double S, double V) {
	int hi = static_cast<int>(H / 60.0);
	hi = (hi == 6) ? 5 : hi % 6;
	double f = (H / 60.0) - hi;
	double p = V * (1.0 - S);
	double q = V * (1.0 - f * S);
	double t = V * (1.0 - (1.0 - f) * S);

	double r = 0, g = 0, b = 0;

	switch (hi) {
	case 0: r = V; g = t; b = p; break;
	case 1: r = q; g = V; b = p; break;
	case 2: r = p; g = V; b = t; break;
	case 3: r = p; g = q; b = V; break;
	case 4: r = t; g = p; b = V; break;
	case 5: r = V; g = p; b = q; break;
	}

	uint8_t ir = static_cast<uint8_t>(std::clamp(r * 255.0, 0.0, 255.0));
	uint8_t ig = static_cast<uint8_t>(std::clamp(g * 255.0, 0.0, 255.0));
	uint8_t ib = static_cast<uint8_t>(std::clamp(b * 255.0, 0.0, 255.0));

	return zenithstg::Color(ir, ig, ib);
}

zenithstg::Color
GamingColor(int offset, double mul) {
	return GetColorHsv(std::fmod((t + offset) * mul, 360), 1, 1);
}

void
SmartSetDrawBlendMode(int blend_mode, int pal) {
	GetDrawBlendMode(&current_blend_mode, &current_blend_pal);
	if (!(current_blend_mode == blend_mode && current_blend_pal == pal)) {
		SetDrawBlendMode(blend_mode, pal);
	}
}

double
Rad(double angle) {
	return (kPi / 180) * angle;
}