// AUTHOR : ANDRES
#include <inventory.h>
#include <inventory_slot.h>

Inventory::Inventory(){

  inventory_ = nullptr;

}

Inventory::~Inventory(){

  if(nullptr != inventory_)
  MKA::EraseList(&inventory_);

}

void Inventory::init(const int rows, const int cols,
  const sf::Vector2f init_pos){

  float offset_x = init_pos.x;
  float offset_y = init_pos.y;

  InventorySlot* newslot = nullptr;

  for(int j = 0 ; j < cols ; ++j){

    for(int i = 0 ; i < rows ; ++i){

      newslot = new InventorySlot();

      newslot->init({offset_x, offset_y}, {70.0f, 70.0f});

      MKA::InsertNodeList(&inventory_, (void*)newslot);

      offset_x += newslot->rect_slot_.getSize().x;

    }

    offset_x = init_pos.x;
    offset_y += newslot->rect_slot_.getSize().y;

  }

}

void Inventory::draw(sf::RenderWindow& window){

  InventorySlot* slot = nullptr;

  for(int i = 0 ; i < MKA::ListSize(inventory_) ; ++i){

    slot = (InventorySlot*)MKA::IndexListInfo(inventory_, i);

    window.draw(slot->rect_slot_);

  }

}

// Inventory::Inventory(int inventory_position){
//     inventory_position = -1;
//     inventory_position_ = inventory_position;
// }
//
// void Inventory::assignItemSlot(int inventory_position){
//   inventory_position_ = inventory_position;
// }
//
// void Inventory::MoveItemToInventory(){
//
//   /*if(Item.map_position_ == character.map_position_){
//       quitar item del mapa;
//       assignItemSlot(int inventory_position);
//   }*/
// }
//
// /* COMO DIBUJAR EL ITEM EN EL MAIN
//   if(item.inventory_position_ > -1){
//   draw item en su item slot;
//   }else{
//   draw item en su map position;
//   }
// */
