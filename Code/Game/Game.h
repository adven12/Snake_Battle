#pragma once
#include <string>
#include <iostream>
#include "GameEnumeration.h"
#include "../Tools/FileManager.h"
#include "../Tools/Console.h"
#include "GameExeption.h"
#include "../World/GameObjects.h"
#include "../Tools/InputManager.h"

class Game 
{
public:
	~Game();

	static Game& GetInstance();
	Game(Game& other) = delete;
	Game& operator=(Game& object) = delete;

	void HandleInput();
	void Update(double deltaTime);
	void Render();

	void HandleInputMenu();
	void HandleInputGameScene();

	void UpdateMenu();
	void UpdateGameScene(double deltaTime);

	void RenderMenu() const;
	void RenderGameScene() const;

	void HandleExeption(const GameException& error);
	void HandleOtherExeption(const std::exception& exe);

	void AllocateGameObjects();
	void DealocateGameObjects();

	bool isRunning = true;
private:
	Game();
	void ReadMenuFromFile();

	/////// Data aplication

	std::string filenameMainMenu = "Assets/MainMenu.txt";
	std::string mainMenuContent;
	std::string filenameLevel = "Assets/Level.txt";

	GameWindow currentWindow = GameWindow::MainMenu;
	MainMenuItem mainMenuSelectedItem = MainMenuItem::StartGame;
	Direction newSnakeDirection = Direction::None;

	/////// Objects

	std::unique_ptr<Apple> apple;
	std::unique_ptr<Walls> walls;
	std::unique_ptr<Field> field;
	std::unique_ptr<SnakePlayer> snakePlayer;
	std::unique_ptr<SnakeBot> snakeBot;
	
};