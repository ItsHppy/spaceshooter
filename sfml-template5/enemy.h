#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
struct Obstacle {
	sf::Texture texture;
	sf::Sprite sprite;
	float speedY;
	float speedX;
};
void respawn(Obstacle& obs) {
	int choice1 = rand() % 2 + 1;
	if (choice1 == 1) { obs.texture.loadFromFile("car.png"); }
	if (choice1 == 2) { obs.texture.loadFromFile("car3.png"); }
	obs.sprite.setTexture(obs.texture);
	int posx = rand() % 351 + 100;
	posx = posx - posx % 100;
	int posy = -150.f;
	obs.sprite.setPosition(posx, posy);
}
void obstacleInit(Obstacle& obs) {
	obs.texture.loadFromFile("car.png");
	obs.sprite.setTexture(obs.texture);
	respawn(obs);
	obs.speedY = 5.f;
	obs.speedX = 0.f;
}
void obstacleUpdate(Obstacle& obs) {
	obs.sprite.move(obs.speedX, obs.speedY);
	if (obs.sprite.getPosition().y >= WINDOW_HEIGHT) {
		respawn(obs);
	}
}
void obstacleDraw(sf::RenderWindow& window, const Obstacle& obs) {
	window.draw(obs.sprite);
}
