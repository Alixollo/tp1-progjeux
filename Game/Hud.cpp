#include "stdafx.h"
#include "Hud.h"
#include "ContentManager.h"
#include "game.h"

const std::string Hud::POINTS_STRING = "Points : ";

Hud::Hud()
{

}

void Hud::initialize()
{
  const std::string introductionText = "Aliens are invading Mars!";
  hudView = sf::View(sf::FloatRect(0, 0, (float)Game::GAME_WIDTH, (float)Game::GAME_HEIGHT));
  gameTitle.setFont(ContentManager::getInstance().getFont());
  gameTitle.setCharacterSize(50);
  gameTitle.setFillColor(sf::Color::Blue);
  gameTitle.setOutlineThickness(4);
  gameTitle.setOutlineColor(sf::Color(0,255,0,255));
  gameTitle.setString(introductionText);
  gameTitle.setPosition(Game::GAME_WIDTH / 2.0f - gameTitle.getLocalBounds().width / 2.0f, 0 + gameTitle.getLocalBounds().height / 2.0f);

  std::string points = POINTS_STRING;
  points += "0";
  pointsText.setFont(ContentManager::getInstance().getFont());
  pointsText.setCharacterSize(32);
  pointsText.setFillColor(sf::Color::Blue);
  pointsText.setOutlineThickness(4);
  pointsText.setOutlineColor(sf::Color(0, 255, 0, 255));
  pointsText.setString(points);
  pointsText.setPosition(0 + pointsText.getLocalBounds().width / 2.0f, 0 + pointsText.getLocalBounds().height / 2.0f);
}

void Hud::update(const int points) {
    std::string pointsStr = POINTS_STRING;
    pointsStr += std::to_string(points);

    pointsText.setString(pointsStr);
}

void Hud::draw(sf::RenderWindow& window)  const
{
  window.setView(hudView);
  window.draw(gameTitle);
  window.draw(pointsText);
}