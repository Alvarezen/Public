/**
  * @file artist.h
  * @brief artist file of the game
  * @details This is the file which we use of rsubcharacter artist
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __ARTIST_H__
#define __ARTIST_H__ 1

#include <string.h>
#include <character.h>
#include "spells.h"


class Artist : public Character {

public:

   Artist();

  ~Artist();

	/** @brief init for artist spells
 	*   Initialization the artist atributes for using in spells class
  	*   @return nothing
 	*   @param hp hp for the artist 
	*   @param mana mana for the artist 
	*   @param attack attack for the artist 
	*   @param defense defense for the artist 
 	*   @param criattack criattack for the artist 	
  	*/

	void init(float hp, float mana, float attack,
			  float defense, float criattack) override;

private:

	/** @var array for the artist spells */
	Spells* spell_[4];//base attack
	// Spells model_;//heavy attack
	// Spells hdtexture_;//super attack
	// Spells patreon_;// target tiene que ser aliado, ripristina mana
	//
	// void turn(char turn_);

};

#endif //!__ARTIST_H__
