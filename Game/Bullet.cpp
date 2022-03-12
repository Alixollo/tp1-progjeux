#include "stdafx.h"
#include "Bullet.h"
#include "ContentManager.h"
#include "game.h"

const float Bullet::BULLET_SPEED = 600;
const unsigned long long Bullet::TIME_TO_LIVE = 2000;

Bullet::Bullet(const sf::Vector2f& initialPosition, const sf::Vector2f& initialThrust)
	: GameObject()
	, activationTime(0)
{
	setPosition(initialPosition);
	move(initialThrust);
}

Bullet::Bullet(const Bullet& src)
	:GameObject(src)
{
	initialize(src.getPosition(), src.isSpecial);
}


void Bullet::draw(sf::RenderWindow& window) const
{
	window.draw(*this);
}

#include <Windows.h>
bool Bullet::update(float elapsedTime)
{
	move(sf::Vector2f(cos(getRotationAngleInRadians()) * BULLET_SPEED * elapsedTime, sin(getRotationAngleInRadians()) * BULLET_SPEED * elapsedTime));
	if (getPosition().x > Game::GAME_WIDTH || getPosition().x < 0 || getPosition().y > Game::GAME_HEIGHT || getPosition().y < 0)
		return true;
	if ((::GetTickCount64() - activationTime) > TIME_TO_LIVE)
		return true;
	return false;
}

void Bullet::initialize(const sf::Vector2f& initialPosition, const bool isSpecial)
{
	sf::Texture texture;
	if (!isSpecial) {
		texture = ContentManager::getInstance().getNormalBulletTexture();
	}
	else {
		ContentManager::getInstance().getSpecialBulletTexture();
	}

	GameObject::initialize(texture, initialPosition);
	const sf::SoundBuffer& soundBuffer = ContentManager::getInstance().getShotSoundBuffer();
	sound.setBuffer(soundBuffer);
	this->isSpecial = isSpecial;
}

void Bullet::activate()
{
	GameObject::activate();
	activationTime = ::GetTickCount64();
	sound.play();
}