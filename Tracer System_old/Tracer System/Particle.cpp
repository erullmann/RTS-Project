#include "stdafx.h"
#include "Particle.h"
#include <math.h>
#include <iostream>

float Particle::gConstant = 1.0;
float Particle::aConstant = 1.0;

bool m_active = false;
int id = -1;
float radius =0;

void Particle::UpdateGeneral(float timeFactor) // timeFactor is the amount of time, in secounds, since the last frame update
	{
		if (m_active == true)
		{
			//update velocity
			velocity += (acceleration * timeFactor);
			//velocityX += (accelerationX * timeFactor);
			//velocityY += (accelerationY * timeFactor);
			
			//update location
			location += (velocity * aConstant);
			acceleration.x = 0;
			acceleration.y = 0;
			//locationX += (velocityX * aConstant);
			//locationY += (velocityY * aConstant);
		}
			
			//std::cout<<id<<" particle is at "<<locationX<<", "<<locationY<<"\n";
	}

void Particle::AccelerationFromLinearField(float fieldStrengthX, float fieldStrengthY)
	{
			//accelerationX -= (fieldStrengthX);
			//accelerationY -= (fieldStrengthY);
	}

void Particle::AccelerationFromRadialField(sf::Vector2f fieldLocation, float fieldMass)
	{
			//find distance away from field orign
			sf::Vector2f delta;
			delta.x = fieldLocation.x - location.x;
			delta.y = fieldLocation.y - location.y;
			float distance;
			distance = ((delta).x)*((delta).x) + ((delta).y)*((delta).y);

			//float distanceX = locationFieldX-locationX;
			//float distanceY = locationFieldY-locationY;
			float heading;

			//distance = sqrt((distanceY)*(distanceY) + (distanceX)*(distanceX));
			heading = atan2((delta).y, (delta).x);

			//apply acceleration
			float totalAcceleration;
			totalAcceleration = gConstant * (fieldMass) / (distance);
			
			acceleration.x += (cos(heading) * totalAcceleration);
			acceleration.y += (sin(heading) * totalAcceleration);

			//std::cout<<id<<" particle is being accelerated by "<<totalAcceleration<<"\n";
			//std::cout<<id<<" at heading "<<heading<<"\n";
	}

void Particle::AccelerationFromUniversalField(float fieldStrengthX, float fieldStrengthY) // this seems repeditive but allows use to make a general field without having to test for collisions with a field
	{
			//accelerationX -= (fieldStrengthX);
			//accelerationY -= (fieldStrengthY);
	}

void Particle::Load(sf::Vector2f inputLocation, float inputMass, int idIN, sf::Vector2f inputVelocity)
	{
		location = inputLocation;
		float thousand = 500;
		velocity.x = (inputVelocity.x/thousand);
		velocity.y = (inputVelocity.y/thousand);
		acceleration.x = 0;
		acceleration.y = 0;
		mass = inputMass;
		m_active = true;
		id = idIN;
		radius = (log(mass))/2;
		_isMarked = false;
		//std::cout<<"Particle loaded at "<<location.x<<", "<<location.y<<"\n";
	}
void Particle::Merge(sf::Vector2f inputVelocity, float inputMass)
{
	mass += inputMass;
	//velocity.x += inputVelocity.x/mass;
	//velocity.y += inputVelocity.y/mass;
}

void Particle::Destroy()
	{
		_isLoaded = false;
		velocity.x = 0;
		velocity.y = 0;
		acceleration.x = 0;
		acceleration.y = 0;
		m_active = false;
		radius = 0;
		_isMarked = false;
	}

void Particle::Draw(sf::RenderWindow& renderWindow)
	{
			if(m_active = true)
			{	
				bool negative = false;
				sf::CircleShape Circle;
				if (mass < 0)
				{
					negative = true;
				}
				radius = (log(abs(mass)))/2;
				Circle.SetPosition(location.x, location.y);
				Circle.SetRadius(radius);
				if (negative == true)
					Circle.SetFillColor(sf::Color(0, 0, 255, 255));
				else
					Circle.SetFillColor(sf::Color(255, 0, 0, 255));
				renderWindow.Draw(Circle);
			}
	}

sf::Vector2f Particle::ReturnLocation()
{
	return location;
}

sf::Vector2f Particle::ReturnVelocity()
{
	return velocity;
}


float Particle::ReturnMass()
{
	return mass;
}

int Particle::ReturnId()
{
	return id;
}

bool Particle::ReturnMark()
{
	return _isMarked;
}

void Particle::Mark()
{
	_isMarked = !_isMarked;
}