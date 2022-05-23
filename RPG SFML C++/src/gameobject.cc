/**
  * @file gameobject.h
  * @brief gameobject file of the game
  * @details File that is use to gameobject
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#include <gameobject.h>

int GameObject::next_id_ = 0;

GameObject::GameObject(){

  enable_ = 1;
  id_ = next_id_;
  next_id_++;

}

GameObject::~GameObject(){

  id_--;

}


void GameObject::init(uint8_t status){ enable_ = status; }

void GameObject::set_ActiveStatus(uint8_t newstatus){ enable_ = newstatus; }

uint8_t GameObject::get_ActiveStatus(){ return enable_; }

int GameObject::get_id(){ return id_; }
