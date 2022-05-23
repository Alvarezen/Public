/**
  * @file doors.h
  * @brief doors file of the game
  * @details This is the file which we use for doors of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __DOORS_H__
#define __DOORS_H__ 1

#include <SFML/Graphics.hpp>
#include <string.h>
#include "gameobject.h"


class Doors {

public:

   Doors();

   ~Doors();

  /** @brief Function for init 
  *   @return nothing
  *   @param  origin Use for the origin map
  *   @param  destiny Use for the destiny map
  *   @param  t_trigger Use for the tile which use for change the map
  */

	void init(int, int, int, int);

  int get_mapOrigin();

  int get_mapDestiny();

  int get_tileTrigger();

  int get_tileDestiny();

private:

	/** @var integer for the origin map */
  int map_origin_;
	/** @var integer for the destiny map */
  int map_destiny_;
	/** @var integer for the tile which use for change the map */
  int tile_trigger_;
/** @var integer for the tile which use for the destiny to change the map */
  int tile_destiny_;


};

#endif //!__DOORS_H__
