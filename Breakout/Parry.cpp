#include "Parry.h"
#include <iostream>

Parry::Parry(sf::RenderWindow* window)
    :_window(window),_width(window->getSize().x - 75)
{
    _ParrySprite.setFillColor(sf::Color::Yellow);
    _ParrySprite.setPosition((window->getSize().x - _width) / 2.0f, window->getSize().y - 20.0f);
    _ParrySprite.setSize(sf::Vector2f(_width, 25));
}

Parry::~Parry()
{
}

void Parry::update(float dt) {
    
}

void Parry::render()
{
    _window->draw(_ParrySprite);
}

sf::FloatRect Parry::getBounds() const
{
    return _ParrySprite.getGlobalBounds();
}