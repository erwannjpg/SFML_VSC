#include "Game.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

Game::Game() : ball(), padel_L(100, 240), padel_R(700, 240) // Liste d'initialisation
{
}

void Game::start()
{

    window.create(sf::VideoMode(800, 600), "Pong Game");
    window.setFramerateLimit(60);
    initScore();
    sf::Font ScoreFont;
    sf::Text ScoreText;
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::render()
{
    window.clear();
    ball.render(window);
    padel_L.render(window);
    padel_R.render(window);
    window.draw(ScoreText);
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

            if (event.key.code == sf::Keyboard::Z)
                padel_L.move(-1);
            if (event.key.code == sf::Keyboard::S)
                padel_L.move(1);
            if (event.key.code == sf::Keyboard::Up)
                padel_R.move(-1);
            if (event.key.code == sf::Keyboard::Down)
                padel_R.move(1);
        }
    }
}
void Game::update()
{
    ball.update();
    if (ball.getBounds().intersects(padel_L.getBounds()) || ball.getBounds().intersects(padel_R.getBounds()))
        ball.reverseX();
    checkPoints();
}

void Game::checkPoints()
{
    if (ball.getPosition().x <= 0)
    {
        scoreRight++;
        ball.resetPosition(400.0f, 300.0f);
    }
    if (ball.getPosition().x >= 790)
    {
        scoreLeft++;
        ball.resetPosition(400.0f, 300.0f);
    }
    ScoreText.setString("Score: " + std::to_string(scoreLeft) + " - " + std::to_string(scoreRight));
}

void Game::initScore()
{
    ScoreFont.loadFromFile("assets/RETROTECH.ttf");
    ScoreText.setFont(ScoreFont);
    ScoreText.setCharacterSize(24);
    ScoreText.setFillColor(sf::Color::White);
    ScoreText.setPosition(325, 10);
    ScoreText.setString("Score: 0 - 0");
}