#pragma once
/*CaloriePoolComponent.h
 Implements CaloriePool Class
  -Provides a pool of calories or 'energy' that can be withdrawn from by other components of the creature
  -other components can also add to the pool (by eating or whatever)
  -if the calorie pool drops below zero the creature dies (passes message to AI Class)
  -idealy the creature should have a rather large calorie buffer
 */

#include "BaseEntity.h"

class CaloriePool {
public:
	CaloriePool(BaseEntity* owner);

	void update();

	//add a particular amount of calories to the pool
	//-amount: amount of calories to add
	void addCalories(int amount);

	//true if there are enough calories
	//false otherwise
	//use this to check 'non-manditory' calorie needs (and then fail them if they can't be forfilled) then take the calories needed right after;
	//-amount: amount of calories that could be removed
	bool checkCalories(int amount);

	//take an amount of calories from the pool
	//can kill the creature if too many are taken
	//-amount: amount of calories to take
	void takeCalories(int amount);

	//returns current Calorie count
	int currentCalories(); 

private:

	int _pool;

	BaseEntity* _owner;

	void postDeathMsg();
};