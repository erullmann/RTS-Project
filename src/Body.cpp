#pragma once

#include "Body.h"

Body::Body(BaseEntity* owner, float optMuscle, float optRatio, float optAge, float maxAge, float startFat, float startMuscle){
	_owner = owner;
	_optMuscle = optMuscle;
	_optRatio = optRatio;
	_optAge = optAge;
	_maxAge = maxAge;
	_fat = startFat;
	_muscle = startMuscle;
}

void Body::readMessages(std::vector<msg*>* msgBuffer){
	caloriesLastBurned = 0;

	for(std::vector<msg*>::iterator iter = msgBuffer->begin(); iter != msgBuffer->end(); iter++){
		if((*iter)->type == msg::MESSAGETYPE::CALORIECHANGE){
			_caloriePool += (*iter)->change.amount;

			if(!(*iter)->change.isGiving){
				caloriesLastBurned += (*iter)->change.amount;
			}
		}
	}
}

void Body::update(sf::Time frameTime){
	updateMuscle();


}