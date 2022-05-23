/**
  * @file programmer.h
  * @brief programmer file of the game
  * @details This is the file which we use for programmer of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __PGMR_H__
#define __PGMR_H__ 1

#include <SFML/Graphics.hpp>
#include <string.h>
#include "character.h"
#include "spells.h"



class Programmer : public Character {


public:

	Programmer();

	~Programmer();

	void init(float hp, float mana, float attack,
			      float defense, float criattack) override;

	Spells* spell_[4];//base.attack
	// Spells algorithm_;//heavy.attack
	// Spells dtools_; //targetear aliado para subir su ataque
	// Spells ciberseg_; //targetear aliado para subir su defensa

};



#endif //!__PGMR_H__
