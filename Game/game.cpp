#include "stdafx.h"
#include "game.h"
#include "ContentManager.h"
#include <iostream>

#pragma region Constantes
const unsigned int Game::FRAME_RATE = 60;
const float Game::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const unsigned int Game::GAME_WIDTH = 1280;
const unsigned int Game::GAME_HEIGHT = 720;
const int Game::WORLD_WIDTH = 3384; //Taille du field
const int Game::WORLD_HEIGHT = 1656;
const float Game::GAMEPAD_SPEEDRATIO = 0.5f;
const float Game::KEYBOARD_SPEED = 200.0f;
const float Game::KEYBOARD_ROTATION = 5.0f;
const int Game::CONTROLLER_DEAD_ZONE = 20;
const float Game::FREECAM_SPEED = 3;
const int Game::MAX_ENEMY_AMOUNT = 15;
const float Game::ENEMY_SPAWN_SPEED = 3;
const int Game::POINTS_PER_ENEMY_SPAWN = 10;
#pragma endregion


Game::Game(std::string windowName)
	: gameName(windowName)
	, isInPause(false)
	, inputs()
	, spawnTimer(0)
	, points(0)
{
}

#pragma region Methodes de base
void Game::run()
{
	// Chargement des ressources
	if (!init())
	{
		return;
	}

	// Boucle de jeu
	while (window.isOpen())
	{
		handleEvents();

		update();

		window.clear();
		window.setView(view);
		draw(window);
		window.display();
	}
}

void Game::handleEvents()
{
	sf::Event event;
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (window.pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Key::P)
				isInPause = !isInPause;
		}
		else if (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 7)
			isInPause = !isInPause;
	}
	//Si le Gamepad est connecté, on l'utilise pour sélectionner et déplacer les vaisseaux
	if (sf::Joystick::isConnected(0))
	{
		inputs.speedValueY = handleControllerDeadZone(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y)) / GAMEPAD_SPEEDRATIO;
		inputs.speedValueX = handleControllerDeadZone(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X)) / GAMEPAD_SPEEDRATIO;

		float rotationAxisY = handleControllerDeadZone(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V)) / 1000.0f;
		float rotationAxisX = handleControllerDeadZone(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U)) / 1000.0f;
		inputs.rotationValue = atan2f(rotationAxisY, rotationAxisX);

		// ppoulin
		// Reste à gérer le lancement de projectiles
		// A COMPLÉTER
		// inputs.shouldFire = ...
		float inputValueZ = handleControllerDeadZone(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z));
		if (inputValueZ > 0) {
			inputs.shouldFire = true;
		}
	}
	//Sinon on se rabat sur le clavier
	else
	{
		inputs.speedValueX = inputs.speedValueY = 0.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			inputs.rotationValue -= KEYBOARD_ROTATION;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			inputs.rotationValue += KEYBOARD_ROTATION;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			inputs.speedValueX -= Game::KEYBOARD_SPEED;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			inputs.speedValueX += Game::KEYBOARD_SPEED;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			inputs.speedValueY -= Game::KEYBOARD_SPEED;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			inputs.speedValueY += Game::KEYBOARD_SPEED;

		// ppoulin
		// Reste à gérer le lancement de projectiles
		// A COMPLÉTER
		// inputs.shouldFire = ...
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			inputs.shouldFire = true;
		}

	}
}

//Portée analogue -100 à 100
float Game::handleControllerDeadZone(float analogInput)
{
	if (fabs(analogInput) < CONTROLLER_DEAD_ZONE)
	{
		analogInput = 0.0f;
	}
	return analogInput;
}

void Game::draw(sf::RenderWindow& window)  const
{
	window.setView(view);
	window.draw(background);

	player.draw(window);
	for (Enemy enemy : this->enemies) {
		if (enemy.isActive()) {
			enemy.draw(window);
		}
	}
	//anEnemy.draw(window);

	// Toujours dessiner le Hud par-dessus tout (en dernier).
	hud.draw(window);
}

bool Game::init()
{
	// Création de la fenêtre et de la vue
	window.create(sf::VideoMode(Game::GAME_WIDTH, Game::GAME_HEIGHT, 32), gameName);
	window.setFramerateLimit(FRAME_RATE);
	view = sf::View(sf::FloatRect(0, 0, GAME_WIDTH, GAME_HEIGHT));
	view.setCenter(WORLD_WIDTH / 2, WORLD_HEIGHT / 2);
	viewLimits.minX = GAME_WIDTH / 2;
	viewLimits.minY = GAME_HEIGHT / 2;
	viewLimits.maxX = WORLD_WIDTH - viewLimits.minX;
	viewLimits.maxY = WORLD_HEIGHT - viewLimits.minY;

	// Chargement des ressources
	if (ContentManager::getInstance().loadContent() == false)
	{
		return false;
	}

	// Arrière-plan
	background.setTexture(ContentManager::getInstance().getBackgroundTexture());
	// Couleur teintée fortement en rouge
	background.setColor(sf::Color(255, 64, 64, 255));

	// Hud
	hud.initialize();

	// Musique
	if (!gameMusic.openFromFile("Assets\\Music\\sgMusic.ogg"))
		return false;
	gameMusic.setVolume(gameMusic.getVolume() / 5); //Le son était beaucoup trop fort...
	gameMusic.setLoop(true);
	gameMusic.play();

	// Joueur
	player.initialize(sf::Vector2f(WORLD_WIDTH / 2, WORLD_HEIGHT / 2 + 100));

	// Attributs reliés au gameplay
	inputs.reset();

	for (int i = 0; i < MAX_ENEMY_AMOUNT; i++) {
		Enemy enemy;
		enemy.initialize();
		this->enemies.push_back(enemy);
	}

	return true;
}

//Vous devrez centrer la vue sur le player: https://www.sfml-dev.org/tutorials/2.4/graphics-view-fr.php
bool Game::update()
{
	if (!isInPause) {
		this->player.update(inputs.speedValueX, inputs.speedValueY, TIME_PER_FRAME, WORLD_WIDTH, WORLD_HEIGHT, inputs.rotationValue);
		view.setCenter(player.getPosition());

		this->handleEnemySpawn();

		this->hud.update(points);
	}
	else {
		view.move(inputs.speedValueX * TIME_PER_FRAME * FREECAM_SPEED, inputs.speedValueY * TIME_PER_FRAME * FREECAM_SPEED);
	}
	adjustCrossingViewLimits();

	return false;
}

void Game::handleEnemySpawn() {
	this->spawnTimer += TIME_PER_FRAME;

	if (this->spawnTimer >= ENEMY_SPAWN_SPEED) {
		this->spawnEnemy();
		this->points += POINTS_PER_ENEMY_SPAWN;
		this->spawnTimer = 0;
	}
}

void Game::spawnEnemy() {
	for (Enemy &enemy : this->enemies) {
		if (!enemy.isActive()) {
			enemy.setPosition(player.getPosition());
			enemy.activate();
			break;
		}
	}
}

void Game::adjustCrossingViewLimits()
{
	if (view.getCenter().x < viewLimits.minX)
	{
		view.setCenter(viewLimits.minX, view.getCenter().y);
	}
	else if (view.getCenter().x > viewLimits.maxX)
	{
		view.setCenter(viewLimits.maxX, view.getCenter().y);
	}

	if (view.getCenter().y < viewLimits.minY)
	{
		view.setCenter(view.getCenter().x, viewLimits.minY);
	}
	else if (view.getCenter().y > viewLimits.maxY)
	{
		view.setCenter(view.getCenter().x, viewLimits.maxY);
	}
}
#pragma endregion
