#ifndef Player_H
#define Player_H

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(int, int);
	void render(sf::RenderWindow &window);
	void move(int direction);
	sf::FloatRect getBounds() const;

private:
	sf::RectangleShape shape;
	float speed;
};
#endif