#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Padel.h"

class Game
{
public:
    Game();
    void start();
    void update();

private:
    sf::RenderWindow window;
    Ball ball;
    Padel padel_L;
    Padel padel_R;
    sf::Text ScoreText;
    sf::Font ScoreFont;
    void processEvents();
    void render();
    int scoreLeft = 0;
    int scoreRight = 0;
    void checkPoints();
    void initScore();
};

#endif