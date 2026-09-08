#include "player.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>


Player::Player(const std::string& texture): playerTexture(texture), playerSprite(playerTexture) {
	if (!playerTexture.loadFromFile(texture, false, sf::IntRect({0, 0}, {360, 325}))) {
		std::cerr << "failed to load backscreen" << std::endl;
		return; 
	}
	playerTexture.setSmooth(true);
	playerSprite.setTexture(playerTexture);
	playerSprite.scale({0.2f, 0.2f});
	width = playerSprite.getOrigin().x;
	height = playerSprite.getOrigin().y;
}

sf::Vector2f Player::getRate() const {
	return rate;
}

void Player::jump() {
	if (isOnGround) {
		rate.y = -100;
		isOnGround = false;
	}
}

void Player::rotate(bool toLeft, bool toRight) {
	if (toLeft == true && toRight == false) {
		rotateLeft = true;
		rotateRight = false;
	}
	else if (toLeft == false && toRight == true) {
		rotateLeft = false;
		rotateRight = true;
	}
	else {
		rotateLeft = false;
		rotateRight = false;
	}
}	

void Player::update(float time) {
	rate.y += 80 * time;

	if (rotateLeft) {
		rate.x = -150;
	}
       	else if (rotateRight) {
		rate.x = 150;
	} 
	else {
		rate.x = 0;
		//if (std::abs(rate.x) < 1.0f) rate.x = 0;
	}

	sf::Vector2f pos = getPosition();
	pos.x += rate.x * time;
	pos.y += rate.y * time;
	setPosition(pos);
	playerSprite.setPosition(getPosition());
}

sf::FloatRect Player::getBounds() const {
    return playerSprite.getGlobalBounds();
}

void Player::togglePlatform() {
	isOnGround = true;
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(playerSprite, states);
}
