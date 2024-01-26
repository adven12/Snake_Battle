#include "FileManager.h"

bool FileManager::ReadFromFile(std::string& filename, std::string& content) 
{
	std::ifstream fileStream(filename);
	content.clear();

	if (!fileStream.is_open()) 
	{
		return 0;
	}
	std::string textLine;

	while (!fileStream.eof()) 
	{
		std::getline(fileStream, textLine);
		textLine.push_back('\n');
		content += textLine;
	}

	fileStream.close();
	return true;
}