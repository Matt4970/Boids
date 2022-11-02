#pragma once

#include "SFML\Graphics.hpp"
#include "Bird.h"

class Simulation
{
private:
	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	sf::Event event;

	void initVariables();
	void initWindow();

	Bird birbs[50];
	int numBirbs;

public:

	// Constructors and Deconstructors
	Simulation();
	~Simulation();

	// Functions
	const bool running() const;
	void pollEvents();

	void update();
	void render();
};