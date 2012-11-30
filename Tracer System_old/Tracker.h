#include "stdafx.h"
#include "Particle.h"
#include <vector>

class Tracker
{
public:

	void Initialise(int reserve);

	int AddParticle(sf::Vector2f location, sf::Vector2f velocity, float mass);

	void GenerateProtoDisk(float mass, sf::Vector2f location);

	void FreeParticle(int id);

	void FreeAll();

	Particle& GetParticle(int id);

	void IterateParticles(float timeFactor, sf::RenderWindow& renderWindow);

	std::vector<Particle> m_Particles;

	std::vector<int> m_freeParticles;

	bool Pause;
};