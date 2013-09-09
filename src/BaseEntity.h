/////////////////////
//BaseObject 
//The base class for all ingame objects
/////////////////////
#pragma once

#include "SFML\Graphics.hpp"
#include "Types.h"
#include "BaseComponent.h"
#include "DrawComponent.h"
#include "Message.h"

class BaseEntity
{
public:

	//calls update for all the contents of updateBuffer
	//-frameTime: time since last frame, useful for entities that do actions periodicly
	void update(sf::Time frameTime); 

	//draws object on screen based on info in the msg buffer
	void draw(); 

	//dystroys the unit, and all child components
	void destroy(); 

	//post a message to this entity (usually from anouther enemy for attacks and stuff)
	//-message: message to be posted
	void postMessage(msg* message);

	//returns a pointer to the message buffer
	std::vector<msg*>* getMessageBuffer();

	//returns the type of the entity (see entitytypes.h for full list)
	ENTITYTYPE returnType();

	//return position of entity 
	sf::Vector2i returnPosition();

	//dumps the old update buffer and makes a new one, use with caution, 
	//dosn't delete old components, use getBuffer to get and delete them as nessary
	//remember to delete newBuffer after calling this to avoid memory leaks, this is a copy operation
	//-newBuffer: the contents of the new buffer
	void alterComponentList(std::vector<BaseComponent*> newBuffer); 

	//returns the contents of the update buffer
	std::vector<BaseComponent*>* getComponentList();

private:

	//clears the message buffer (use every frame)
	void clearMsgBuffer();

	std::vector<BaseComponent*> _updateBuffer;

	std::vector<msg*> _msgBuffer;

	DrawComponent* _drawComponent;

	ENTITYTYPE _type;
};