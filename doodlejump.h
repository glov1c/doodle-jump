
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>


class Game: public sf::Drawable, public sf::Transformable {
	Player player;
	std::vector<Platform> platforms;
	sf::Clock clock;
	sf::RenderWindow window;

	void update();

	public:
		Game();
		void run();

};
