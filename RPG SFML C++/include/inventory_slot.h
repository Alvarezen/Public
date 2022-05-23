/*
File: inventory_slot.h
Author: Alvaro Vazquez
Description: inventory slot implementation
*/

#ifndef __INVSLOT_H__
#define __INVSLOT_H__ 1

#include <SFML/Graphics.hpp>
#include <stdint.h>
#include <gameobject.h>

class Item;
class Sprite;

class InventorySlot{

public:

  InventorySlot();

  InventorySlot(const InventorySlot&);

  ~InventorySlot();

  void init(const sf::Vector2f pos, const sf::Vector2f size);

  uint8_t set_itemAtSlot(Item&);
  Item& get_itemAtSlot() const;

  uint8_t set_cleanSlot();

  sf::RectangleShape rect_slot_;
  Item* item_;

protected:


private:


};

#endif //!__INVSLOT_H__
