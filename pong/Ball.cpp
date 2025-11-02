#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Ball::Ball()
{
	std::cout << "Ball constructor called" << std::endl;
	shape.setRadius(10.0f);
	shape.setFillColor(sf::Color::White);
	shape.setPosition(400.0f, 300.0f);

	speedX = 2.0f;
	speedY = 2.0f;
}

void Ball::render(sf::RenderWindow &window)
{
	window.draw(shape);
}

void Ball::update()
{
	shape.move(speedX, speedY);
	if (shape.getPosition().x <= 0 || shape.getPosition().x >= 790)
			reverseX();
	if (shape.getPosition().y <= 0 || shape.getPosition().y >= 590)
		reverseY();
}

Ball::reverseX()
{
	if (speedX < 10.0f && speedX > -10.0f)
		return speedX = -(speedX) * 1.1f;
	else
		return speedX = -speedX;
}

Ball::reverseY()
{
	return speedY = -speedY;
}

sf::FloatRect Ball::getBounds() const
{
	return shape.getGlobalBounds();
}

sf::Vector2f Ball::getPosition() const
{
	return shape.getPosition();
}

void Ball::resetPosition(float x, float y)
{
	shape.setPosition(x, y);
	speedX = (speedX > 0) ? 2.0f : -2.0f;
}