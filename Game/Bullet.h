#pragma once
#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
	static const float BULLET_SPEED;
	static const unsigned long long TIME_TO_LIVE;
public:
	Bullet(const sf::Vector2f& initialPosition = sf::Vector2f(0,0), const sf::Vector2f& initialThrust = sf::Vector2f(0, 0));
	Bullet(const Bullet& src);
	virtual void initialize(const sf::Vector2f& initialPosition, const bool isSpecial);
	virtual void activate() override;
	void draw(sf::RenderWindow& window) const;
	bool update(float elapsedTime);

private:
	Bullet& operator=(const Bullet& rhs);
	sf::Sound sound;
	unsigned long long activationTime;
	bool isSpecial;
};