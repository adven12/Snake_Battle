#pragma once
#include <string>
#include <vector>
#include "../Tools/Tools.h"
#include "../Game/GameExeption.h"
#include "../Tools/FileManager.h"

class Walls 
{
public:
	bool ReadWallsFromFile(std::string& filename);
	std::vector<Vector2<unsigned>> GetWallsPosition() const;

private:
	std::vector<Vector2<unsigned>> wallsPosition;
};