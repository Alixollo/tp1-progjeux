#include "stdafx.h"
#include "ContentManager.h"
#include "random.h"

ContentManager::ContentManager()
{
}

ContentManager& ContentManager::getInstance()
{
	static ContentManager instance;
	return instance;
}


bool ContentManager::loadContent()
{
	if (!backgroundTexture.loadFromFile("Assets\\Sprites\\Backgrounds\\MoonReflectiveBackground.png"))
	{
		return false;
	}

	if (!playerTexture.loadFromFile("Assets\\Sprites\\SpacemanAndAliens\\Spaceman.png"))
	{
		return false;
	}

	if (!enemyTexture1.loadFromFile("Assets\\Sprites\\SpacemanAndAliens\\Alien1.png"))
	{
		return false;
	}
	if (!enemyTexture2.loadFromFile("Assets\\Sprites\\SpacemanAndAliens\\Alien2.png"))
	{
		return false;
	}
	if (!enemyTexture3.loadFromFile("Assets\\Sprites\\SpacemanAndAliens\\Alien3.png"))
	{
		return false; 
	}

	////SFML supports the audio file formats WAV, OGG/Vorbis and FLAC. Due to licensing issues MP3 is not supported.
	if (!normalBulletTexture.loadFromFile("Assets\\Sprites\\Bullet.png"))
	{
		return false;
	} 
	if (!bonusTexture.loadFromFile("Assets\\Sprites\\BoostLogo.png"))
	{
		return false;
	}
	
		if (!specialBulletTexture.loadFromFile("Assets\\Sprites\\Blast.png"))
		{
			return false;
		}
	if (!shotSoundBuffer.loadFromFile("Assets\\Sounds\\SpaceShots\\Shot01.ogg"))
	{
		return false;
	}

	if (!alienDeathSoundBuffer.loadFromFile("Assets\\Sounds\\Characters\\AlienDeath.ogg"))
	{
		return false;
	}

	if (!playerDeathSoundBuffer.loadFromFile("Assets\\Sounds\\Characters\\PlayerDeath.ogg"))
	{
		return false;
	}

	if (false == font.loadFromFile("Assets\\Fonts\\segoepr.ttf"))
		return false;


	return true;
}

const sf::SoundBuffer& ContentManager::getAlienDeathSoundBuffer() const
{
	return alienDeathSoundBuffer;
}

const sf::SoundBuffer& ContentManager::getPlayerDeathSoundBuffer() const
{
	return playerDeathSoundBuffer;
}

const sf::Font& ContentManager::getFont() const
{
	return font;
}

const sf::Texture& ContentManager::getBackgroundTexture() const
{
	return backgroundTexture;
}

const sf::Texture& ContentManager::getPlayerTexture() const
{
	return playerTexture;
}


const sf::Texture& ContentManager::getEnemy1Texture() const
{
	return enemyTexture1;
}

const sf::Texture& ContentManager::getEnemy2Texture() const
{
	return enemyTexture2;
}
const sf::Texture& ContentManager::getEnemy3Texture() const
{
	return enemyTexture3;
}

const sf::Texture& ContentManager::getNormalBulletTexture() const
{
	return normalBulletTexture;
}

const sf::Texture& ContentManager::getSpecialBulletTexture() const
{
	return specialBulletTexture;
}

const sf::SoundBuffer& ContentManager::getShotSoundBuffer() const
{
	return shotSoundBuffer;
}

const sf::Texture& ContentManager::getBonusTexture() const
{
	return bonusTexture;
}