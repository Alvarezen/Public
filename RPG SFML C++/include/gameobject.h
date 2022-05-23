/**
  * @file gameobject.h
  * @brief gameobject file of the game
  * @details File that is use to gameobject
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __GO_H__
#define __GO_H__ 1

#include <SFML/Graphics.hpp>

class GameObject{

public:

  GameObject();

  virtual ~GameObject();

  void init(uint8_t status);

  void set_ActiveStatus(uint8_t);
  uint8_t get_ActiveStatus();

  int get_id();

  virtual void draw(sf::RenderWindow& window) = 0;

protected:

  uint8_t enable_;

private:

  int id_;
  static int next_id_;

};

#endif //!__GO_H__
