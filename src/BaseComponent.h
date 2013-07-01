#pragma once
/*BaseComponent.h
 Defines the basic API that all Components (except draw components) need to interact with BaseEntity
 Also holds small details like the Component Type
*/

#include "SFML\System.hpp"
#include "Message.h"
#include "Types.h"
#include <vector>

class BaseComponent {
public:

	//almost all the below should be replaced by inheritors
	
	BaseComponent();

	//reads the message buffer given to it and stores the info it needs
	// -msgBuffer: the messages to be read
	virtual void getMessages(std::vector<msg*>* msgBuffer);

	//update the component (update position, health, whatever)
	// -frameTime: the time since the last frame
	virtual void update(sf::Time frameTime);

	//post messages to a given message buffer
	// -msgBuffer: the place where the messages go
	virtual void postMessages(std::vector<msg*>* msgBuffer);

	virtual void destroy();

	//returns the entity type that this component is... (duh)
	enum COMPONENTTYPE returnType();

private:

	enum COMPONENTTYPE _type;

};

