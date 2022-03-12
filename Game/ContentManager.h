#pragma once
class ContentManager
{
public:
	bool loadContent();
	const sf::Texture& getBackgroundTexture() const;
	const sf::Texture& getPlayerTexture() const;
	const sf::Texture& getEnemy1Texture() const;
	const sf::Texture& getEnemy2Texture() const;
	const sf::Texture& getEnemy3Texture() const;
	const sf::Texture& getNormalBulletTexture() const;
	const sf::Texture& getSpecialBulletTexture() const;
	const sf::Texture& getBonusTexture() const;
	const sf::SoundBuffer& getShotSoundBuffer() const;
	const sf::SoundBuffer& getAlienDeathSoundBuffer() const;
	const sf::SoundBuffer& getPlayerDeathSoundBuffer() const;
	const sf::Font& getFont() const;
	static ContentManager& getInstance();
private:
	ContentManager();

	sf::Texture backgroundTexture;
	sf::Texture playerTexture;
	sf::Texture bonusTexture;
	sf::Texture enemyTexture1;
	sf::Texture enemyTexture2;
	sf::Texture enemyTexture3;
	sf::Texture normalBulletTexture;
	sf::Texture specialBulletTexture;
	sf::SoundBuffer shotSoundBuffer;
	sf::SoundBuffer playerDeathSoundBuffer;
	sf::SoundBuffer alienDeathSoundBuffer;
	sf::Font font;
};



