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

	bool gameOver = false;
	float highestWorldY = 0;
	float worldOffset = 20;

	void update(float time);
	void reset();
	void checkCollisions();
	void init();
	void render(sf::RenderWindow& window);

	public:
		Game()=delete;
		Game(const std::string& backscreen);
		void run();

};
