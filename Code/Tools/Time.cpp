#include "Time.h"

double Time::priviousTime = 0;
double Time::currentTime = std::clock(); // �������� �-��� ������ � ������� ������� �������� returns the number of secunds since the program was launched   

double Time::DeltaTime() 
{ 
	// ������������� ��� ��� ������� �ᒺ��� ��� used for all moving objects 
	priviousTime = currentTime;
	currentTime = std::clock();

	return (currentTime - priviousTime) / MILLISEC_IN_SEC; // ����������� ��� �� ������� � ��� �� �������� � �����.

}