#pragma once
#include "../Tools/Tools.h"
#include <iostream>

class Apple 
{
public:
	Apple(const Vector2<unsigned>& initialPosition);
	Vector2<unsigned> GetPosition() const;
	void SetPosition(Vector2<unsigned>& newApplePosition);

private:
	Vector2<unsigned> applePosition;
};