/**
  * @file music.h
  * @brief sounds file of the game
  * @details This is the file which we use for sounds of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __MUS_H__
#define __MUS_H__ 1

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "gameobject.h"
#include <string.h>


class Music{

public:

	Music();

	~Music();

	void init(const char* filename);

	void play();

	void pause();

	void stop();

	void setVolume (float volume);

	void setLoop(bool condition);

	sf::Music music_;
	int music_playing_;


private:

};

#endif //!__MUSIC_H_
