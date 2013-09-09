#pragma once
/*BodyComponent.h
	Class that defienes the body and stats of the creature.
	Features
		-Calorie Pool that dicides what and how much the creature can do
		-Fat Pool that adds to calorie pool if nessary
		-Burns calories based on weight
		-gains muscle based on activity.
		*/
#define CALTOMUSCLE 900 //calories to spend to gain a pound of muscle
#define CALTOFAT 500 //calories in one kg of fat
#define MUSCLELOSTPERSECPERKG 0.00016 //10g of muscle lost per minute per kg of the animals weight
#define FATLOSTPERSECPERKG 0.00016 //10g of fat lost per minute per kg of the animals weight



#include "BaseEntity.h"
#include "BaseComponent.h"

class BodyComponent : public BaseComponent {
public:

	//Constructs the BodyComponent class
	//owner is the Entity that owns this object
	//optMuscle is the optimal amount of muscle that the creature should have at it's optimal age
	//optRatio is the optimal ratio of fat to muscle that the creature should maintain
	//optAge is the age that creature is most fit
	//maxAge is the average lifespan of the creatrue
	//topSpeed is the maximum speed of the animal, at the peak of it's life
	//startFat is the starting fat
	//startMuscle is the starting muscle
	BodyComponent(BaseEntity* parent, float optMuscle, float optRatio, float optAge, float maxAge, float topSpeed, float startFat, float startMuscle);
	
	//Check for calorie addition and subtraction
	//count calories burned
	void readMessages(std::vector<msg*>* msgBuffer);

	//update muscle amount, 
	//put excess calories into fat
	void update(sf::Time frameTime);

	//post stats, current calories, post death mesage if all fat and calories are gone
	void postMessages(std::vector<msg*>* msgBuffer);


private:

	bool _alive;//BodyComponent rots over time if dead

	float _age, _optAge, _maxAge;//these are used to calcuate modifiers on the stats of the creature

	float _optMuscle, _optRatio;//these are the optimal stats that the creature tries to aim for

	float _fat; //kg

	float _muscle; //kg, total wieght = _muscle + _fat

	float _topSpeed;

	void updateMuscle();

	float caloriesLastBurned; //calories burned during the last frame

	float caloriesLastGained; //total calories eaten during the last frame

	float calculateMoveSpeed(); //m/s

	float calculateAttackSpeed(); //sec

	float calculateStrength(); //(kg*m/s^2)
		
};