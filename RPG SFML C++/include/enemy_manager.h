/**
  * @file enemy_manager.h
  * @brief enemy_manager file of the game
  * @details This is the file which we use for enemy_manager of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */



#ifndef __ENEMYIA__H__
#define __ENEMYIA__H__

#include <SFML/Graphics.hpp>
#include <mka_list.h>

class Tilemap;
class Tile;
class CharacterManager;
class Character;

class EnemyManager{

public:

  enum kIAstate{
    kIAstate_patrol,
    kIAstate_attack
  };

  EnemyManager();

  ~EnemyManager();

  /** @brief Function for init
  *   @return nothing
  *   @param  map_range Use for the map range
  *   @param  amount_range Use for the amount range of the enemies
  *   @param  speed Use for speed
  */

  void init(Tilemap&,
    sf::Vector2i map_range,
    sf::Vector2i amount_range,
    float speed);

  /** @brief Function for manhattan distance
  *   @return nothing
  *   @param  id1 Use for id1 of the distance
  *   @param  id2 Use for id2 of the distance
  */

  int ManhattanDistance(int id1, int id2);

  /** @brief Function for calculapath
  *   @return nothing
  *   @param  tilemap Use for tilemap class
  *   @param  characterManager Use for characterManager class
  *   @param  character Use for character class
  */

  void calculatePath(Tilemap&, CharacterManager&, Character*);

  /** @brief Function for calculapathcloserpath
  *   @return tile
  *   @param  tilemap Use for tilemap class
  *   @param  characterManager Use for characterManager class
  *   @param  character Use for character class
  */

  Tile* calculateCloserPath(Tilemap&, CharacterManager&, Character*);

  /** @brief Function for movement
  *   @return nothing
  */

  void movement();

  /** @brief Function update
  *   @return tile
  *   @param  tilemap Use for tilemap class
  *   @param  characterManager Use for characterManager class
  */

  void update(Tilemap&, CharacterManager&);

  /** @brief Function update
  *   @return character
  *   @param  char_man Use for char_man and range
  */

  Character* get_randomTarget(CharacterManager& char_man);

  /** @brief Function for enemy turns
  *   @return nothing
  *   @param  tilemap Use for tilemap class
  *   @param  characterManager Use for characterManager class
  */

  void enemyTurns(Tilemap&, CharacterManager&);

  MKA::List* get_enemyList();

  /** @brief Function for cheking enemy and his life
  *   @return nothing
  *   @param  tilemap Use for tilemap class
  */

  void checkAliveEnemies(Tilemap& map);

private:

  MKA::List* enemy_list_;
  int init_pos_map_;
  int enemy_amount_;
  int turns_;
  Character* character_selected_;
  Character* target_;
  int smooth_movement_end_;
  uint8_t calculate_distance_;
  Tile* closest_tile_;
  float speed_movement_;
  uint8_t turn_end_;
  int total_turns_;
  uint8_t restart_path_;
  int frames_wait_end_turn_;

};

#endif //!__ENEMYIA__H__
