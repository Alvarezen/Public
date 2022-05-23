/*
File: sprite.cc
Author: Saul Vicente Camacho Diaz
Description: sprite implementation
*/

#include <sprite.h>

Sprite::Sprite(){

}

Sprite::~Sprite(){

}

void Sprite::initSprite(const Texture& newtexture){

  sprite_.setTexture(*newtexture.texture_);
}

void Sprite::initSprite(const sf::Sprite& sprite){

  sprite_ = sprite;

}

sf::Color Sprite::getSpritePixel(const char* png_file, const sf::Vector2i coords){

  sf::Image image;
  if (!image.loadFromFile(png_file)){
    return sf::Color(0, 0, 0, 0);
  } else {
    return image.getPixel(coords.x, coords.y);
  }

}

sf::Vector2f Sprite::get_position(){
  return sprite_.getPosition();
}

void Sprite::set_position(sf::Vector2f pos){
  sprite_.setPosition(pos);
}

float Sprite::get_globalWidth(){
  return sprite_.getGlobalBounds().width;
}

float Sprite::get_globalHeight(){
  return sprite_.getGlobalBounds().height;
}

float Sprite::get_localWidth(){
  return sprite_.getLocalBounds().width;
}

float Sprite::get_localHeight(){
  return sprite_.getLocalBounds().height;
}

sf::Vector2f Sprite::get_scale(){
  return sprite_.getScale();
}

void Sprite::set_scale(sf::Vector2f scale){
  sprite_.setScale(scale);
}

sf::Vector2f Sprite::get_origin(){
  return sprite_.getOrigin();
}

void Sprite::set_origin(sf::Vector2f origin){
  sprite_.setOrigin(origin);
}

float Sprite::get_rotation(){
  return sprite_.getRotation();
}

void Sprite::set_rotation(float rot){
  sprite_.setRotation(rot);
}

sf::Sprite Sprite::get_sprite(){
  return sprite_;
}

void Sprite::draw(sf::RenderWindow& window){
    window.draw(sprite_);
}

void Sprite::set_boxBounds(){
  box_.setPosition(sprite_.getPosition());

  box_.setSize(sf::Vector2f(sprite_.getLocalBounds().width,
  sprite_.getLocalBounds().height));
}

int Sprite::isSelected(sf::RenderWindow& window){
  sf::Vector2f mouseworld;
  sf::FloatRect boundingbox;

  mouseworld = window.mapPixelToCoords(
    sf::Mouse::getPosition(window)
  );

  boundingbox = box_.getGlobalBounds();

  if(boundingbox.contains(mouseworld)){
  return 1;
  }else{
    return 0;
  }
}

int Sprite::isClicked(sf::RenderWindow& window){
  if(Sprite::isSelected(window) == 1 &&
      click_.isMouseButtonDown(sf::Mouse::Left) == 1){
  return 1;
  }else{
    return 0;
  }
}
