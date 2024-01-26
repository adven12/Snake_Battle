#include "Field.h"

const Vector2<unsigned> Field::GetRandomPosition() const
{
	Vector2<unsigned> randomPosition;

	do 
	{
		randomPosition = 
		{
		randomPosition.x = std::rand() % (CONSOLE_WIDTH - 2) + 1,
		randomPosition.y = std::rand() % (CONSOLE_HEIGHT - 2) + 1
		};
	} while (field[randomPosition.y][randomPosition.x] == ' ');
	
	return randomPosition;
}

void Field::AllocateField() 
{
	field = new char* [CONSOLE_HEIGHT];

	for (size_t i = 0; i < CONSOLE_HEIGHT; i++)
	{
		field[i] = new char[CONSOLE_WIDTH];
	}
}
void Field::DeallocateField() 
{
	for (size_t i = 0; i < CONSOLE_HEIGHT; i++)
	{
		delete[] field[i];
	}

	delete[] field;
	field = nullptr;
}

void Field::ClearField() 
{
	for (size_t i = 0; i < CONSOLE_HEIGHT; i++)
	{
		for (size_t j = 0; j < CONSOLE_WIDTH; j++)
		{
			field[i][j] = ' ';
		}
	}
}

void Field::Set(const std::unique_ptr<Walls>& walls) 
{
	std::vector<Vector2<unsigned>> wallsPosition = walls->GetWallsPosition();

	for (size_t i = 0; i < wallsPosition.size(); i++)
	{
		field[wallsPosition[i].y][wallsPosition[i].x] = '*';
	}
}
void Field::Set(const std::unique_ptr<Apple>& apple) 
{
	Vector2<unsigned> applePosition = apple->GetPosition();
	field[applePosition.y][applePosition.x] = 'A';
}

// a templte method for setting snake on the field, for objects such as SnakePlayer and SnakeBot
template <typename T>
void Field::Set(const std::unique_ptr<T>& objectsnake) 
{
	// get zero element of the vector - this is the head  
	Vector2<unsigned> headPosition = objectsnake->GetHeadPosition();
	field[headPosition.y][headPosition.x] = 'O';

	// get all body, including the head  
	std::vector<Vector2<unsigned>> snakeBody = objectsnake->GetPosition();

	// change every position depending on the currrent path  
	for (size_t i = 1; i < snakeBody.size(); i++)
	{
		if (objectsnake->GetDirection() == Direction::Up) { snakeBody[i].y++; }
		else if (objectsnake->GetDirection() == Direction::Down) { snakeBody[i].y--; }
		else if (objectsnake->GetDirection() == Direction::Right) { snakeBody[i].x--; }
		else if (objectsnake->GetDirection() == Direction::Left) { snakeBody[i].x++; }

		// than put the body parts on the field
		field[snakeBody[i].y][snakeBody[i].x] = 'o';
	}
}

// explicit  initialization  the templte method, becouse it is into separate file
template void Field::Set(const std::unique_ptr<SnakePlayer>& objectsnake);
template void Field::Set(const std::unique_ptr<SnakeBot>& objectsnake);

void Field::Render() const 
{
	for (size_t i = 0; i < CONSOLE_HEIGHT; i++)
	{
		for (size_t j = 0; j < CONSOLE_WIDTH; j++)
		{
			std::cout << field[i][j];
		}
		std::cout << '\n';
	}
}

char** Field::GetField() const 
{
	return field;
}