#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <armadillo>
#include "Tile.h"
#include "Level.h"
#include "Player.h"
#include "Debug.h"

using namespace std;
using namespace arma;

//Constructor
Level::Level(string path, int levelTileSize) {

	//Set tilesize
	tileSize = levelTileSize;

	//Load level from image
	loadTilemap(loadRawTilemapFromImage(path));
};

//Load a raw tilemap from an image
vector<vector<int>> Level::loadRawTilemapFromImage(string path) {

	//Level image
	sf::Image image;

	//Raw tilemap to pipe image data to
	vector<vector<int>> rawTilemap;
	
	//Load image and handle errors
	if (!image.loadFromFile(path)) {
		cout << "Failed to load image" << endl;
	}

	//Level dimensions
	size.x = image.getSize().x;
	size.y = image.getSize().y;

	//Iterate through pixels of image and add to tilemap according to color channels
	for (int y = 0; y < size.y; y++) {
		
		//Current row in raw tilemap
		vector<int> row;
		for (int x = 0; x < size.x; x++) {

			//Current pixel in iteration
			sf::Color pixel = image.getPixel(x, y);
			
			//Pipe raw data to tilemap
			if (pixel.r > 200)row.push_back(1);			//Solid tile (white)
			else if (pixel.r < 50)row.push_back(0);		//Non solid tile (black)
		}

		//Pipe row data to map
		rawTilemap.push_back(row);
	}
	return rawTilemap;
};

//Load the render ready tilemap from a raw tilemap
void Level::loadTilemap(vector<vector<int>> rawTilemap) {

	int y = 0;

	for (vector<int> row : rawTilemap) {

		int x = 0;

		for (int type : row) {

			if (type == 2) {
				spawn = sf::Vector2f(x * tileSize, y * tileSize);
			}

			if (type == 3) {
				finish = sf::Vector2f(x * tileSize, y * tileSize);
			}

			//Add a tile to the map depending on the type
			Tile tile = Tile(x * tileSize, y * tileSize, type, tileSize);
			tilemap.push_back(tile);
			x++;
		}
		y++;
	}
};

//Get a tile from tilemap coordinates
Tile Level::getTileFromMap(sf::Vector2i position) {
	if (position.x < size.x && position.x > 0 && position.y < size.y && position.y > 0) {
		return tilemap[position.y * size.x + position.x];
	}
	
	return Tile(0, 0, 0, 64);
};

//Get a tile from world coordinates
Tile Level::getTileFromWorld(sf::Vector2f position) {
	int x = static_cast<int>(ceil(position.x / tileSize));
	int y = static_cast<int>(ceil(position.y / tileSize));

	if (x < size.x && x > 0 && y < size.y && y > 0) {
		return tilemap[y * size.x + x];
	}

	return Tile(0, 0, 0, 64);
};

//Get an array of tiles from level sample area
mat Level::getTilemapSample(sf::Vector2f position, sf::Vector2i halfSize) {

	mat sample(halfSize.x * 2, halfSize.y * 2);

	for (int y = 0; y < halfSize.y * 2; y++) {
		for (int x = 0; x < halfSize.x * 2; x++) {
			float tileX = (position.x - halfSize.x) + x * tileSize;
			float tileY = (position.y - halfSize.y) + y * tileSize;
			Tile tile = getTileFromWorld(sf::Vector2f(tileX, tileY));
			sample(x, y) = tile.type;
		}
	}

	return sample;
};

//Draw the level
void Level::drawLevel(sf::RenderWindow& window) {
	int count = 0;
	for (Tile n : tilemap) {
		if (n.type != 0) {
			//if (sqrt(pow(playerPosition.x - n.position.x, 2) + pow(playerPosition.y - n.position.y, 2)) < 1000) {
				count++;
				n.draw(window);
			//}
		}
	}
};



