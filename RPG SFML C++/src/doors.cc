/**
  * @file doors.h
  * @brief doors file of the game
  * @details This is the file which we use for doors of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#include <doors.h>


Doors::Doors(){

    map_origin_ = 0;
    map_destiny_ = 0;
    tile_trigger_ = 0;

}


Doors::~Doors(){


}

void Doors::init(int origin, int destiny, int t_trigger, int tile_dest){

    map_origin_ = origin;
    map_destiny_ = destiny;
    tile_trigger_ = t_trigger;
    tile_destiny_ = tile_dest;

}

int Doors::get_mapOrigin(){
  return map_origin_;
}

int Doors::get_mapDestiny(){
  return map_destiny_;
}

int Doors::get_tileTrigger(){
  return tile_trigger_;
}

int Doors::get_tileDestiny(){
  return tile_destiny_;
}
