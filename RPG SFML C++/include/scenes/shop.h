/**
  * @file shop.h
  * @brief shop file of the game
  * @details This is the file which we use for shop scene
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __SHOP_H__
#define __SHOP_H__ 1

#include <SFML/Graphics.hpp>
#include "label.h"
#include <scene.h>
#include <sprite.h>
#include <texture.h>
#include <items.h>

/** forward declarations */
class Character;
class Item;

class Shop : public Scene{

public:

  Shop();

  virtual ~Shop();

  void init() override;

  void input() override;

  void update() override;

  /** @brief Establishes the item`upgrade
  *
  *   Establishes the item`s upgrade on every characyers playable
  *   on the game. This function use the character getters and
  *   add the upgrade of each item.
  *
  *   @return nothing
  *
  *   @param character The character datatype to call it and use it functions.
  *   @param item The item datatype to call it and use it functions.
  */

  void payItems(Item& item);

private:
  /** @var pointer for the class Item forward declaration */
  Item* item_[12];
	/** @var pointer for the class Texture forward declaration */
  Texture* bilal_texture_;
  /** @var pointer for the class Sprite forward declaration */
  Sprite *bilal_sprite_;
	/** @var pointer for the class Texture forward declaration */
  Texture* coin_texture_;
  /** @var pointer for the class Sprite  forward declaration */
  Sprite *coin_sprite_[12];
	/** @var Character list */
  MKA::List* char_list_;
	/** @var pointer for the class Label forward declaration */
  Label* label_[25];

  Texture* texture_mogu_;
  Sprite* mogu_;
  Label* exit_;


};

#endif
