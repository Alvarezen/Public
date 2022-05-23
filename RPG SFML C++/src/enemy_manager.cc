/*
File: enemy_manager.cc
Author: Adam Álvarez Enfedal
Description: enemy_manager implementation
*/

#include <enemy_manager.h>
#include <character_manager.h>
#include <gmath.h>
#include <character.h>
#include <texture.h>
#include <tilemap.h>
#include <tile.h>
#include <input.h>
#include <game.h>

EnemyManager::EnemyManager(){

  enemy_list_ = nullptr;
  enemy_amount_ = 0;
  init_pos_map_ = 0;
  smooth_movement_end_ = 0;
  turns_ = 0;
  closest_tile_ = nullptr;
  character_selected_ = nullptr;
  target_ = nullptr;
  closest_tile_ = nullptr;
  calculate_distance_ = 0;
  speed_movement_ = 0;
  turn_end_ = 0;
  restart_path_ = 0;
  frames_wait_end_turn_ = 0;
  total_turns_ = 0;

}

EnemyManager::~EnemyManager(){

  MKA::EraseList(&enemy_list_);

}

void EnemyManager::init(Tilemap& combat_map,
  sf::Vector2i map_range,
  sf::Vector2i amount_range,
  float speed){

  speed_movement_ = speed;

  Texture *texture = nullptr;
  Character* enemy = nullptr;

  init_pos_map_ = Math::RandomInt(map_range.y, map_range.x);

  for(int i = 0 ; i < Math::RandomInt(amount_range.y, amount_range.x) ; ++i){

    enemy = new Character();

    texture = Texture::CreateTexture();
    texture->set_TextureFromFile(
      "../data/sprites/characters/sprite_sheet_enemies.png"
    );

    enemy->init(
      {0, 0}, {1, 1},
      *texture, 100.0f,
      100.0f, 100.0f,
      100.0f, 100.0f,
      1, 1, 0, 0, Character::kCharactersType_enemy, 4, 2, 0, 50.0f);

    if(combat_map.set_characterMapPos(*enemy, init_pos_map_ + i)){
      MKA::InsertNodeList(&enemy_list_, (void*)enemy);
    }

  }

}

void EnemyManager::enemyTurns(Tilemap& map, CharacterManager& char_man){

  if(!char_man.character_turn_){

    Character* enemy = nullptr;

    if(nullptr != (enemy = (Character*)MKA::IndexListInfo(enemy_list_, turns_))){

      calculatePath(map, char_man, enemy);

      if(turn_end_){

        target_->reciveAttack(*character_selected_);
        uint8_t turn = character_selected_->getTurns();
        turn = 1;
        character_selected_->setTurns(turn);
        turns_++;
        character_selected_ = nullptr;
        target_ = nullptr;
        closest_tile_ = nullptr;
        turn_end_ = 0;
        restart_path_ = 0;
        frames_wait_end_turn_ = 0;


      }

    }

    if(total_turns_ == MKA::ListSize(enemy_list_)){

      char_man.character_turn_ = 1;
      char_man.characters_all_actions_ = 0;
      turn_end_ = 0;
      total_turns_ = 0;
      character_selected_ = nullptr;
      target_ = nullptr;
      closest_tile_ = nullptr;
      turn_end_ = 0;
      restart_path_ = 0;
      frames_wait_end_turn_ = 0;
      turns_ = 0;

    }


  }


}

Character* EnemyManager::get_randomTarget(CharacterManager& char_man){

  MKA::List* aux_character_list = char_man.get_characterList();
  Character* character = nullptr;
  Character* character_to_return = nullptr;
  int randn = Math::RandomInt(MKA::ListSize(aux_character_list) - 1, 0);

  if(randn != -1){

    for(int i = 0; i < MKA::ListSize(aux_character_list) ; ++i){

      character = (Character*)MKA::IndexListInfo(aux_character_list, i);

      if(randn == i){

        character_to_return = character;

      }

    }

    return character_to_return;

  } else {

    return nullptr;

  }



}

Tile* EnemyManager::calculateCloserPath(Tilemap& map, CharacterManager& char_man, Character* enemy){

  Character* character = get_randomTarget(char_man);

  if(nullptr != character){

    MKA::List* aux_range = map.updateRangeCharacter(*character, 1);
    Tile* tile = nullptr;
    Tile* tile_to_return_ = nullptr;
    Tile& enemy_tile = map.get_characterMapPosTile(*enemy);
    int range[4];
    uint8_t found = 0;
    int find_free_tile = 0;

    for(int i = 0; i < MKA::ListSize(aux_range) ; ++i){

      tile = (Tile*)MKA::IndexListInfo(aux_range, i);

      tile->manhattan_dis_ = map.ManhattanDistance(tile->tile_id_, enemy_tile.tile_id_);
      range[i] = map.ManhattanDistance(tile->tile_id_, enemy_tile.tile_id_);

    }

    Math::OrderNumbers(range, 4, 1);

    for(int i = 0; i < MKA::ListSize(aux_range) ; ++i){

      tile = (Tile*)MKA::IndexListInfo(aux_range, i);

      if(range[find_free_tile] == tile->manhattan_dis_ && !found){

        if(map.moveCharacterAtTile(*enemy, tile->tile_id_, 1)){

          tile_to_return_ = tile;
          character_selected_ = enemy;
          target_ = character;
          found = 1;

        } else {

          find_free_tile++;

        }

      }

    }


    return tile_to_return_;

  } else {

    return nullptr;

  }

}

void EnemyManager::calculatePath(Tilemap& map, CharacterManager& char_man, Character* enemy){

  if(!restart_path_){

    closest_tile_ = calculateCloserPath(map, char_man, enemy);

    if(closest_tile_ == nullptr){

      Game::selected_scene_ = 4;
      Game::change_scene_ = 1;

    }

    restart_path_ = 1;

  }

}

void EnemyManager::movement(){

  if(nullptr != character_selected_ && nullptr != closest_tile_ && !turn_end_){

    if(character_selected_->sprite_.sprite_.getPosition().x <=
    closest_tile_->get_debugTile().getPosition().x){

      character_selected_->sprite_.sprite_.move({speed_movement_, 0.0f});

    }

    if(character_selected_->sprite_.sprite_.getPosition().x >=
    closest_tile_->get_debugTile().getPosition().x){

      character_selected_->sprite_.sprite_.move({-speed_movement_, 0.0f});

    }

    if(character_selected_->sprite_.sprite_.getPosition().x ==
    closest_tile_->get_debugTile().getPosition().x ||
    (character_selected_->sprite_.sprite_.getPosition().x -
    closest_tile_->get_debugTile().getPosition().x) <= -speed_movement_){

      smooth_movement_end_ = 1;

    }

    if(smooth_movement_end_){

      if(character_selected_->sprite_.sprite_.getPosition().y <=
      closest_tile_->get_debugTile().getPosition().y){

        character_selected_->sprite_.sprite_.move({0.0f, speed_movement_});

      }

      if(character_selected_->sprite_.sprite_.getPosition().y >=
      closest_tile_->get_debugTile().getPosition().y){

        character_selected_->sprite_.sprite_.move({0.0f, -speed_movement_});

      }

    }

    sf::FloatRect boundingbox;

    boundingbox = character_selected_->sprite_.sprite_.getGlobalBounds();
    if(boundingbox.contains(closest_tile_->get_debugTile().getPosition())){

      frames_wait_end_turn_++;
      if(frames_wait_end_turn_ >= 50){
        turn_end_ = 1;
        frames_wait_end_turn_ = 0;
        total_turns_++;
      }

    }

  }

}

void EnemyManager::update(Tilemap& map, CharacterManager& char_man){

  enemyTurns(map, char_man);
  movement();
  checkAliveEnemies(map);

  if(MKA::ListSize(enemy_list_) == 0){

    Game::selected_scene_ = 5;
    Game::change_scene_ = 1;

  }

}

MKA::List* EnemyManager::get_enemyList(){

  return enemy_list_;

}

void EnemyManager::checkAliveEnemies(Tilemap& map){

  Character* character = nullptr;

  for(int j = 0; j < MKA::ListSize(enemy_list_); ++j){

    character = (Character*)MKA::IndexListInfo(enemy_list_, j);

    if(character->getHp() <= 0.0f){
      map.resetTile(map.get_characterMapPosTile(*character));
      MKA::DeleteNodeList(&enemy_list_, j);
    }

  }

}
