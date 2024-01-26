#include "Game/Game.h"
#include "Tools/Time.h"


int main()
{
	Game& game = Game::GetInstance();

	try
	{
		while (game.isRunning)
		{
			game.HandleInput();
			game.Update(Time::DeltaTime()); // called  Time::DeltaTime() only one time, than function pass argument into two different methods
			game.Render();
		}
	}
	catch (const GameException& error)
	{
		game.HandleExeption(error);
	}
	catch (const std::exception& exe)
	{
		game.HandleOtherExeption(exe);
	}

	return 0;
}


