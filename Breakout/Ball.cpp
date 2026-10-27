#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1})
{
    _ballTexture.loadFromFile("textures/ball.png");

    _sprite.setRadius(RADIUS);
    _sprite.setTexture(&_ballTexture);
    _sprite.setFillColor(sf::Color::White);
    
    randomSpawn(_sprite); //sets up spawn values that we want to be random
    _window->setKeyRepeatEnabled(false);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        // timer for parry window.
        _timeHeld += dt;
    }

    // check for powerup, tick down or correct
    if (_timeWithPowerupEffect > 0.f)
    {
        _timeWithPowerupEffect -= dt;
    }
    else
    {
        if (_velocity != VELOCITY)
            _velocity = VELOCITY;   // reset speed.
        else
        {
            setFireBall(0);    // disable fireball
            _sprite.setFillColor(sf::Color::White);  // back to normal colour.
        }        
    }

    // Fireball effect
    if (_isFireBall)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        _sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }

    // Update position with a subtle floating-point error
    _sprite.move(_direction * _velocity * dt);

    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2u windowDimensions = _window->getSize();

    // bounce on walls
    if ((position.x >= windowDimensions.x - 2 * RADIUS && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
    }

    // lose life bounce
    if (position.y > windowDimensions.y)
    {
        _sprite.setPosition(500, 300);
        _direction = { 0, 1 };
        _gameManager->loseLife();
        _parrymult = 1;
        setVelocity(_parrymult, 3);
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        _direction.y *= -1; // Bounce vertically

        float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
        _direction.x = paddlePositionProportion * 2.0f - 1.0f;

        // Adjust position to avoid getting stuck inside the paddle
        _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * RADIUS);
    }

    if (_justParried) {
        _parryTimer += dt;
        if (_parryTimer > 3) {
            _justParried = false;
            _parrymult = 1;
        }
    }

    // collision with parry window
    if (_sprite.getGlobalBounds().intersects(_gameManager->getParry()->getBounds())) 
    {   
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            _justParried = true;
            _parrymult += 1;
            _parryTimer = 0;
            if (_timeHeld > 0.1) {
                
            }
            else {
                (_direction.y *= -1); // Bounce vertically
                _sprite.setPosition(_sprite.getPosition().x, _gameManager->getParry()->getBounds().top - 2 * RADIUS);
                setVelocity(_parrymult, 3);
            }
        }
    }

    // reset parry window if space is not being pressed
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        _timeHeld = 0;
    }

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
    if (_isFireBall) return; // no collisisons when in fireBall mode.
    if (collisionResponse == 1)
    {
        _direction.x *= -1; // Bounce horizontally
    }
    else if (collisionResponse == 2)
    {
        _direction.y *= -1; // Bounce vertically
    }
}

void Ball::render()
{
    _window->draw(_sprite);
}

void Ball::setVelocity(float coeff, float duration)
{
    _velocity = coeff * VELOCITY;
    _timeWithPowerupEffect = duration;
}

void Ball::setFireBall(float duration)
{
    if (duration) 
    {
        _isFireBall = true;
        _timeWithPowerupEffect = duration;        
        return;
    }
    _isFireBall = false;
    _timeWithPowerupEffect = 0.f;    
}

void Ball::randomSpawn(sf::CircleShape &_sprite) {

    //a vector of pairs that contains ball spawn details (x pos, direction)
    std::vector<std::pair<float, float>> spawnVec = {
        {100, 1}, //left
        {490, 0}, //middle
        {880, -1} //right
    };

    srand(time(0)); //setting seed value to get random vals each time game is run
    int randSpawn = (rand() % 3); //getting a random value between 0 and 3

    //setting position and direction of the ball based off of random spawnVec values
    _sprite.setPosition(spawnVec[randSpawn].first, 300);
    _direction.x = { spawnVec[randSpawn].second };
    
    //debuggin
    std::cout << "X Coord: " << spawnVec[randSpawn].first << "\n";
    std::cout << "X Dir: " << spawnVec[randSpawn].second << "\n";
    std::cout << "Random Number: " << randSpawn << "\n";
}

sf::FloatRect Ball::getBounds() const
{
    return _sprite.getGlobalBounds();
}