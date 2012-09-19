#include "stdafx.h"
#include "Tracker.h"
#include <iostream>

//std::vector<Particle> m_Particles;
//std::vector<int> m_freeParticles;

void Tracker::Initialise(int reserve)
{
	Pause = false;
	m_Particles.reserve(reserve);
	m_freeParticles.reserve(reserve);
}

int Tracker::AddParticle(sf::Vector2f location, sf::Vector2f velocity, float mass)
{
	int id = -1;

	if(m_freeParticles.size())//if there are any bullets existing
	{
		id = m_freeParticles.back(); //get the id of the last free bullet location
		m_freeParticles.pop_back(); //delete the last free bullet
	}
	else
	{
		id = m_Particles.size(); //id equals amount of bullets existing (+1)
		Particle newParticle;
		m_Particles.push_back(newParticle);//add new bullet
	}

	m_Particles[id].Load(location, mass, id, velocity);
	std::cout<<id<<" Loaded\n";
	return id;
}

void Tracker::GenerateProtoDisk(float mass, sf::Vector2f inputLocation)
{
	int i;
	for (i = 0; i < 50; i++)
	{
		sf::Vector2f location;
		location = inputLocation;
		location.x += std::rand() % 100;
		location.y += std::rand() % 100;
		sf::Vector2f velocity;
		velocity.x = 0;
		velocity.y = 0;
		AddParticle(location, velocity, mass);
	}
}

void Tracker::FreeParticle(int id)
{
	m_Particles[id].Destroy(); //kill the bullet
	m_freeParticles.push_back(id);//add it to free bullet list
	std::cout<<id<<" Destroyed\n";
}

void Tracker::FreeAll()
{
	int count = 0;
	std::vector<Particle>::iterator j;
	for (j = m_Particles.begin(); j != m_Particles.end(); j++)
	{
		FreeParticle(j->ReturnId());
		count++;
	}
	std::cout<<count<<" particles cleared.\n";
}

Particle& Tracker::GetParticle(int id)
{
	return m_Particles[id];
}

void Tracker::IterateParticles(float timeFactor, sf::RenderWindow& renderWindow)
{
	std::vector<Particle>::iterator i;
	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		if ((i->m_active) == true && Pause == false)
		{
			//i->AccelerationFromLinearField(0,0);
			//i->AccelerationFromUniversalField(0,0);
			i->UpdateGeneral(timeFactor);
			i->Draw(renderWindow);
			if (i->ReturnMark() == true)
			{
				FreeParticle(i->ReturnId());
			}

			else
			{
				//sub-iterator for affecting each other
				std::vector<Particle>::iterator j;
				for (j = m_Particles.begin(); j != m_Particles.end(); j++)
				{
					if (j->ReturnId() != i->ReturnId() && (j->m_active) == true)
					{
						i->AccelerationFromRadialField(j->ReturnLocation(), (j->ReturnMass()));

						long double distanceX, distanceY;
						distanceX = ((i->ReturnLocation()).x - (j->ReturnLocation()).x);
						distanceY = ((i->ReturnLocation()).y - (j->ReturnLocation()).y);
						if (((abs(distanceX) < i->radius) == true) && ((abs(distanceY) < i->radius) == true))
						{
							float mass;
							mass = j->ReturnMass();
							i->Merge(j->ReturnVelocity(), mass);
							int id;
							id = (j->ReturnId());
							std::cout<<id<<" Collided with "<<i->ReturnId()<<"\n";
							j->Mark();
						}
						//std::cout<<i->id<<" was accelerated by "<<j->id<<"\n";
					}
				}
			}
		}	
	}
}