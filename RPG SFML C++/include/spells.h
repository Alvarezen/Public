/**
  * @file spells.h
  * @brief spells file of the game
  * @details This is the file which we use for spells of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __SPELLS_H__
#define __SPELLS_H__ 1

#include "gameobject.h"
#include <string.h>
#include <stdint.h>


class Spells : public GameObject{

public:

	Spells();

	~Spells();

  /** @brief Initilization the Spells attributes
  *
  *   Initialization the Spells atributtes for using it in the combat
  *   and other ui function
  *
  *   @return nothing
  *   @param name The name of the spell
  *   @param mana The mana cost of the spell
  *   @param range The range of the spell
  *   @param damage The damage of the spell
  *
  */

	void initSpells(float mana, const char* name, int range, float damage);
	// void getSpellDamage();
	// float getSpellMana();
	// int getSpellRange();
	// std::string getSpellName();

	uint8_t checkMana(float character_mana);
	void castSpell(float *character_mana);
	void spellDamage(float *target_life);

	const char* name_;
	float damage_;  //PARA CURAS DAÑO NEGATIVO EJ: heal.damage_ = -20;
	float mana_;
	int range_;

	void draw(sf::RenderWindow&) override;

protected:


private:


};

#endif //!__SPELLS_H__
