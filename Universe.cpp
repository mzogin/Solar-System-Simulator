#include "CelestialBody.h"
#include <memory>
#include <vector>

int main(int argc, char *argv[]) {

  if (argc != 3) {
    return -1;
  }
  std::string simulation_Time(argv[1]);
  std::string step_Time(argv[2]);
  std::string::size_type sz;

  cout << "Simulation time: " << simulation_Time << endl;
  cout << "Step time: " << step_Time << endl;

  double totalTime = std::stod(simulation_Time, &sz); //, &sz
  double stepTime = std::stod(step_Time, &sz);        //, &sz
  double simTime = 0.0;

  std::string planets, rad;

  std::cin >> planets;
  std::cin >> rad;

  int numPlanets = std::stoi(planets.c_str());
  double radius = std::stod(rad.c_str());

  cout << "Number of planets: " << numPlanets << endl;
  cout << "Radius: " << radius << endl;

  std::vector<std::unique_ptr<CelestialBody>> bodies;

  for (int i = 0; i < numPlanets; i++) {
    CelestialBody *temp = new CelestialBody();

    cin >> *temp;
    temp->setRadius(radius);
    temp->setPosition();
    //cout << *temp << endl;

    bodies.push_back(unique_ptr<CelestialBody>(temp));
  }

  sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Solar System");

  window.setFramerateLimit(60);
  sf::Image background;

  if (!background.loadFromFile("background.jpg")) {
    return -1;
  }

  sf::Music music;
  if(!music.openFromFile("2001.wav"))//make sure music file opens
  {
	  return -1;
  }
  music.play();

  //for displaying elapsed time
  sf::Font timeFont;
  if(!timeFont.loadFromFile("arial.ttf"))
  {
	  return -1;
  }
  sf::Text timeText;
  timeText.setFont(timeFont);
  timeText.setCharacterSize(15);
  timeText.setFillColor(sf::Color::White);

  sf::Texture backTex;
  backTex.loadFromImage(background);
  sf::Sprite backSprite;
  backSprite.setTexture(backTex);
  
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear();
    window.draw(backSprite);

    for (auto itr = bodies.begin(); itr != bodies.end(); itr++) {
      window.draw(*itr->get());
      timeText.setString("Elapsed time: " + to_string(simTime));
      window.draw(timeText);

      //cout << *itr->get() << endl;

      double forceX = 0;
      double forceY = 0;
      //sum up the x and y forces on each body
      for (auto itr2 = bodies.begin(); itr2 != bodies.end(); itr2++) {
        if (itr != itr2) {
          forceX += getForceX(*itr->get(), *itr2->get());
          forceY += getForceY(*itr->get(), *itr2->get());
        }
      }
      (*itr)->setForces(forceX, forceY);

      (*itr->get()).step(stepTime);
      // cout << *itr->get() << endl;
      (*itr->get()).setPosition();
      //cout << *itr->get() << endl;
    }
    window.display();

    simTime += stepTime;
    if (simTime >= totalTime) // end of simulation
    {
      break;
    }
  }

  //debugging
  cout << "\n\nFinal postitions:\n" << endl;
  cout << numPlanets << endl;
  cout << radius << endl;
  for(auto i = bodies.begin(); i != bodies.end(); i++)
  {
	  cout << *i->get() << endl;
	  
  }
  return 0;
}
