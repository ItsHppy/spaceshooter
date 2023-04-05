#pragma once 
#include "SFML/Graphics.hpp" 
#include "settings.h" 
#include "Player.h" 
#include "meteor.h" 
#include <vector> 
#include "laser.h" 
#include "textobj.h"

class Game {
private:
	sf::RenderWindow window;
	std::vector<Meteor*> meteorSprites;
	Player player;
	TextObj text;

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}


	void Update() {
		switch (gameState) {
		case PLAY:
			player.Update();
			for (auto meteor : meteorSprites) {
				meteor->update();
			}
			break;
		case GAME_OVER:
			text.update("GAME OVER");
			break;
		}
	}

	void checkCollisions() {
		sf::FloatRect playerBounds = player.getHitBox();
		for (auto& meteor : meteorSprites) {
			sf::FloatRect meteorBounds = meteor->getHitBox();
			if (meteorBounds.intersects(playerBounds)) {
				meteor->spawn();
				player.decreaseHp(meteor->getDamage());

			}
			auto laserSprites = player.getLaserSprites();
			for (auto& laser : *laserSprites) {

				sf::FloatRect laserBounds = laser->getHitBox();
				if (meteorBounds.intersects(laserBounds)) {
					meteor->spawn();
				}
			}
			(*laserSprites).remove_if([](Laser* laser) {return laser->isHit(); });
		}
	}


	void Draw() {
		switch (gameState) {
		case PLAY:
			window.clear();
			for (auto meteor : meteorSprites) {
				window.draw(meteor->getSprite());
			}
			player.Draw(window);
			window.display();
			break;
		case GAME_OVER:
			window.clear();
			text.draw(window);
			window.display();
			break;
		}
	}


public:
	enum GameState { PLAY, GAME_OVER };
	GameState gameState = PLAY;

	Game():text("GAME_OVER", sf::Vector2f{ 250.f, 350.f }) {
		sf::VideoMode videoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
		window.create(videoMode, WINDOW_TITLE);
		{
			window.setFramerateLimit(FPS);
			meteorSprites.reserve(METEORS_QTY);
			for (int i = 0; i < METEORS_QTY; i++) {
				Meteor* m = new Meteor();
				meteorSprites.push_back(new Meteor());
			}
		}
	}
	void play() {
		while (window.isOpen()) {
				checkEvents();
				Update();
				if (player.getHp() <= 0) gameState = GAME_OVER;
				checkCollisions();
				Draw();
		}
	}
};