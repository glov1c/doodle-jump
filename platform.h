#pragma once 

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

class Platform: public sf::Drawable, public sf::Transformable {
	sf::RectangleShape rect;
	sf::Color color = sf::Color::Green;
	float width = 90;
	float height = 10;


	public:
		Platform();
		Platform(float x, float y);
		sf::Vector2f getPosition() const;
		void setPosition(const sf::Vector2f& pos);
		sf::FloatRect getBounds() const;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
