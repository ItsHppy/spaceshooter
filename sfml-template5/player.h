#pragma once 
#include "settings.h" 
#pragma once 
#include "settings.h" 
#include "laser.h" 
#include <list> 
#include "textobj.h"
class Player {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	float speedx;
	std::list<Laser*> laserSprites;
	sf::Clock timer;
	int hp;
	int point;
	TextObj hpText;
public:
	Player() :hpText(std::to_string(hp), sf::Vector2f{ 0.f, 0.f }) {
		texture.loadFromFile(PLAYER_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(PLAYER_START_POS);
		timer.restart();
		speedx = 0.f;
		hp = 100;
		point = 0;
	}

	void Update() {
		speedx = 0.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			speedx = -PLAYER_SPEED;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			speedx = PLAYER_SPEED;
		}
		sf::Vector2f playerPosition = sprite.getPosition();
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.move(speedx, 0.f);
		if (sprite.getPosition().x < 0) {
			sprite.setPosition(0.f, playerPosition.y);
		}
		if (sprite.getPosition().x > WINDOW_WIDTH - bounds.width) {
			sprite.setPosition(WINDOW_WIDTH - bounds.width, playerPosition.y);
		}
		fire();
		for (auto laser : laserSprites) {
			laser->update();
		}
		hpText.update("HP:" + std::to_string(hp));
	}

	void Draw(sf::RenderWindow& window) {
		window.draw(sprite);
		for (auto laser : laserSprites) {
			window.draw(laser->getSprite());
		}
		hpText.draw(window);
	}


	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }

	int getHp() { return hp; }

	bool isAlive() { return hp > 0; }

	void pointChange(int damage) {
		point = point + damage;
	}

	std::list<Laser*>* getLaserSprites() { return &laserSprites; }
	void decreaseHp(int damage) { hp -= damage; };

	void fire() {
		int now = timer.getElapsedTime().asMilliseconds();
		if (now > FIRE_COOLDOWN) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				sf::Vector2f pos = sprite.getPosition();
				sf::FloatRect bounds = sprite.getGlobalBounds();
				sf::Vector2f posCenter = sf::Vector2f{ pos.x + bounds.width / 2,pos.y + bounds.height / 2 };
				auto laser = new Laser(posCenter);
				laserSprites.push_back(laser);
				timer.restart();
			}
		}
	}
};