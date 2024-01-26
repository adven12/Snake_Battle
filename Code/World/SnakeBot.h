#pragma once
#include "Snake.h"
#include <Windows.h>
#include "SnakePlayer.h"

class SnakeBot : public Snake 
{
public:
	SnakeBot(const Vector2<unsigned>& initialPosition);

	virtual void Move(Vector2<unsigned>& applePosition, double deltaTime, const std::vector <Vector2<unsigned>> playerSnakePosition);
	Vector2<unsigned>& AvoidCollision(const Vector2<unsigned>& playerSnakeHead, Vector2<unsigned>& applePosition);
};