/**
  * @file item.h
  * @brief item file of the game
  * @details This is the file which we use for item of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __ITE_H__
#define __ITE_H__ 1

#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "texture.h"
#include "gameobject.h"


class Sprite;
class Character;

class Item : public GameObject{

public:

  Item();

  ~Item();
  /** @var Use it for the health points of the items*/
  float hp_;
  /** @var Use it for the mana points of the items*/
  float mana_;
  /** @var Use it for the attack points of the items*/
  float attack_;
  /** @var Use it for the defense points of the items*/
  float defense_;
  /** @var Use it for the critp points of the items*/
  float critp_;
  /** @var Use it for the cost of the items`s coins*/
  int item_coins_;
  /** @var Use it to know if item is dropped/bought or not*/
  uint8_t dropped_;
  /** @var Use it to know if item is legendary or not*/
  uint8_t legendary_;
  /** @var Use it to know if item is ussable for any character or not*/
  uint8_t usable_;

  Sprite* sprite_;
  Texture* texture_;

  /** @brief Initilization the Item attributes
  *
  *   Initialization the Item attributes for using on
  *   playable characters of the game.
  *   It has the parameters we need to use for the items.
  *
  *   @return nothing
  *
  *   @param item The vector2f for initial position on the map
  *   @param hp Establishes the initial health points of this character
  *   @param mana Establishes the initial mana of this character
  *   @param attack Establishes the initial attack points of this character
  *   @param defense Establishes the initial defense of this character
  *   @param criattack Establishes the initial critical attack points of this character
  *   @param critp Establishes the initial level of the character
  *   @param critd Establishes the initial level of the character
  *   @param dropped Establishes the move on the map of the character
  *   @param item_coins Put the character life true on the game. We use uint8 like a char
  *   @param legendary Establishes character enum for another thing of the gam.
  *   @param ussable Establishes character enum for another thing of the gam.  *
  */
  void init(int health,
            int defense,
            int attack,
            int mana,
            int crit_attack,
            uint8_t legendary_item,
            uint8_t dropped_item,
            int item_coins);

  void initItem(const char* sprite_address);

  void draw(sf::RenderWindow& window) override;


};

#endif //!__ITEM_H__
