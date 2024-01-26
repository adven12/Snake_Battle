#include "Snake.h"

Snake::Snake(const Vector2<unsigned>& initialPosition)
{
	snakeBody.push_back(initialPosition);
}

std::vector<Vector2<unsigned>> Snake::GetPosition() const
{	
	return snakeBody;
}
Vector2<unsigned> Snake::GetHeadPosition() const {
	return snakeBody[0];
}
const Direction Snake::GetDirection() const 
{
	return snakeDirection;
}

bool Snake::DoTouch(const std::unique_ptr<Apple>& apple)
{
	if (snakeBody[0] == apple->GetPosition()) 
	{
		Increase();
		return true;
	}
	return false;
}
bool Snake::DoTouchOtherSnake(const std::vector <Vector2<unsigned>>& snakeBodyPosition) 
{
	if ((snakeBody.size() - snakeBodyPosition.size()) >= 1 && snakeBody[0] == snakeBodyPosition[0])
	{
		Kill(); return true;
	}

	return false;
}
bool Snake::DoTouchItself() 
{
	if (snakeBody.size() < 4) 
	{
		return false;
	}
	for (size_t i = 4; i <= snakeBody.size(); i++)
	{
		if (snakeBody[0] == snakeBody[i - 1]) 
		{
			Kill();
		}
	}

	return false;
}

void Snake::Increase() 
{
	snakeBody.push_back(snakeBody[snakeBody.size() - 1]);
}

void Snake::Kill() 
{
	isAlive = false;
}

bool Snake::IsAlive() const 
{
	return isAlive;
}

bool Snake::DoNeedToMove(double deltaTime) 
{
	passedDistance += speed * deltaTime;

	if (passedDistance >= cellsToPass)
	{
		cellsToPass++;
		canChangeDirection = true;
		return true;
	}

	return false;
}

void Snake::SetDirection(const Direction newSnakeDirection)
{
	// check if the current direction is oppisite to the new direction
	if ((snakeDirection == Direction::Up && newSnakeDirection == Direction::Down) ||
		(snakeDirection == Direction::Down && newSnakeDirection == Direction::Up) ||
		(snakeDirection == Direction::Right && newSnakeDirection == Direction::Left) ||
		(snakeDirection == Direction::Left && newSnakeDirection == Direction::Right) ||
		newSnakeDirection == Direction::None)
	{
		return;
	}	

	snakeDirection = newSnakeDirection;	
}