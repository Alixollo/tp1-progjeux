#pragma once
#include "GameObject.h"
class Game;

class Character : public GameObject
{

public:
	Character();
	Character(const Character& src);

	virtual void draw(sf::RenderWindow& window) const;


private:
	Character& operator=(const Character& src);
};


