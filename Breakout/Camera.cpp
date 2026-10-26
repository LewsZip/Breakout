#include "Camera.h"

#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>


// Return a number in |-1, 1]
static inline float randn(void) {
  return -1+2*((float)rand()) / RAND_MAX;
}

Camera::Camera(sf::RenderWindow* window): _animation() {

  // Initialize randomizer
  srand(time(0));

  // Retrieve SFML window and the associated view
  _window = window;
  _view = _window->getView();

  // Compute and set the view center
  sf::Vector2u size = window->getSize();
  _center = sf::Vector2f(size.x/2, size.y/2);
  _view.setCenter(_center);

  //call to reset camera angle to 0 whenever initialized
  reset();
}


void Camera::shake(float strength, float duration_ms) {

  // Set animation parameters
  _animation.max = sf::milliseconds(duration_ms);
  _animation.current = sf::seconds(0);

  // Trauma is inscreased each time this function is called: several calls increase shaking
  _animation.strength += strength;
}


void Camera::update(float dt) {

  // Don't do anythin if animation is finished...
  if (  _animation.current >= _animation.max) {
    return;
  }

  // ... otherwise compute a random angle...
  double angle = CAMERA_SHAKE_ANGLE * _animation.strength * randn();

  // ... and a random XY-offset...
  sf::Vector2f offset;
  offset.x = CAMERA_SHAKE_OFFSET * _animation.strength * randn();
  offset.y = CAMERA_SHAKE_OFFSET * _animation.strength * randn();

  // ... and appply them to the view
  _view.setRotation(angle);
  _view.setCenter(_center+offset);
  _window->setView(_view);

  // Update animation time
  _animation.current += sf::seconds(dt);

  // Decrease trauma parameter depending on time (squared)
  float ratio = _animation.current.asSeconds() / _animation.max.asSeconds();
  _animation.strength *= 1.0 - ratio*ratio;
}

void Camera::reset() {
    // ... and appply them to the view
    _view.setRotation(0);
    _view.setCenter(_center);
    _window->setView(_view);
}
