#include "Parry.h"
#include <iostream>

Parry::Parry(sf::RenderWindow* window)
    :_window(window),_width(window->getSize().x - 125)
{
    _sprite.setFillColor(sf::Color::Yellow);
    _sprite.setPosition((window->getSize().x - _width) / 2.0f, window->getSize().y - 20.0f);
    _sprite.setSize(sf::Vector2f(_width, 25));
}

Parry::~Parry()
{
}

void Parry::render()
{
    _window->draw(_sprite);
}

sf::FloatRect Parry::getBounds() const
{
    return _sprite.getGlobalBounds();
}