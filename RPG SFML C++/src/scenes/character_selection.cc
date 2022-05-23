#include <character_selection.h>
//#include <sql_management.h>
#include <gamemanager.h>
#include "label.h"
#include <texture.h>
#include <sprite.h>
#include <game.h>
#include <character_manager.h>


Character_selection::Character_selection(){

  for(int i = 0; i<22 ;i++){
    label_[i] = nullptr;
  }

}


void Character_selection::init(){

  // if (!music_.openFromFile("../data/sounds/main_theme.ogg"))
  // {
  //   printf("error, file not found");
  // }else{
  //   printf("ready to use");
  // }

  //music_.play();

  cursor_sound_.initBuffer("../data/sounds/cursor_.ogg");
  cursor_sound_.setBuffer(cursor_sound_.buffer_);
  cursor_sound_.setVolume(25);

  char0_created_ = 0;
  char1_created_ = 0;
  char2_created_ = 0;
  char3_created_ = 0;


  selected_character_ = 0;
  selected_class_ = 0;



  for(int i=0 ; i<4 ; i++){
    characters_created_[i] = new Character();
    characters_created_[i]->init(0.0f,0.0f,0.0f,0.0f,0.0f);
  }

  characters_class_[0] = new Character();
  characters_class_[0]->init(100.0f,80.0f,50.0f,40.0f,10.0f);
  characters_class_[0]->chartype_ = Character::kCharactersType_programmer;

  characters_class_[1] = new Character();
  characters_class_[1]->init(60.0f,120.0f,75.0f,20.0f,20.0f);
  characters_class_[1]->chartype_ = Character::kCharactersType_artist;

  characters_class_[2] = new Character();
  characters_class_[2]->init(50.0f,150.0f,60.0f,15.0f,10.0f);
  characters_class_[2]->chartype_ = Character::kCharactersType_designer;

  characters_class_[3] = new Character();
  characters_class_[3]->init(75.0f,90.0f,60.0f,25.0f,10.0f);
  characters_class_[3]->chartype_ = Character::kCharactersType_techartist;


  //gm.get_classesDataFromDatabase();

  //ClassData* classdata =
  //(ClassData*)MKA::IndexListInfo(Database::extracted_queries_, 0);

  for(int i = 0; i<22 ;i++){
    label_[i] = new Label();
  }
  selected_class_ID_=0;

  label_[0]->initLabel("Andres", sf::Vector2f(100,200),sf::Color::White,
                                                sf::Color::Black);
  label_[1]->initLabel("Saul", sf::Vector2f(100,400),sf::Color::White,
                                                sf::Color::Black);
  label_[2]->initLabel("Adam", sf::Vector2f(100,600),sf::Color::White,
                                                sf::Color::Black);
  label_[3]->initLabel("Alvaro", sf::Vector2f(100,800),sf::Color::White,
                                                sf::Color::Black);

  /*label_[4]->initLabel((const char*)classdata->profession,
    sf::Vector2f(429,70),sf::Color::White, sf::Color::Black
  );
  label_[4]->description_ = label_[4]->text_;
  label_[4]->setLabelDescription(classdata->description);*/

  label_[4]->initLabel("Programmer",
    sf::Vector2f(429,200),sf::Color::White, sf::Color::Black
  );
  label_[4]->description_ = label_[4]->text_;
  label_[4]->setLabelDescription("The Backend\n" \
                              "The last sentient pillar standing between " \
                              "machines and humans.\n" \
                              "Patient, resilient and absurdly wary of " \
                              "Artists and Designers.\n" \
                              "Love them or hate them, you'll need at least\n " \
                              "one to pull through this madness.");
  label_[4]->setDescriptionFont(label_[0]->font_,25);

  label_[5]->initLabel("Artist", sf::Vector2f(792,200),sf::Color::White,
                                sf::Color::Black);
  label_[5]->description_ = label_[5]->text_;
  label_[5]->setLabelDescription("The Virtuoso\nThe most human part of a " \
 "development team.\nWeird, original, see them as you like an artist's brain" \
 " is fascinating and unique.\nOr maybe they are just crazy.\nNot really fond" \
 " of computers but if you wanna really hit you'll need their " \
 "stunning visuals");
  label_[5]->setDescriptionFont(label_[0]->font_,25);

  label_[6]->initLabel("Designer", sf::Vector2f(1060,200),sf::Color::White,
                                sf::Color::Black);
  label_[6]->description_ = label_[6]->text_;
  label_[6]->setLabelDescription("The Creator\nCreative, optimistic, witty, " \
  "every team get better when they have a good Designer.\nSometimes their" \
  " ideas are a little too much but it's why you need them");
  label_[6]->setDescriptionFont(label_[0]->font_,25);

  label_[7]->initLabel("Tech Artist", sf::Vector2f(1341,200),sf::Color::White,
                                sf::Color::Black);
  label_[7]->description_ = label_[7]->text_;
  label_[7]->setLabelDescription("The Conductor\nRare, resourceful, pragmatic," \
  " this element is the only member respected by everyone\nin the" \
  " team. Usually.\nLogic as a programmer, creative as an artist." \
  " Needs lots of caffeine tho.");
  label_[7]->setDescriptionFont(label_[0]->font_,25);


  hp = (char*)malloc(6*sizeof(char));
  mana = (char*)malloc(6*sizeof(char));
  attack = (char*)malloc(6*sizeof(char));
  defense = (char*)malloc(6*sizeof(char));
  criattack = (char*)malloc(6*sizeof(char));

  snprintf(hp,6*sizeof(char),"%f",characters_created_[0]->getHp());
  snprintf(mana,6*sizeof(char),"%f",characters_created_[0]->getMana());
  snprintf(attack,6*sizeof(char),"%f",characters_created_[0]->getAttack());
  snprintf(defense,6*sizeof(char),"%f",characters_created_[0]->getDefense());
  snprintf(criattack,6*sizeof(char),"%f",characters_created_[0]->getCriattack());


  label_[8]->initLabel("HP", sf::Vector2f(429,400),sf::Color::White,
                                                sf::Color::Black);
  label_[9]->initLabel("Mana", sf::Vector2f(429,460),sf::Color::White,
                                                sf::Color::Black);
  label_[10]->initLabel("Attack", sf::Vector2f(429,530),sf::Color::White,
                                                sf::Color::Black);
  label_[11]->initLabel("Defense", sf::Vector2f(429,600),sf::Color::White,
                                                sf::Color::Black);
  label_[12]->initLabel("Crit", sf::Vector2f(429,670),sf::Color::White,
                                                sf::Color::Black);
  label_[13]->initLabel(hp, sf::Vector2f(570,400),sf::Color::White,
                                                sf::Color::Black);
  label_[14]->initLabel(mana, sf::Vector2f(570,460),sf::Color::White,
                                                sf::Color::Black);
  label_[15]->initLabel(attack, sf::Vector2f(570,530),sf::Color::White,
                                                sf::Color::Black);
  label_[16]->initLabel(defense, sf::Vector2f(570,600),sf::Color::White,
                                                sf::Color::Black);
  label_[17]->initLabel(criattack, sf::Vector2f(570,670),sf::Color::White,
                                                sf::Color::Black);
  label_[18]->initLabel(" ", sf::Vector2f(792,400),sf::Color::White,
                                                sf::Color::Black);
  label_[19]->initLabel("CONFIRM", sf::Vector2f(960,850),sf::Color::White,
                                                sf::Color::Black);
  label_[20]->initLabel("PLAY", sf::Vector2f(1500,850),sf::Color::White,
                                                sf::Color::Black);
  label_[21]->initLabel("Assign a class to each character",
                                                sf::Vector2f(500,70),
                                                sf::Color::White,
                                                sf::Color::Black);

//   for(int i=0;i<20;i++){
//     label_[i].drawText(window);
//     label_[i].drawBox(window);
//     if(label_[i].isSelected(window) == 1){
//       window.draw(menu_cursor_sprite_);
//     }
//   }

for(int i = 0; i<22 ;i++){
  MKA::InsertNodeList(&gameobject_list_, (void*)label_[i]);
}


  for(int i=0;i<8;i++){
    if (!label_[i]->font_.loadFromFile("../data/fonts/karmasuture.ttf")){
      printf("\nerror font\n");
      return;
    }
    label_[i]->setLabelFont(label_[i]->font_,40);
    label_[i]->getTextBox();
  }
  for(int i=8;i<22;i++){
    if (!label_[i]->font_.loadFromFile("../data/fonts/karmasuture.ttf")){
      printf("\nerror font\n");
      return;
    }
    label_[i]->setLabelFont(label_[i]->font_,25);
  }
  for(int i = 19 ; i<22; i++){
    label_[19]->setLabelFont(label_[19]->font_,40);
    label_[19]->getTextBox();
    label_[20]->setLabelFont(label_[19]->font_,40);
    label_[20]->getTextBox();
    label_[21]->setLabelFont(label_[19]->font_,40);
    label_[21]->getTextBox();
  }

  menu_cursor_texture_ = Texture::CreateTexture();
  menu_cursor_texture_->set_TextureFromFile(
    "../data/sprites/menu/menu_cursor.png"
  );

  menu_cursor_sprite_ = new Sprite();
  menu_cursor_sprite_->initSprite(*menu_cursor_texture_);
  menu_cursor_sprite_->sprite_.setPosition(-50,0);
  menu_cursor_sprite_->sprite_.setOrigin(
    menu_cursor_sprite_->sprite_.getLocalBounds().width*0.5f,
    0);
  menu_cursor_sprite_->sprite_.setScale(0.35f,0.35f);
  MKA::InsertNodeList(&gameobject_list_, (void*)menu_cursor_sprite_);



  character_cursor_sprite_ = new Sprite();
  character_cursor_sprite_->initSprite(*menu_cursor_texture_);
  character_cursor_sprite_->sprite_.setPosition(-50,0);
  character_cursor_sprite_->sprite_.setOrigin(
    character_cursor_sprite_->sprite_.getLocalBounds().width*0.5f,
    0);
  character_cursor_sprite_->sprite_.setScale(0.35f,0.35f);
  MKA::InsertNodeList(&gameobject_list_, (void*)character_cursor_sprite_);


  for(int i = 0; i<4; i++){
    character_selection_texture_[i] = Texture::CreateTexture();
    character_selection_img_[i] = new Sprite();
  }
  character_selection_texture_[0]->set_TextureFromFile(
    "../data/sprites/character_selector/Kralvaros.png");
  character_selection_texture_[1]->set_TextureFromFile(
    "../data/sprites/character_selector/adam.png");
  character_selection_texture_[2]->set_TextureFromFile(
    "../data/sprites/character_selector/saul.png");
  character_selection_texture_[3]->set_TextureFromFile(
    "../data/sprites/character_selector/Andres.png");

  character_selection_img_[0]->initSprite(*character_selection_texture_[0]);
  characters_class_[0]->ui_sprite_.initSprite(*character_selection_texture_[0]);

  character_selection_img_[1]->initSprite(*character_selection_texture_[1]);
  characters_class_[1]->ui_sprite_.initSprite(*character_selection_texture_[1]);

  character_selection_img_[2]->initSprite(*character_selection_texture_[2]);
  characters_class_[2]->ui_sprite_.initSprite(*character_selection_texture_[2]);

  character_selection_img_[3]->initSprite(*character_selection_texture_[3]);
  characters_class_[3]->ui_sprite_.initSprite(*character_selection_texture_[3]);


  character_selection_img_[3]->sprite_.setPosition(105,850);
  character_selection_img_[2]->sprite_.setPosition(105,650);
  character_selection_img_[1]->sprite_.setPosition(105,450);
  character_selection_img_[0]->sprite_.setPosition(105,250);
  character_selection_img_[3]->sprite_.setScale(1.5f,1.5f);
  character_selection_img_[2]->sprite_.setScale(1.5f,1.5f);
  character_selection_img_[1]->sprite_.setScale(1.5f,1.5f);
  character_selection_img_[0]->sprite_.setScale(1.5f,1.5f);

  for(int i = 0; i<4; i++){
  MKA::InsertNodeList(&gameobject_list_, (void*)character_selection_img_[i]);
  }

  labels_id_[0] = label_[4]->get_id();
  labels_id_[1] = label_[5]->get_id();
  labels_id_[2] = label_[6]->get_id();
  labels_id_[3] = label_[7]->get_id();

  //gm.ddbb.endExtractQueries();


}

void Character_selection::update(){

  if(selected_class_ID_ == labels_id_[0]){

      label_[18]->text_ = label_[4]->description_;
      selected_class_ = 0;
      snprintf(hp,6*sizeof(char),"%f",characters_class_[0]->getHp());
      snprintf(mana,6*sizeof(char),"%f",characters_class_[0]->getMana());
      snprintf(attack,6*sizeof(char),"%f",characters_class_[0]->getAttack());
      snprintf(defense,6*sizeof(char),"%f",characters_class_[0]->getDefense());
      snprintf(criattack,6*sizeof(char),"%f",characters_class_[0]->getCriattack());


  }
  if(selected_class_ID_ == labels_id_[1]){

      label_[18]->text_ = label_[5]->description_;
      selected_class_ = 1;
      snprintf(hp,6*sizeof(char),"%f",characters_class_[1]->getHp());
      snprintf(mana,6*sizeof(char),"%f",characters_class_[1]->getMana());
      snprintf(attack,6*sizeof(char),"%f",characters_class_[1]->getAttack());
      snprintf(defense,6*sizeof(char),"%f",characters_class_[1]->getDefense());
      snprintf(criattack,6*sizeof(char),"%f",characters_class_[1]->getCriattack());


  }
  if(selected_class_ID_ == labels_id_[2]){

      label_[18]->text_ = label_[6]->description_;
      selected_class_ = 2;
      snprintf(hp,6*sizeof(char),"%f",characters_class_[2]->getHp());
      snprintf(mana,6*sizeof(char),"%f",characters_class_[2]->getMana());
      snprintf(attack,6*sizeof(char),"%f",characters_class_[2]->getAttack());
      snprintf(defense,6*sizeof(char),"%f",characters_class_[2]->getDefense());
      snprintf(criattack,6*sizeof(char),"%f",characters_class_[2]->getCriattack());
  }
  if(selected_class_ID_ == labels_id_[3]){

      label_[18]->text_ = label_[7]->description_;
      selected_class_ = 3;
      snprintf(hp,6*sizeof(char),"%f",characters_class_[3]->getHp());
      snprintf(mana,6*sizeof(char),"%f",characters_class_[3]->getMana());
      snprintf(attack,6*sizeof(char),"%f",characters_class_[3]->getAttack());
      snprintf(defense,6*sizeof(char),"%f",characters_class_[3]->getDefense());
      snprintf(criattack,6*sizeof(char),"%f",characters_class_[3]->getCriattack());

  }

  label_[18]->text_.setPosition(792,400);
  label_[18]->text_.setLineSpacing(3);
  label_[18]->setLabelFont(label_[0]->font_,25);

  character_selection_img_[selected_character_]->initSprite(*character_selection_texture_[selected_class_]);

  for(int i = 4; i < 8; i++){
    if(label_[i]->isClicked(*scene_window_)){
      menu_cursor_sprite_->sprite_.setPosition(label_[i]->text_.getPosition().x
      - menu_cursor_sprite_->sprite_.getLocalBounds().width*0.5f,
      label_[i]->text_.getPosition().y);
      selected_class_ID_ = label_[i]->get_id();
      cursor_sound_.play();

    }
  }

  for(int i = 0; i < 4; i++){
    if(label_[i]->isClicked(*scene_window_)){
      character_cursor_sprite_->sprite_.setPosition(label_[i]->text_.getPosition().x
      - character_cursor_sprite_->sprite_.getLocalBounds().width*0.5f,
      label_[i]->text_.getPosition().y);
      selected_character_ = i;
      cursor_sound_.play();

      //music_.pause();
      printf("\n%d",i);
    }
  }

  label_[13]->initLabel(hp, sf::Vector2f(570,400),sf::Color::White,
                                                sf::Color::Black);
  label_[14]->initLabel(mana, sf::Vector2f(570,460),sf::Color::White,
                                                sf::Color::Black);
  label_[15]->initLabel(attack, sf::Vector2f(570,530),sf::Color::White,
                                                sf::Color::Black);
  label_[16]->initLabel(defense, sf::Vector2f(570,600),sf::Color::White,
                                                sf::Color::Black);
  label_[17]->initLabel(criattack, sf::Vector2f(570,670),sf::Color::White,
                                                sf::Color::Black);

    if(label_[19]->isClicked(*scene_window_)){
      menu_cursor_sprite_->sprite_.setPosition(label_[19]->text_.getPosition().x
      - menu_cursor_sprite_->sprite_.getLocalBounds().width*0.5f,
      label_[19]->text_.getPosition().y);
      cursor_sound_.play();
      characters_created_[selected_character_] = characters_class_[selected_class_];
      characters_created_[selected_character_]->ui_sprite_ = characters_class_[selected_class_]->ui_sprite_;
      printf("\n confirm");
      switch(selected_character_){
        case 0:char0_created_ = 1 ; break;
        case 1:char1_created_ = 1 ; break;
        case 2:char2_created_ = 1 ; break;
        case 3:char3_created_ = 1 ; break;
      }
    }




    if(label_[20]->isClicked(*scene_window_) &&
          char0_created_ == 1 &&
          char1_created_ == 1 &&
          char2_created_ == 1 &&
          char3_created_ == 1 ){

      menu_cursor_sprite_->sprite_.setPosition(label_[20]->text_.getPosition().x
      - menu_cursor_sprite_->sprite_.getLocalBounds().width*0.5f,
      label_[20]->text_.getPosition().y);

      cursor_sound_.play();

      MKA::List* character_list = nullptr;

      GameManager& gm = GameManager::Instance();

      gm.init();

      for(int i=0 ; i<4 ; i++){
      //   CharacterManager::get_characterList();
        // MKA::InsertNodeList(&character_list_, (void*)characters_created_[i]);
      // printf("\nhp: %f\n",characters_created_[i]->getHp() );
      // printf("\nmana: %f\n",characters_created_[i]->getMana() );
      // printf("\nattack: %f\n",characters_created_[i]->getAttack() );
      // printf("\ndef: %f\n",characters_created_[i]->getDefense() );
      // printf("\ncrit %f\n",characters_created_[i]->getCriattack() );
      MKA::InsertNodeList(&character_list, (void*)characters_created_[i]);
      }

      gm.set_charactersToDatabase(character_list);
      delete &gm;
      Game::change_scene_ = 1;
      Game::selected_scene_ = 5;
    }





}

void Character_selection::input(){

}


Character_selection::~Character_selection(){

  for(int i = 0; i<22 ;i++){
    if(nullptr != label_[i]){
    delete label_[i];
    }
  }
  for(int i = 0; i<4 ;i++){
    if(nullptr != character_selection_texture_[i]){
      character_selection_texture_[i];
    }
  }
  for(int i = 0; i<4 ;i++){
    if(nullptr != character_selection_img_[i]){
    delete character_selection_img_[i];
    }
  }
  for(int i = 0; i<4 ;i++){
    if(nullptr != characters_created_[i]){
    delete characters_created_[i];
    }
  }
  for(int i = 0; i<4 ;i++){
    if(nullptr != characters_class_[i]){
    delete characters_class_[i];
    }
  }
  if(nullptr != menu_cursor_texture_){
  delete menu_cursor_texture_;
  }
  if(nullptr != menu_cursor_sprite_){
  delete menu_cursor_sprite_;
  }
  if(nullptr != character_cursor_sprite_){
  delete character_cursor_sprite_;
  }
  if(nullptr != mana){
  delete mana;
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
