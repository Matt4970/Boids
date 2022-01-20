#include "Simulation.h"
#include "Bird.h"

int main(void)
{
	Simulation simulation;
	
	while (simulation.running())
	{
		simulation.update();
		simulation.render();
	}

	return 0;
}