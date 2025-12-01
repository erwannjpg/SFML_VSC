#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#ifdef _WIN32
#include <windows.h> // pour system("pause") si besoin
#endif

#include "ParticleSystem.h"
int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Feu d'artifice - Exo complet");
	window.setFramerateLimit(60);

	std::list<ParticleSystem> fireworks;
	sf::Clock clock;
	float spawnTimer = 0.f;
	const float spawnPeriod = 1.5f; // une explosion toutes les 1.5s

	while (window.isOpen())
	{
		// events
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		float dt = clock.restart().asSeconds();
		spawnTimer += dt;

		// spawn périodique : créer un système et l'exploser
		if (spawnTimer >= spawnPeriod)
		{
			spawnTimer = 0.f;

			// position aléatoire dans la zone haute
			sf::Vector2f pos(
				100.f + static_cast<float>(rand() % 800),
				80.f + static_cast<float>(rand() % 240));

			ParticleSystem ps = CreateParticleSystem(
				0.01f,		  // spawnPeriod (non utilisé pour explosion instant)
				0.8f, 1.f,	  // minLife, maxLife
				pos,		  // origin
				100.f,		  // spawnRadius (petit)
				5.f,		  // particleRadius (base)
				100.f, 300.f, // minSpeed, maxSpeed (rapide pour grande portée)
				0.12f,		  // frictionCoef (léger)
				5.f		  // systemLifetime
			);

			PlayParticleSystem(ps);
			Explode(ps); // explosion massive instantanée
			fireworks.push_back(ps);
		}

		// update systems and clean finished ones
		for (auto it = fireworks.begin(); it != fireworks.end();)
		{
			UpdateParticleSystem(*it, dt);

			if (!IsParticleSystemPlaying(*it) && it->particles.empty())
				it = fireworks.erase(it);
			else
				++it;
		}

		// draw
		window.clear(sf::Color::Black);
		for (auto &ps : fireworks)
			DrawParticleSystem(ps, window);
		window.display();
	}

	return 0;
}
