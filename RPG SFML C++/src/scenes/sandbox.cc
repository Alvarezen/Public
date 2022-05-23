/*
File: combat.cc
Author: Adam Álvarez Enfedal
Description: sandbox scene implementation
*/

#include <sandbox.h>
#include <gamemanager.h>
#include <texture.h>
#include <tilemap.h>
#include <sql_management.h>
#include <character_manager.h>
#include <enemy_manager.h>
#include <character.h>
#include <developer_t.h>
#include <input.h>
#include <ui.h>
#include <camera.h>
#include <doors.h>
#include <game.h>
#include <sprite.h>
#include <label.h>

Sandbox::Sandbox(){

  sandbox_map_ = nullptr;
  dev_tool_map_ = nullptr;
  camera_ = nullptr;
  free_move_char_ = nullptr;
  sandbox_map_ = new Tilemap();

  for(int i = 0 ; i < 3 ; ++i){

    doors_[i] = nullptr;

  }


}

Sandbox::~Sandbox(){

  if(nullptr != sandbox_map_){
    delete sandbox_map_;
  }
  if(nullptr != dev_tool_map_){
    delete dev_tool_map_;
  }
  if(nullptr != camera_){
    delete camera_;
  }
  if(nullptr != free_move_char_){
    delete free_move_char_;
  }

  for(int i = 0 ; i < 3 ; ++i){

    if(nullptr != doors_[i]){

      delete doors_[i];

    }

  }

}

void Sandbox::LoadMap(Doors& door, GameManager& gm){

  if(sandbox_map_->LoadTilemap(gm.get_ddbb(), door.get_mapDestiny())){
    printf("socorro");
    MKA::List* aux_chars_database = nullptr;
    gm.set_charactersFromDatabase(&aux_chars_database);
    printf("%d\n", MKA::ListSize(aux_chars_database));

    characters->set_characterList(aux_chars_database);
    MKA::InsertNodeList(&gameobject_list_, (void*)sandbox_map_);

    MKA::List* aux_characters_list = nullptr;
    aux_characters_list = characters->get_characterList();

    free_move_char_ = (Character*)MKA::IndexListInfo(aux_characters_list, 0);

    if(sandbox_map_->set_characterMapPos(*free_move_char_, door.get_tileDestiny())){
      MKA::InsertNodeList(&gameobject_list_, (void*)free_move_char_);
    }

  }

}

void Sandbox::init(){

  music_.init("../data/sounds/world_music.ogg");
  music_.setVolume(15);
  music_.setLoop(true);

  GameManager& gm = GameManager::Instance();
  gm.init();

  characters = new CharacterManager();
  enemies_ = new EnemyManager();

  sandbox_map_->init("../data/fonts/tilemap.ttf");
  camera_ = new Camera();
  camera_->init();
  camera_->camera_->setSize(
    {GameManager::s_windowWidth_ * 1.0f, GameManager::s_windowHeight_ * 1.0f}
  );
  // // camera_->camera_->move({390.0f, 0.0f});

  for(int i = 0 ; i < 3 ; ++i){
    doors_[i] = new Doors();
  }

  doors_[0]->init(3, 2, 298, 110); // spawn door
  LoadMap(*doors_[0], gm);
  doors_[1]->init(2, 3, 451, 452); // door level 1 to level 2
  doors_[2]->init(3, 2, 298, 297); // door level 2 to level 1

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


  save_ = new Label();
  save_->font_ = *gm.get_fontFromDatabaseWithTag("karmasuture");
  save_->initLabel("SAVE", sf::Vector2f(1718,180),sf::Color::White,
                                                sf::Color::Black);
  save_->setLabelFont(save_->font_,30);
  save_->getTextBox();
  MKA::InsertNodeList(&gameobject_list_, (void*)save_);
  delete &gm;

}

void Sandbox::LoadNextMap(){

  int char_pos = sandbox_map_->get_characterMapPos(*free_move_char_);

  if(char_pos == 212 || char_pos == 209){

    music_.setLoop(false);
    music_.stop();
    Game::selected_scene_ = 2;
    Game::change_scene_ = 1;
  }

  if(char_pos == doors_[0]->get_tileTrigger()){

    MKA::EraseList(&gameobject_list_);

    GameManager& gm = GameManager::Instance();
    gm.init();

    LoadMap(*doors_[1], gm);

    delete &gm;

  }

  if(char_pos == doors_[1]->get_tileTrigger()){

    MKA::EraseList(&gameobject_list_);

    GameManager& gm = GameManager::Instance();
    gm.init();

    LoadMap(*doors_[2], gm);

    delete &gm;

  }

}

void Sandbox::input(){

  if(sandbox_map_->inputMovement(*free_move_char_)){

    LoadNextMap();

  }

}


void Sandbox::update(){

  music_.play();

  if(mogu_->isClicked(*scene_window_) == 1){
    printf("ADAM TOMATE ESE BOTON\n");
  }

  dev_tool_map_->TilemapTool(*sandbox_map_, *this);

  // scene_window_->setView(*(camera_->camera_));

}
