#include "stdafx.h"
#include "Character.h"
#include "game.h"

Character::Character()
{
}

Character::Character(const Character& src)
	: GameObject(src)
{
}

void Character::draw(sf::RenderWindow& window) const
{
	if (isActive())
		window.draw(*this);
}

