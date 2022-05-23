/**
  * @file item_manager.h
  * @brief item_manager file of the game
  * @details This is the file which we use for item_manager of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __ITEMMANAGER_H__
#define __ITEMMANAGER_H__

#include <SFML/Graphics.hpp>
#include <mka_list.h>
#include "sprite.h"

class Item;

class ItemManager{

public:

  ItemManager();

  ~ItemManager();

  MKA::List* item_list_;

private:


};

#endif //!__ITEMMANAGER_H__
