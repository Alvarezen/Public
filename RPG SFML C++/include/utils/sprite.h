/**
  * @file sprite.h
  * @brief sprite generator of the game
  * @details This is the file that we use to create sprites, based on texture file
  * @author Saúl Vicente Camacho Díaz <camachodi@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __SPRITE_H__
#define __SPRITE_H__ 1

#include <SFML/Graphics.hpp>
#include <texture.h>
#include <gameobject.h>
#include <input.h>

class Sprite : public GameObject{

public:

  Sprite();

  ~Sprite();

  /** @brief Initilization for sprites
 	*   Initialization the sprite based on texture
  *   @return nothing
 	*   @param const Texture& newtexture
  */

  void initSprite(const Texture& newtexture);
  void initSprite(const sf::Sprite& sprite);
  sf::Color getSpritePixel(const char* png_file, const sf::Vector2i coords);

  sf::Vector2f get_position();
  void set_position(const sf::Vector2f pos);

  float get_globalWidth();
  float get_globalHeight();

  float get_localWidth();
  float get_localHeight();

  sf::Vector2f get_scale();
  void set_scale(sf::Vector2f scale);

  sf::Vector2f get_origin();
  void set_origin(sf::Vector2f origin);

  float get_rotation();
  void set_rotation(float rot);

  void draw(sf::RenderWindow&) override;

  sf::Sprite get_sprite();

  void set_boxBounds();

  int isSelected(sf::RenderWindow& window);//0 = false, 1 = true;

  int isClicked(sf::RenderWindow& window);//0 = false, 1 = true;

// GUSTAVO: Why did you remove private/protected?
//private:

  sf::Sprite sprite_;

  Input click_;

  sf::RectangleShape box_;

};

#endif
