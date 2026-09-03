#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

class Player: public sf::Drawable, public sf::Transformable {
	sf::Texture texture;
	sf::Vector2f rate = {0, 0};
	const float width;
	const float height;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		Player()=delete;
		Player(const std::string& texture, const float width = 30, const float height = 40);
	
		void update(float time);
		void rotate();
		void jump();
		void fall();
		void reset();
};	
