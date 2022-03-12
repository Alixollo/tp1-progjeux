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
  /// <param name="windowName">Titre de la fenêtre</param>
  Game(std::string windowName);

  /// <summary>
  /// Point d'entrée du jeu
  /// </summary>
  void run();

private:
  /// <summary>
  /// Titre de la fenêtre de jeu
  /// </summary>
  std::string gameName;

  /// <summary>
  /// Fenêtre de rendu
  /// </summary>
  sf::RenderWindow window;

  /// <summary>
  /// Sprite affiché en arrière-plan
  /// </summary>
  sf::Sprite background;

  /// <summary>
  /// Musique diffusée pendant le jeu
  /// </summary>
  sf::Music gameMusic;

  /// <summary>
  /// Indique si le jeu est en pause
  /// </summary>
  bool isInPause;

  /// <summary>
  /// Masque d'entrées
  /// </summary>
  Inputs inputs;

  /// <summary>
  /// Limites du jeu
  /// </summary>
  GameLimits viewLimits;

  /// <summary>
  /// View dans laquelle sont dessinés les acteurs du jeu
  /// </summary>
  sf::View view;

  /// <summary>
  /// Interface utilisateur
  /// </summary>
  Hud hud;

  /// <summary>
  /// Gère la position de la caméra dans la vue
  /// </summary>
  void adjustCrossingViewLimits();

  /// <summary>
  /// Met à jour le jeu
  /// </summary>
  /// <returns>true si le jeu doit se terminer (partie perdue), false sinon</returns>
  bool update();

  /// <summary>
  /// Dessine le jeu à l'écran
  /// </summary>
  /// <param name="window">Le contexte de rendu</param>
  void draw(sf::RenderWindow& window) const;

  /// <summary>
  /// Initialise le jeu (création de la fenêtre, chargement des assets, etc)
  /// </summary>
  /// <returns>true si tout s'est bien déroulé, false sinon</returns>
  bool init();

  /// <summary>
  /// Gère les événements dans le jeu
  /// </summary>
  void handleEvents();

  /// <summary>
  /// Gère la dead zone du contrôleur
  /// </summary>
  /// <param name="analogInput">la valeur analogue du contrôleur</param>
  /// <returns>0 si la valeur analogue est petite en valeur absolue ou analogInput sinon</returns>
  float handleControllerDeadZone(float analogInput);

  void handleEnemySpawn();

  void spawnEnemy();

  /// <summary>
  /// Le personnage contrôlé par le joueur
  /// </summary>
  Player player;

  std::list<Enemy> enemies;

  std::list<Bullet> normalBullets;
  std::list<Bullet> specialBullets;

  float spawnTimer;

  int points;
};

