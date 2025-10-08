#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
enum GameState {
    waiting,
    timing,
    finished,
};
bool isKeyPressed()
{
if (_kbhit())
{
while (_kbhit()) 
{
_getch();
}
return true;
}
return false; 
}
std::string getAppPath() {
char cExeFilePath[256];
GetModuleFileNameA(NULL, cExeFilePath, 256);
std::string exeFilePath = cExeFilePath;
int exeNamePos = exeFilePath.find_last_of("\\/");
std::string appPath = exeFilePath.substr(0, exeNamePos + 1);
return appPath;
}
const float PI = 3.14159265358979323846f;
const float turnPerSecond = 0.1f; 
std::string getRAssetPath() {
    return getAppPath() + "Asset\\";
}

int main() {
        srand(time(NULL));
    float minTime = 1.0f;
    float maxTime = 10.0f;
    float winInterval = 1.0f; 
    bool hasloose = false;
    int i = 0;
    float timeToFind = 0.0f;
        timeToFind = ((float)rand() / (float)RAND_MAX) * (maxTime - minTime) + minTime;
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "ChronoSpacer");
    // Initialise everything below
    // Game loop
    sf::Font font;
sf::Texture texture;
sf::Sprite sprite;
sf::Clock clock;
sf::Vector2u texturesize = texture.getSize();
sf::Event::KeyReleased ;
sf::Keyboard::Space ;
std::string message = "1. Essaie d'appuyer  sur la barre espace apres exactement " + std::to_string(timeToFind) + " secondes !";
std::string message2 = "2. Appuie sur une touche pour demarrer le chrono.";
sf::Text text(message, font, 30);
        text.setFillColor(sf::Color::Magenta);
    text.setPosition(210, 250);
    sf::Text text2(message2, font, 30);
    text2.setFillColor(sf::Color::Magenta);
    text2.setPosition(230, 100);
GameState state =  waiting;
if (!font.loadFromFile(getRAssetPath() + "Tokyo.ttf")) {
}
if (!texture.loadFromFile(getRAssetPath() + "Oiseau.jpg")) {
}
sprite.setTexture(texture);

clock_t start = 0;
clock_t end = 0;
window.clear();
     float deltaTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    float deltaAngle = deltaTime * PI * 2.0f * turnPerSecond;
    sf::CircleShape circle; 
    window.draw(sprite);
    sprite.setOrigin(texturesize.x / 2.f, texturesize.y / 2.f);
    sprite.setPosition(400, 300);
    sprite.setScale(0.1f, 0.1f);
    sprite.rotate(deltaAngle*50.f);
    sf::Text title("ChronoSpacer" , font, 80);
    title.setFillColor(sf::Color::Magenta);
    title.setPosition(240, 20);
    window.draw(title);
while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        // Process any input event here
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
    switch(state) 
    {
    case waiting:
        {
            window.clear();
        window.draw(sprite);
          sprite.rotate(deltaAngle*30.f);
        window.draw(title);
        sf::Text text(message, font, 30);
        text.setFillColor(sf::Color::Magenta);
        text.setPosition(15, 150);
        sf::Text text2(message2, font, 30);
        text2.setFillColor(sf::Color::Magenta);
        text2.setPosition(15, 200);
        window.draw(text);
        window.draw(text2);
        // Check for space key release event
        if ( event.key.code )
        {
            state = timing;
            start = std::clock();
        }
        }
        break;
    case timing:
        {
        window.clear();
        window.draw(sprite);
          sprite.rotate(deltaAngle*30.f);
        window.draw(title);
        message = "3. Appuie sur une touche quand tu penses que le temps est ecoule !";
        sf::Text text(message, font, 30);
        text.setFillColor(sf::Color::Magenta);
        text.setPosition(15, 150); 
        window.draw(text);
        // Check for space key release event
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
            state = finished;
            end = std::clock();
        }
        }
        break;
    case finished:
        {
            window.clear();
        window.draw(sprite);
          sprite.rotate(deltaAngle*30.f);
        window.draw(title);
         float elapsed = float(end - start) / CLOCKS_PER_SEC;
         float diff = elapsed - timeToFind;
         std::string diffMessage = "Difference avec le temps cible : " + std::to_string(diff) + " secondes.";
         sf::Text text2(diffMessage, font, 25);
        text2.setFillColor(sf::Color::Magenta);
        text2.setPosition(200, 200);
        window.draw(text2);
         std::string message;
         if (abs(diff) <= winInterval) {
            message = "Bravo, tu as gagne !";
            winInterval *= 0.9f; 
            
        } else {
            message = "Dommage, tu as perdu !";
            hasloose = true;
        }
        sf::Text text(message, font, 30);
        text.setFillColor(sf::Color::Magenta);
        text.setPosition(300, 150);
        window.draw(text);
        }
        break;
    default:
        {
        }
        break;
    }
    window.display();    
}
return 0;
}
