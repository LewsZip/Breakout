#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
#include <ctime>
#include <iostream>

class GameManager;  // forward declaration

class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
    void randomSpawn(sf::CircleShape &_sprite);

    //a vector of pairs that contains ball spawn details (x pos, direction)
    std::vector<std::pair<float, float>> spawnVec = {
        {0, 1},
        {500, 0},
        {1000, 1}
    };

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    float _timeWithPowerupEffect;

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

