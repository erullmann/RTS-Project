/* Component.h
   Base class for component class, implements recieving messages and thats about it
*/

#pragma once

class Component {
public:
	virtual void recieveMessage(void *data) = 0;
};