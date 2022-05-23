/*
File: tile.h
Author: Alvaro Vazquez
Description: tile implementation
*/

#include <tile.h>

Tile::Tile(){

  debug_tile_ = nullptr;
  debug_tile_num_ = nullptr;
  range_tile_ = nullptr;
  walkable_ = 1;
  pos_ = {0.0f, 0.0f};
  size_ = {0.0f, 0.0f};
  tile_id_ = 0;
  item_id_ = -1;
  character_id_ = -1;
  draw_debug_ = 0;
  in_range_ = 0;
  manhattan_dis_ = 0;

}

Tile::~Tile(){

  if(nullptr != debug_tile_){
    delete debug_tile_;
  }

  if(nullptr != debug_tile_num_){
    delete debug_tile_num_;
  }

  if(nullptr != range_tile_){
    delete range_tile_;
  }

}

void Tile::init(sf::Vector2f pos, sf::Vector2f size, int temp_id,
  sf::Font& font, uint8_t walkable){

    size_ = size;
    pos_ = pos;
    tile_id_ = temp_id;

  if(nullptr == debug_tile_){

    debug_tile_ = new sf::RectangleShape();
    debug_tile_->setPosition(pos_);
    debug_tile_->setSize(size_);
    debug_tile_->setOutlineThickness(1);
    debug_tile_->setFillColor(sf::Color(0, 0, 0, 0));

  }

  if(nullptr == range_tile_){

    range_tile_ = new sf::RectangleShape();
    range_tile_->setPosition(pos_);
    range_tile_->setSize(size_);
    range_tile_->setOutlineThickness(1);
    range_tile_->setFillColor(sf::Color(0, 0, 255, 100));

  }

  if(nullptr == debug_tile_num_){

    debug_tile_num_ = new sf::Text();
    debug_tile_num_->setString(std::to_string(tile_id_));
    debug_tile_num_->setScale(0.4f, 0.4f);
    debug_tile_num_->setPosition(pos_);
    debug_tile_num_->setFont(font);

  }

  walkable_ = walkable;

}

sf::RectangleShape& Tile::get_debugTile(){

  return *debug_tile_;

}

void Tile::drawRange(sf::RenderWindow& window){

  window.draw(*range_tile_);

}

void Tile::draw(sf::RenderWindow& window){

  if(walkable_){

    debug_tile_->setOutlineColor(sf::Color(0, 255, 0));

  } else {

    debug_tile_->setOutlineColor(sf::Color(255, 0, 0));

  }

  window.draw(*debug_tile_num_);
  window.draw(*debug_tile_);

}
