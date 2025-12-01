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

Player::Player(int posX, int posY)
{
	shape.setSize(sf::Vector2f(10.0f, 10.0f));
	shape.setFillColor(sf::Color::Yellow);
	shape.setPosition(posX, posY);
	speed = 10.0f;
}

void Player::move(int direction) 
{
	shape.move( direction * speed,0);
	if (shape.getPosition().y < 0)
		shape.setPosition(shape.getPosition().y, 0);
	if (shape.getPosition().x + shape.getSize().x > 800)
		shape.setPosition(shape.getPosition().y, 800 - shape.getSize().x);
}

void Player::render(sf::RenderWindow &window)
{
	window.draw(shape);
}

sf::FloatRect Player::getBounds() const
{
	return shape.getGlobalBounds();
}