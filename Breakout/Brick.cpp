#include "Brick.h"

Brick::Brick(float x, float y, float width, float height)
    : _isDestroyed(false)
{
    sf::Color lightPink = { 255,191,176,255 }; 
    sf::Color deepRed = { 193,39,0,255 }; 
    _shape.setFillColor(lightPink);
    _shape.setOutlineColor(deepRed);
    _shape.setOutlineThickness(2.0f);
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
}

void Brick::render(sf::RenderWindow& window)
{
    
    if (!_isDestroyed) {
        window.draw(_shape);
    }
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}
