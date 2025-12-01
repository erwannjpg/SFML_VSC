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
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Padel::Padel(int posX, int posY)
{
	shape.setSize(sf::Vector2f(10.0f, 100.0f));
	shape.setFillColor(sf::Color::White);
	shape.setPosition(posX, posY);
	speed = 10.0f;
}

void Padel::move(int direction)
{
	shape.move(0, direction * speed);
	if (shape.getPosition().y < 0)
		shape.setPosition(shape.getPosition().x, 0);
	if (shape.getPosition().y + shape.getSize().y > 600)
		shape.setPosition(shape.getPosition().x, 600 - shape.getSize().y);
}

void Padel::render(sf::RenderWindow &window)
{
	window.draw(shape);
}

sf::FloatRect Padel::getBounds() const
{
	return shape.getGlobalBounds();
}