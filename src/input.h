#pragma once
#ifndef ZENITHSTG_SRC_INPUT_H_
#define ZENITHSTG_SRC_INPUT_H_

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#ifndef DISABLE_DINPUT

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace zenithstg::input {
	LPDIRECTINPUT8 g_pDI = nullptr;
	LPDIRECTINPUTDEVICE8 g_pController = nullptr;

	BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext) {
		LPDIRECTINPUTDEVICE8* ppDevice = (LPDIRECTINPUTDEVICE8*)pContext;

		if (FAILED(g_pDI->CreateDevice(pdidInstance->guidInstance, ppDevice, nullptr)))
			return DIENUM_CONTINUE;

		return DIENUM_STOP;
	}

	bool InitDirectInput() {
		HWND hWnd = GetMainWindowHandle();

		if (FAILED(DirectInput8Create(NULL, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pDI, nullptr))) return false;

		if (FAILED(g_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, &g_pController, DIEDFL_ATTACHEDONLY))) return false;

		if (!g_pController) return false;

		if (FAILED(g_pController->SetDataFormat(&c_dfDIJoystick2))) return false;

		if (FAILED(g_pController->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))) return false;

		g_pController->Acquire();
		return true;
	}

	void PollController() {
		if (!g_pController) return;

		DIJOYSTATE2 js;
		ZeroMemory(&js, sizeof(js));

		HRESULT hr = g_pController->Poll();
		if (FAILED(hr)) {
			hr = g_pController->Acquire();
			while (hr == DIERR_INPUTLOST) hr = g_pController->Acquire();
			return;
		}

		if (SUCCEEDED(g_pController->GetDeviceState(sizeof(DIJOYSTATE2), &js))) {
			std::cout << "X: " << js.lX << " Y: " << js.lY << std::endl;
			for (int i = 0; i < 128; i++)
			{
				if (js.rgbButtons[i] & 0x80)
					std::cout << "Button " << i << " pressed" << std::endl;
			}
		}
	}

	void CleanupDirectInput() {
		if (g_pController) {
			g_pController->Unacquire();
			g_pController->Release();
			g_pController = nullptr;
		}
		if (g_pDI) {
			g_pDI->Release();
			g_pDI = nullptr;
		}
	}
}
#endif
#endif