#include "ParticleSystem.h"
#include <cstdlib>
#include <cmath>

static float Rand01()
{
	return float(rand()) / float(RAND_MAX);
}

static constexpr float PI = 3.14159265f;
ParticleSystem CreateParticleSystem(
	float period,
	float minLife, float maxLife,
	sf::Vector2f origin,
	float spawnRadius,
	float particleRadius,
	float minSpeed, float maxSpeed,
	float frictionCoef,
	float systemLifetime)
{
	ParticleSystem ps;
	ps.spawnPeriod = period;
	ps.spawnTimer = 0.f;

	ps.minLife = minLife;
	ps.maxLife = maxLife;

	ps.origin = origin;
	ps.spawnRadius = spawnRadius;
	ps.particleRadius = particleRadius;

	ps.minSpeed = minSpeed;
	ps.maxSpeed = maxSpeed;
	ps.frictionCoef = frictionCoef;

	ps.systemLifetime = systemLifetime;
	ps.systemTimeElapsed = 0.f;
	ps.isPlaying = false;

	return ps;
}


void AddParticleToSystem(ParticleSystem &system, float life)
{
	Particle p(life);

	// Taille aléatoire entre particleRadius*0.5 et particleRadius*2.0
	float minSz = system.particleRadius * 0.5f;
	float maxSz = system.particleRadius * 4.0f;
	float radius = minSz + (maxSz - minSz) * Rand01();
	p.shape.setRadius(radius);
	p.shape.setOrigin(radius, radius);

	// Position aléatoire dans un disque autour de origin
	float angle = 2.f * PI * Rand01();
	float distance = system.spawnRadius * std::sqrt(Rand01());
	float x = system.origin.x + std::cos(angle) * distance;
	float y = system.origin.y + std::sin(angle) * distance;
	p.shape.setPosition(x, y);

	// Direction vers l'extérieur (basé sur l'angle)
	p.direction = sf::Vector2f(std::cos(angle), std::sin(angle));

	// Vitesse aléatoire
	p.speed = system.minSpeed + (system.maxSpeed - system.minSpeed) * Rand01();

	// Couleur aléatoire (plein)
	p.shape.setFillColor(sf::Color(
		static_cast<sf::Uint8>(128 + rand() % 128),
		static_cast<sf::Uint8>(128 + rand() % 128),
		static_cast<sf::Uint8>(128 + rand() % 128),
		255));

	system.particles.push_back(p);
}

void Explode(ParticleSystem &system)
{
	const int explosionCount = 150;
	for (int i = 0; i < explosionCount; ++i)
	{
		float life = system.minLife + (system.maxLife - system.minLife) * Rand01();
		AddParticleToSystem(system, life);
	}
}


void UpdateParticleSystem(ParticleSystem &system, float deltaTime)
{
	if (!system.isPlaying)
		return;

	// Durée du système
	system.systemTimeElapsed += deltaTime;
	if (system.systemTimeElapsed >= system.systemLifetime)
	{
		system.isPlaying = false;
		ClearParticleSystem(system);
	}
	// Spawn procédural : incrémente timer et spawn si nécessaire
	system.spawnTimer += deltaTime;
	while (system.spawnTimer >= system.spawnPeriod)
	{
		system.spawnTimer -= system.spawnPeriod;
		float life = system.minLife + (system.maxLife - system.minLife) * Rand01();
		AddParticleToSystem(system, life);
	}
	

	// Update particules
	for (auto it = system.particles.begin(); it != system.particles.end();)
	{
		Particle &p = *it;
		p.timeElapsed += deltaTime;

		// Suppression si morte
		if (p.timeElapsed >= p.lifetime)
		{
			it = system.particles.erase(it);
			continue;
		}

		// Déplacement : position += dir * speed * dt
		sf::Vector2f pos = p.shape.getPosition();
		pos += p.direction * p.speed * deltaTime;
		p.shape.setPosition(pos);

		// Diminution de la vitesse : speed = max(0, speed - speed*speed*friction*dt)
		p.speed -= p.speed * p.speed * system.frictionCoef * deltaTime;
		if (p.speed < 0.f)
			p.speed = 0.f;

		// Animation d'échelle : scale = sin(PI * time / lifetime)
		float t = p.timeElapsed;
		float life = p.lifetime;
		float scale = std::sin(PI * (t / life));
		if (scale < 0.f)
			scale = 0.f;
		p.shape.setScale(scale, scale);

		// Fade-out alpha pour plus de propreté (optionnel)
		float lifeRatio = 1.f - (p.timeElapsed / p.lifetime);
		sf::Color c = p.shape.getFillColor();
		c.a = static_cast<sf::Uint8>(255 * lifeRatio);
		p.shape.setFillColor(c);

		++it;
	}
}


void ClearParticleSystem(ParticleSystem &system)
{
	system.particles.clear();
	system.spawnTimer = 0.f;
	system.systemTimeElapsed = 0.f;
	system.isPlaying = false;
}

void PlayParticleSystem(ParticleSystem &system)
{
	system.isPlaying = true;
	system.systemTimeElapsed = 0.f;
	system.spawnTimer = 0.f;
}

bool IsParticleSystemPlaying(const ParticleSystem &system)
{
	return system.isPlaying;
}

void DrawParticleSystem(ParticleSystem &system, sf::RenderWindow &window)
{
	for (auto &p : system.particles)
		window.draw(p.shape);
}