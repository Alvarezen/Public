// GUSTAVO: Be careful with the copy-paste workflow.
// You have copied the same header as sprite.h .
/**
  * @file sprite.h
  * @brief sprite generator of the game
  * @details This is the file that we use to create sprites, based on texture file
  * @author Saúl Vicente Camacho Díaz <camachodi@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __TEXTURE_H__
#define __TEXTURE_H__ 1

#include <SFML/Graphics.hpp>
#include <gameobject.h>
#include <string.h>

class Texture{

public:

  Texture();

  ~Texture();

  void set_TextureFromFile(const char* _name, bool is_char = false);
  void set_TextureFromBuffer(const sf::Vector2i size);
  sf::Sprite& get_SubSprite(sf::Vector2f _reqFrame, float _col, float _row);
  sf::Sprite& get_Sprite();

  static Texture* CreateTexture();
  // GUSTAVO: This should not be public for the factory to work.
  static int total_textures_;

  sf::Texture* texture_;
  sf::Vector2f framePixelSize_;
  sf::Vector2f requiredFrame_;
  float nCol;
  float nRow;

};

#endif //!__ASSET_H__
