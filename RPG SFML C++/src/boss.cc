/*
File: boss.cc
Author: Adam Álvarez Enfedal
Description: boss.cc implementation
*/


#include <string.h>
#include <SFML/Graphics.hpp>
#include "boss.h"


Boss::Boss()
{

}

Boss::~Boss()
{

}


void Boss::changePhase(KBossType bosstype)
{	

	if(hp_ <= ((hp_ * 50) / 100)){

		switch(bosstype)
  		{
    	case KBossType_fede:

			hp_ = hp_ * 2.0f;
			range_ = range_ * 2;
			attack_ = attack_ * 2.0f;
			move_ = move_ * 3;
			defense_ = defense_ * 1.5f;
			criattack_ = criattack_ * 2.0f;

    	break;
		case KBossType_gustavo:

			hp_ = hp_ * 3.0f;
			attack_ = attack_ * 2.0f;
			defense_ = defense_ * 1.5f;
			criattack_ = criattack_ * 3.0f;

    	break;
		case KBossType_jaime:

			hp_ = hp_ * 2.0f;
			attack_ = attack_ * 4.0f;
			defense_ = defense_ * 3.0f;
			criattack_ = criattack_ * 5.0f;

    	break;
		}
	}
}


