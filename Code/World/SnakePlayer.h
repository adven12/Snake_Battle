#pragma once
#include "Snake.h"

class SnakePlayer : public Snake 
{
public:
	SnakePlayer(const Vector2<unsigned>& initialPosition);

	virtual void Move(Direction newSnakeDirection, double deltaTime);
};