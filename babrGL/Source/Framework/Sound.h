#pragma once

#include <GL\glew.h>
#include <windows.h>
#include <mmsystem.h>
#include "soloud_wavstream.h"


class Sound
{
public:
	Sound::Sound(){};
	Sound::Sound(GLint soundID) {
		HRSRC imageRes = NULL;
		HGLOBAL imageResDataHandle = NULL;

		HMODULE hModule = GetModuleHandle(NULL);

		HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(soundID), L"WAVE");
		HGLOBAL hMemory = LoadResource(hModule, hResource);
		DWORD dwSize = SizeofResource(hModule, hResource);
		LPVOID lpAddress = LockResource(hMemory);
		gWave.loadMem((unsigned char*)lpAddress, dwSize, true, true);
		UnlockResource(hMemory);
	};

	SoLoud::WavStream* Sound::GetSound() { return &gWave; }
	private:
		SoLoud::WavStream gWave;
};