#pragma once 

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

class Platform: public sf::Drawable, public sf::Transformable {
	sf::Color color = sf::Color::Green;
	const float width = 60;
	const float height = 5;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		Platform();
		Platform(float x, float y);
		sf::Vector2f getPosition() const;
};
