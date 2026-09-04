#include "doodlejump.h"
#include "platform.h"
#include "player.h"

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

int main() {
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode({600, 800}), "My window");

	sf::Texture backscreen;
	if (!backscreen.loadFromFile("background.png", false, sf::IntRect({0, 0}, {800, 600}))) {
		std::cerr << "failed to load backscreen" << std::endl;
		return EXIT_FAILURE;
	}
	sf::Sprite backscreenSprite(backscreen);
	backscreenSprite.scale({1.33f, 1.33f});

	std::vector<Platform> platforms;
	sf::RenderStates states;
	states.transform.translate({0, 0});
	for(int i = 0; i < 5; i++) {
		platforms.push_back(Platform(rand() % 550 + 50, rand() % 700 + 50));
	}

	while (window.isOpen())
	{
		while (const auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear(sf::Color::Black);
		window.draw(backscreenSprite);
		
		for(int i = 0; i < 5; i++) {
			window.draw(platforms[i], states);
		}
		
		window.display();
	}

	return 0;
}	
