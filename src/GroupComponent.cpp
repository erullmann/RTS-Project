#pragma once

#include "GroupComponent.h"

GroupComponent::GroupComponent(){
	_group = new EntityList;
	_leader = NULL;
}

GroupComponent::~GroupComponent(){
	_group->~EntityList();
}

void GroupComponent::setLeader(BaseEntity *newLeader){
	_leader = newLeader;
}

void GroupComponent::addMember(BaseEntity *newMember){
	if (isMember(newMember) || newMember == NULL){
		//don't add to group
	} else {
		_group->pushBack(newMember);
	}
}

void GroupComponent::removeMember(BaseEntity *oldMember){
	if (isLeader(oldMember)){
		setLeader(NULL);
	}
	_group->removeEntity(oldMember);
}

EntityList* GroupComponent::getMembers(){
	return _group;
}

BaseEntity* GroupComponent::getLeader(){
	return _leader;
}

bool GroupComponent::isLeader(BaseEntity *entity){
	return entity == _leader;
}

bool GroupComponent::isMember(BaseEntity *entity){
	BaseEntity *ittr = _group->iterateEntites();

	while (ittr != NULL){
		if (ittr = entity){
			_group->resetIterator();
			return true;
		}
		else
			ittr = _group->iterateEntites();
	}

	return false;
}

bool GroupComponent::hasLeader(){
	return _leader != NULL;
}

int GroupComponent::numberOfMembers(){
	return _group->length();
}

int GroupComponent::numberOfFollowers(){
	if (hasLeader())
		return _group->length();
	else
		return _group->length() - 1;
}
