/**
  * @file cursor.cc
  * @brief cursor file of the game
  * @details that is use to establish a visual cursor at map
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#include <cursor.h>
#include <tile.h>

Cursor::Cursor(){

  tile_aiming_ = 0;
  mouse_pos_ = {0.0f, 0.0f};
  size_ = {0.0f, 0.0f};
  default_color_ = sf::Color::White;

}

Cursor::~Cursor(){

}

void Cursor::init(sf::Vector2f size){

  size_ = size;

  cursor_shape_.setSize({size.x, size.y});
  cursor_shape_.setFillColor(sf::Color(0, 0, 0, 0));
  cursor_shape_.setOutlineThickness(2);
  cursor_shape_.setOutlineColor(default_color_);

}

void Cursor::input(sf::RenderWindow& window){

  mouse_pos_ = (sf::Vector2f)window.mapPixelToCoords(
    sf::Mouse::getPosition(window)
  );

}

void Cursor::attackMode(uint8_t change_color_){

  if(change_color_){

    if(cursor_shape_.getOutlineColor() == default_color_){

      cursor_shape_.setOutlineColor(sf::Color::Red);

    }

  } else {

    cursor_shape_.setOutlineColor(default_color_);

  }

}

void Cursor::update(Tile& tile){

  sf::FloatRect boundingbox;

  boundingbox = tile.get_debugTile().getGlobalBounds();

  if(boundingbox.contains(mouse_pos_) && tile.walkable_){

    cursor_shape_.setPosition({tile.pos_.x, tile.pos_.y});

    tile_aiming_ = tile.tile_id_;

  }

}

void Cursor::draw(sf::RenderWindow& window){

  window.draw(cursor_shape_);

}
