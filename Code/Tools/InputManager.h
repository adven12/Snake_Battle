#pragma once
#include <conio.h>

class InputManager 
{
public: 
	enum class Key 
	{
		Enter = 13,
		Up = 72,
		Down = 80,
		Right = 77,
		Left = 75,
		Escape = 27,
		Arrow = 224,
		None
	};

	static bool IsPressedKey();
	static Key PressedKey();

private:
	static Key pressedKey;
};