/**
  * @file camera.h
  * @brief camera file of the game
  * @details This is the file which we use of camera of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __CHAMANAGER_H__
#define __CHAMANAGER_H__

#include <SFML/Graphics.hpp>
#include <mka_list.h>
#include "sprite.h"
#include <ui.h>

class Tilemap;
class Character;
class Tile;
class EnemyManager;
class Ui;

class CharacterManager{

public:

  enum kCharacterAction{
    kCharacterAction_none = -1,
    kCharacterAction_attack = 0,
    kCharacterAction_move = 1
  };

  CharacterManager();

  ~CharacterManager();

  void init();

  /** @brief Insert character on a list
  *   Insertation the character on a character list to use the list
  *   on diferent scenes of the games.
  *   @return nothing
  *   @param character Object of the list
  *
  */
  void insertCharacterList(Character& character);

  /** @brief Getter of the character list
  *   Getter the character`s list of the game to use it in another
  *   class of the game.
  *   @return character_list_
  */
  MKA::List* get_characterList();

  /** @brief Setter of the character list
  *   Setter the character`s list of the game to use it in another
  *   class of the game.
  *   @return character_list_
  *   @param modified_list Use to can modify the character list
  *   on another class of the game.
  */
  void set_characterList(MKA::List* modified_list);

  void updateCharacters(Tilemap& noruega);

  void attackManager(Tilemap& ceuta, EnemyManager& enemyman, Ui& feedback);

  void movementManager(Tilemap& melilla);

  void turnCharacters(Tilemap& melilla);

  void incraseActionsAtTurn();

  void characterFinishedTurn();

  void selectorManager(Tilemap& nightcity);

  Character* get_characterSelected();

  kCharacterAction get_characterState();
  void set_characterState(kCharacterAction);

  void endCharacterTurn();

  void set_characterClicked(uint8_t);
  uint8_t get_characterClicked();

  void update(Tilemap&, EnemyManager& enemyman, Ui&);

  void movement();

  void checkAliveCharacters(Tilemap& map);

  void increaseCharacterTurns(Character&);

  uint8_t character_turn_;
  int characters_all_actions_;

private:

  /** @var List data type for characters list.*/
  MKA::List* character_list_;
  Character* character_selected_;
  Tile* next_tile_;
  Tilemap* map_;
  kCharacterAction character_action_;
  static int s_max_actions;
  int character_ended_turn_;
  int total_turns_;
  uint8_t end_turn_;
  uint8_t character_clicked_;
  uint8_t moving_;

};

#endif //!__CHAMANAGER_H__
