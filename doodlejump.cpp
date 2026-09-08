#include "doodlejump.h"
#include "platform.h"
#include "player.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <cstdlib>

Game::Game(const std::string& backscreen): player(Player("jumper.png")), backscreenTexture(backscreen), backscreenSprite(backscreenTexture) {
	srand(time(NULL));
	if (!backscreenTexture.loadFromFile(backscreen, false, sf::IntRect({0, 0}, {800, 600}))) {
		std::cerr << "failed to load backscreen" << std::endl;
		return; 
	}
	backscreenSprite.setTexture(backscreenTexture);
	backscreenSprite.scale({1.33f, 1.33f});

	for(int i = 0; i < 5; i++) {
		platforms.push_back(Platform(rand() % 550 + 50, rand() % 700 + 50));
	}

}

void Game::update(float time) {
	player.update(time);

	checkCollisions();

	if (player.getRate().y < 0) {
		worldOffset -= player.getRate().y * time;
        
		float playerWorldY = player.getPosition().y;
		if (playerWorldY < highestWorldY) {
		    highestWorldY = playerWorldY;
		}
	}

	if (player.getPosition().y > 900) {
        	gameOver = true;
    	}
}

void Game::render(sf::RenderWindow& window) {
	window.clear(sf::Color::Black);
	window.draw(backscreenSprite);
	window.draw(player);
	
	sf::RenderStates states;
	states.transform.translate({0, worldOffset});
	for(int i = 0; i < 5; i++) {
		window.draw(platforms[i], states);
	}
	
	window.display();
}	

void Game::checkCollisions() {
	sf::FloatRect playerBounds = player.getBounds();
	sf::Vector2f playerRate = player.getRate();

	for (auto& platform : platforms) {
		sf::FloatRect platformBounds = platform.getBounds();
		
		playerBounds.position.y -= worldOffset;

		if (playerBounds.findIntersection(platformBounds) && playerRate.y > 0) {
			float playerBottom = playerBounds.position.y + playerBounds.size.y;
			float platformTop = platformBounds.position.y;

			if (playerBottom >= platformTop && playerBottom - playerRate.y * 0.1f <= platformTop) {
				player.togglePlatform();
				player.jump();
				break;
			}
		}
	}
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
