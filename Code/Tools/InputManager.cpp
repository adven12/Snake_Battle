#include "InputManager.h"

InputManager::Key InputManager::pressedKey = InputManager::Key::None;

bool InputManager::IsPressedKey()
{
	return _kbhit();
}
InputManager::Key InputManager::PressedKey() 
{
	pressedKey = static_cast<Key>(_getch());
	
	if(pressedKey == Key::Arrow)
		pressedKey = static_cast<Key>(_getch());
	return pressedKey;
}
