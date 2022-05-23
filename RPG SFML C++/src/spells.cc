/*
File: spells.cc
Author: Andres
Description: spells implementation
*/

#include <string.h>
#include "spells.h"

Spells::Spells(){
	damage_ = 0.f;
	name_ = "0";
	mana_ = 0.f;
	range_= 0;
}

Spells::~Spells(){

}

void Spells::initSpells(float damage, const char* name, int range, float mana){

	mana_ = mana;
	range_ = range;
	damage_ = damage;
	name_ = name;

}

uint8_t Spells::checkMana(float character_mana){

	if(character_mana > mana_){
			return 1;
	}else{
			return 0;
	}
}

void Spells::castSpell(float *character_mana){

	*character_mana -= mana_;

}

void Spells::spellDamage(float *target_stat){

	*target_stat -= damage_;

}

void Spells::draw(sf::RenderWindow& window)
{
  // GUSTAVO: ???
	window;

}
