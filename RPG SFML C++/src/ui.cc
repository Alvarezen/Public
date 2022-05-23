// AUTHOR : ANDRES

#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "ui.h"
#include <scene.h>
#include <character.h>


Ui::Ui(){

  list_ = nullptr;
  label_feedback_ = nullptr;
  damage_dealed = 0;

}


void Ui::init(){

  // GameManager& gm = GameManager::Instance();
  // gm.init();
  // gm.set_charactersFromDatabase(&char_list_);

  // MKA::List* item_list = gm.get_itemsDataFromDatabase();
  //
  // for(int i=0;i<MKA::ListSize(item_list);i++){
  //   item_[i] = (Item*) MKA::IndexListInfo(item_list,i);
  // }

  character = new Programmer();
  label_feedback_ = new Label();
  label_feedback_->initLabel("Feedback", sf::Vector2f(20,20),
                    sf::Color::White,sf::Color::Black);
  character->init(100.0f,80.0f,50.0f,40.0f,10.0f);
  // character->chartype_ = Character::kCharactersType_programmer;

  level = (char*)malloc(5*sizeof(char));
  hp = (char*)malloc(7*sizeof(char));
  attack = (char*)malloc(5*sizeof(char));
  defense = (char*)malloc(5*sizeof(char));
  criattack = (char*)malloc(5*sizeof(char));
  feedback = (char*)malloc(5*sizeof(char));

  for(int i=0; i<22 ; i++){
    label_[i] = new Label();
  }

    info_[0] = new Label();

                    //CHARACTERS DETAILS
  label_[0]->initLabel(" ", sf::Vector2f(45,862),
                    sf::Color::White,sf::Color::Black);
  label_[1]->initLabel("LVL :", sf::Vector2f(45,975),
                    sf::Color::White,sf::Color::Black);
  info_[0]->initLabel("Character's level->\nThe higher it" \
                    " gets the stronger it becomes!",
                    sf::Vector2f(45,1035),
                    sf::Color::White,sf::Color::Black);
  label_[2]->initLabel(" ", sf::Vector2f(100,975),
                    sf::Color::White,sf::Color::Black);
                    //STATS
  label_[3]->initLabel("HP", sf::Vector2f(240,890),
                    sf::Color::White,sf::Color::Black);
  label_[4]->initLabel("MANA", sf::Vector2f(240,930),
                    sf::Color::White,sf::Color::Black);
  label_[5]->initLabel("Dmg", sf::Vector2f(700,885),
                    sf::Color::White,sf::Color::Black);
  label_[6]->initLabel(" ", sf::Vector2f(770,885),
                    sf::Color::White,sf::Color::Black);
  label_[7]->initLabel("Def", sf::Vector2f(700,925),
                    sf::Color::White,sf::Color::Black);
  label_[8]->initLabel(" ", sf::Vector2f(770,925),
                    sf::Color::White,sf::Color::Black);
  label_[9]->initLabel("Crit%", sf::Vector2f(700,965),
                    sf::Color::White,sf::Color::Black);
  label_[10]->initLabel(" ", sf::Vector2f(770,965),
                    sf::Color::White,sf::Color::Black);
                    //INVENTORY
  label_[11]->initLabel("Inventory:", sf::Vector2f(1250,885),
                    sf::Color::White,sf::Color::Black);
  label_[12]->initLabel("sprites\n go here", sf::Vector2f(1250,925),
                    sf::Color::White,sf::Color::Black);
                    //SPELLS
  label_[13]->initLabel(character->spell_[0]->name_, sf::Vector2f(1000,885),
                    sf::Color::White,sf::Color::Black);
  label_[14]->initLabel(character->spell_[1]->name_, sf::Vector2f(1000,935),
                    sf::Color::White,sf::Color::Black);
  label_[15]->initLabel(character->spell_[2]->name_, sf::Vector2f(1000,985),
                    sf::Color::White,sf::Color::Black);
  label_[16]->initLabel(character->spell_[3]->name_, sf::Vector2f(1000,1035),
                    sf::Color::White,sf::Color::Black);
  label_[21]->initLabel("Spells->", sf::Vector2f(890,885),
                    sf::Color::White,sf::Color::Black);
  for(int i=0;i<4;i++){
    spell_mana_[i] = (char*)malloc(5*sizeof(char));
  }
  snprintf(spell_mana_[0],3*sizeof(float),"%02d",(int)character->spell_[0]->mana_);
  snprintf(spell_mana_[1],3*sizeof(float),"%02d",(int)character->spell_[1]->mana_);
  snprintf(spell_mana_[2],3*sizeof(float),"%02d",(int)character->spell_[2]->mana_);
  snprintf(spell_mana_[3],3*sizeof(float),"%02d",(int)character->spell_[3]->mana_);

  label_[17]->initLabel(spell_mana_[0], sf::Vector2f(1200,885),
                    sf::Color::White,sf::Color::Black);
  label_[18]->initLabel(spell_mana_[1], sf::Vector2f(1200,935),
                    sf::Color::White,sf::Color::Black);
  label_[19]->initLabel(spell_mana_[2], sf::Vector2f(1200,985),
                    sf::Color::White,sf::Color::Black);
  label_[20]->initLabel(spell_mana_[3], sf::Vector2f(1200,1035),
                    sf::Color::White,sf::Color::Black);

  for(int i=0;i<22;i++){
    if (!label_[i]->font_.loadFromFile("../data/fonts/karmasuture.ttf")){
      printf("\nerror font\n");
      return;
    }
    label_[i]->setLabelFont(label_[i]->font_,20);
  }

  info_[0]->setLabelFont(label_[0]->font_,20);
  label_feedback_->setLabelFont(label_[0]->font_, 20);

  for(int i=0;i<4;i++){
    character_texture_[i] = Texture::CreateTexture();
  }
  character_texture_[0]->set_TextureFromFile("../data/sprites/character_selector/Kralvaros.png");
  character_texture_[1]->set_TextureFromFile("../data/sprites/character_selector/adam.png");
  character_texture_[2]->set_TextureFromFile("../data/sprites/character_selector/saul.png");
  character_texture_[3]->set_TextureFromFile("../data/sprites/character_selector/Andres.png");

  character_sprite_ = new Sprite();
  character_sprite_->initSprite(*character_texture_[0]);
  character_sprite_->sprite_.setPosition(45,900);
  // character_sprite_->sprite_.setOrigin(
  //   character_sprite_->sprite_.getLocalBounds().width*0.5f,
  //   character_sprite_->sprite_.getLocalBounds().height*0.5f
  // );

  // pixelfont_ = label_[0]->font_;

  for(int i=0;i<22;i++){
    label_[i]->getTextBox();
  }
  info_[0]->getTextBox();
  info_[0]->box_.setFillColor(sf::Color(100,100,255,255));

  hp_ = new sf::RectangleShape();
  hp_->setPosition(sf::Vector2f(320.f, 890.f));
  hp_->setFillColor(sf::Color(0, 120, 0));
  hp_->setSize(sf::Vector2f(character->getHp(), 25.0f));

  mana_ = new sf::RectangleShape();
  mana_->setPosition(sf::Vector2f(320.f, 930.f));
  mana_->setFillColor(sf::Color(0, 70, 200));
  mana_->setSize(sf::Vector2f(character->getMana(), 25.0f));

  // exp_ = new sf::RectangleShape();
  // exp_->setPosition(sf::Vector2f(45.f, 1013.f));
  // exp_->setFillColor(sf::Color(255, 229, 50));
  // exp_->setSize(sf::Vector2f((float)character->getExperience(), 12.0f));

  hp_bg_ = new sf::RectangleShape();
  hp_bg_->setPosition(sf::Vector2f(320.f, 890.f));
  hp_bg_->setFillColor(sf::Color(40, 0, 0));
  hp_bg_->setSize(sf::Vector2f(character->getMaxHp(), 25.0f));

  mana_bg_ = new sf::RectangleShape();
  mana_bg_->setPosition(sf::Vector2f(320.f, 930.f));
  mana_bg_->setFillColor(sf::Color(40, 0, 0));
  mana_bg_->setSize(sf::Vector2f(character->getMaxMana(), 25.f));

  // delete &gm;


}

void Ui::update(sf::RenderWindow& window, Character *selected_character){

  if(selected_character != nullptr){
    mana_num_ = selected_character->getMana();
    hp_num_ = selected_character->getHp();

    // // character_sprite_ = selected_character->ui_sprite_;kCharactersType_programmer
    // switch(selected_character::kCharactersType){
    //   case 0: character_sprite_->initSprite(*character_texture_[0]); break;
    //   case 1: character_sprite_->initSprite(*character_texture_[1]); break;
    //   case 2: character_sprite_->initSprite(*character_texture_[2]); break;
    //   case 3: character_sprite_->initSprite(*character_texture_[3]); break;
    // }
    // character_sprite_->sprite_ = selected_character->ui_sprite_.sprite_;

    snprintf(level,5*sizeof(char),"%d",selected_character->getLevel());
    snprintf(attack,5*sizeof(char),"%f",selected_character->getAttack());
    snprintf(defense,5*sizeof(char),"%f",selected_character->getDefense());
    snprintf(criattack,5*sizeof(char),"%f",selected_character->getCriattack());
    snprintf(feedback, 20 * sizeof(char), "Deals %d to enemy", damage_dealed);
    label_feedback_->setLabelString(feedback);


    label_[0]->setLabelString((const char*)selected_character->getName());
    label_[2]->setLabelString(level);
    label_[6]->setLabelString(attack);
    label_[8]->setLabelString(defense);
    label_[10]->setLabelString(criattack);

    mana_num_ = selected_character->getMana();
    hp_num_ = selected_character->getHp();

    hp_->setSize(sf::Vector2f(hp_num_, 25.f));
    mana_->setSize(sf::Vector2f(mana_num_, 25.f));
    // exp_->setSize(sf::Vector2f(150.f, 12.f));
    // for(int i=0;i<17;i++){
    //   if(label_[i]->isClicked(window) == 1){
    //     printf("ID: %d\n",label_[i]->get_id());
    //     printf("hp: %f\n",hp_num_);
    //   }
    // }
    //
    // for(int i=0;i<17;i++){
    //   if(label_[i]->isClicked(window) == 1){
    //     printf("ID: %d\n",label_[i]->get_id());
    //   }
    // }
  }


  // for(int i=0;i<17;i++){
  //
  //   if(label_[i]->isSelected(window) == 1){
  //     info_[0]->drawBox(window);
  //     info_[0]->drawText(window);
  //   }
  //
  //   info_[0]->text_.setPosition(
  //     sf::Vector2f((float)sf::Mouse::getPosition(window).x+15.0f
  //     ,(float)sf::Mouse::getPosition(window).y)
  //   );
  //
  //   info_[0]->box_.setPosition(
  //     sf::Vector2f((float)sf::Mouse::getPosition(window).x+15.0f
  //     ,(float)sf::Mouse::getPosition(window).y)
  //   );
  //
  // }

}


void Ui::draw(sf::RenderWindow& window){

  for(int i=0; i<11 ; i++){
    label_[i]->drawText(window);
  }
  label_feedback_->drawText(window);
  window.draw(*hp_bg_);
  window.draw(*mana_bg_);
  window.draw(*hp_);
  window.draw(*mana_);
  window.draw(*mana_);
  // window.draw(*exp_);
  // window.draw(*provisional);
  character_sprite_->draw(window);

  // for(int i=0; i<2 ; i++){
  //   info_[i]->drawBox(window);
  //   info_[i]->drawText(window);
  // }
}

void Ui::combatFeedback(Character& dealer,
  Character& receiver,
  int dg_dealed){

  if(dealer.chartype_ == Character::kCharactersType_enemy){

    printf("Enemy deals %d damage to %s\n", dg_dealed, receiver.getName());
    damage_dealed = dg_dealed;

  } else {

    printf("%s deals %d damage to Enemy\n", dealer.getName(), dg_dealed);
    damage_dealed = dg_dealed;

  }

}

Ui::~Ui(){

  for(int i = 0;i<22;i++){
    if(nullptr != label_[i]){
      delete label_[i];
    }
  }
  for(int i = 0;i<4;i++){
    if(nullptr != spell_mana_[i]){
      delete spell_mana_[i];
    }
  }
  for(int i = 0;i<6;i++){
    if(nullptr != info_[i]){
      delete info_[i];
    }
  }
  for(int i = 0;i<12;i++){
    if(nullptr != item_[i]){
      delete item_[i];
    }
  }
  for(int i = 0;i<4;i++){
    // GUSTAVO: I believe you mean:
    //
    // character_texture_[i]
    //
    // not
    //
    // character_texture_[4]
    if(nullptr != character_texture_[4]){
      delete character_texture_[4];
    }
  }
  if(nullptr != character_sprite_){
    delete character_sprite_;
  }
  if(nullptr != character){
    delete character;
  }

  if(nullptr != level){
  delete level;
  }
  if(nullptr != hp){
  delete hp;
  }

  if(nullptr != attack){
  delete attack;
  }
  if(nullptr != defense){
  delete defense;
  }
  if(nullptr != criattack){
  delete criattack;
  }


}
