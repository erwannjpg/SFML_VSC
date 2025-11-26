#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <list>
#include <SFML/Graphics.hpp>

struct Particle
{
	float lifetime;	   // durée de vie (sec)
	float timeElapsed; // temps écoulé depuis création

	float speed;			// vitesse
	sf::Vector2f direction; // direction normalisée

	sf::CircleShape shape; // forme SFML

	Particle(float life = 1.f)
		: lifetime(life), timeElapsed(0.f), speed(0.f), direction(0.f, 0.f), shape()
	{
	}
};


struct ParticleSystem
{
	std::list<Particle> particles;

	// génération procédurale
	float spawnPeriod; // période de création (sec)
	float spawnTimer;  // chronomètre

	float minLife, maxLife; // durée de vie min / max des particules

	// rendu / spawn
	sf::Vector2f origin;  // origine (centre d'émission)
	float spawnRadius;	  // rayon de spawn
	float particleRadius; // taille de base (mais on rend aléatoire ensuite)

	// bonus : vitesse / friction
	float minSpeed, maxSpeed;
	float frictionCoef;

	// durée et état du système
	float systemLifetime;
	float systemTimeElapsed;
	bool isPlaying;
};

ParticleSystem CreateParticleSystem(
	float period,
	float minLife, float maxLife,
	sf::Vector2f origin = sf::Vector2f(400.f, 300.f),
	float spawnRadius = 100.f,
	float particleRadius = 4.f,
	float minSpeed = 50.f, float maxSpeed = 150.f,
	float frictionCoef = 0.2f,
	float systemLifetime = 2.0f);

void AddParticleToSystem(ParticleSystem &system, float life);
void Explode(ParticleSystem &system);

void UpdateParticleSystem(ParticleSystem &system, float deltaTime);
void ClearParticleSystem(ParticleSystem &system);

void PlayParticleSystem(ParticleSystem &system);
bool IsParticleSystemPlaying(const ParticleSystem &system);

void DrawParticleSystem(ParticleSystem &system, sf::RenderWindow &window);
void ClearParticleSystem(ParticleSystem &system);
void DrawParticleSystem(ParticleSystem &system, sf::RenderWindow &window);
void Explode(ParticleSystem &system);
#endif // PARTICLE_SYSTEM_H