#pragma once
#include <Windows.h> // API
#include <iostream>
#include "ConsoleSizeSetting.h"

namespace Console 
{
	void SetApplicationSettings();
	void ResetCursorPosition();
	void SetCursorPosition(size_t x, size_t y);
	void HideCursor(); // disable blinking cursor
	void SetWindowSize(SHORT width, SHORT height);
	void SetFontSettings(SHORT fontSize, const wchar_t* fontName);
	void DisableScrollBars();
	void DisableMaximizeButton();
	void DisableWindowResizing();
	void SetConsoleWindowTitle();
	void SetRandomSeed();
	void ClearScreen();
}

