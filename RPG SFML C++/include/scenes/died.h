//Author Andres Carsana
#ifndef __DIE_H__
#define __DIE_H__ 1

#include "label.h"
#include <scene.h>
#include <SFML/Audio.hpp>
#include <sprite.h>
#include <texture.h>


class Died : public Scene{

public:

  Died();

  virtual ~Died();

  void init() override;

  void input() override;

  void update() override;

private:

  Texture* died_texture_;
  Sprite *died_sprite_;

  Texture* died_cursor_texture_;
  Sprite *died_cursor_sprite_;

  Label *label_;


};

#endif
