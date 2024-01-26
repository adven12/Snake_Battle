#pragma once
#include <vector>
#include <iostream>
#include "../Game/GameEnumeration.h"
#include "../Tools/ConsoleSizeSetting.h"
#include "Apple.h"
#include "../Tools/Tools.h"
#include "../Tools/Time.h"

class Snake 
{
public:
	Snake() {};
	Snake(const Vector2<unsigned>& initialPosition);
	virtual ~Snake() {}

	std::vector<Vector2<unsigned>> GetPosition() const;
	Vector2<unsigned> GetHeadPosition() const;
	const Direction GetDirection() const;
	virtual void Move() {};
	bool DoTouch(const std::unique_ptr<Apple>& apple);
	bool DoTouchOtherSnake(const std::vector <Vector2<unsigned>>& snakeBodyPosition);
	void Increase();
	bool DoTouchItself();
	void Kill();
	bool IsAlive() const;
	void SetDirection(const Direction newSnakeDirection);

protected:
	Direction snakeDirection = Direction::None;
	bool isAlive = true;
	std::vector<Vector2<unsigned>> snakeBody;
	short speed = 8;
	double passedDistance = 0;
	short cellsToPass = 1;
	bool canChangeDirection = true;

	bool DoNeedToMove(double deltaTime);
};