#include "doodlejump.h"
#include "platform.h"
#include "player.h"

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode({600, 800}), "My window");

	while (window.isOpen())
	{
		while (const auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear(sf::Color::Black);
		sf::Texture backscreen;
		if (!backscreen.loadFromFile("background.png", false, sf::IntRect({0, 0}, {800, 600}))) {
			std::cerr << "failed to load backscreen" << std::endl;
			return EXIT_FAILURE;
		}
		sf::Sprite backscreenSprite(backscreen);
		backscreenSprite.scale({1.33f, 1.33f});
		window.draw(backscreenSprite);
		window.display();
	}
}	
