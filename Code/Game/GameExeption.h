#pragma once
#include <string>

// container of information about possible game errors.
class GameException 
{
public:
	GameException(const std::string& initMessage="Error", const std::string& initFunc="", const int initLine = 0);

	const std::string& GetErrorMessage() const;
	const std::string& GetErrorFunc() const;
	const int GetErrorLine() const;

private:
	std::string errorMessage;
	std::string errorFunc;
	int errorline;
};