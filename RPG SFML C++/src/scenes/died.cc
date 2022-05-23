#include "died.h"
#include "gamemanager.h"
#include "game.h"

Died::Died(){

  died_cursor_texture_ = nullptr;
  died_texture_ = nullptr;

}

void Died::init(){


    GameManager& gm = GameManager::Instance();
    gm.init();


    label_ = new Label();

    label_->initLabel("Continue",
    sf::Vector2f((float)GameManager::s_windowWidth_/2,
          (float)GameManager::s_windowHeight_/2 + 200),
          sf::Color::White,sf::Color::Black);

    label_->font_ = *gm.get_fontFromDatabaseWithTag("karmasuture");
    label_->setLabelFont(label_->font_,50);
    label_->getTextBox();
    label_->centerText();
    MKA::InsertNodeList(&gameobject_list_, (void*)label_);

    died_texture_ = gm.get_textureFromDatabaseWithTag("diedlogo");

    died_sprite_ = new Sprite();
    died_sprite_->initSprite(*died_texture_);
    died_sprite_->sprite_.setPosition((float)GameManager::s_windowWidth_/2,
        (float)GameManager::s_windowHeight_/4 + 50);
    died_sprite_->sprite_.setOrigin(
      died_sprite_->sprite_.getLocalBounds().width*0.5f,
      died_sprite_->sprite_.getLocalBounds().height*0.5f);
    died_sprite_->sprite_.setScale(10,10);
    MKA::InsertNodeList(&gameobject_list_, (void*)died_sprite_);

    died_cursor_texture_ = gm.get_textureFromDatabaseWithTag("menucursor");

    died_cursor_sprite_ = new Sprite();
    died_cursor_sprite_->initSprite(*died_cursor_texture_);
    died_cursor_sprite_->sprite_.setPosition(-50,0);
    died_cursor_sprite_->sprite_.setOrigin(
      died_cursor_sprite_->sprite_.getLocalBounds().width*0.5f,
      died_cursor_sprite_->sprite_.getLocalBounds().height*0.4f);
    died_cursor_sprite_->sprite_.setScale(0.35f,0.35f);
    MKA::InsertNodeList(&gameobject_list_, (void*)died_cursor_sprite_);


  delete &gm;
}

void Died::update(){

  if(label_->isSelected(*scene_window_) == 1){
    died_cursor_sprite_->sprite_.setPosition(label_->text_.getPosition());
    died_cursor_sprite_->sprite_.setPosition(
      died_cursor_sprite_->sprite_.getPosition().x
    - label_->text_.getLocalBounds().width*0.5f
    - died_cursor_sprite_->sprite_.getLocalBounds().width*0.5f,
    died_cursor_sprite_->sprite_.getPosition().y);
  }

  if(label_->isClicked(*scene_window_) == 1){
    Game::selected_scene_ = 0;
    Game::change_scene_ = 1;
  }

}

void Died::input(){

}

Died::~Died(){

  if(died_cursor_sprite_ != nullptr){
    delete died_cursor_sprite_;
  }
  if(died_sprite_ != nullptr){
    delete died_sprite_;
  }
  if(died_texture_ != nullptr){
    delete died_texture_;
  }
  if(died_cursor_texture_ != nullptr){
    delete died_cursor_texture_;
  }

    if(label_ != nullptr){
    delete label_;
    }

}
