#include "stdafx.h"
#include "Player.h"
#include "game.h"
#include "ContentManager.h"
#include <iostream>
Player::Player()
	: Character()
{
	activate();
}

void Player::initialize(const sf::Vector2f& initialPosition)
{
	Character::initialize(ContentManager::getInstance().getPlayerTexture(), initialPosition);
}

void Player::update(const float speedX, const float speedY, const float gameSpeed, 
						const int worldWidth, const int worldHeight, float rotation) {
	float movementX = speedX * gameSpeed;
	float movementY = speedY * gameSpeed;

	if (movementX + this->getPosition().x + (this->getTexture()->getSize().x) > worldWidth || movementX + this->getPosition().x - (this->getTexture()->getSize().x / 2) < 0) {
		movementX = 0;
	}
	if (movementY + this->getPosition().y + (this->getTexture()->getSize().y / 2) > worldHeight || movementY + this->getPosition().y - (this->getTexture()->getSize().y / 2) < 0) {
		movementY = 0;
	}

	this->setRotation(rotation);
	this->move(movementX, movementY);
}
