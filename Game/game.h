#pragma once
#include "stdafx.h"
#include "Player.h"
#include "GameLimits.h"
#include "Inputs.h"
#include "Hud.h"
#include "Enemy.h"
#include "Bullet.h"

class Game
{
public:
  static const unsigned int FRAME_RATE;
  static const float TIME_PER_FRAME;
  static const int CONTROLLER_DEAD_ZONE;
  static const unsigned int GAME_WIDTH;
  static const unsigned int GAME_HEIGHT;
  static const float GAMEPAD_SPEEDRATIO;
  static const float KEYBOARD_SPEED;
  static const float KEYBOARD_ROTATION;
  static const int WORLD_WIDTH;
  static const int WORLD_HEIGHT;
  static const float FREECAM_SPEED;
  static const int MAX_ENEMY_AMOUNT;
  static const float ENEMY_SPAWN_SPEED;
  static const int POINTS_PER_ENEMY_SPAWN;

public:
  /// <summary>
  /// Construit un jeu
  /// </summary>
  /// <param name="windowName">Titre de la fen�tre</param>
  Game(std::string windowName);

  /// <summary>
  /// Point d'entr�e du jeu
  /// </summary>
  void run();

private:
  /// <summary>
  /// Titre de la fen�tre de jeu
  /// </summary>
  std::string gameName;

  /// <summary>
  /// Fen�tre de rendu
  /// </summary>
  sf::RenderWindow window;

  /// <summary>
  /// Sprite affich� en arri�re-plan
  /// </summary>
  sf::Sprite background;

  /// <summary>
  /// Musique diffus�e pendant le jeu
  /// </summary>
  sf::Music gameMusic;

  /// <summary>
  /// Indique si le jeu est en pause
  /// </summary>
  bool isInPause;

  /// <summary>
  /// Masque d'entr�es
  /// </summary>
  Inputs inputs;

  /// <summary>
  /// Limites du jeu
  /// </summary>
  GameLimits viewLimits;

  /// <summary>
  /// View dans laquelle sont dessin�s les acteurs du jeu
  /// </summary>
  sf::View view;

  /// <summary>
  /// Interface utilisateur
  /// </summary>
  Hud hud;

  /// <summary>
  /// G�re la position de la cam�ra dans la vue
  /// </summary>
  void adjustCrossingViewLimits();

  /// <summary>
  /// Met � jour le jeu
  /// </summary>
  /// <returns>true si le jeu doit se terminer (partie perdue), false sinon</returns>
  bool update();

  /// <summary>
  /// Dessine le jeu � l'�cran
  /// </summary>
  /// <param name="window">Le contexte de rendu</param>
  void draw(sf::RenderWindow& window) const;

  /// <summary>
  /// Initialise le jeu (cr�ation de la fen�tre, chargement des assets, etc)
  /// </summary>
  /// <returns>true si tout s'est bien d�roul�, false sinon</returns>
  bool init();

  /// <summary>
  /// G�re les �v�nements dans le jeu
  /// </summary>
  void handleEvents();

  /// <summary>
  /// G�re la dead zone du contr�leur
  /// </summary>
  /// <param name="analogInput">la valeur analogue du contr�leur</param>
  /// <returns>0 si la valeur analogue est petite en valeur absolue ou analogInput sinon</returns>
  float handleControllerDeadZone(float analogInput);

  void handleEnemySpawn();

  void spawnEnemy();

  /// <summary>
  /// Le personnage contr�l� par le joueur
  /// </summary>
  Player player;

  std::list<Enemy> enemies;

  std::list<Bullet> normalBullets;
  std::list<Bullet> specialBullets;

  float spawnTimer;

  int points;
};

