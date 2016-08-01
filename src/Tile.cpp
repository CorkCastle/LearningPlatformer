#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"

using namespace std;

//Constructor
Tile::Tile(float tileX, float tileY, int tileType, float tileSize) {
	
	//Tile position
	position.x = tileX;
	position.y = tileY;

	//Tile dimensions
	size = tileSize;

	//Defualt rendering
	shape.setSize(sf::Vector2f(size, size));
	shape.setFillColor(sf::Color::White);
	shape.setOutlineColor(sf::Color(133, 133, 133, 255));
	shape.setOutlineThickness(1);
	type = tileType;
};

//Render the tile
void Tile::draw(sf::RenderWindow& window) {

	//If the tile is solid
	if (type == 1) {
		shape.setPosition(position.x, position.y);
		window.draw(shape);
	}
};