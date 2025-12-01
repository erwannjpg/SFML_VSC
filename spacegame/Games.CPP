#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <windows.h>
#include <cstdlib>
#include <cmath>
#include "player.h"
#include "Games.h"
Game::Game() : playermain(400, 540) 
{
}

void Game::start()
{

	window.create(sf::VideoMode(800, 600), "Spacegame");
	window.setFramerateLimit(60);
	sf::Font ScoreFont;
	sf::Text ScoreText;
	while (window.isOpen())
	{
		processEvents();
		render();
	}
}

void Game::render()
{
	window.clear();
	playermain.render(window);
	window.display();
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				window.close();

			if (event.key.code == sf::Keyboard::Q)
				playermain.move(-1);
			if (event.key.code == sf::Keyboard::D)
				playermain.move(1);
	}
}
}
