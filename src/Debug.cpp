#include <SFML/Graphics.hpp>

#include "Debug.h"
#include "Tile.h"

#include <iostream>

using namespace std;

//Draw an arbitrary rectangle
void Debug::rect(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::RenderWindow& window) {
	//if (debuggingEnabled) {

		sf::RectangleShape rect;

		//Rendering colors
		rect.setFillColor(sf::Color(0, 0, 0, 0));
		rect.setOutlineColor(color);
		rect.setOutlineThickness(1);

		//Shape dimensions
		rect.setPosition(position);
		rect.setSize(size);
		window.draw(rect);
	//}
};

//Draw a rectangle from a tile object
void Debug::rect(Tile tile, sf::Color color, sf::RenderWindow& window) {
	//if (debuggingEnabled) {
		sf::RectangleShape rect;

		//Rendering colors
		rect.setFillColor(sf::Color(0, 0, 0, 0));
		rect.setOutlineColor(color);
		rect.setOutlineThickness(1);

		//Shape dimensions
		rect.setPosition(tile.position.x, tile.position.y);
		rect.setSize(sf::Vector2f(tile.size, tile.size));
		window.draw(rect);
	//}
};

//Draw text
void Debug::text(string text, sf::Vector2f position, sf::RenderWindow& window) {
	//if (debuggingEnabled) {
		//sf::Text text(text, font);
		//text.setPosition(position);
		//window.draw(text);
	//}
};

//Draw a line from two vectors
void Debug::line(sf::Vector2f start, sf::Vector2f end, sf::RenderWindow& window) {
	//if (debuggingEnabled) {

		sf::Vertex line[] = {
			sf::Vertex(start),
			sf::Vertex(end)
		};

		window.draw(line, 2, sf::Lines);
	//}
};