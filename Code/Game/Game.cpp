#include "Game.h"

Game& Game::GetInstance()
{
	static Game game;
	return game;
}
Game::~Game() {}
Game::Game() 
{
	Console::SetApplicationSettings();
	ReadMenuFromFile();
}

void Game::HandleInput()
{
	switch (currentWindow) 
	{
		case GameWindow::MainMenu: HandleInputMenu(); break;
		case  GameWindow::GameScene: HandleInputGameScene(); break;
		default: throw GameException("Error!", __func__, __LINE__);
	}
}
void Game::HandleInputMenu()
{
	if (InputManager::IsPressedKey()) 
	{
		switch (InputManager::PressedKey())
		{
		case InputManager::Key::Up: mainMenuSelectedItem = ChangeMainMenuItemUp(mainMenuSelectedItem, MainMenuItem::StartGame, MainMenuItem::Exit); break;
		case InputManager::Key::Down: mainMenuSelectedItem = ChangeMainMenuItemDown(mainMenuSelectedItem, MainMenuItem::StartGame, MainMenuItem::Exit);	break;
		case InputManager::Key::Enter: 
			switch (mainMenuSelectedItem) 
			{
			case MainMenuItem::StartGame: currentWindow = GameWindow::GameScene; AllocateGameObjects(); break;
			case MainMenuItem::Exit: Console::ClearScreen(); exit(0); break;
			}
			break;
		case InputManager::Key::Escape: Console::ClearScreen(); exit(0); break;
		default: break; //throw GameException("Error!", __func__, __LINE__);
		}
	}
}
void Game::HandleInputGameScene() 
{
	if (InputManager::IsPressedKey()) 
	{
		switch (InputManager::PressedKey())
		{
		case InputManager::Key::Up: newSnakeDirection = Direction::Up;  break;
		case InputManager::Key::Down: newSnakeDirection = Direction::Down; break;
		case InputManager::Key::Right: newSnakeDirection = Direction::Right;  break;
		case InputManager::Key::Left: newSnakeDirection = Direction::Left;  break;
		case InputManager::Key::Escape:currentWindow = GameWindow::MainMenu; field->DeallocateField(); DealocateGameObjects(); return; break;
		default: break; // throw GameException("Error!", __func__, __LINE__);
		}
	}
}

void Game::Update(double deltaTime) 
{
	switch (currentWindow) 
	{
	case GameWindow::MainMenu: UpdateMenu(); break;
	case  GameWindow::GameScene: UpdateGameScene(deltaTime); break;
	default: throw GameException("Error!", __func__, __LINE__);
	}
}
void Game::UpdateMenu() 
{
	size_t arrowPosition =  mainMenuContent.find('->');

	if (arrowPosition != std::string::npos) 
	{
		mainMenuContent[arrowPosition] = ' ';
		mainMenuContent[arrowPosition - 1] = ' ';
	}
	switch (mainMenuSelectedItem) 
	{
	case MainMenuItem::StartGame: arrowPosition = mainMenuContent.find("Start Game");
		mainMenuContent[arrowPosition - 3] = '>';
		mainMenuContent[arrowPosition - 4] = '-'; break;
	case MainMenuItem::Exit: arrowPosition = mainMenuContent.find("Exit");
		mainMenuContent[arrowPosition - 3] = '>';
		mainMenuContent[arrowPosition - 4] = '-'; break;
	default: throw GameException("Error!", __func__, __LINE__);
	}
}
void Game::UpdateGameScene(double deltaTime) 
{
	snakePlayer->Move(newSnakeDirection, deltaTime);

	Vector2<unsigned> applePosition = apple->GetPosition();
	snakeBot->Move(applePosition, deltaTime, snakePlayer->GetPosition());

	if(snakePlayer->DoTouch(apple) || snakeBot->DoTouch(apple))
	{ 
		Vector2<unsigned> randomPosition;

		char** checkField = field->GetField(); // called the field for generation in a random empty place  
		do 
		{
			randomPosition = 
			{
			randomPosition.x = std::rand() % (CONSOLE_WIDTH - 2) + 1,
			randomPosition.y = std::rand() % (CONSOLE_HEIGHT - 2) + 1 
			};
		} while (checkField[randomPosition.y][randomPosition.x] != ' ');

		apple->SetPosition(randomPosition);
	}

	snakePlayer->DoTouchOtherSnake(snakeBot->GetPosition());
	snakeBot->DoTouchOtherSnake(snakePlayer->GetPosition());

	snakePlayer->DoTouchItself();

	if (!snakePlayer->IsAlive() || !snakeBot->IsAlive()) 
	{
		currentWindow = GameWindow::MainMenu;
		field->DeallocateField();
		DealocateGameObjects();
	}
}

void Game::Render() 
{
	Console::ResetCursorPosition();

	switch (currentWindow)
	{
	case GameWindow::MainMenu: RenderMenu(); break;
	case GameWindow::GameScene:	RenderGameScene(); break;
	default: throw(GameException("Error", __func__, __LINE__)); 
	}
}
void Game::RenderMenu() const 
{
	std::cout << mainMenuContent;
}
void Game::RenderGameScene() const 
{
	field->ClearField();

	field->Set(walls);
	field->Set(apple);
	field->Set(snakePlayer);
	field->Set(snakeBot);

	field->Render(); 
}

void Game::HandleExeption(const GameException& error) 
{
	isRunning = false;
	Console::ClearScreen();

	std::cout << "Error!" << "\n";
	std::cout << error.GetErrorMessage() << "\n";
	std::cout << error.GetErrorFunc() << "\n";
	std::cout << error.GetErrorLine() << "\n";

	system("pause");
}
void Game::HandleOtherExeption(const  std::exception& exe) 
{
	isRunning = false;
	Console::ClearScreen();

	std::cout << "Error!" << "\n";
	std::cout << exe.what() << "\n";

	system("pause");
}

void Game::ReadMenuFromFile() 
{
	try 
	{
		if (!FileManager::ReadFromFile(filenameMainMenu, mainMenuContent)) 
		{
			throw(GameException("File " + mainMenuContent + " could not been opened", __func__, __LINE__));
		}
	}
	catch (const GameException& error) 
	{
		HandleExeption(error);
	}
	catch (const std::exception& exe) 
	{
		HandleOtherExeption(exe);
	}
}

void Game::AllocateGameObjects() 
{
	field.reset(new Field());
	field->AllocateField();

	walls.reset(new Walls());
	if (!walls->ReadWallsFromFile(filenameLevel))
		throw(GameException("Error", __func__, __LINE__));

	Vector2<unsigned> snakeHeadPosition = 
	{
	snakeHeadPosition.x = CONSOLE_WIDTH / 2,
	snakeHeadPosition.y = CONSOLE_HEIGHT / 2
	};
	snakePlayer.reset(new SnakePlayer(snakeHeadPosition));

	// get a new starting position for SnakeBot
	snakeHeadPosition = 
	{
	snakeHeadPosition.x = (CONSOLE_WIDTH / 4),
	snakeHeadPosition.y = (CONSOLE_HEIGHT / 4)
	};
	snakeBot.reset(new SnakeBot(snakeHeadPosition));

	apple.reset(new Apple(field->GetRandomPosition()));
}
void Game::DealocateGameObjects() 
{
	apple.reset();
	walls.reset();
	field.reset();
	snakePlayer.reset();
	snakeBot.reset();
}