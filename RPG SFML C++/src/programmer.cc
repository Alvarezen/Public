/*
File: programmer.cc
Author: Adam Álvarez Enfedal
Description: programmer.cc implementation
*/


#include <string.h>
#include <SFML/Graphics.hpp>
#include "programmer.h"
#include "spells.h"
#include <character.h>


Programmer::Programmer(){

	hp_ = 0.0f;
	mana_ = 0.0f;
	attack_ = 0.0f;
	defense_ = 0.0f;
	criattack_ = 0.0f;

}



Programmer::~Programmer(){


}

void Programmer::init(float hp, float mana, float attack,
			      float defense, float criattack)
{
	for(int i = 0 ; i < 4 ; i++){
		spell_[i] = new Spells();
	}

	spell_[0]->initSpells(1.f,"compile.bat", 8, 0.0f);
	spell_[1]->initSpells(3.f,"Debugging",8, 20.0f);
	spell_[2]->initSpells(-1.f,"Development Tool" ,10, 15.0f); //doesnt scale with stats, cant't crit
	spell_[3]->initSpells(-1.f,"Cibersecurity",10, 15.0f); //doesnt scale with stats, cant't crit

	Character::init(hp,  mana,  attack,
			       defense,  criattack);
}
