// AUTHOR : ANDRES
#ifndef __INV_H__
#define __INV_H__ 1

#include <SFML/Graphics.hpp>
#include <gameobject.h>
#include <mka_list.h>
#include <stdint.h>

class Inventory : public GameObject{

public:

  Inventory();

  virtual ~Inventory();

  void init(const int rows, const int cols,
            const sf::Vector2f init_pos);

  void draw(sf::RenderWindow& window) override;

  // Inventory(int patatasconbacon);
  //
  // void assignItemSlot(int inventory_position);
  //
  // void MoveItemToInventory(/*Item.map_position_ == character.map_position_*/);

protected:

  MKA::List* inventory_;
  //int inventory_position_;

private:


};

#endif //!__INV_H__
