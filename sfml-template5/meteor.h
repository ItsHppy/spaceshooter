#pragma once
#include "settings.h"

class Meteor {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	static std::string textureFileNames[];
	static int arrDamage[];
	float speedx, speedy;
	int damage;
public:

	Meteor() {
		int index = rand() % 4;
		damage = arrDamage[index];
		texture.loadFromFile(textureFileNames[index]);
		sprite.setTexture(texture);
		spawn();
	}

	void spawn() {
		float meteorWidth = sprite.getLocalBounds().width;
		float x = rand() % (int)(WINDOW_WIDTH - meteorWidth);
		float y = rand() % (int)(WINDOW_HEIGHT / 2) - WINDOW_HEIGHT / 2;
		sprite.setPosition(x, y);
		speedx = rand() % 5 - 2; // от -2 до 2
		speedy = rand() % 6 + 3; // от 3 до 8

	}

	void update() {
		sprite.move(speedx, speedy);
		sf::Vector2f pos = sprite.getPosition();
		float meteorWidth = sprite.getLocalBounds().width;
		if (pos.x < -meteorWidth || pos.y > WINDOW_HEIGHT || pos.x > WINDOW_WIDTH)
		{
			spawn();
		}
	}

	sf::Sprite& getSprite() { return sprite; }

	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }

	int getDamage() { return damage; }
};


std::string Meteor::textureFileNames[] = { "images\\tinymeteor.png", "images\\smallmeteor.png", "images\\mediummeteor.png", "images\\bigmeteor.png" };

int Meteor::arrDamage[] = { 5, 15, 30, 50 };