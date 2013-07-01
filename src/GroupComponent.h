/* file GroupComponent.h
Class providing group member tracking, essentally adds leaders functionality to EntityList
Only keeps track of group members doesnt allow for group planning and coordination
	-If you want central planning/orders use LeaderComponent and FollowerComponent
	-LeaderComponent can plan and issue orders and FollowerComponent can recieve them
One instance of this class per group, all members have a pointer to it
Can chain groups/leaders to create a sort of chain of command
	-LeaderComponent will only issue orders to groups it is leader of
*/
//CONSIDER REMOVING
#pragma once

#include "BaseEntity.h"
#include "EntityList.h"

class GroupComponent {
public:

	GroupComponent();

	~GroupComponent();

	//Sets group leader to newLeader, overriding the old one
	//Pass in NULL to make group leaderless
	//newLeader must already be part of group to be set to leader
	void setLeader(BaseEntity *newLeader);

	//Adds newMember to group
	//does nothing if newMember already in group or newMember = NULL
	void addMember(BaseEntity *newMember);

	//Removes oldMember from group
	void removeMember(BaseEntity *oldMember);

	//returns list of all members
	EntityList *getMembers();

	//returns leader
	BaseEntity *getLeader();

	//returns true if entity is the leader
	bool isLeader(BaseEntity *entity);

	//returns true if entity is a member of the group
	bool isMember(BaseEntity *entity);

	//returns true if the group has a leader
	bool hasLeader();

	//does what it says
	int numberOfMembers();

	//does what it says
	int numberOfFollowers();

private:

	EntityList *_group;

	BaseEntity *_leader;
	
};