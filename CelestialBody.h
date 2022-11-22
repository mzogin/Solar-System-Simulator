#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

const int winWidth = 1000;
const int winHeight = 1000;
const double gravity = 6.67e-11;

class CelestialBody : public sf::Drawable {
public:
  CelestialBody();
  CelestialBody(double x, double y, double xv, double yv, double m, double rad,
                std::string name);

  void setRadius(double rad);
  void setPosition();
  void setVelocity(double x, double y);

  void setForces(double x, double y);

  void step(double seconds);

  friend istream &operator>>(istream &input, CelestialBody &bod);
  friend ostream &operator<<(ostream &output, CelestialBody &bod);

  double xPos, yPos;
  double mass;

private:
  void virtual draw(sf::RenderTarget &target, sf::RenderStates states) const;
  double xVel, yVel;
  double radius;
  double xForce, yForce;
  double xAccel, yAccel;

  string filename;

  sf::Image img;
  sf::Sprite spr;
  sf::Texture tex;
};

double getForceX(CelestialBody &bod1, CelestialBody &bod2);
double getForceY(CelestialBody &bod1, CelestialBody &bod2);

#endif
