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
    sf::FloatRect getBounds() const;
    sf::Vector2u windowSize;

private:
    sf::CircleShape _sprite;
    sf::Texture _ballTexture;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    bool _justParried;
    float _timeWithPowerupEffect;
    float _timeHeld;
    float _parryTimer;
    float _parrymult = 1;
    float _parryhits = 0;

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

