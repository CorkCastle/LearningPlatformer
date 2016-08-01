#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Tile {
public:
	
	//Dimensions
	sf::Vector2i position;
	int size;
	
	//Properties
	int type;

	sf::RectangleShape shape;
	
	//Constructor
	Tile(float x, float y, int type, float size);
	
	//Rendering
	void draw(sf::RenderWindow& window);
};