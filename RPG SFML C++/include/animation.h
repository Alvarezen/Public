// GUSTAVO: Be careful with the copy-past thing, please.
/**
  * @file sprite.h
  * @brief sprite generator of the game
  * @details This is the file that we use to create sprites, based on texture file
  * @author Saúl Vicente Camacho Díaz <camachodi@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__ 1

#include <SFML/Graphics.hpp>
#include <string.h>
#include <texture.h>

class Animation{

public:

  Animation();

  ~Animation();

  void selectFrame();
  void setFrameCol(float frame);
  void setFrameRow(float frame);
  void animateFrame();

protected:

private:

  Texture texture_;

};

#endif //!__ANIMATION_H__
