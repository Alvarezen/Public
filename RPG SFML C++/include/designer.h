/**
  * @file designer.h
  * @brief designer file of the game
  * @details This is the file which we use for designer of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __DESIGNER_H__
#define __DESIGNER_H__ 1

#include <string.h>
#include "character.h"
#include "spells.h"


class Designer : public Character {


public:

	Designer();

	~Designer();

	/** @brief init for designer spells
 	*   Initialization the designer atributes for using in spells class
  *   @return nothing
 	*   @param hp hp for the designer 
	*   @param mana mana for the designer 
	*   @param attack attack for the designer 
	*   @param defense defense for the designer 
 	*   @param criattack criattack for the designer 	
  */

	void init(float hp, float mana, float attack,
			  float defense, float criattack) override;


private:

	/** @var array for the artist spells */
	Spells* spell_[4];//target aliado, curar 1 aliado
	// Spells challenge_;//base attack
	// Spells fellowship_;//target equipo, cura equipo
	// Spells narrative_;//el enemigo se queda escuchando la narrativa, perdiendo el turno

};



#endif //!__DESIGNER_H__
