#include <SFML/Graphics.hpp>
#include <iostream>
#include "Debug.h"
#include "Level.h"
#include "Player.h"

using namespace std;

//Constructor
Player::Player(sf::Vector2f startPosition, float playerSize) {

	//Starting position
	position = startPosition;

	//Dimensions
	size = playerSize;

	//Movement
	velocity = sf::Vector2f(0, 0);

	//Default rendering
	shape.setSize(sf::Vector2f(64, 64));
	shape.setFillColor(sf::Color(22, 22, 22, 255));
	shape.setOutlineColor(sf::Color(122, 122, 122, 255));
	shape.setOutlineThickness(1);
};

//Predict the movement of the player with the current neural network
string Player::predictMovement(mat prediction) {

	//The index of the maximum element in prediction matrix
	int maxIndex = 0;

	//Initialize maximum value
	float max = prediction(0, 0);

	//Interate over prediction matrix
	for (int i = 1; i < 3; i++) {
		if (prediction(0, i) > max) {

			//New maximum found
			max = prediction(0, i);
			maxIndex = i;
		}
	}

	//Return movement command based on output of prediction calculation
	if (maxIndex == 0) return "left";
	if (maxIndex == 1) return "up";
	if (maxIndex == 2) return "right";
};

//Player rendering
void Player::draw(sf::RenderWindow& window, sf::View& view, Level level, string move) {

	//Player control scheme
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || move == "up") {

		//Grounded check
		if (grounded) { 

			//Jump
			velocity.y = -20;
			position.y += 0.5;
			grounded = false;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || move == "left") {

		//Move player left
		velocity.x = -7;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || move == "right") {
		
		//Move player right
		velocity.x = 7;
	}

	//Add force of gravity to player velocity
	velocity.y += 0.8;
	
	//Position at player center
	int centerX = position.x - (size / 2);
	int centerY = position.y - (size / 2);

	//Dimensions
	int halfSize = size / 2;
	float skin = 2;

	//Nearest tiles for preforming collision checks
	Tile currentTile = level.getTileFromWorld(sf::Vector2f(centerX, centerY));
	Tile below = level.getTileFromWorld(sf::Vector2f(centerX, centerY + (currentTile.size / 2) + velocity.y));
	Tile right = level.getTileFromWorld(sf::Vector2f(centerX + skin + (currentTile.size / 2), centerY));
	Tile top = level.getTileFromWorld(sf::Vector2f(centerX, centerY - skin - (currentTile.size / 2)));
	Tile left = level.getTileFromWorld(sf::Vector2f(centerX - skin - (currentTile.size / 2), centerY));

	//Check bottom collision
	if (below.type != 0 && velocity.y > 0) {
		grounded = true;
		velocity.y = 0;
	}
	else {
		grounded = false;
	}

	//Check top collision
	if (top.type != 0 && velocity.y < 0) velocity.y = 0;
	 
	//Check left collision
	if (left.type != 0 && velocity.x < 0) velocity.x = 0;

	//Check right collision
	if (right.type != 0 && velocity.x > 0) velocity.x = 0;

	//Update player position
	position.y += velocity.y;
	position.x += velocity.x;

	//Update position tracking
	lastX = position.x;

	//Centered camera
	view.setCenter(position);
	
	//Reset x velocity to prevent momentum build up
	velocity.x = 0;
	
	//Render player
	shape.setPosition(position);
	window.draw(shape);
};