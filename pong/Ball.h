#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball
{
public:
	Ball();
	void update();
	void render(sf::RenderWindow &window);
	reverseX();
	reverseY();
	// void setPosition(float x, float y) { shape.setPosition(x, y); }
	sf::FloatRect getBounds() const;
	sf::Vector2f getPosition() const;
	void resetPosition(float x, float y);

private:
	sf::CircleShape shape;
	float speedX;
	float speedY;
};

#endif