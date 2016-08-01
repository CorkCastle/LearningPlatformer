#pragma once

#include <SFML/Graphics.hpp>
#include <armadillo>
#include <vector>

#include "Tile.h"

using namespace std;
using namespace arma;

class Level {
public:
	//Level properties
	sf::Vector2i size;
	vector<vector<int>> rawTilemap;
	vector<Tile> tilemap;
	int tileSize; 

	//Spawn tile coordinates
	sf::Vector2f spawn;

	//Finish tile coordinates
	sf::Vector2f finish;

	//Constructor
	Level(string path, int tileSize);

	//Tilemap methods
	vector<vector<int>> loadRawTilemapFromImage(string path);
	void loadTilemap(vector<vector<int>> rawTilemap);
	Tile getTileFromMap(sf::Vector2i position);
	Tile getTileFromWorld(sf::Vector2f position);
	mat getTilemapSample(sf::Vector2f position, sf::Vector2i size);

	//Drawing methods
	void drawLevel(sf::RenderWindow& window);
};