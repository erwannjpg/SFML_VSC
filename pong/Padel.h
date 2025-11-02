#ifndef PADEL_H
#define PADEL_H

#include <SFML/Graphics.hpp>

class Padel
{
public:
	Padel(int, int);
	void render(sf::RenderWindow &window);
	void move(int direction);
	sf::FloatRect getBounds() const;

private:
	sf::RectangleShape shape;
	float speed;
};

#endif