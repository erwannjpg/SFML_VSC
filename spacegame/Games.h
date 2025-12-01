#ifndef GAMES_H
#define GAMES_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
public:
	Game();
	void start();
private:
	sf::RenderWindow window;
	Player playermain;
	void processEvents();
	void render();
};

#endif