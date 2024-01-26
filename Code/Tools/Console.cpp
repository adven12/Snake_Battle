#include "Console.h"

namespace Console 
{
	void SetApplicationSettings() 
	{
		ResetCursorPosition();
		HideCursor(); // disable blinking cursor
		SetWindowSize(CONSOLE_WIDTH, CONSOLE_HEIGHT);
		SetFontSettings(30, L"Consolas");
		DisableScrollBars();
		DisableMaximizeButton();
		DisableWindowResizing(); // зміна розмірів вікна 
		SetConsoleWindowTitle();
		SetRandomSeed(); //  //srand(static_cast<unsigned>(time(nullptr)));  // srand - встановлює нове "зерно" від, якого відшов при генерації. Цим зерном явлються 
	// time(nullptr) - який повератає кожну секунду нове число типом long long. Щоб не виникало попередження з конвертацією типів, перетворюємо це чило в unsigned за допомогою static_cast
	}

	void DisableWindowResizing() 
	{
		HWND consoleWindow = GetConsoleWindow(); // take a pointer to the console

		SetWindowLong( // makros 
			consoleWindow, // this console
			GWL_STYLE, // definite style
			GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX // disable window scalability
		);
	}
	void SetCursorPosition(size_t x, size_t y) 
	{
		static HANDLE consoleWindow = GetStdHandle(STD_OUTPUT_HANDLE); // take console
		std::cout.flush(); // clear stream
		COORD newCursorPosition = { static_cast<SHORT>(x), static_cast<SHORT>(y) }; // new coordinates
		SetConsoleCursorPosition(consoleWindow, newCursorPosition);
	}
	void ResetCursorPosition() 
	{ 
		// set cursor to the starting position
		SetCursorPosition(0, 0);
	}
	void SetConsoleWindowTitle() 
	{
		SetConsoleTitle(L"Console Snake"); // macro accepts a string  
	}
	void SetRandomSeed() 
	{
		// for appearance of apple
		std::srand(static_cast<unsigned>(std::time(nullptr)));
	}
	void DisableMaximizeButton() 
	{
		HWND consoleWindow = GetConsoleWindow();
		DWORD windowStyle = GetWindowLong(consoleWindow, GWL_STYLE);
		windowStyle &= ~WS_MAXIMIZEBOX;

		SetWindowLong(consoleWindow, GWL_STYLE, windowStyle);
		SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
	}
	void DisableScrollBars() 
	{
		HANDLE consoleWindow = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
		GetConsoleScreenBufferInfo(consoleWindow, &bufferInfo);
		COORD newBuffetSize = { bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1,
		bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1 };
		SetConsoleScreenBufferSize(consoleWindow, newBuffetSize);
	}
	void HideCursor() 
	{
		HANDLE consoleWindow = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.dwSize = 100;
		cursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(consoleWindow, &cursorInfo);
	}
	void SetFontSettings(SHORT fontSize, const wchar_t* fontName) 
	{
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;
		cfi.dwFontSize.Y = fontSize;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, sizeof(L"Consolas"), fontName);

		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	}
	void SetWindowSize(SHORT w, SHORT h) 
	{
		SMALL_RECT windowArea = { 0,0,w,h };
		static HANDLE consoleWindow = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleWindowInfo(consoleWindow, TRUE, &windowArea);
	}
	void ClearScreen() 
	{
		system("cls");
	} 
}