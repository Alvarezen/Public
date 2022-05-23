/*
File: character.cc
Author: Adam Álvarez Enfedal
Description: character implementation
*/

#include <SFML/Graphics.hpp>
#include "character.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <tilemap.h>
#include <tile.h>



Character::Character()
{
  // GUSTAVO: Instead of doing this, please have an actual variable string, 
  // like std::string or char[] , and do a strcpy() or similar operation 
	name_ = "Name";
	hp_ = 0.0f;
	maxhp_ = 0.0f;
	level_ = 1;
	mana_ = 0.0f;
	maxmana_ = 0.0f;
	attack_ = 0.0f;
	defense_ = 0.0f;
	criattack_ = 0.0f;
	alive_ = 1;
  	turns_ = 0;
	experience_ = 0;
	distincion_coin_ = 0;
	range_ = 0;
	col_ = 0;
	max_experience_ = 0;

}

Character::Character(const Character& charcopy)
{
	hp_ = charcopy.hp_;
	mana_ = charcopy.mana_;
	attack_ = charcopy.attack_;
	defense_ = charcopy.defense_;
	criattack_ = charcopy.criattack_;
	alive_ = charcopy.alive_;
  	turns_ = charcopy.turns_;
	experience_ = charcopy.experience_;
	sprite_ = charcopy.sprite_;
	distincion_coin_ = charcopy.distincion_coin_;
	range_ = charcopy.range_;
	col_ = charcopy.col_;
	name_ = charcopy.name_;
	max_experience_ = charcopy.max_experience_;
}

Character::~Character()
{

}

void Character::init(
  const sf::Vector2f pos,
  const sf::Vector2f  scale,
  Texture &texture,
  float maxhp, float maxmana,
  float attack, float defense,
  float criattack, int level,
  uint8_t alive,
  uint8_t turns, int experience,
  kCharactersType chartype, int range,
  float col, const char* name, int max_experience
)
{

	chartype_ = chartype;
	sprite_.initSprite(texture.get_SubSprite({1.0f + (col * 3.0f), 0.0f}, 12, 4));
	name_ = name;
	sprite_.sprite_.setPosition(pos);
	sprite_.sprite_.setScale(scale);
	maxhp_ = maxhp;
	maxmana_ = maxmana;
	hp_ = maxhp_;
	mana_ = maxmana_;
	attack_ = attack;
	level_ = level;
	defense_ = defense;
	criattack_ = criattack;
	alive_ = alive;
	turns_ = turns;
	experience_ = experience;
	range_ = range;
	col_ = col;
	name_ = name;
	max_experience_ = max_experience;

}

void Character::init(float hp, float mana, float attack,
		 float defense, float criattack)
{

    hp_ = hp;
	mana_ = mana;
	attack_ = attack;
	defense_ = defense;
	criattack_ = criattack;

}


void Character::lifeOn(uint8_t life)
{

	alive_ = life;
	life = 1;

}

void Character::checkHealth(){

	if(hp_ <= 0){

		alive_ = 0;
		enable_ = 0;

	}

}

void Character::update(Tilemap& tilemap)
{

	tilemap.updateRangeCharacter(*this);

}

void Character::draw(sf::RenderWindow& window)
{

	checkHealth();

	if(enable_){

		window.draw(sprite_.sprite_);

	}


}

void Character::setHp(float hp)
{

	hp_ = hp;
}

float Character::getHp() const
{

	return hp_;
}

void Character::setMaxHp(float maxhp)
{

	maxhp_ = maxhp;
}

float Character::getMaxHp() const
{

	return maxhp_;
}

void Character::setAttack(float attack)
{

	attack_ = attack;
}

float Character::getAttack() const
{

	return attack_;
}

void Character::setMana(float mana)
{

	mana_ = mana;
}

float Character::getMana() const
{

	return mana_;
}

void Character::setMaxMana(float maxmana)
{

	maxmana_ = maxmana;
}

float Character::getMaxMana() const
{

	return maxmana_;
}

void Character::setDefense(float defense)
{

	defense_ = defense;
}

float Character::getDefense() const
{

	return defense_;
}

void Character::setCriattack(float criattack)
{

	criattack_ = criattack;
}

float Character::getCriattack() const
{

	return criattack_;
}

void Character::setLevel(int level)
{

	level_ = level;
}

int Character::getLevel() const
{

	return level_;
}

void Character::setTurns(uint8_t turns)
{

	turns_ = turns;
}

uint8_t Character::getTurns()
{

	return turns_;
}

void Character::setLife(uint8_t life)
{

	alive_ = life;
}

uint8_t Character::getLife() const
{

	return alive_;
}

void Character::setExperience(int experience)
{

	experience_ = experience;
}

int Character::getExperience() const
{

	return experience_;
}

int Character::getRange()
{

	return range_;
}

Character::kCharactersType Character::getKcharacter() const
{

	return chartype_;
}

void Character::setName(const char* name)
{

	name_ = name;
}

const char* Character::getName() const
{

	return name_;
}

void Character::levelUp()
{

	if (experience_ == max_experience_){

		experience_ = 0;
		max_experience_ += 10;


		hp_ += 10.0f;
		attack_ += 10.0f;
		defense_ += 10.0f;
		mana_ += 10.0f;
		criattack_ += 0.5f;

		level_++;
	}

	if(experience_ > max_experience_){

		experience_ -= max_experience_;
		max_experience_ += 10;

		hp_ += 10.0f;
		attack_ += 10.0f;
		defense_ += 10.0f;
		mana_ += 10.0f;
		criattack_ += 0.5f;

		level_++;
	}
}

int Character::get_maxExp(){

	return max_experience_;

}

int Character::reciveAttack(Character& character)
{

	float dmg_total = 0.0f;
	int crit_prob = 0;

	crit_prob = rand() % 101;

	dmg_total = (character.attack_ * (100.0f / (100.0f + defense_)));

	if((float)crit_prob <= (character.criattack_ * 100.0f))
	{
		dmg_total = dmg_total * 2.0f;
	}

	hp_ -= dmg_total;

	return (int)dmg_total;

}
