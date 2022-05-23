/**
  * @file scene.h
  * @brief scene file of the game
  * @details This is the file which we use for scene of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __SCENE_H__
#define __SCENE_H__

#include <SFML/Graphics.hpp>
#include <stdint.h>
#include <mka_list.h>

class Scene{

public:

    Scene();

    virtual ~Scene();

    void get_window(sf::RenderWindow& window);

    void reset();

    MKA::List* get_gameobjectList();
    void set_gameobjectList(MKA::List*);

    virtual void init();

    virtual void input() = 0;

    virtual void update() = 0;

    void draw(sf::RenderWindow&);

protected:

  MKA::List* gameobject_list_;
  sf::RenderWindow* scene_window_;

};

#endif
