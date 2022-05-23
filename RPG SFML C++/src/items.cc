/*
File: item.h
Author: Adam Álvarez Enfedal
Description: item class implementation
*/

#include <SFML/Graphics.hpp>
#include "items.h"
#include <sprite.h>
#include <character.h>

Item::Item()
{

  sprite_ = nullptr;
  hp_ = 0.0f;
  mana_ = 0.0f;
  attack_ = 0.0f;
  defense_ = 0.0f;
  critp_ = 0.0f;
  dropped_ = 0;
  item_coins_ = 0;
  usable_ = 0;


}

Item::~Item(){
  if(nullptr != sprite_){
    delete sprite_;
  }
}

void Item::init(int health,
                int defense,
                int attack,
                int mana,
                int crit_attack,
                uint8_t legendary_item,
                uint8_t dropped_item,
                int item_coins){
     hp_ = (float)health;
     defense_ = (float)defense;
     attack_ = (float)attack;
     mana_ = (float)mana;
     critp_ = (float)crit_attack;
     legendary_ = legendary_item;
     usable_ = dropped_item;
     item_coins_ = item_coins;
          }

void Item::initItem(const char* sprite_address)

{

  texture_ = Texture::CreateTexture();
  texture_->set_TextureFromFile(sprite_address);
  sprite_ = new Sprite();
  sprite_->initSprite(*texture_);
  sprite_->set_position(sf::Vector2f(0.0f,0.0f));

}

void Item::draw(sf::RenderWindow& window)
{

  window.draw(sprite_->sprite_);

}
