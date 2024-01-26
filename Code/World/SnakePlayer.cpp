#include "SnakePlayer.h"

SnakePlayer::SnakePlayer(const Vector2<unsigned>& initialPosition) 
{
	snakeBody.push_back(initialPosition);
}

void SnakePlayer::Move(Direction newSnakeDirection, double deltaTime)
{
	if (DoNeedToMove(deltaTime) || canChangeDirection == true) 
	{
		canChangeDirection = false; 

		// possibility chech for a new direction   
		SetDirection(newSnakeDirection);

		switch (snakeDirection)
		{
		case Direction::Up: snakeBody[0].y--; break;
		case Direction::Down: snakeBody[0].y++; break;
		case Direction::Left:  snakeBody[0].x--; break;
		case Direction::Right:  snakeBody[0].x++; break;
		case Direction::None: return;
		default: return;
		}

		if (snakeBody.size() > 1) 
		{
			for (size_t i = snakeBody.size() - 1; i > 0; i--)
			{
				snakeBody[i] = snakeBody[i - 1];
			}
		}

		if (snakeBody[0].x == 0)
			snakeBody[0].x = CONSOLE_WIDTH - 2;
		else if (snakeBody[0].x == CONSOLE_WIDTH - 1)
			snakeBody[0].x = 1;
		else if (snakeBody[0].y == 0)
			snakeBody[0].y = CONSOLE_HEIGHT - 2;
		else if (snakeBody[0].y == CONSOLE_HEIGHT - 1)
			snakeBody[0].y = 0;
	}
}