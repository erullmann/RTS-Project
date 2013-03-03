/* DrawComponent.cpp
*/
#pragma once
#include "DrawComponent.h"
#include <iostream>
#include <math.h>

sf::Vector2f DrawComponent::calculateScreenPosition(sf::Vector2f location){
	float XPos = (_spriteSize.x/2)*(location.x - location.y);
	float YPos = (_spriteSize.y/2)*(location.y + location.x);
	sf::Vector2f position_final(XPos, YPos);
	return position_final;
}

DrawComponent::DrawComponent(ResourceManager &resourceManager, ENTITYTYPE type, sf::RenderWindow &renderWindow, sf::Vector2i spriteSize, sf::Vector2i defaultFramePos, sf::Vector2i attackAnimationStart, sf::Vector2i deathAnimationStart, sf::Vector2i moveAnimationStart, int attackFrames, int moveFrames, int deathFrames){
	float millesecondsPerFrame = 1000/12;

	_texture = resourceManager.returnElementTexture(type);
	_renderWindow = &renderWindow;
	_spriteSize = spriteSize;
	_sprite.setOrigin(spriteSize.x/2, spriteSize.y/2);
	_sprite.setTexture(*_texture);
	_defaultFramePos = defaultFramePos;
	_attackAnimationStart = attackAnimationStart;
	_deathAnimationStart = deathAnimationStart;
	_moveAnimationStart = moveAnimationStart;
	_lengthOfAttackAnimation = sf::milliseconds(attackFrames * millesecondsPerFrame);
	_numberOfAttackFrames = attackFrames;
	_lengthOfMoveAnimation = sf::milliseconds(moveFrames * millesecondsPerFrame);
	_numberOfMoveFrames = moveFrames;
	_lengthOfDeathAnimation = sf::milliseconds(deathFrames * millesecondsPerFrame);
	_numberOfDeathFrames = deathFrames;
}

DrawComponent::~DrawComponent(){

}

//static objects
void DrawComponent::drawInGame(sf::Vector2f location){
	_sprite.setPosition(calculateScreenPosition(location));
	sf::Rect<int> texRect(_defaultFramePos.x * _spriteSize.x, _defaultFramePos.y * _spriteSize.y, _spriteSize.x, _spriteSize.y);
	_sprite.setTextureRect(texRect);
	_renderWindow->draw(_sprite);
}

//death animation
void DrawComponent::drawInGame(sf::Vector2f location, sf::Time timeOfDeath){
	_sprite.setPosition(calculateScreenPosition(location));
	//calculates percentage of animation completed
	float animationComplete = timeOfDeath.asMilliseconds() / _lengthOfDeathAnimation.asMilliseconds();

	if (animationComplete <= 1.0f){
		//converts percentage into a number of frames
		int animationFrame = floor(animationComplete * _numberOfDeathFrames); //converts it into a number of frames, skipping the first one

		sf::Rect<int> texRect((animationFrame + _deathAnimationStart.x) * _spriteSize.x, _deathAnimationStart.y * _spriteSize.y, _spriteSize.x, _spriteSize.y);
		_sprite.setTextureRect(texRect);
		_renderWindow->draw(_sprite);
	}
	else{
		drawInGame(location);
	}
}

//mobile units
void DrawComponent::drawInGame(sf::Vector2f location, bool moving, bool attacking, int heading, sf::Time timeOfLastAttack, sf::Time timeOfStartMove){
	_sprite.setPosition(calculateScreenPosition(location));
	if(attacking){
		float attackComplete = timeOfLastAttack.asMilliseconds() / _lengthOfAttackAnimation.asMilliseconds();
		int animationFrame = floor(attackComplete * _numberOfAttackFrames);

		sf::Rect<int> texRect((animationFrame + _attackAnimationStart.x) * _spriteSize.x, (heading + _attackAnimationStart.y) * _spriteSize.y, _spriteSize.x, _spriteSize.y);
		_sprite.setTextureRect(texRect);
		_renderWindow->draw(_sprite);
	}
	else if(moving){
		float moveComplete = (timeOfStartMove.asMilliseconds() % _lengthOfMoveAnimation.asMilliseconds()) / _lengthOfMoveAnimation.asMilliseconds();
		int animationFrame = floor(moveComplete * _numberOfMoveFrames);

		sf::Rect<int> texRect((animationFrame + _moveAnimationStart.x) * _spriteSize.x, (heading + _moveAnimationStart.y) * _spriteSize.y, _spriteSize.x, _spriteSize.y);
		_sprite.setTextureRect(texRect);
		_renderWindow->draw(_sprite);
	}
	else{
		sf::Rect<int> texRect(_moveAnimationStart.x * _spriteSize.x, (heading + _moveAnimationStart.y) * _spriteSize.y, _spriteSize.x, _spriteSize.y);
		_sprite.setTextureRect(texRect);
		_renderWindow->draw(_sprite);
	}
}

void DrawComponent::drawInGame(sf::Vector2f location, float healthStatus, int healthFrames){
	_sprite.setPosition(calculateScreenPosition(location));
	int animationFrame = 1/floor(healthStatus * healthFrames);
	sf::Rect<int> texRect(animationFrame * _spriteSize.x, 0, _spriteSize.x, _spriteSize.y);
	_sprite.setTextureRect(texRect);
	_renderWindow->draw(_sprite);
}

void DrawComponent::drawInWindow(int alignX, int alignY){
	sf::Vector2u windowSize = _renderWindow->getSize();
	sf::Vector2f windowSegment(windowSize.x/7, windowSize.y/7);

	_sprite.setOrigin(_sprite.getTextureRect().width/2, _sprite.getTextureRect().height/2);
	if (alignX == 0){
		_sprite.setOrigin(0, _sprite.getOrigin().y);
	}
	if (alignY == 0){
		_sprite.setOrigin(_sprite.getOrigin().x, 0);
	}
	if (alignX == 6){
		_sprite.setOrigin(_sprite.getTextureRect().width, _sprite.getOrigin().y);
	}
	if (alignY == 6){
		_sprite.setOrigin(_sprite.getOrigin().x, _sprite.getTextureRect().height);
	}

	_sprite.setPosition(alignX * windowSegment.x, alignY * windowSegment.y);
	//note ui sprites use default (full) texture
	_renderWindow->draw(_sprite);
}

void DrawComponent::drawInWindow(sf::Vector2f location, sf::Color color){
	_sprite.setPosition(location);
	_sprite.setColor(color);
	_renderWindow->draw(_sprite);
}