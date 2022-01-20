#include "Simulation.h"
#include "Bird.h"

#include<iostream>

void Simulation::initVariables()
{
	this->videoMode = sf::VideoMode(1600, 900);
	this->numBirbs = 10;
	for (int i = 0; i < numBirbs; i++)
	{
		Bird birb;
		this->birbs[i] = birb;
	}
	this->birbs[0].body.setFillColor(sf::Color(200, 0, 0));
}

void Simulation::initWindow()
{
	this->window = new sf::RenderWindow(this->videoMode, "Boids Simulation", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(75);
}

Simulation::Simulation()
{
	this->initVariables();
	this->initWindow();
}

Simulation::~Simulation()
{
	delete this->window;
}

const bool Simulation::running() const
{
	return this->window->isOpen();
}

void Simulation::pollEvents()
{
	while (this->window->pollEvent(event))
	{
		switch (this->event.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->event.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
		}
	}
}

void Simulation::update()
{
	pollEvents();
	for (int i = 0; i < this->numBirbs; i++) this->birbs[i].update(sf::Mouse::getPosition(*this->window), this->birbs, this->numBirbs);

	this->birbs[0].inView(sf::Vector2f(sf::Mouse::getPosition(*this->window)));
	if (this->birbs[0].withinView)
	{
		// std::cout << "Working!\n";
	}
}

void Simulation::render()
{
	this->window->clear(sf::Color(242, 216, 213, 255));

	for (int i = 0; i < this->numBirbs; i++) this->birbs[i].render(this->window);

	this->window->display();
}