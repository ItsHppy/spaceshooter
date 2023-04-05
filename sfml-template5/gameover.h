#pragma once
#include "settings.h"
#include "player.h"
class GameOver {
private:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	GameOver(sf::Vector2f pos) {
		texture.loadFromFile(END_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(pos);
	}
	void Draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}


	sf::Sprite& getSprite() { return sprite; }
};