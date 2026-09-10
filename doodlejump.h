#pragma once

#include "player.h"
#include "platform.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>


class Game {
	Player player;
	sf::Texture backscreenTexture;
	sf::Sprite backscreenSprite;
	std::vector<Platform> platforms;
	sf::Clock clock;
	sf::Font font = sf::Font("resources/ARIAL.ttf");
	sf::Text text;

	bool gameOver = false;
	float worldOffset = 0;
	float counter = 0;

	void update(float time);
	void reset();
	void render(sf::RenderWindow& window);

	public:
		Game()=delete;
		Game(const std::string& backscreen);
		void run();

};
