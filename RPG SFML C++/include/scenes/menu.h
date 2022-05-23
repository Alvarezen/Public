//Author Andres Carsana
#ifndef __MEN_H__
#define __MEN_H__ 1

#include "label.h"
#include <scene.h>
#include <SFML/Audio.hpp>
#include <sprite.h>
#include <texture.h>
#include <sounds.h>
#include <music.h>


class Menu : public Scene{

public:

  Menu();

  virtual ~Menu();

  void init() override;

  void input() override;

  void update() override;

  void drawMenu(sf::RenderWindow &);

private:

  Texture* menu_texture_;
  Sprite *menu_sprite_;

  // sf::Music music_;
  Sounds cursor_sound_;
  // int music_playing_;
  Music music_;

  Texture* menu_cursor_texture_;
  Sprite *menu_cursor_sprite_;

  Label *label_[4];



};

#endif
