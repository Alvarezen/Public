/*
File: character_manager.cc
Author: Adam Álvarez Enfedal
Description: character_manager implementation
*/

#include <SFML/Graphics.hpp>
#include <character_manager.h>
#include <enemy_manager.h>
#include <string.h>
#include <character.h>
#include <tilemap.h>
#include <input.h>
#include <tile.h>
#include <game.h>
#include <ui.h>

int CharacterManager::s_max_actions = 2;

CharacterManager::CharacterManager()
{

  character_list_ = nullptr;
  character_selected_ = nullptr;
  next_tile_ = nullptr;
  map_ = nullptr;
  character_clicked_ = 0;
  character_action_ = kCharacterAction_none;
  character_ended_turn_ = 0;
  end_turn_ = 0;
  characters_all_actions_ = 0;
  character_turn_ = 1;
  moving_ = 0;
  total_turns_ = 0;

}

CharacterManager::~CharacterManager()
{
  MKA::EraseList(&character_list_);
}


MKA::List* CharacterManager::get_characterList()
{

	return character_list_;
}

void CharacterManager::set_characterList(MKA::List* modified_list)
{

	character_list_ = modified_list;

}

void CharacterManager::insertCharacterList(Character& character)
{

  MKA::InsertNodeList(&character_list_, (void*)&character);

}

void CharacterManager::increaseCharacterTurns(Character& character_turns){

  uint8_t aux_turns = character_turns.getTurns();
  aux_turns++;
  character_turns.setTurns(aux_turns);

}

void CharacterManager::characterFinishedTurn(){

  characters_all_actions_++;

}

void CharacterManager::updateCharacters(Tilemap& noruega)
{
  Character* character = nullptr;
  map_ = &noruega;
  int id_found = noruega.selectCharacterCursor();

  for(int i = 0; i < MKA::ListSize(character_list_); ++i){

    character = (Character*)MKA::IndexListInfo(character_list_, i);

    if(id_found == character->get_id()
    && character_clicked_
    && character_action_ != kCharacterAction_attack
    && character->getTurns() < 2
    && character->chartype_ != Character::kCharactersType_enemy){

      noruega.resetRangeCharacter();
      character_selected_ = character;

      character_action_ = kCharacterAction_none;
      character_clicked_ = 0;
    }

    if(nullptr != character_selected_){

      if(character_selected_->get_id() == character->get_id()){

        character->update(noruega);

      }

    }

  }

  if(total_turns_ == 2){

    character_ended_turn_++;

    total_turns_ = 0;

  }

  if(MKA::ListSize(character_list_) == 0){

    Game::selected_scene_ = 4;
    Game::change_scene_ = 1;

  }

}

void CharacterManager::selectorManager(Tilemap& nightcity)
{

  Character* character = nullptr;
  int id_found = nightcity.selectCharacterCursor();

  if(id_found == -1
    && character_action_ == CharacterManager::kCharacterAction_none){
    character_clicked_ = 0;
  }

  for(int i = 0; i < MKA::ListSize(character_list_); ++i){

    character = (Character*)MKA::IndexListInfo(character_list_, i);

    if(character->chartype_ == Character::kCharactersType_enemy){

      if(id_found == character->get_id()
      && character_action_ == kCharacterAction_none){

        character_clicked_ = 0;

      }

    }

  }

}

void CharacterManager::turnCharacters(Tilemap& ceuta)
{

  if(character_ended_turn_ == MKA::ListSize(character_list_)){

    ceuta.resetRangeCharacter();
    character_ended_turn_ = 0;
    character_clicked_ = 0;
    character_selected_ = nullptr;
    next_tile_ = nullptr;
    characterFinishedTurn();

    Character* character = nullptr;

    for(int i = 0; i < MKA::ListSize(character_list_); ++i){

      character = (Character*)MKA::IndexListInfo(character_list_, i);

      uint8_t turn = character->getTurns();
      turn = 0;
      character->setTurns(turn);

    }

    character_turn_ = 0;

  }

}

void CharacterManager::attackManager(
  Tilemap& ceuta,
  EnemyManager& enemyman,
  Ui& feedback){

  if(character_action_ == kCharacterAction_attack
    && character_selected_->getTurns() < 2){

    ceuta.cursor_.attackMode(true);

    MKA::List* chars_in_range = nullptr;
    int* id = nullptr;
    Character* character = nullptr;
    int id_to_attack = 0;
    MKA::List* aux_enemy = enemyman.get_enemyList();

    chars_in_range = ceuta.charactersInRange();
    id_to_attack = ceuta.selectCharacterCursor();

    for(int i = 0; i < MKA::ListSize(chars_in_range); ++i){

      id = (int*)MKA::IndexListInfo(chars_in_range, i);

      for(int j = 0; j < MKA::ListSize(aux_enemy); ++j){

        character = (Character*)MKA::IndexListInfo(aux_enemy, j);

        //If player attacks to empty tile at map
        if(character_clicked_ && id_to_attack == -1){

          character_action_ = kCharacterAction_none;
          character_clicked_ = 0;

        }

        if(*id == character->get_id()
          && character_clicked_
          && character->get_id() != character_selected_->get_id()
          && *id == id_to_attack){

          feedback.combatFeedback(
            *character_selected_, *character,
            character->reciveAttack(*character_selected_)
          );

          increaseCharacterTurns(*character_selected_);
          character_clicked_ = 0;
          character_action_ = kCharacterAction_none;
          character_selected_ = nullptr;
          total_turns_++;
          ceuta.resetRangeCharacter();

        }

      }

    }

  }

  if(character_action_ == kCharacterAction_none){

    ceuta.cursor_.attackMode(false);

  }

}

void CharacterManager::movement(){

  float speed = 2.0f;

  if(nullptr != character_selected_ && nullptr != next_tile_){

      if(character_selected_->sprite_.sprite_.getPosition().x <
      next_tile_->get_debugTile().getPosition().x){

        character_selected_->sprite_.sprite_.move({speed, 0.0f});
        moving_ = 1;
      }

      if(character_selected_->sprite_.sprite_.getPosition().x >
      next_tile_->get_debugTile().getPosition().x){

        character_selected_->sprite_.sprite_.move({-speed, 0.0f});
        moving_ = 1;
      }

      if(character_selected_->sprite_.sprite_.getPosition().y <
      next_tile_->get_debugTile().getPosition().y){

        character_selected_->sprite_.sprite_.move({0.0f, speed});
        moving_ = 1;
      }

      if(character_selected_->sprite_.sprite_.getPosition().y >
      next_tile_->get_debugTile().getPosition().y){

        character_selected_->sprite_.sprite_.move({0.0f, -speed});
        moving_ = 1;
      }

      if(character_selected_->sprite_.sprite_.getPosition() ==
          next_tile_->get_debugTile().getPosition()){

            character_action_ = kCharacterAction_none;
            character_selected_ = nullptr;
            next_tile_ = nullptr;
            moving_ = 0;

          }

  }

}

void CharacterManager::movementManager(Tilemap& melilla){

  if(character_action_ == kCharacterAction_move
    && character_selected_->getTurns() < 2){

    MKA::List* tiles_in_range = nullptr;
    int aiming_tile = 0;
    Tile* tile_id = nullptr;
    Character* character = nullptr;

    tiles_in_range = melilla.tilesInRange();
    aiming_tile = melilla.selectTileCursor();


    for(int i = 0; i < MKA::ListSize(tiles_in_range); ++i){

      tile_id = (Tile*)MKA::IndexListInfo(tiles_in_range, i);

      for(int j = 0; j < MKA::ListSize(character_list_); ++j){

        character = (Character*)MKA::IndexListInfo(character_list_, j);

        if(aiming_tile == tile_id->tile_id_
          && character_clicked_
          && character->get_id() == character_selected_->get_id()){

          if(melilla.moveCharacterAtTile(*character_selected_, tile_id->tile_id_, 1)){

            melilla.resetRangeCharacter();
            next_tile_ = tile_id;
            character_clicked_ = 0;
            increaseCharacterTurns(*character_selected_);
            total_turns_++;
          }

        }

      }

    }

  }

}

Character* CharacterManager::get_characterSelected(){

  return character_selected_;

}

CharacterManager::kCharacterAction CharacterManager::get_characterState(){

  return character_action_;

}

void CharacterManager::set_characterState(kCharacterAction action){

  character_action_ = action;

}

void CharacterManager::endCharacterTurn(){

  if(nullptr != map_){

    uint8_t turns = character_selected_->getTurns();
    turns = 2;
    character_selected_->setTurns(turns);
    map_->resetRangeCharacter();

  }

}

void CharacterManager::set_characterClicked(uint8_t charclicked){

  character_clicked_ = charclicked;

}

uint8_t CharacterManager::get_characterClicked(){

  return character_clicked_;

}

void CharacterManager::update(Tilemap& combat_map_, EnemyManager& enemyman, Ui& ui){

  checkAliveCharacters(combat_map_);

  if(character_turn_){

    movement();
    selectorManager(combat_map_);
    turnCharacters(combat_map_);

    if(!moving_)
    updateCharacters(combat_map_);


    if(nullptr != character_selected_){

      attackManager(combat_map_, enemyman, ui);
      movementManager(combat_map_);

    }

  }

}

void CharacterManager::checkAliveCharacters(Tilemap& map){

  Character* character = nullptr;

  for(int j = 0; j < MKA::ListSize(character_list_); ++j){

    character = (Character*)MKA::IndexListInfo(character_list_, j);

    if(character->getHp() <= 0.0f){
      map.resetTile(map.get_characterMapPosTile(*character));
      MKA::DeleteNodeList(&character_list_, j);
    }

  }

}
