#include "CelestialBody.h"
// constructor will initialize private data memberst
// as well as load the image into new texture obj, then make a sprite with that
// texture

CelestialBody::CelestialBody() { return; }

CelestialBody::CelestialBody(double x, double y, double xv, double yv, double m,
                             double rad, string name) {
  xPos = x;
  yPos = y;
  xVel = xv;
  yVel = yv;
  mass = m;
  radius = rad;
  filename = name;

  if (!img.loadFromFile(filename)) // check to make sure file opens
  {
    return;
  }

  tex.loadFromImage(img);

  spr.setTexture(tex);

  spr.setPosition(sf::Vector2f(xPos, yPos));
}

void CelestialBody::draw(sf::RenderTarget &target,
                         sf::RenderStates states) const {
  target.draw(spr);
}

void CelestialBody::setRadius(double rad) { radius = rad; }

void CelestialBody::setPosition() {
  double xPosScreen = ((xPos / radius) * (winWidth / 2)) + (winWidth / 2);
  double yPosScreen = - ((yPos / radius) * (winHeight / 2)) + (winHeight / 2);
  spr.setPosition(sf::Vector2f(xPosScreen, yPosScreen));//only change the position on screen
}

void CelestialBody::setVelocity(double x, double y) {
  xVel = x;
  yVel = y;
}

void CelestialBody::setForces(double x, double y) {
  xForce = x;
  yForce = y;
}

void CelestialBody::step(double seconds) {
  xAccel = xForce / mass;
  yAccel = yForce / mass;
  xVel = xVel + (xAccel * seconds);
  yVel = yVel + (yAccel * seconds);
  xPos = xPos + (xVel * seconds);
  yPos = yPos + (yVel * seconds);
}

// operator to read in universe file and set up the celestial bodies
istream &operator>>(istream &input, CelestialBody &bod) {
  // take input in order of the txt file
  input >> bod.xPos >> bod.yPos;
  input >> bod.xVel >> bod.yVel;
  input >> bod.mass >> bod.filename;

  if (!bod.img.loadFromFile(
          bod.filename)) // exit with input if file does not load
  {
    return input;
  }

  bod.tex.loadFromImage(bod.img); // repeat same steps as in constructor
  bod.spr.setTexture(bod.tex);
  bod.spr.setPosition(sf::Vector2f(bod.xPos, bod.yPos));

  return input;
}

ostream &operator<<(ostream &output, CelestialBody &bod) {
  //output << "Filename: " << bod.filename << std::endl;
  //output << "Pos X: " << bod.xPos << std::endl;
  //output << "Pos Y: " << bod.yPos << std::endl;
  //output << "Vel X: " << bod.xVel << std::endl;
  //output << "Vel Y: " << bod.yVel << std::endl;
  
  output << setw(12) << bod.xPos << " " << setw(12) << bod.yPos << " ";
  output << setw(10) << bod.xVel << " " << setw(10) << bod.yVel << " ";
  output << setw(12) << bod.mass << " " << setw(12) << bod.filename;
  return output;
}
//finds x component of force between 2 bodies
double getForceX(CelestialBody &bod1, CelestialBody &bod2) {
  double distX = bod2.xPos - bod1.xPos;
  double distY = bod2.yPos - bod1.yPos;
  double r2 = pow(distX, 2) + pow(distY, 2);
  double r = sqrt(r2);
  double force = (gravity * bod1.mass * bod2.mass) / r2;
  double forceX = force * (distX / r);
  return forceX;
}
//finds y component of force
double getForceY(CelestialBody &bod1, CelestialBody &bod2) {
  double distX = bod2.xPos - bod1.xPos;
  double distY = bod2.yPos - bod1.yPos;
  double r2 = pow(distX, 2) + pow(distY, 2);
  double r = sqrt(r2);
  double force = (gravity * bod1.mass * bod2.mass) / r2;
  double forceY = force * (distY / r);
  return forceY;
}
