#pragma once
/*Body.h
	Class that defienes the body and stats of the creature.
	Features
		-Calorie Pool that dicides what and how much the creature can do
		-Fat Pool that adds to calorie pool if nessary
		-Burns calories based on weight
		-gains muscle based on activity.
		*/
#define CALTOMUSCLE 500
#define CALTOFAT 100
#include "BaseEntity.h"
#include "BaseComponent.h"

class Body : public BaseComponent {
public:

	//Constructs the Body class
	//owner is the Entity that owns this object
	//optMuscle is the optimal amount of muscle that the creature should have at it's optimal age
	//optRatio is the optimal ratio of fat to muscle that the creature should maintain
	//optAge is the age that creature is most fit
	//maxAge is the average lifespan of the creatrue
	//startFat is the starting fat
	//startMuscle is the starting muscle
	Body(BaseEntity* owner, float optMuscle, float optRatio, float optAge, float maxAge, float startFat, float startMuscle);
	
	//Check for calorie addition and subtraction
	//count calories burned
	void readMessages(std::vector<msg*>* msgBuffer);

	//update muscle amount, 
	//calculate current stats, 
	//refil calorie pool to minimum from fat or put excess calories into fat
	void update(sf::Time frameTime);

	//post stats, post death mesage if all fat and calories are gone
	void postMessages(std::vector<msg*>* msgBuffer);


private:

	bool _alive;//Body rots over time if dead

	float _age, _optAge, _maxAge;//these are used to calcuate modifiers on the stats of the creature

	float _optMuscle, _optRatio;//these are the optimal stats that the creature tries to aim for

	float _caloriePool; //kCal

	float _fat; //kg

	float _muscle; //kg, total wieght = _muscle + _fat

	void updateMuscle();

	float caloriesLastBurned; //calories burned during the last frame

	float calculateMoveSpeed();

	float calculateAttackSpeed();

	float calculateStrength();

	BaseEntity* _owner;
		
};