/**
  * @file boss.h
  * @brief boss file of the game
  * @details This is the file which we use of bosses of the game
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

class Boss : public Character {

public:

  /** enum for the phases of the boss */
  enum kBossPhases
  {

    kBossPhases_none = -1,
    kBossPhases_first = 0,
    kBossPhases_second = 1,

  };

	/** enum for discriminate the type of the boss */
  enum KBossType
  {

    KBossType_none = -1,
    KBossType_gustavo = -2,
    KBossType_fede = -3,
    KBossType_jaime = - 4,

  };

  Boss();

  Boss(const Boss& bosscopy);

 	/** @var variable for enum kBossPhases */ 
  kBossPhases boss_phase_;

  
  void changePhase(KBossType bosstype);

  virtual ~Boss();


private:


};

#endif //!__boss_H__
