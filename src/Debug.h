#pragma once
#include <SFML/Graphics.hpp>

#include "Tile.h"

#include <iostream>

using namespace std;

class Debug {
public: 

	//Font
	//static sf::Font font;

	//Wether or not debugging methods render to window
	//static bool debuggingEnabled;

	//Render text
	static void text(string text, sf::Vector2f position, sf::RenderWindow& window);

	//Render a line
	static void line(sf::Vector2f start, sf::Vector2f end, sf::RenderWindow& window);

	//Render a rectangle or a rectangle from a tile	
	static void rect(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::RenderWindow& window);
	static void rect(Tile tile, sf::Color color, sf::RenderWindow& window);
};
