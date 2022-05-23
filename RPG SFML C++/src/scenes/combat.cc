/**
  * @file combat.cc
  * @brief combat funcs file of the game
  * @details File that is use to manage and visualize the combat scene
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */


#include <combat.h>
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

Combat::Combat(){

  combat_map_ = nullptr;
  characters = nullptr;
  dev_tool_map_ = nullptr;
  enemies_ = nullptr;
  camera_ = nullptr;

}

Combat::~Combat(){

  if(nullptr != combat_map_){
    delete combat_map_;
  }

  if(nullptr != characters){
    delete characters;
  }

  if(nullptr != dev_tool_map_){
    delete dev_tool_map_;
  }

  if(nullptr != enemies_){
    delete enemies_;
  }

  if(nullptr != camera_){
    delete camera_;
  }

}

void Combat::init(){

  characters = new CharacterManager();
  enemies_ = new EnemyManager();
  combat_map_ = new Tilemap();
  // camera_ = new Camera();
  // camera_->init();
  // camera_->camera_->setSize(
  //   {(float)GameManager::s_windowWidth_,
  //     (float)GameManager::s_windowHeight_}
  // );

  ui_ = new Ui();

  ui_->init();

  MKA::InsertNodeList(&gameobject_list_, (void*)ui_);

  GameManager& gm = GameManager::Instance();
  gm.init();

  combat_map_->init("../data/fonts/tilemap.ttf");

  if(combat_map_->LoadTilemap(gm.get_ddbb(), 1)){


    MKA::List* aux_chars_database = nullptr;
    gm.set_charactersFromDatabase(&aux_chars_database);

    characters->set_characterList(aux_chars_database);

    MKA::InsertNodeList(&gameobject_list_, (void*)combat_map_);

    Character* aux_character = nullptr;
    MKA::List* aux_characters_list = nullptr;
    aux_characters_list = characters->get_characterList();

    //Push player character to draw
    for(int i = 0; i < MKA::ListSize(aux_characters_list); ++i){

      aux_character = (Character*)MKA::IndexListInfo(aux_characters_list, i);

        MKA::InsertNodeList(&gameobject_list_, (void*)aux_character);
        combat_map_->set_characterMapPos(*aux_character, 300 + i);

    }

    //Push enemie character to draw
    enemies_->init(*combat_map_, {225, 390}, {3, 3}, 2.0f);
    Character* aux_enemy = nullptr;
    MKA::List* aux_enemies_list = nullptr;
    aux_enemies_list = enemies_->get_enemyList();

    for(int i = 0; i < MKA::ListSize(aux_enemies_list); ++i){

      aux_enemy = (Character*)MKA::IndexListInfo(aux_enemies_list, i);

        MKA::InsertNodeList(&gameobject_list_, (void*)aux_enemy);

    }

  } else {

    printf("Error loading combat map.");

  }


  delete &gm;

}

void Combat::input(){

  combat_map_->input(*scene_window_);
  Character* character = characters->get_characterSelected();

  if(Input::isMouseButtonDown(sf::Mouse::Left)){

    characters->set_characterClicked(1);

  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)
    && nullptr != character){
    characters->set_characterState(
      CharacterManager::kCharacterAction::kCharacterAction_move
    );
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)
    && nullptr != character){
    characters->set_characterState(
      CharacterManager::kCharacterAction::kCharacterAction_attack
    );
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)
    && nullptr != character){
    characters->endCharacterTurn();
  }

}

void Combat::update(){

  dev_tool_map_->TilemapTool(*combat_map_, *this);
  dev_tool_map_->CharacterTool(*characters);
  dev_tool_map_->EnemyTool(*enemies_);


  ui_->update(*scene_window_, characters->get_characterSelected());

  combat_map_->update();

  characters->update(*combat_map_, *enemies_, *ui_);
  enemies_->update(*combat_map_, *characters);

  // scene_window_->setView(*(camera_->camera_));

}
