#include "Bird.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

void Bird::initVariables()
{
	this->velocity = sf::Vector2f((rand() % 20) - 10, (rand() % 20) - 10);
	this->position = sf::Vector2f((float)(rand() % 1500 + 50), (float)(rand() % 800 + 50)); // Initialize to a random position on screen.
	this->viewRadius = powf(100.f, 2); // Num is squared so I can save time doing the square root during the distance formula
	this->FOV = 270.f;
}

void Bird::initBody()
{
	this->body = sf::CircleShape(10.f, 3);
	this->body.setOrigin(10.f, 10.f);
	this->body.setFillColor(sf::Color(117, 117, 117, 255));
	this->body.setRotation(this->orientation);
	this->body.setPosition(this->position.x, this->position.y);
}

Bird::Bird()
{
	initVariables();
	initBody();
}

sf::Vector2f Bird::separation(Bird birbs[50], int numBirbs)
{
	return sf::Vector2f(0.f, 0.f);
}

sf::Vector2f Bird::alignment(Bird birbs[50], int numBirbs)
{
	return sf::Vector2f(0.f, 0.f);
}

sf::Vector2f Bird::cohesion(Bird birbs[50], int numBirbs)
{
	sf::Vector2f center = sf::Vector2f(0.f, 0.f);
	int birbsCounted = 0;

	for (int i = 0; i < numBirbs; i++)
	{
		inView(birbs[i].position);

		if (!withinView) continue;

		center += birbs[i].position;

		birbsCounted++;
	}

	center -= this->position;
	birbsCounted--;

	if (birbsCounted == 0) return sf::Vector2f(0, 0);

	center *= 1.f / birbsCounted;
	center -= this->position;

	return center *= 0.01f;
}

sf::Vector2f Bird::remainInBounds()
{
	sf::Vector2f adjustment = sf::Vector2f(0.f, 0.f);

	if (this->position.x > 1550)
	{
		adjustment.x = -((position.x - 1550) * 0.05f);
	}
	else if (this->position.x < 50)
	{
		adjustment.x = std::fabs(position.x + 50) * 0.05f;
	}
	if (this->position.y > 850)
	{
		adjustment.y = -((position.y - 850) * 0.05f);
	}
	else if (this->position.y < 50)
	{
		adjustment.y = std::fabs(position.y - 50) * 0.05f;
	}

	return adjustment;
}

void Bird::inView(sf::Vector2f position)
{
	float distance = 0.f;
	float angle = 0.f;
	
	float x = position.x - this->position.x;
	float y = position.y - this->position.y;

	this->withinView = true;
	
	// Make sure the birb is close enough to be in view.
	distance = powf(x, 2) + powf(y, 2);
	if (this->viewRadius <= distance)
	{
		this->withinView = false;
		return;
	}

	// Get the angle from position of birb to the other birb (MOUSE FOR TEST PURPOSES) between 0 - 360 degrees.
	angle = (float)(atan2f(y, x) * (180 / M_PI) + 90.f);
	angle -= orientation;
	if (angle < 0) angle += 360.f;

	sf::Vector2f limit = sf::Vector2f(0 - (this->FOV / 2), 0 + (this->FOV / 2));
	if (limit.x < 0) limit.x += 360;
	if (limit.y < 0) limit.y += 360;

	// Make sure the birb is within los.

	if (limit.x > limit.y)
	{
		if (angle < limit.x && angle > limit.y) this->withinView = false;
	} else {
		if (angle > limit.x && angle < limit.y) this->withinView = false;
	}

	// std::cout << "Orientation: " << this->orientation << ". Angle: " << angle << ". Limit : " << limit.x << ", " << limit.y << ". Within : " << this->withinView << "\n";
}

// Check for collision within this function then send the average variables off to the other functions.
// In order to get the values that will be used to move and rotate the birb.
void Bird::update(sf::Vector2i mousePos, Bird birbs[50], int numBirbs)
{
	float maxSpeed = 10.f;
	float minSpeed = 2.5f;

	sf::Vector2f rule1 = this->cohesion(birbs, numBirbs);
	// sf::Vector2f rule2 = this->separation(birbs, numBirbs);
	// sf::Vector2f rule3 = this->alignment(birbs, numBirbs);
	sf::Vector2f rule4 = this->remainInBounds();

	this->velocity = this->velocity + rule1 + rule4;

	// Limit the speed while conserving direction.
	if (abs(this->velocity.x) > maxSpeed)
	{
		this->velocity = (this->velocity / abs(this->velocity.x)) * maxSpeed;
	} 
	else if (abs(this->velocity.y) > maxSpeed) 
	{
		this->velocity = (this->velocity / abs(this->velocity.y)) * maxSpeed;
	}

	this->position += this->velocity;

	this->orientation = (float)(atan2f(this->velocity.y, this->velocity.x) * (180 / M_PI) + 90.f);

	this->body.setRotation(this->orientation);
	this->body.setPosition(this->position);
}

void Bird::render(sf::RenderTarget *target)
{
	target->draw(this->body);
}