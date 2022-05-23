/**
  * @file techartist.h
  * @brief techartis file of the game
  * @details This is the file which we use for techartis of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __TECART_H__
#define __TECART_H__ 1

#include <SFML/Graphics.hpp>
#include <string.h>
#include "character.h"
#include "spells.h"


class Tecnicalartist : public Character {

public:

	Tecnicalartist();

  	~Tecnicalartist();

	void init(float hp, float mana, float attack,
			  float defense, float criattack) override;


private:
	Spells* spell_[4];//base att
	// Spells shading_;//stealths ally
	// Spells render_;//next target ally attack crits
	// Spells particle_;//AoE attack
};

#endif //!__TECART_H__
