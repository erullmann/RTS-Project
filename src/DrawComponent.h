/* DrawComponent.h
   Provides drawing functionality to units, ui elements,  those who want it
   Some notes about drawing
	-all animations move at 12fps
	-the owner class dicides if animations get played
	-the owner class gives draw class animation lengths 
*/

//CONSIDER SPLITTING INTO DIFFRENT DRAW CLASSES
#pragma once
#include "SFML\Graphics.hpp"
#include "ResourceManager.h"

class DrawComponent {
public:

	//Note to self: Consider loading animation metadata here, detailing start location (on texture) and length of attack/move/death animations
	//Constructor for DrawComponent that grabs the resources 
	//	-resorceManager gets the texturesheet that the entity needs
	//	-type assists with above
	//	-renderWindow tells draw where to draw to
	//	-spriteSize tells draw size of each frame in pixels
	//	-spriteCenter tells draw where to center the sprite
	//	-attackFrames tells draw length of the attack animation (in frames) (min 0)
	//	-moveFrames does above for move animation (min 0)
	//	-dieFrames does above for deathAnimation (min 1)//also is default image
	DrawComponent(ResourceManager &resourceManager, ENTITYTYPE type, sf::RenderWindow &renderWindow, sf::Vector2i spriteSize, sf::Vector2i defaultFramePos, sf::Vector2i attackAnimationStart, sf::Vector2i deathAnimationStart, sf::Vector2i moveAnimationStart, int attackFrames, int moveFrames, int dieFrames);

	//Frees memory, cleans up, etc.
	~DrawComponent();

	//Draw tiles/dead/static things on the map (displays first (death) frame by default)
	//	-location is the location of the object on the map
	void drawInGame(sf::Vector2f location);

	//Draw dieing objects on the map (displays first (death) frame by default)
	//	-location is the location of the object on the map
	//	-timeOfDeath is when the object died
	void drawInGame(sf::Vector2f location, sf::Time timeOfDeath);

	//Draw mobile units on the map
	//	-location is the location of the object on the map
	//	-moveStatus tells draw if the object is moving and move animation should be played
	//	-heading tells draw direction object is looking (mod 8)
	//  -timeOfLastAttack tells draw when attack last ocured (if timeOfLastAttack > lengthOfAttackAnimation, animation isn't played)
	//	-timeOfStartMove tells draw when object started moveing (modulated by lengthOfMoveAnimation and used to claculate frames)
	void drawInGame(sf::Vector2f location, bool moving, bool attacking, int heading, sf::Time timeOfLastAttack, sf::Time timeOfStartMove);

	//Draw buildings on the map
	//	-location is the location of the object on the map
	//	-healthStatus is the health of the building as a percentage (used to show distruction)
	//  -timeOfLastAttack tells draw when an attack last ocured (if timeOfLastAttack > lengthOfAttackAnimation, animation isn't played)
	void drawInGame(sf::Vector2f location, float healthStatus, int healthFrames);

	//Draw things (UI elements usually) on the screen, aligned to a corner or centered
	//	-alignX is used to align the sprite on the x-axis (if not in corner spriteCenter should be in middle of image,
	//        otherwise it should be in corrisponding corner) (0 <= alignX <= 6, 0 is farleft)
	//	-alignY is used to align the sprite on the y-axis (if not in corner spriteCenter should be in middle of image,
	//        otherwise it should be in corrisponding corner) (0 <= alignY <= 6, 0 is bottom)
	void drawInWindow(int alignX, int alignY);

	//Draw freefloating UI elements
	//	-location is location of ui element (pixel aligned)
	//	-color lets us color images (if inactive or disabled for instance)
	void drawInWindow(sf::Vector2f location, sf::Color color);

private:
	
	sf::Vector2f calculateScreenPosition(sf::Vector2f mapLocation);

	sf::Texture *_texture;

	sf::Sprite _sprite;

	sf::Time _lengthOfAttackAnimation, _lengthOfMoveAnimation, _lengthOfDeathAnimation;
	int _numberOfAttackFrames, _numberOfMoveFrames, _numberOfDeathFrames;

	sf::Vector2i _defaultFramePos, _deathAnimationStart, _attackAnimationStart, _moveAnimationStart;

	sf::Vector2i _spriteSize;

	sf::RenderWindow *_renderWindow;

};