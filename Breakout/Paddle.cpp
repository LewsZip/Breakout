#include "Paddle.h"
#include <iostream>

Paddle::Paddle(sf::RenderWindow* window)
    : _window(window), _width(PADDLE_WIDTH), _timeInNewSize(0.0f), _isAlive(true)
{
    _paddleTex.loadFromFile("textures/paddle.png");

    _sprite.setTexture(&_paddleTex);
    _sprite.setPosition((window->getSize().x - _width) / 2.0f, window->getSize().y - 75.0f);
    _sprite.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));
}

Paddle::~Paddle()
{
}

void Paddle::moveLeft(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && position > 0 or sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && position > 0)
    {
        _sprite.move(sf::Vector2f(-dt * _currentSpeed, 0));
    }
}

void Paddle::moveRight(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && position < _window->getSize().x - _width or sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && position < _window->getSize().x - _width)
    {
        _sprite.move(sf::Vector2f(dt * _currentSpeed, 0));
    }
}

void Paddle::update(float dt)
{
    if (_timeInNewSize > 0)
    {
        _timeInNewSize -= dt;
    }
    else
    {
        setWidth(1.0f, 0.0f); // Reset to default width after duration
    }

    //speed up paddle if lshift is held
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) _currentSpeed = PADDLE_SPEED * 2;
    else _currentSpeed = PADDLE_SPEED;
}

void Paddle::render()
{
    _window->draw(_sprite);
}

sf::FloatRect Paddle::getBounds() const
{
    return _sprite.getGlobalBounds();
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff, float duration)
{
    _width = coeff * PADDLE_WIDTH;
    _sprite.setSize(sf::Vector2f(_width, _sprite.getSize().y));
    _timeInNewSize = duration;
    float newX = _sprite.getPosition().x + (_width - PADDLE_WIDTH) / 2;
    _sprite.setPosition(newX, _sprite.getPosition().y);
}
