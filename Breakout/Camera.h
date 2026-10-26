#ifndef CAMERA_HPP
#define CAMERA_HPP

#define CAMERA_SHAKE_ANGLE 10.0f
#define CAMERA_SHAKE_OFFSET 20.0f

#include <SFML/Graphics.hpp>


//struct for animation
struct CameraAnimation {
  sf::Time current;
  sf::Time max;
  float strength;
};


class Camera {
public:

  Camera(sf::RenderWindow* window);
  void shake(float strength, float duration_ms);
  void update(float dt);
  void reset();

private:
	//camera/view params
  CameraAnimation _animation;
  sf::RenderWindow* _window;
  sf::View _view;
  sf::Vector2f _center;
};

#endif
