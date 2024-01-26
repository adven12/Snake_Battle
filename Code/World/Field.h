#pragma once
#include <random>
#include <iostream>
#include "../Tools/Tools.h"
#include "../Tools/ConsoleSizeSetting.h"
#include "../Tools/Console.h"
#include "Walls.h"
#include "Apple.h"
#include "SnakeBot.h"
#include "SnakePlayer.h"

//class Walls;

class Field 
{
public:
	const Vector2<unsigned> GetRandomPosition() const;
	void AllocateField();
	void DeallocateField();
	void ClearField();
	void Render() const;
	char** GetField() const;
	void Set(const std::unique_ptr<Walls>& walls);
	void Set(const std::unique_ptr<Apple>& apple);

	template <typename T>
	void Set(const std::unique_ptr<T>& objectsnake);

private:
	char** field;
};