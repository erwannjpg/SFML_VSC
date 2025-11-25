#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "ParticleSystem.h"

extern void Explode(ParticleSystem &system); // Déclaration pour utiliser la fonction

int main()
{
	srand((unsigned)time(nullptr));

	sf::RenderWindow window(sf::VideoMode(800, 600), "Feu d'artifice");
	window.setFramerateLimit(60);

	// Liste de systèmes de particules (plusieurs explosions)
	std::vector<ParticleSystem> fireworks;

	sf::Clock clock;

	// TIMER POUR DÉCLENCHER DES EXPLOSIONS
	float explosionTimer = 0.f;
	float explosionDelay = 1.5f; // Une explosion toutes les 1.5 sec (à ajuster)

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		float dt = clock.restart().asSeconds();
		explosionTimer += dt;
		if (explosionTimer >= explosionDelay)
		{
			explosionTimer = 0.f;

			// Création d'un système à position aléatoire
			ParticleSystem ps = CreateParticleSystem(
				0.1f,		  // période (pas utilisé ici)
				1.f, 2.f,	  // vie des particules
				2.f, 6.f,	  // taille min/max
				100.f, 300.f, // speed min/max
				2.5f,		  // friction
				3.f,		  // durée du système
				sf::Vector2f(rand() % 800, rand() % 600),
				0.f // spawnRadius (inutile pour explosion)
			);

			PlayParticleSystem(ps);

			// 💥 ON LANCE L'EXPLOSION DIRECTEMENT
			Explode(ps);

			fireworks.push_back(ps);
		}
		// ------------------------------

		// ------------------------------
		// UPDATE DES SYSTÈMES
		// ------------------------------
		for (auto &fw : fireworks)
			UpdateParticleSystem(fw, dt);

		// ------------------------------
		// DRAW
		// ------------------------------
		window.clear(sf::Color::Black);

		for (auto &fw : fireworks)
			DrawParticleSystem(fw, window);

		window.display();
	}

	return 0;
}
