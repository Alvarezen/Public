/**
  * @file tile.h
  * @brief tile file of the game
  * @details File that is use to tile implementation
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __TILE_H__
#define __TILE_H__ 1

#include <SFML/Graphics.hpp>
#include <stdint.h>
#include <gameobject.h>

class Tile : public GameObject{

public:

  Tile();

  ~Tile();

  /** @brief Initalize tile
  *
  *   Initialize tile by taking the position, size, id, and the font
  *    for the debug mode, by default the tile will be walkable.
  *    Also initializes the rectangles shape for determinate the
  *    range of a character
  *
  *   @param pos The position in world coordinates
  *   @param size The size of the Tile in world coordinates
  *   @param id The id that will identify the Tile
  *   @param font The font that will be use for debug mode
  *   @param walkable Establishes if the Tile can be walkable or no
  */
  void init(sf::Vector2f pos, sf::Vector2f size, int id,
    sf::Font& font, uint8_t walkable = 1);

  sf::RectangleShape& get_debugTile();

  /** @brief Draw tile elements
  *
  *   Draws the drawable tile objects at screen
  *
  *   @param window The render window used at the game
  */
  void draw(sf::RenderWindow& window) override;

  /** @brief Draws the rectangle that represents a range
  *
  *   Draws the rectangles that will appears visually with
  *    a default color that represents a range
  *
  *   @param window The render window used at the game
  */
  void drawRange(sf::RenderWindow& window);

  /** Position of the Tile in world coordinates */
  sf::Vector2f pos_;
  /** Size of the Tile in world coordinates */
  sf::Vector2f size_;
  /** Establishes if the Tile is walkable or no */
  uint8_t walkable_;
  /** Establishes if the Tile has a Item object with his id, -1 otherwise */
  int item_id_;
  /** Establishes if the Tile has a Character object with his id, -1 otherwise */
  int character_id_;
  /** Establishes the Tile id */
  int tile_id_;
  /** Establishes if the Tile is a ranged one */
  uint8_t in_range_;
  /** Establishes if the tile is into the calculation of Manhattan Distance */
  int manhattan_dis_;

private:

  /** The rectangle shape that has the debug tile */
  sf::RectangleShape* debug_tile_;
  /** The rectangle shape that has the range tile */
  sf::RectangleShape* range_tile_;
  /** The number that has the debug tile*/
  sf::Text* debug_tile_num_;
  /** The value that establishes when the debug rectangle has to appear */
  uint8_t draw_debug_;


};

#endif //!__TILE_H__
