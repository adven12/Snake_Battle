#include "Apple.h"

Apple::Apple(const Vector2<unsigned>& initialPosition) : applePosition(initialPosition) {}

Vector2<unsigned> Apple::GetPosition() const 
{
	return applePosition;
}

void Apple::SetPosition(Vector2<unsigned>& newApplePosition) 
{
	applePosition = newApplePosition;
}