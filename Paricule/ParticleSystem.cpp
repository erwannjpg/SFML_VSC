#include "ParticleSystem.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>

ParticleSystem CreateParticleSystem(
	float period,
	float minLife, float maxLife,
	float minSize, float maxSize,
	float minSpeed, float maxSpeed,
	float frictionCoef,
	float systemLifetime,
	sf::Vector2f origin,
	float spawnRadius)
{
	ParticleSystem ps;

	ps.spawnPeriod = period;
	ps.spawnTimer = 0.f;

	ps.minLife = minLife;
	ps.maxLife = maxLife;

	ps.minSize = minSize;
	ps.maxSize = maxSize;

	ps.minSpeed = minSpeed;
	ps.maxSpeed = maxSpeed;

	ps.frictionCoef = frictionCoef;

	ps.origin = origin;
	ps.spawnRadius = spawnRadius;

	ps.systemLifetime = systemLifetime;
	ps.systemTimeElapsed = 0.f;
	ps.isPlaying = false;

	return ps;
}

static float Rand01()
{
	return float(rand()) / float(RAND_MAX);
}

void AddParticleToSystem(ParticleSystem &system, float life)
{
	Particle p(life);

	float radius = system.minSize + (system.maxSize - system.minSize) * (float(rand()) / RAND_MAX);
	p.shape.setRadius(radius);
	p.shape.setOrigin(radius, radius);

	float angle = 2.f * 3.1415926f * (float(rand()) / RAND_MAX);
	float dist = system.spawnRadius * sqrt((float(rand()) / RAND_MAX));

	float x = system.origin.x + cos(angle) * dist;
	float y = system.origin.y + sin(angle) * dist;
	p.shape.setPosition(x, y);

	p.direction = sf::Vector2f(cos(angle), sin(angle));

	p.speed = system.minSpeed + (system.maxSpeed - system.minSpeed) * (float(rand()) / RAND_MAX);
	p.speed = 200 + rand() % 600; // vitesse plus grande
	p.shape.setFillColor(sf::Color(
		rand() % 255,
		rand() % 255,
		rand() % 255));

	system.particles.push_back(p);
}
void UpdateParticleSystem(ParticleSystem &system, float deltaTime)
{
	if (!system.isPlaying)
		return;

	// Durée du système
	system.systemTimeElapsed += deltaTime;
	if (system.systemTimeElapsed >= system.systemLifetime)
		system.isPlaying = false;

	// Spawn automatique
	system.spawnTimer += deltaTime;
	while (system.spawnTimer >= system.spawnPeriod)
	{
		system.spawnTimer -= system.spawnPeriod;

		float life = system.minLife + (system.maxLife - system.minLife) * Rand01();
		AddParticleToSystem(system, life);
	}

	// Update de chaque particule
	for (auto it = system.particles.begin(); it != system.particles.end();)
	{
		Particle &p = *it;

		p.timeElapsed += deltaTime;
		if (p.timeElapsed >= p.lifetime)
		{
			it = system.particles.erase(it);
			continue;
		}

		// Déplacement
		sf::Vector2f pos = p.shape.getPosition();
		pos += p.direction * p.speed * deltaTime;
		p.shape.setPosition(pos);
		float frictionCoef = 0.15f;
		// Friction
		p.speed -= p.speed * p.speed * system.frictionCoef * deltaTime;
		if (p.speed < 0.f)
			p.speed = 0.f;

		++it;
	}
}

void PlayParticleSystem(ParticleSystem &system)
{
	system.isPlaying = true;
	system.systemTimeElapsed = 0.f;
}

bool IsParticleSystemPlaying(const ParticleSystem &system)
{
	return system.isPlaying;
}

void ClearParticleSystem(ParticleSystem &system)
{
	system.particles.clear();
}

void DrawParticleSystem(ParticleSystem &system, sf::RenderWindow &window)
{
	for (auto &p : system.particles)
		window.draw(p.shape);
}
void Explode(ParticleSystem &system)
{
	// On spawn brutalement beaucoup de particules d’un coup
	const int explosionCount = 200;

	for (int i = 0; i < explosionCount; i++)
	{
		float life = system.minLife + (system.maxLife - system.minLife) * Rand01();
		Particle p(life);

		// Taille
		float radius = system.minSize + (system.maxSize - system.minSize) * Rand01();
		p.shape.setRadius(radius);
		p.shape.setOrigin(radius, radius);

		// Direction totalement aléatoire
		float angle = Rand01() * 2.f * 3.1415926f;
		p.direction = sf::Vector2f(cos(angle), sin(angle));

		// Position = centre de l’explosion
		p.shape.setPosition(system.origin);

		// VITESSE ÉLEVÉE POUR UN GROS BOOM
		p.speed = 300.f + Rand01() * 900.f;

		// Couleur vive
		p.shape.setFillColor(sf::Color(
			rand() % 255,
			rand() % 255,
			rand() % 255));

		system.particles.push_back(p);
	}
}