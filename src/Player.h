#pragma once

#include <armadillo>
#include <SFML/Graphics.hpp>
#include "Level.h"

using namespace std;
using namespace arma;

class Player {
public:

	//Movement
	sf::Vector2f position;
	sf::Vector2f velocity;
	bool grounded;
	float lastX = -128;

	//Neural network training
	sf::Clock clock;
	float fitness = 0;

	//Predict player movement
	string predictMovement(mat prediction);
	
	//Player dimensions
	float size;

	//Rendering
	sf::RectangleShape shape;

	//Constructor
	Player(sf::Vector2f startPosition, float size);

	//Rendering
	void draw(sf::RenderWindow& window, sf::View& view, Level level, string move);
};
