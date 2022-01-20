#pragma once

#include "SFML\Graphics.hpp"

class Bird
{
private:
	float viewRadius;
	float tooCloseF;
	float FOV; // 270 degrees means the birb can see everything but the 90 degrees directly behind him

	void initVariables();
	void initBody();
public:
	sf::CircleShape body;
	bool withinView;
	bool tooClose;

	float orientation;
	sf::Vector2f velocity;
	sf::Vector2f position;
	
	// Constructor and Deconstructor
	Bird();

	// Functions
	sf::Vector2f separation(Bird birbs[10], int numBirbs);
	sf::Vector2f alignment(Bird birbs[10], int numBirbs);
	sf::Vector2f cohesion(Bird birbs[10], int numBirbs);
	sf::Vector2f remainInBounds();

	void inView(sf::Vector2f position);

	void update(sf::Vector2i mousePos, Bird birbs[10], int numBirbs);
	void render(sf::RenderTarget *target);
};