#include "Time.h"

double Time::priviousTime = 0;
double Time::currentTime = std::clock(); // повератаЇ к-сть секунд з моменту запуску програми returns the number of secunds since the program was launched   

double Time::DeltaTime() 
{ 
	// використовуЇц€ дл€ вс≥х рухомих обТЇкт≥в гри used for all moving objects 
	priviousTime = currentTime;
	currentTime = std::clock();

	return (currentTime - priviousTime) / MILLISEC_IN_SEC; // визначаЇтьс€ час м≥ж кадрами в сек та переводе в м≥л≥сек.

}