/**
  * @file cursor.h
  * @brief cursor file of the game
  * @details that is use to establish a visual cursor at map
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __CURSOR_H__
#define __CURSOR_H__

#include <gameobject.h>

class Tile;

class Cursor : public GameObject{

public:

  Cursor();

  ~Cursor();

  void init(sf::Vector2f size);

  void input(sf::RenderWindow&);

  void update(Tile& tile);

  void draw(sf::RenderWindow&) override;

  void attackMode(uint8_t);

  int tile_aiming_;

private:

  sf::RectangleShape cursor_shape_;
  sf::Vector2f mouse_pos_;
  sf::Vector2f size_;
  sf::Color default_color_;

};


#endif //!__CURSOR_H__
