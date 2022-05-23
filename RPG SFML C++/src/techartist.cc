/*
File: technicalartist.cc
Author: Adam Álvarez Enfedal
Description: techincal artist implementation
*/


#include <string.h>
#include <SFML/Graphics.hpp>
#include "techartist.h"



Tecnicalartist::Tecnicalartist(){

	hp_ = 0.0f;
	mana_ = 0.0f;
	attack_ = 0.0f;
	defense_ = 0.0f;
	criattack_ = 0.0f;

}



Tecnicalartist::~Tecnicalartist(){

}

void Tecnicalartist::init(float hp, float mana, float attack,
			      float defense, float criattack)
{
	for(int i = 0 ; i < 4 ; i++){
		spell_[i] = new Spells();
	}

	spell_[0]->initSpells(-1.0f,"Shading Tools",10, 30.0f);
	spell_[1]->initSpells(2.0f,"Efficient Assets",10, 10.0f);
	spell_[2]->initSpells(0.0f,"High Quality Render",6 , 20.0f);
	spell_[3]->initSpells(0.35f,"Particle Systems",3, 20.0f);

	Character::init(hp,  mana,  attack,
			       defense,  criattack);
}
