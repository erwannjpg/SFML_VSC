#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <list>
#include <SFML/Graphics.hpp>

// -------------------------------------------------------------
// Structure Particle
// -------------------------------------------------------------
struct Particle
{
	float lifetime;
	float timeElapsed;

	sf::CircleShape shape;

	sf::Vector2f direction;
	float speed;

	Particle(float life = 1.f)
		: lifetime(life),
		  timeElapsed(0.f),
		  direction(0.f, 0.f),
		  speed(0.f)
	{
	}
};

// -------------------------------------------------------------
// Structure ParticleSystem
// -------------------------------------------------------------
struct ParticleSystem
{
	std::list<Particle> particles;

	float spawnPeriod;
	float spawnTimer;

	float minLife;
	float maxLife;

	float minSize;
	float maxSize;

	float minSpeed;
	float maxSpeed;

	float frictionCoef;

	sf::Vector2f origin;
	float spawnRadius;

	float systemLifetime;
	float systemTimeElapsed;

	bool isPlaying;
};

// -------------------------------------------------------------
// Fonctions
// -------------------------------------------------------------
ParticleSystem CreateParticleSystem(
	float period,
	float minLife, float maxLife,
	float minSize, float maxSize,
	float minSpeed, float maxSpeed,
	float frictionCoef,
	float systemLifetime,
	sf::Vector2f origin,
	float spawnRadius);

void AddParticleToSystem(ParticleSystem &system, float life);

void UpdateParticleSystem(ParticleSystem &system, float deltaTime);

void PlayParticleSystem(ParticleSystem &system);
bool IsParticleSystemPlaying(const ParticleSystem &system);

void ClearParticleSystem(ParticleSystem &system);
void DrawParticleSystem(ParticleSystem &system, sf::RenderWindow &window);

#endif