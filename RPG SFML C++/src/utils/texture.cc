/*
File: texture.cc
Author: Saul Vicente Camacho Diaz
Description: texture implementation
*/

#include <texture.h>

Texture::Texture(){

  texture_ = nullptr;

}

Texture::~Texture(){

  if(nullptr != texture_)
  delete texture_;

}

void Texture::set_TextureFromFile(const char* _name, bool is_char){

  if(nullptr == texture_){

    std::string path_;

    texture_ = new sf::Texture();

    if(is_char){

      path_ += "../data/sprites/characters/sprite_sheet_";
      path_ += _name;
      path_ += ".png";

    } else {

      path_ += _name;

    }

    if(!texture_->loadFromFile(path_)){
      return;
    }

  }

}

void Texture::set_TextureFromBuffer(const sf::Vector2i size){

  if(nullptr == texture_){

    texture_ = new sf::Texture();
    if(!texture_->create(size.x, size.y)){
      return;
    }
  }
}

sf::Sprite& Texture::get_SubSprite(sf::Vector2f _reqFrame, float _col, float _row){

  sf::Sprite* sprite = new sf::Sprite();

  nCol = _col;
  nRow = _row;

  framePixelSize_ = sf::Vector2f(texture_->getSize().x / nCol, texture_->getSize().y / nRow);

  requiredFrame_ = _reqFrame;

  sf::IntRect rect((int)requiredFrame_.x * (int)framePixelSize_.x,
                   (int)requiredFrame_.y * (int)framePixelSize_.y,
                   (int)framePixelSize_.x, (int)framePixelSize_.y);

  sprite->setTexture(*texture_);
  sprite->setTextureRect(rect);
  return *sprite;

}

sf::Sprite& Texture::get_Sprite(){

  sf::Sprite* sprite = new sf::Sprite();
  sprite->setTexture(*texture_);
  return *sprite;

}

Texture* Texture::CreateTexture(){

    Texture* ptrtexture = new Texture();
    return ptrtexture;

  }
