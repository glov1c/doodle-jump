#include "doodlejump.h"
#include "platform.h"
#include "player.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <cstdlib>

Game::Game(const std::string& backscreen): player(Player("jumper.png")), backscreenTexture(backscreen), backscreenSprite(backscreenTexture), text(font) {
	srand(time(NULL));
	if (!backscreenTexture.loadFromFile(backscreen, false, sf::IntRect({0, 0}, {800, 600}))) {
		std::cerr << "failed to load backscreen" << std::endl;
		return; 
	}
	backscreenSprite.setTexture(backscreenTexture);
	backscreenSprite.scale({1.33f, 1.33f});

	platforms.push_back(Platform(275, 550));
	for(int i = 0; i < 5; i++) {
		platforms.push_back(Platform(rand() % 550 + 50, rand() % 300));
	}

}


void Game::update(float time) {
	player.update(time);

	worldOffset -= 0.09 * time;
	if (worldOffset > 0) 
		counter += (worldOffset / 10);
	float playerWorldY = 800 / 2.0f + worldOffset;
        sf::FloatRect playerBounds = player.getBounds();

	for(auto& platform : platforms) {
		sf::Vector2f pos = platform.getPosition();
		platform.setPosition({pos.x, pos.y + worldOffset});
	}

	for (auto& platform : platforms) {
		sf::FloatRect platformBounds = platform.getBounds();
		sf::FloatRect playerBounds = player.getBounds();
		playerBounds.position.y += (playerBounds.size.y - 5) ;
		playerBounds.size.y = 5;

		if (playerBounds.findIntersection(platformBounds)) {
			float platformTop = platformBounds.position.y;
			if (worldOffset < 0 && playerWorldY < platformTop + 10.0f) {
				worldOffset = 0.15;
				break;
			}
		}
	}
}

void Game::render(sf::RenderWindow& window) {
	window.clear(sf::Color::Black);
	window.draw(backscreenSprite);

	text.setString(std::to_string(static_cast<int>(counter)));
	text.setCharacterSize(36);
	text.setFillColor(sf::Color::Red);
	text.setPosition({290, 5});
	window.draw(text);

	window.draw(player);
	

	while (platforms.size() < 15  && (worldOffset > 0)) {
		platforms.push_back(Platform(rand() % 450 + 50, -100 - (rand() % 400)));
		platforms.push_back(Platform(rand() % 450 + 50, -400 - (rand() % 400)));
		platforms.push_back(Platform(rand() % 450 + 50, -800 - (rand() % 400)));
	}

	for(auto it = platforms.begin(); it != platforms.end(); ) {
		if (it->getPosition().y > 800 || it->getPosition().y < -1200) {
			it = platforms.erase(it);
		}
		else {
			++it;
		}
	}

	if (platforms.size() == 0) gameOver = true;

	for(auto& platform : platforms) {
		window.draw(platform); 
	}

	
	window.display();
}	



void Game::run() {
	sf::RenderWindow window(sf::VideoMode({600, 800}), "Doodle jump");

	while (window.isOpen() && !gameOver) {
		float time = clock.restart().asSeconds();

		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();

			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				switch (keyPressed->scancode) {
					case sf::Keyboard::Scancode::Escape:
						window.close();
						break;
					case sf::Keyboard::Scancode::A:
						player.rotate(1, 0);
						break;
					case sf::Keyboard::Scancode::D:
						player.rotate(0, 1);
						break;

					default:
						break;
				}

			}
			else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
				if (keyReleased->scancode == sf::Keyboard::Scancode::A) player.rotate(0, 0);
				if (keyReleased->scancode == sf::Keyboard::Scancode::D) player.rotate(0, 0);
			}
		}

		if (!gameOver) 
			update(time);

		render(window);
	}
}
