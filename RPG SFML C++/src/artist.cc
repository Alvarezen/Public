/*
File: artist.cc
Author: Adam Álvarez Enfedal
Description: artist implementation
*/

#include <string.h>
#include "artist.h"


Artist::Artist(){

}


Artist::~Artist(){

}

void Artist::init(float hp, float mana, float attack,
									float defense, float criattack)
{

	for(int i = 0 ; i < 4 ; i++){
		spell_[i] = new Spells();
	}

	spell_[0]->initSpells(1.0f,"Sketch", 4, 0.0f);
	spell_[1]->initSpells(3.0f,"3D Model", 5, 20.0f);
	spell_[2]->initSpells(5.0f,"4K Texture", 5, 40.0f);
  spell_[3]->initSpells(-15.0f,"Patreon", 20, 25.0f); //doesnt scale with stats, cant't crit

	Character::init(hp,  mana,  attack, defense, criattack);
}
