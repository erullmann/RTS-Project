#pragma once

#include "BodyComponent.h"

BodyComponent::BodyComponent(BaseEntity* parent, float optMuscle, float optRatio, float optAge, float maxAge, float topSpeed, float startFat, float startMuscle){
	_parentEntity = parent;
	_optMuscle = optMuscle;
	_optRatio = optRatio;
	_optAge = optAge;
	_maxAge = maxAge;
	_fat = startFat;
	_muscle = startMuscle;
	_topSpeed= topSpeed;
	_alive = true;
	_age = 10;//just for now, we can change this later
}

void BodyComponent::readMessages(std::vector<msg*>* msgBuffer){
	caloriesLastBurned = 0;

	caloriesLastGained = 0;

	for(std::vector<msg*>::iterator iter = msgBuffer->begin(); iter != msgBuffer->end(); iter++){
		if((*iter)->type == msg::MESSAGETYPE::CALORIECHANGE){

			if((*iter)->change.isGiving){
				caloriesLastGained += (*iter)->change.amount;
			} else {
				caloriesLastBurned += (*iter)->change.amount;
			}
		}
	}
}

void BodyComponent::update(sf::Time frameTime){
	//update muscle
	_muscle -= MUSCLELOSTPERSECPERKG * frameTime.asSeconds() * (_muscle + _fat);//muscle lost is proportional to mass and time
	_muscle += caloriesLastBurned / CALTOMUSCLE;

	//update fat
	_fat -= FATLOSTPERSECPERKG * frameTime.asSeconds() * (_muscle + _fat);//lose some fat from just living
	_fat += (caloriesLastGained - caloriesLastBurned) / CALTOFAT;//lose fat from effort
}

void BodyComponent::postMessages(std::vector<msg*>* msgBuffer){
	//calorie count
	msg* calorieCountMsg = new msg;
	calorieCountMsg->type = msg::MESSAGETYPE::CALORIECOUNT;
	calorieCountMsg->count.amount = _fat * CALTOFAT;
	msgBuffer->push_back(calorieCountMsg);
	
	//stats
	msg* statsMsg = new msg;
	statsMsg->type = msg::MESSAGETYPE::CURRENTSTATS;
	statsMsg->stats.attackSpeed = calculateAttackSpeed();
	statsMsg->stats.moveSpeed = calculateMoveSpeed();
	statsMsg->stats.strength = calculateStrength();
	statsMsg->stats.mass = (_fat + _muscle);
	msgBuffer->push_back(statsMsg);

	//hunger and the rest is responsibility of other components

}

float BodyComponent::calculateAttackSpeed(){
	//generall fitness inverted
	return 1/(((_fat/_muscle)/_optRatio)/2 + abs((_age/_maxAge)-(_optAge/_maxAge))/2);
}

float BodyComponent::calculateMoveSpeed(){
	return (((_fat/_muscle)/_optRatio)*_topSpeed/2 + abs((_age/_maxAge)-(_optAge/_maxAge))*_topSpeed/2);
}

float BodyComponent::calculateStrength(){
	//muscle as percentage of bodyweight times musclemass
	//so beteen two guys of same muscle, the leaner guy wins
	return (_muscle/(_fat + _muscle))*_muscle;
}

COMPONENTTYPE BaseComponent::_type = BODY_COMP;