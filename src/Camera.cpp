#include <iostream>

#include "Camera.h"

using namespace std;

Camera::Camera(sf::RenderWindow& window, float cameraX, float cameraY, float width, float height) {
	x = cameraX;
	y = cameraY;
	view.setCenter(sf::Vector2f(cameraX, cameraY));
	view.setSize(sf::Vector2f(width, height));
	window.setView(view);
};

void Camera::move(float dx, float dy) {
	x += dx;
	y += dy;
	view.setCenter(sf::Vector2f(x, y));
};