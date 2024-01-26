#include "SnakeBot.h"

SnakeBot::SnakeBot(const Vector2<unsigned>& initialPosition) 
{
	snakeBody.push_back(initialPosition);
}

void SnakeBot::Move(Vector2<unsigned>& applePosition, double deltaTime, const std::vector <Vector2<unsigned>> playerSnakePosition)
{
	if (DoNeedToMove(deltaTime) || canChangeDirection == true) 
	{
		canChangeDirection = false;

		int dx = applePosition.x - snakeBody[0].x;
		int dy = applePosition.y - snakeBody[0].y;

		int playerScore = playerSnakePosition.size();
		int botScore = snakeBody.size();

		// the Bot's snake will be hunting the Player's snake, if it is three points more
		if ((playerScore - botScore) >= 3) 
		{
			Vector2<unsigned> snakeBotTarget = AvoidCollision(playerSnakePosition[0], applePosition);

			dx = snakeBotTarget.x - snakeBody[0].x;
			dy = snakeBotTarget.y - snakeBody[0].y;
		}
		if ((botScore - playerScore) >= 3) 
		{
			dx = playerSnakePosition[0].x - snakeBody[0].x;
			dy = playerSnakePosition[0].y - snakeBody[0].y;
		} 

		// define the shortest direction for path of the Bot to the target  (apple or Player's snake)
		if (std::abs(dx) > std::abs(dy)) 
		{
			// move up or down 
			if (dx > 0) { SetDirection(Direction::Right); }
			else { SetDirection(Direction::Left); }
		}
		else 
		{ 
			if (dy > 0) { SetDirection(Direction::Down); }
			else { SetDirection(Direction::Up); }
		}

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

Vector2<unsigned>& SnakeBot::AvoidCollision(const Vector2<unsigned>& playerSnakeHead, Vector2<unsigned>& applePosition) 
{
	int dx = playerSnakeHead.x - snakeBody[0].x;
	int dy = playerSnakeHead.y - snakeBody[0].y;

	if (dx < 5 || dy < 5) 
	{
		Vector2<unsigned> alternativePosition;

		do 
		{
			alternativePosition = 
			{
			alternativePosition.x = std::rand() % (CONSOLE_WIDTH - 2) + 1,
			alternativePosition.y = std::rand() % (CONSOLE_HEIGHT - 2) + 1 };
		} while (dx > 10 || dy > 10);
		
		return alternativePosition;
	}

	return applePosition;
}

