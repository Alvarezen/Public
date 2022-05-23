/*
File: shop.h
Author: Adam Álvarez Enfedal
Description: shop class implementation
*/

#include <string.h>
#include <shop.h>
#include <character.h>
#include <scene.h>
#include <game.h>
#include "gamemanager.h"


Shop::Shop()
{
  char_list_ = nullptr;
}

Shop::~Shop()
{
  MKA::EraseList(&char_list_);

  for(int i = 0;i<12;i++){
    if(nullptr != item_[i]){
      delete item_[i];
    }
  }
  for(int i = 0;i<25;i++){
    if(nullptr != label_[i]){
      delete label_[i];
    }
  }
  if(nullptr != bilal_texture_){
    delete bilal_texture_;
  }
  if(nullptr != bilal_sprite_){
    delete bilal_sprite_;
  }
  if(nullptr != coin_texture_){
    delete coin_texture_;
  }
  for(int i = 0;i<12;i++){
    if(nullptr != coin_sprite_[i]){
      delete coin_sprite_[i];
    }
  }

}

void Shop::init()
{

  GameManager& gm = GameManager::Instance();
  gm.init();

  gm.set_charactersFromDatabase(&char_list_);


  MKA::List* item_list = gm.get_itemsDataFromDatabase();

  for(int i=0;i<MKA::ListSize(item_list);i++){
    item_[i] = (Item*) MKA::IndexListInfo(item_list,i);
  }
  item_[0]->initItem("../data/sprites/items/keyboard.png");
  item_[0]->sprite_->set_position(sf::Vector2f(220.0f,700.0f));
  item_[1]->initItem("../data/sprites/items/notepad++.png");
  item_[1]->sprite_->set_position(sf::Vector2f(400.0f,700.0f));
  item_[2]->initItem("../data/sprites/items/atom.png");
  item_[2]->sprite_->set_position(sf::Vector2f(580.0f,700.0f));
  item_[3]->initItem("../data/sprites/items/cocos2d.png");
  item_[3]->sprite_->set_position(sf::Vector2f(760.0f,700.0f));
  item_[4]->initItem("../data/sprites/items/maya.png");
  item_[4]->sprite_->set_position(sf::Vector2f(940.0f,700.0f));
  item_[5]->initItem("../data/sprites/items/photoshop.png");
  item_[5]->sprite_->set_position(sf::Vector2f(1120.0f,700.0f));
  item_[6]->initItem("../data/sprites/items/rpggm.png");
  item_[6]->sprite_->set_position(sf::Vector2f(220.0f,850.0f));
  item_[7]->initItem("../data/sprites/items/sql.png");
  item_[7]->sprite_->set_position(sf::Vector2f(400.0f,850.0f));
  item_[8]->initItem("../data/sprites/items/tiledmap.png");
  item_[8]->sprite_->set_position(sf::Vector2f(580.0f,850.0f));
  item_[9]->initItem("../data/sprites/items/unreal.png");
  item_[9]->sprite_->set_position(sf::Vector2f(760.0f,850.0f));
  item_[10]->initItem("../data/sprites/items/visual.png");
  item_[10]->sprite_->set_position(sf::Vector2f(940.0f,850.0f));
  item_[11]->initItem("../data/sprites/items/zbrush.png");
  item_[11]->sprite_->set_position(sf::Vector2f(1120.0f,850.0f));

  for(int i=0;i<12;i++){
    item_[i]->sprite_->set_boxBounds();
    MKA::InsertNodeList(&gameobject_list_, (void*)item_[i]->sprite_);
  }

  coin_texture_ = gm.get_textureFromDatabaseWithTag("distincoin");

  for(int i=0;i<12;i++){
    coin_sprite_[i] = new Sprite();
    coin_sprite_[i]->initSprite(*coin_texture_);
  }

  coin_sprite_[0]->sprite_.setPosition(320.0f,715.0f);
  coin_sprite_[1]->sprite_.setPosition(500.0f,715.0f);
  coin_sprite_[2]->sprite_.setPosition(680.0f,715.0f);
  coin_sprite_[3]->sprite_.setPosition(860.0f,715.0f);
  coin_sprite_[4]->sprite_.setPosition(1040.0f,715.0f);
  coin_sprite_[5]->sprite_.setPosition(1220.0f,715.0f);
  coin_sprite_[6]->sprite_.setPosition(320.0f,865.0f);
  coin_sprite_[7]->sprite_.setPosition(500.0f,865.0f);
  coin_sprite_[8]->sprite_.setPosition(680.0f,865.0f);
  coin_sprite_[9]->sprite_.setPosition(860.0f,865.0f);
  coin_sprite_[10]->sprite_.setPosition(1040.0f,865.0f);
  coin_sprite_[11]->sprite_.setPosition(1220.0f,865.0f);

  for(int i=0;i<12;i++){
    coin_sprite_[i]->sprite_.setScale(0.5f,0.5f);
    // coin_sprite_->sprite_.set_boxBounds();
    coin_sprite_[i]->sprite_.setOrigin(
      coin_sprite_[i]->sprite_.getLocalBounds().width*0.5f,
      coin_sprite_[i]->sprite_.getLocalBounds().height*0.4f);
      MKA::InsertNodeList(&gameobject_list_, (void*)coin_sprite_[i]);
  }


  bilal_texture_ = gm.get_textureFromDatabaseWithTag("bilal");
  bilal_sprite_ = new Sprite();
  bilal_sprite_->initSprite(*bilal_texture_);
  bilal_sprite_->sprite_.setPosition((float)GameManager::s_windowWidth_/3,
      (float)GameManager::s_windowHeight_/4);
  bilal_sprite_->sprite_.setScale(2.0f,2.0f);
  bilal_sprite_->sprite_.setOrigin(
    bilal_sprite_->sprite_.getLocalBounds().width*0.5f,
    bilal_sprite_->sprite_.getLocalBounds().height*0.4f);
  MKA::InsertNodeList(&gameobject_list_, (void*)bilal_sprite_);

  for(int i = 0; i<25; i++){
    label_[i] = new Label();
    label_[i]->font_ = *gm.get_fontFromDatabaseWithTag("karmasuture");
  }

  label_[24]->initLabel("Give me my money, get what you need\n" \
    "and let me get back to work.\nAnormal.",
    sf::Vector2f((float)GameManager::s_windowWidth_/3*2,
    (float)GameManager::s_windowHeight_/5),
    sf::Color::White,sf::Color::Black);
  label_[24]->setLabelFont(label_[0]->font_,40);

  // GUSTAVO: Please don't do this:
  // - Do not declare 12 strings named price0, price1, etc... Declare an array
  // of 12 strings like:
  //
  // std::string prices[12];
  //
  // or
  //
  // char prices[5][12];
  //
  // - If you are allocating 3 bytes, please do NOT write 5 bytes in the 
  // snprintf call. You are making a buffer overflow!
  // - All these malloc'ed buffers never get freed: MEMORY LEAK!
  // - These errors are highlighted by the esat_checker script. Please run the
  // esat_checker script! 
  char *price0 = (char*)malloc(3*sizeof(char));
  char *price1 = (char*)malloc(3*sizeof(char));
  char *price2 = (char*)malloc(3*sizeof(char));
  char *price3 = (char*)malloc(3*sizeof(char));
  char *price4 = (char*)malloc(3*sizeof(char));
  char *price5 = (char*)malloc(3*sizeof(char));
  char *price6 = (char*)malloc(3*sizeof(char));
  char *price7 = (char*)malloc(3*sizeof(char));
  char *price8 = (char*)malloc(3*sizeof(char));
  char *price9 = (char*)malloc(3*sizeof(char));
  char *price10 = (char*)malloc(3*sizeof(char));
  char *price11 = (char*)malloc(3*sizeof(char));
  snprintf(price0,5*sizeof(char),"%d",item_[0]->item_coins_);
  snprintf(price1,5*sizeof(char),"%d",item_[1]->item_coins_);
  snprintf(price2,5*sizeof(char),"%d",item_[2]->item_coins_);
  snprintf(price3,5*sizeof(char),"%d",item_[3]->item_coins_);
  snprintf(price4,5*sizeof(char),"%d",item_[4]->item_coins_);
  snprintf(price5,5*sizeof(char),"%d",item_[5]->item_coins_);
  snprintf(price6,5*sizeof(char),"%d",item_[6]->item_coins_);
  snprintf(price7,5*sizeof(char),"%d",item_[7]->item_coins_);
  snprintf(price8,5*sizeof(char),"%d",item_[8]->item_coins_);
  snprintf(price9,5*sizeof(char),"%d",item_[9]->item_coins_);
  snprintf(price10,5*sizeof(char),"%d",item_[10]->item_coins_);
  snprintf(price11,5*sizeof(char),"%d",item_[11]->item_coins_);

  label_[1]->initLabel(price0,
    sf::Vector2f(360.0f,715.0f),
    sf::Color::White,sf::Color::Black);
  label_[1]->setLabelFont(label_[1]->font_,20);
  label_[2]->initLabel(price1,
    sf::Vector2f(540.0f,715.0f),
    sf::Color::White,sf::Color::Black);
  label_[2]->setLabelFont(label_[1]->font_,20);
  label_[3]->initLabel(price2,
    sf::Vector2f(720.0f,715.0f),
    sf::Color::White,sf::Color::Black);
  label_[3]->setLabelFont(label_[1]->font_,20);
  label_[4]->initLabel(price3,
    sf::Vector2f(900.0f,715.0f),
    sf::Color::White,sf::Color::Black);
  label_[4]->setLabelFont(label_[1]->font_,20);
  label_[5]->initLabel(price4,
    sf::Vector2f(1080.0f,715.0f),
    sf::Color::White,sf::Color::Black);
  label_[5]->setLabelFont(label_[1]->font_,20);
  label_[6]->initLabel(price5,
    sf::Vector2f(1260.0f,715.0f),
    sf::Color::White,sf::Color::Black);
  label_[6]->setLabelFont(label_[1]->font_,20);
  label_[7]->initLabel(price6,
    sf::Vector2f(360.0f,865.0f),
    sf::Color::White,sf::Color::Black);
  label_[7]->setLabelFont(label_[1]->font_,20);
  label_[8]->initLabel(price7,
    sf::Vector2f(540.0f,865.0f),
    sf::Color::White,sf::Color::Black);
  label_[8]->setLabelFont(label_[1]->font_,20);
  label_[9]->initLabel(price8,
    sf::Vector2f(720.0f,865.0f),
    sf::Color::White,sf::Color::Black);
  label_[9]->setLabelFont(label_[1]->font_,20);
  label_[10]->initLabel(price9,
    sf::Vector2f(900.0f,865.0f),
    sf::Color::White,sf::Color::Black);
  label_[10]->setLabelFont(label_[1]->font_,20);
  label_[11]->initLabel(price10,
    sf::Vector2f(1080.0f,865.0f),
    sf::Color::White,sf::Color::Black);
  label_[11]->setLabelFont(label_[1]->font_,20);
  label_[12]->initLabel(price11,
    sf::Vector2f(1260.0f,865.0f),
    sf::Color::White,sf::Color::Black);
  label_[12]->setLabelFont(label_[1]->font_,20);



  for(int i = 0; i<25; i++){
    label_[i]->getTextBox();
    label_[i]->centerText();
    MKA::InsertNodeList(&gameobject_list_, (void*)label_[i]);

  }


  texture_mogu_ = Texture::CreateTexture();
  texture_mogu_->set_TextureFromFile(
    "../data/sprites/mogu/mogu.png");

  mogu_ = new Sprite();
  mogu_->initSprite(*texture_mogu_);
  mogu_->sprite_.setPosition(1750,100);
  mogu_->sprite_.setOrigin(
  mogu_->sprite_.getLocalBounds().width*0.5f,
    0);
  mogu_->set_boxBounds();
  MKA::InsertNodeList(&gameobject_list_, (void*)mogu_);

  exit_ = new Label();
  exit_->font_ = *gm.get_fontFromDatabaseWithTag("karmasuture");
  exit_->initLabel("EXIT", sf::Vector2f(1718,180),sf::Color::White,
                                                sf::Color::Black);
  exit_->setLabelFont(exit_->font_,30);
  exit_->getTextBox();
  MKA::InsertNodeList(&gameobject_list_, (void*)exit_);


  delete &gm;

}

void Shop::input()
{

}

void Shop::update()
{
  for(int i=0;i<12;i++){
    if(item_[i]->sprite_->isClicked(*scene_window_) == 1){
      printf("Item_Clicked\n");
      printf("old dropped : %d\n",   item_[i]->dropped_);

      Character* aux_character = nullptr;
      for(int j = 0 ; j < 2 ; ++j){
        aux_character = (Character*)MKA::IndexListInfo(char_list_, j);
        printf("old attack : %f\n",   aux_character->getAttack());
      }
      payItems(*item_[i]);
      item_[i]->dropped_ = 1;
      printf("new attack : %f\n",   aux_character->getAttack());
      printf("new dropped : %d\n",   item_[i]->dropped_);
    }
  }

  if(mogu_->isClicked(*scene_window_) == 1){
    printf("ADAM TOMATE ESE BOTON\n");
    Game::selected_scene_ = 5;//CHANGE THIS TO CHANGE LOADED SCENE
    Game::change_scene_ = 1;
  }

}

void Shop::payItems(Item& item)
{

  Character* aux_character = nullptr;

  // GameManager& gm = GameManager::Instance();
  //
  // gm.init();
  // gm.set_charactersFromDatabase(&char_list_);

  for(int i = 0 ; i < MKA::ListSize(char_list_) ; ++i){


    aux_character = (Character*)MKA::IndexListInfo(char_list_, i);

    aux_character->setAttack(item.attack_ + aux_character->getAttack());
    aux_character->setDefense(item.defense_ + aux_character->getDefense());
    aux_character->setMaxHp(item.hp_ + aux_character->getMaxHp());
    aux_character->setMaxMana(item.mana_ + aux_character->getMaxMana());
    aux_character->setCriattack(item.critp_ + aux_character->getCriattack());
  }

  // gm.set_charactersToDatabase(char_list_);
  // delete &gm;
}

  // if(character.distincion_coin_ >= item.item_coins_){
  //   if(item.dropped_ != 1){
  // for(int i=0;i<4;i++){
  //   aux_attack[i] = characters_[i].getAttack();
  //   aux_defense[i] = characters_[i].getDefense();
  //   aux_hp[i] = characters_[i].getHp();
  //   aux_mana[i] = characters_[i].getMana();
  //   aux_criattack[i] = characters_[i].getCriattack();
  // }
  // character.distincion_coin_ -= item.item_coins_;
  //   }
  // }
  //
  // if(character.distincion_coin_ >= item.item_coins_){
  //
  //   if(item.dropped_ != 1)
  //   {
  //
  //     aux_attack[i] += item.attack_;
  //     aux_defense += item.defense_;
  //     aux_hp += item.hp_;
  //     aux_mana += item.mana_;
  //     aux_criattack += item.critp_;
  //     characters_[i].setAttack(aux_attack);
  //     character.setDefense(aux_defense);
  //     character.setHp(aux_hp);
  //     character.setMana(aux_mana);
  //     character.setMana(aux_criattack);
  //
  //     character.distincion_coin_ -= item.item_coins_;
  //   }
  // }
