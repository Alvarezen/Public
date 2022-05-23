#include "menu.h"
#include "gamemanager.h"
#include "game.h"


Menu::Menu(){

  menu_cursor_texture_ = nullptr;
  menu_texture_ = nullptr;

}

void Menu::init(){

  //SOUND
  cursor_sound_.initBuffer("../data/sounds/cursor_.ogg");
  cursor_sound_.setBuffer(cursor_sound_.buffer_);
  cursor_sound_.setVolume(25);

  //MUSIC
  music_.init("../data/sounds/main_theme.ogg");
  music_.setVolume(25);



  GameManager& gm = GameManager::Instance();
  gm.init();

  for(int i=0;i<4;i++){
    label_[i] = new Label();
  }


  label_[0]->initLabel("NEW GAME", sf::Vector2f((float)GameManager::s_windowWidth_/2,
  (float)GameManager::s_windowHeight_/2 +
  (float)GameManager::s_windowHeight_/20),sf::Color::White,sf::Color::Black);
  label_[1]->initLabel("CONTINUE", sf::Vector2f((float)GameManager::s_windowWidth_/2,
  (float)GameManager::s_windowHeight_/2+ (float)GameManager::s_windowHeight_/20 +
  (float)GameManager::s_windowHeight_/11),sf::Color::White,sf::Color::Black);
  label_[2]->initLabel("QUIT", sf::Vector2f((float)GameManager::s_windowWidth_/2,
  (float)GameManager::s_windowHeight_/2+ (float)GameManager::s_windowHeight_/20 +
  (float)GameManager::s_windowHeight_/11*2),sf::Color::White,sf::Color::Black);
  label_[3]->initLabel(" ", sf::Vector2f((float)GameManager::s_windowWidth_/2,
  (float)GameManager::s_windowHeight_/2+ (float)GameManager::s_windowHeight_/20 +
  (float)GameManager::s_windowHeight_/11*3),sf::Color::White,sf::Color::Black);

  for(int i=0;i<4;i++){

    label_[i]->font_ = *gm.get_fontFromDatabaseWithTag("karmasuture");
    label_[i]->setLabelFont(label_[i]->font_,50);
    label_[i]->getTextBox();
    label_[i]->centerText();
    MKA::InsertNodeList(&gameobject_list_, (void*)label_[i]);
  }



  menu_texture_ = gm.get_textureFromDatabaseWithTag("gamelogo");

  menu_sprite_ = new Sprite();
  menu_sprite_->initSprite(*menu_texture_);
  menu_sprite_->sprite_.setPosition((float)GameManager::s_windowWidth_/2,
      (float)GameManager::s_windowHeight_/4);
  menu_sprite_->sprite_.setOrigin(
    menu_sprite_->sprite_.getLocalBounds().width*0.5f,
    menu_sprite_->sprite_.getLocalBounds().height*0.4f);
  MKA::InsertNodeList(&gameobject_list_, (void*)menu_sprite_);

  menu_cursor_texture_ = gm.get_textureFromDatabaseWithTag("menucursor");

  menu_cursor_sprite_ = new Sprite();
  menu_cursor_sprite_->initSprite(*menu_cursor_texture_);
  menu_cursor_sprite_->sprite_.setPosition(-50,0);
  menu_cursor_sprite_->sprite_.setOrigin(
    menu_cursor_sprite_->sprite_.getLocalBounds().width*0.5f,
    menu_cursor_sprite_->sprite_.getLocalBounds().height*0.4f);
  menu_cursor_sprite_->sprite_.setScale(0.35f,0.35f);
  MKA::InsertNodeList(&gameobject_list_, (void*)menu_cursor_sprite_);

  menu_sprite_->set_boxBounds();

  /*
  if (!menu_texture_.loadFromFile("../data/sprites/menu.png")){
    printf("\nerror png\n");
    return;
  }
  menu_sprite_.setTexture(menu_texture_);

  if (!menu_cursor_texture_.loadFromFile("../data/sprites/menu_cursor.png")){
    printf("\nerror png\n");
    return;
  }

  menu_cursor_sprite_.setTexture(menu_cursor_texture_);

  menu_cursor_sprite_.setOrigin(menu_cursor_sprite_.getLocalBounds().width*0.5f,
                             menu_cursor_sprite_.getLocalBounds().height*0.4f);

  menu_cursor_sprite_.setScale(0.35f,0.35f);
  */

  delete &gm;

}

void Menu::input(){

}

void Menu::update(){


  music_.play();



  for(int i = 0; i < 4; i++){
    if(label_[i]->isSelected(*scene_window_) == 1){
      menu_cursor_sprite_->sprite_.setPosition(label_[i]->text_.getPosition());
      menu_cursor_sprite_->sprite_.setPosition(
        menu_cursor_sprite_->sprite_.getPosition().x
      - label_[i]->text_.getLocalBounds().width*0.5f
      - menu_cursor_sprite_->sprite_.getLocalBounds().width*0.5f,
      menu_cursor_sprite_->sprite_.getPosition().y);
    }
  }

  if(label_[2]->isClicked(*scene_window_) == 1){
    Game::exit_ = 1;
  }
  if(label_[0]->isClicked(*scene_window_) == 1){

    music_.stop();

    cursor_sound_.play();

    Game::selected_scene_ = 1;
    Game::change_scene_ = 1;
  }

}

Menu::~Menu(){

  if(menu_cursor_sprite_ != nullptr){
    delete menu_cursor_sprite_;
  }
  if(menu_cursor_texture_ != nullptr){
    delete menu_cursor_texture_;
  }
  if(menu_sprite_ != nullptr){
    delete menu_sprite_;
  }
  if(menu_texture_ != nullptr){
    delete menu_texture_;
  }
  for(int i=0;i<4;i++){
    if(label_[i] != nullptr){
    delete label_[i];
    }
  }
}
