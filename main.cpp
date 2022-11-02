#include "Simulation.h"
#include "Bird.h"

#include <time.h>

int main(void)
{
	srand(unsigned(time(NULL)));

	Simulation simulation;
	
	while (simulation.running())
	{
		simulation.update();
		simulation.render();
	}

	return 0;
}