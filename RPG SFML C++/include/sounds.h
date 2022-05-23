/**
  * @file sounds.h
  * @brief sounds file of the game
  * @details This is the file which we use for sounds of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __SOUNDS_H__
#define __SOUNDS_H__ 1

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "gameobject.h"
#include <string.h>


class Sounds{

public:

	Sounds();

	~Sounds();

	//void Sounds(const sf::SoundBuffer &buffer);

	void initBuffer(const char* filename);

	void play();

	void pause();

	void stop();

	void setBuffer(sf::SoundBuffer &buffer);
	const sf::SoundBuffer *getBuffer() const;

	void setLoop(bool loop);
	bool getLoop()const;

	void setPlayingOffset(sf::Time timeOffset);
	sf::Time getPlayingOffset()const;

	void setVolume (float volume);
	float getVolume()const;

	void setPosition(const sf::Vector3f &position);
	sf::Vector3f getPosition()const;

	sf::SoundBuffer buffer_;
	sf::Sound sound_;

private:

};


#endif //!__SOUNDS_H__
