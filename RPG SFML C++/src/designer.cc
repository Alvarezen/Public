/*
File: designer.cc
Author: Adam Álvarez Enfedal
Description: designer implementation
*/


#include <string.h>
#include <SFML/Graphics.hpp>
#include "designer.h"


Designer::Designer(){

	hp_ = 0.0f;
	mana_ = 0.0f;
	attack_ = 0.0f;
	defense_ = 0.0f;
	criattack_ = 0.0f;

}


Designer::~Designer(){

}

void Designer::init(float hp, float mana, float attack,
			      float defense, float criattack)
{
	for(int i = 0 ; i < 4 ; i++){
		spell_[i] = new Spells();
	}

	spell_[0]->initSpells(-1.f,"Sensation",10, 15.f);
	spell_[1]->initSpells(0.75f,"Challenge",6,0.0f);
	spell_[2]->initSpells(-0.35f,"Fellowship",6, 0.0f);
	spell_[3]->initSpells(0.f,"Narrative",3 , 100.0f);

	Character::init(hp,  mana,  attack,
			       defense,  criattack);
}
