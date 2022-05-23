/**
  * @file inventory_slot.h
  * @brief inventory_slot file of the game
  * @details File that is use to manage the items into a inventory
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#include <inventory_slot.h>
#include <items.h>

InventorySlot::InventorySlot(){

  item_ = nullptr;

}

InventorySlot::InventorySlot(const InventorySlot& invent_slot){

  rect_slot_ = invent_slot.rect_slot_;
  item_ = invent_slot.item_;

}

InventorySlot::~InventorySlot(){

  if(nullptr != item_){
    delete item_;
  }

}

void InventorySlot::init(const sf::Vector2f pos, const sf::Vector2f size){

  rect_slot_.setPosition(pos);
  rect_slot_.setSize(size);
  rect_slot_.setFillColor(sf::Color(0, 0, 0, 0));
  rect_slot_.setOutlineColor(sf::Color(255, 255, 255, 255));
  rect_slot_.setOutlineThickness(1);

}

uint8_t InventorySlot::set_itemAtSlot(Item& item){

  if(item_ == nullptr){

    item_ = new Item();
    item_ = &item;
    //item_->sprite_->setPosition(rect_slot_.getPosition());

    return 1;

  } else {

    return 0;

  }

}

Item& InventorySlot::get_itemAtSlot() const{

  return *item_;

}

uint8_t InventorySlot::set_cleanSlot(){

  if(nullptr != item_){

    delete item_;
    item_ = nullptr;
    return 1;

  } else {

    return 0;

  }

}
