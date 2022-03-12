#include "stdafx.h"
#include "ContentManager.h"
#include "Enemy.h"
#include "game.h"

const float Enemy::SPEED = 300.0f * Game::FRAME_RATE;
Enemy::Enemy()
  : Character()
{

}
Enemy::Enemy(const Enemy& src)
  : Character(src)
  , textureId(src.textureId)
{
  assignTexture();
}

void Enemy::assignTexture()
{
  texture = texture = ContentManager::getInstance().getEnemy3Texture();
  if (textureId ==1)
  {
    texture = ContentManager::getInstance().getEnemy1Texture();
  }
  else if (textureId==2)
  {
    texture = texture = ContentManager::getInstance().getEnemy2Texture();
  }

  setTexture(texture);
  setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);;
}

void Enemy::initialize()
{
  textureId = 3;
  // Trois textures disponibles, au hasard
  double randomNumber = random.nextDouble();
  if (randomNumber < 0.33)
  {
    textureId = 1;
  }
  else if (randomNumber < 0.66)
  {
    textureId = 2;
  }
  assignTexture();
}

