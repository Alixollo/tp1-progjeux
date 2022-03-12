#pragma once
#include "Character.h"
class Player :
    public Character
{
public:
    Player();
    
    void initialize(const sf::Vector2f& initialPosition);

    void update(const float speedX, const float speedY, const float gameSpeed, 
                    const int worldWidth, const int worldHeight, const float rotation);
private:
};

