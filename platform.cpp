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

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(rect, states);
}
