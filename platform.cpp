#include "platform.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

Platform::Platform() {
	rect.setSize({width, height});
	rect.setOrigin({width / 2, height / 2});
	rect.setFillColor(color);
}


Platform::Platform(float x, float y) {
	rect.setSize({width, height});
	rect.setOrigin({width / 2, height / 2});
	rect.setFillColor(color);
	rect.sf::Transformable::setPosition({x, y});
}

sf::FloatRect Platform::getBounds() const {
	return rect.getGlobalBounds();
}

void Platform::setPosition(const sf::Vector2f& pos) {
	rect.setPosition(pos);
}

sf::Vector2f Platform::getPosition() const {
	return rect.getPosition();
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(rect, states);
}
