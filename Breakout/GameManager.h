#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"

#include "Camera.h"
#include <utility>
#include <ctime>
#include <iostream>


class GameManager {
public:
    GameManager(sf::RenderWindow* window);
    void initialize();
    void update(float dt);
    void loseLife();
    void render();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    sf::RenderWindow* getWindow() const;
    UI* getUI() const;


private:
    bool _pause;
    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    int _lives;
    bool _levelComplete;
    int _currentLevel = 0;

    std::vector<float> _shakeStrengthVec = {
        {0.9},
        {0.5},
        {0.25}
    };

    std::pair<POWERUPS, float> _powerupInEffect;

    sf::Font _font;
    sf::Text _masterText;
    sf::Text _retryText;
    sf::Text _levelText;

    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;
    Camera* _cam;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn

    //(int rows, int cols, float brickWidth, float brickHeight, float spacing, int level); 5, 10, 80.0f, 30.0f, 5.0f
    float _brickRows[3] = {1, 4, 8};
    float _brickCols[3] = {1, 8, 16};
    float _brickWidth[3] = {100.f, 40.f, 40.f};
    float _brickHeight[3] = {150.f,15.f,15.f};
    float _brickSpacing[3] = { 5.0f,5.0f,5.0f };
};
