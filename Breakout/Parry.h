#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"


class Parry
{
public:
    Parry(sf::RenderWindow* window);
    ~Parry();

    void update(float dt);
    void render();
    sf::FloatRect getBounds() const;

private:

    sf::RenderWindow* _window;
    sf::RectangleShape _sprite;
    float _width;
};

