#pragma once
#include "Character.h"
#include "random.h"
class Enemy :
  public Character
{
  static const float SPEED;

public:
  Enemy();
  Enemy(const Enemy&);
  void initialize();

private:
  void assignTexture();
  sf::Texture texture;
  int textureId;
  Random random;
};

