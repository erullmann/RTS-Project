#ifndef CLASS_H_
#define CLASS_H_

#include "stdafx.h"
#include "SFML\Graphics.hpp"

class Particle
{
public:
	bool m_active;

	float radius;

	void UpdateGeneral(float timeFactor); // timeFactor is the amount of time, in secounds, since the last update

	void AccelerationFromLinearField(float fieldStrengthX, float fieldStrengthY); // not affected by distance

	void AccelerationFromRadialField(sf::Vector2f fieldLocation, float fieldMass); // circular, affected by distance

	void AccelerationFromUniversalField(float fieldStrengthX, float fieldStrengthY); // gravity etc...
	
	void Load(sf::Vector2f location, float mass, int id, sf::Vector2f velocity);
	
	void Merge(sf::Vector2f velocity, float mass);

	void Destroy();

	void Draw(sf::RenderWindow& renderWindow);

	sf::Vector2f ReturnLocation();
	
	sf::Vector2f ReturnVelocity();

	float ReturnMass();

	int ReturnId();

	bool ReturnMark();

	void Mark();

private:
	//graphics stuff
	sf::Font _font;

	bool _isLoaded;

	bool _isMarked; //to mark for dystruction

	//physics stuff
	float mass;
	
	int id;

	sf::Vector2f location;

	sf::Vector2f velocity;

	sf::Vector2f acceleration;

	static float gConstant;

	static float aConstant; // the universal constant to ajust speed to an easy to use scale
};
#endif