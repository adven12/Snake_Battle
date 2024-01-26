#include "GameExeption.h"

GameException::GameException(const std::string& initMessage, const std::string& initFunc, const int initLine) :
	errorMessage(initMessage), errorFunc(initFunc), errorline(initLine) {}

const std::string& GameException::GetErrorMessage() const
{
	return  errorMessage;
}
const std::string& GameException::GetErrorFunc() const 
{
	return  errorFunc;
}
const int GameException::GetErrorLine() const
{
	return  errorline;
}
