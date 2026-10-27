#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f), _cam(nullptr), _parry(nullptr)
{
    _font.loadFromFile("font/montS.ttf");

    _bgTexture.loadFromFile("textures/bgfull.png");
    _bgTexture.setRepeated(true);

    _background.setTexture(&_bgTexture);
    _background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    _background.setPosition(0, 0);

    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);

    _retryText.setFont(_font);
    _retryText.setPosition(50, 500);
    _retryText.setCharacterSize(48);
    _retryText.setFillColor(sf::Color::Yellow);

    _levelText.setFont(_font);
    _levelText.setPosition(window->getSize().x - 200, 25);
    _levelText.setCharacterSize(48);
    _levelText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);
    _cam = new Camera(_window);
    _parry = new Parry(_window);

    // Create bricks
    _brickManager->createBricks(_brickRows[_currentLevel], _brickCols[_currentLevel], _brickWidth[_currentLevel], _brickHeight[_currentLevel], _brickSpacing[_currentLevel], _currentLevel);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    _levelText.setString("Level: " + std::to_string(_currentLevel + 1));

    if (_lives <= 0)
    {
        _masterText.setString("Game over.");
        _retryText.setString("Press 'R' to restart.");

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            _pause = false;
            _lives = 3;
            _currentLevel = 0;
            _masterText.setString("");
            _retryText.setString("");
            initialize();
        }

        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.");
        levelComplete();
        return;
    }

    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _retryText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) _paddle->moveLeft(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) _ball = new Ball(_window, 400.0f, this); 

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
    _cam->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    //screen shake.
    _cam->shake(_shakeStrengthVec[_lives], 1200);
}

void GameManager::render()
{
    _window->draw(_background);
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _window->draw(_retryText);
    _window->draw(_levelText);
    _ui->render();
    _parry->render();
}

void GameManager::levelComplete()
{
    _currentLevel += 1;
    initialize();
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
Parry* GameManager::getParry() const { return _parry; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
