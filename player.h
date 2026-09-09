#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

class Player: public sf::Drawable, public sf::Transformable {
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::Vector2f rate = {0, 0};
	float width = 30;
	float height = 50;
	bool isOnGround = true;
	bool rotateLeft = false;
	bool rotateRight = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		Player()=delete;
		Player(const std::string& texture);
	
		sf::Vector2f getRate() const;
		void setRate(const sf::Vector2f& newRate);
		sf::FloatRect getBounds() const;
		void update(float time);
		void rotate(bool toLeft, bool toRight);
		void jump();
		void togglePlatform();
		void reset();
};	
