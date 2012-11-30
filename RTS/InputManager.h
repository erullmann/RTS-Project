////////////////////////////////////
//Input Manager: handles playerinputs and passes it to the appropriote units, player
//will later be modified to package inputs and send it to the network manager for transmission
//and excecution
////////////////////////////////////

#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "LevelManager.h"

class InputManager
{
public:
	void getInput(sf::Event& currentEvent); //gets events for network and packages it

	void excecuteInput(sf::RenderWindow& renderWindow, LevelManager& levelManager);//gets input from network, excecutes it simultainuously with network
};