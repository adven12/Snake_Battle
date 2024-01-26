#include "Walls.h"

bool Walls::ReadWallsFromFile(std::string& filename) 
{
	std::string content;

	if (!FileManager::ReadFromFile(filename, content)) return false;

	size_t columnIndex=0; size_t rowIndex=0;
	Vector2<unsigned> itemPosition;

	for (size_t i = 0; i < content.size(); i++)
	{
		if (content[i] == '\n') 
		{
			rowIndex++;
			columnIndex = -1;
		}
		else if (content[i] == '*') 
		{
			itemPosition = 
			{
			itemPosition.x = columnIndex,
			itemPosition.y = rowIndex
			};

			wallsPosition.push_back(itemPosition);
			};

		columnIndex++;
	}

	return true;
}

std::vector<Vector2<unsigned>> Walls::GetWallsPosition() const 
{
	return wallsPosition;
}