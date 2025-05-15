#include "Main.h"

#include "Color.h"
#include "Utility.h"

bool debuging = true;

void apply_window_size() {
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	if (width - height < 560 - 1) {
		Properties.windowSize = 0;
	}
	else if (width - height < 700 - 1) {
		Properties.windowSize = 1;
	}
	else if (width - height < 840 - 1) {
		Properties.windowSize = 2;
	}
	else {
		Properties.windowSize = 1;
	}

	if (debuging) Properties.windowSize = 1;

	return;
}

int rnd() {
	int rnd = std::rand() % 65535;    // 0〜65536の乱数
	return rnd;
}

void
DrawRotaGraph4(int x, int y, double rate, double anglex, double angley, double anglez, int handle, int tranflag, int x_turn_flag, int y_turn_flag) {
	int sx = 0, sy = 0;
	if (handle < 0) return;
	GetGraphSize(handle, &sx, &sy);
	if (sx <= 0 || sy <= 0) return;

	DirectX::XMMATRIX rotX = DirectX::XMMatrixRotationX(static_cast<double>(anglex));
	DirectX::XMMATRIX rotY = DirectX::XMMatrixRotationY(static_cast<double>(angley));
	DirectX::XMMATRIX rotZ = DirectX::XMMatrixRotationZ(static_cast<double>(anglez));
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(static_cast<double>(rate), static_cast<double>(rate), static_cast<double>(rate));
	DirectX::XMMATRIX m = scale * rotZ * rotY * rotX;

	double hw = sx * 0.5f;
	double hh = sy * 0.5f;

	double signX = x_turn_flag ? -1.0f : 1.0f;
	double signY = y_turn_flag ? -1.0f : 1.0f;

	DirectX::XMVECTOR p1 = DirectX::XMVectorSet(-hw * signX, -hh * signY, 0.0f, 1.0f); // 左上
	DirectX::XMVECTOR p2 = DirectX::XMVectorSet(hw * signX, -hh * signY, 0.0f, 1.0f);  // 右上
	DirectX::XMVECTOR p3 = DirectX::XMVectorSet(hw * signX, hh * signY, 0.0f, 1.0f);   // 右下
	DirectX::XMVECTOR p4 = DirectX::XMVectorSet(-hw * signX, hh * signY, 0.0f, 1.0f);  // 左下

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

	DrawModiGraph(lux, luy, rux, ruy, rdx, rdy, ldx, ldy, handle, tranflag);
}

Color GetColorHSV(double H, double S, double V) {
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

	return Color(ir, ig, ib);
}

Color
GamingColor(double mul) {
	return GetColorHSV(std::fmod(frame * mul, 360), 1, 1);
}

void
SmartSetDrawBlendMode(int BlendMode, int Pal) {
	GetDrawBlendMode(&currentBlendMode, &currentBlendPal);
	if (!(currentBlendMode == BlendMode && currentBlendPal == Pal)) {
		SetDrawBlendMode(BlendMode, Pal);
	}
}

double
Rad(double angle) {
	return (pi / 180) * angle;
}