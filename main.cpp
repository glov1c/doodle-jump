#include "doodlejump.h"
#include "platform.h"
#include "player.h"

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

int main() {
	Game game("resources/background.png");
	game.run();
	return 0;
}	
