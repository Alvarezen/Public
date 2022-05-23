/**
  * @file tilemap.h
  * @brief tilemap file of the game
  * @details File that is use to tilemap implementation
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __TILEMAP_H__
#define __TILEMAP_H__
#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <mka_list.h>
#include <stdint.h>
#include <gameobject.h>
#include <cursor.h>

class Sprite;
class Texture;
class Item;
class Character;
class CharacterManager;
class Database;

class Tilemap : public GameObject{

public:

  Tilemap();

  ~Tilemap();

  /** @brief Initalize tilemap
  *
  *   Initialize tilemap by taking a font for the numbers of debug mode
  *
  *   @param f_font The font file direction
  */
  void init(const char* f_font = nullptr);

  /** @brief Generates a new tilemap
  *
  *   Generates a new tilemap from a new texture, the algorithm calculates
  *   the grid based on the texture size (width, height) and the tile size,
  *   then generates tiles with the calculated properties and goes inside
  *   a list
  *
  *   @param texture The texture base for grid
  *   @param tilesize Establishes the size of all tiles
  */
  uint8_t generateNewGrid(Texture&, int tile_size);

  /** @brief Save new tilemap at database
  *
  *   Generates a new tilemap from a new texture, the algorithm calculates
  *   the grid based on the texture size (width, height) and the tile size,
  *   then generates tiles with the calculated properties and goes inside
  *   a list
  *
  *   @param ddbb The database where the tilemap will be saved
  *   @param texture Establishes which texture fits to that grid
  *   @param tile_size Establishes the size of all tiles
  */
  void SaveNewTilemap(Database& ddbb, int texture, int tile_size, int id);

  /** @brief Load tilemap from database
  *
  *   Generates the tilemap by a tileid that will be searched by
  *   the querie of the database
  *
  *   @return If the load process was success with 1, 0
  *     otherwise
  *   @param ddbb The database where the tilemap will be loaded from
  *   @param tilemap_id Identifies the tilemap that has to be loaded
  *     from ddbb tilemap id
  */
  uint8_t LoadTilemap(Database& ddbb, int tilemap_id);

  /** @brief Delete tilemap at database
  *
  *   Deletes tilemap at database, the tiles and the tilemap itself
  *
  *   @param ddbb The database where the tilemap will be deleted
  *   @param tilemap_id Identifies the tilemap that has to be deleted
  */
  uint8_t DeleteTilemap(Database& ddbb, int tilemap_id);

  /** @brief Update tilemap at database
  *
  *   Updates tilemap at database, the tiles and the tilemap itself
  *
  *   @param ddbb The database where the tilemap will be deleted
  *   @param tilemap_id Identifies the tilemap that has to be deleted
  *   @param texture Takes the texture file to tilemap database
  *   @param tile_size Tells to database the size of the tilemap's tiles
  */
  void UpdateTilemap(Database& ddbb,
    int tilemap_id,
    int texture,
    uint32_t tile_size);

  /** @brief Draws tile debug
  *
  *   Draws tile debug, showing his tile's number and square area
  *
  *   @param window The render window used at the game
  */
  void drawGridDebug(sf::RenderWindow&);

  /** @brief Edit grid at debugmode
  *
  *   Edit at debug mode, essentially it can be modified if the
  *   tile is walkable or not
  *
  *   @param window The render window used at the game
  */
  void editGrid(sf::RenderWindow&);

  /** @brief Set Character at pos in tilemap
  *
  *   Sets chatacter at the position of a tile into tilemap
  *
  *   @return correctly_done Returns 0 if couldn't process, 1 otherwise
  *   @param Character The character wished to place into a specific tile
  *   @param int The tile's number of placement
  */
  uint8_t set_characterMapPos(Character&, const int, uint8_t smooth_move = 0);

  /** @brief Get Character at pos in tilemap
  *
  *   Gets the actual position of a character
  *
  *   @return int The tile position where the character is, -1 otherwise
  *   @param Character The character that the map need to found
  */
  int get_characterMapPos(Character&);

  /** @brief Get Character at pos in tilemap
  *
  *   Gets the actual position of a character but the function
  *    gives the tile object
  *
  *   @return Tile The Tile object where the character is
  *   @param Character The Character that the map need to found
  */
  Tile& get_characterMapPosTile(Character&);

  /** @brief Set Item at pos in tilemap
  *
  *   Sets Item at the position of a tile into tilemap
  *
  *   @return correctly_done Returns 0 if couldn't process, 1 otherwise
  *   @param window The render window used at the game
  *   @param const int The tile's number of placement
  */
  uint8_t set_ItemMapPos(Item&, const int);

  /** @brief Input movement of a character
  *
  *   Sets the inputs pressed by the player and in function of that
  *    key pressed it'll represent a direction of movement
  *
  *   @return If the character is moving
  *   @param Character The Character that the player is using
  */
  uint8_t inputMovement(Character&);

  /** @brief The grid movement
  *
  *   Sets the vertical and horizontal movements depending
  *    on the input given by the player
  *
  *   @param Character The Character that the player is using
  *   @param const int The offset of the movement at each tile
  */
  void gridMovement(Character&, const int);

  /** @brief Set the cursor at map position
  *
  *   Gives to the cursor the first position at
  *   a walkable tile
  *
  */
  void set_cursorFirstMapPos();

  /** @brief Looks for a character in tilemap selected by cursor
  *
  *   Looks for a character in the tilemap
  *   selected by the cursor
  *
  *   @return The id of the character selected by cursor, -1 otherwise
  */
  int selectCharacterCursor();

  /** @brief Looks for a tile in tilemap selected by cursor
  *
  *   Looks for a tile in the tilemap
  *   selected by the cursor
  *
  *   @return The id of the tile selected by cursor, -1 otherwise
  */
  int selectTileCursor();

  /** @brief Moves the character to a determinated tile
  *
  *   Moves the character to a determinated tile if this one
  *   is walkable or there is not anyone else in that tile
  *
  *   @return 1 if the character successfully moved, 0 otherwise
  *   @param Character The character that is choseen to move
  */
  uint8_t moveCharacterAtTile(Character&, const int, uint8_t);

  /** @brief Set the cursor at first map position
  *
  *   Gives to the cursor the first position at
  *   a walkable tile
  *
  */
  void updateCursor();

  /** @brief Draws character's range
  *
  *   Draws character's range previously calculated
  *
  *   @param window The render window used at the game
  */
  void drawRangeCharacter(sf::RenderWindow& window);

  /** @brief Updates character's range attack
  *
  *   Calculates respecting the character's position
  * 	the range in tiles of the character's range
  *
  *   @param Character The Character at Tilemap with a range
  */
  MKA::List* updateRangeCharacter(Character&, int custom_range = 0);

  /** @brief Resets character range
  *
  *   Resets character range cleaning all tiles of tilemap
  *
  */
  void resetRangeCharacter();

  /** @brief Characters in Range
  *
  *   Analize all tiles at map and looks for the character
  *   it pass at the function, then determinates if inside
  *   his range if there are characters
  *
  *   @return List of character IDs in range, nullptr otherwise
  */
  MKA::List* charactersInRange();

  /** @brief Characters in Tiles
  *
  *   Analize all tiles at map and looks for the tile where
  *    the Character is, and the function stores the Tile
  *    into a local List
  *
  *   @return List of Tiles where there is a character, nullptr otherwise
  */
  MKA::List* charactersInTiles();

  /** @brief Gets the tiles in range
  *
  *   Gets a list of tiles that are ranged by the character
  *
  *   @return List of tile IDs in range, nullptr otherwise
  */
  MKA::List* tilesInRange();

  /** @brief Input cursor at tilemap
  *
  *   Updates input cursor at game based on window viewport
  *
  *   @param window The render window used at the game
  */
  void input(sf::RenderWindow& window);

  /** @brief Update tilemap elements
  *
  *   Updates objects at game at each frame
  *
  */
  void update();

  /** @brief Draw tilemap elements
  *
  *   Draws the drawable tilemap objects at screen
  *
  *   @param window The render window used at the game
  */
  void draw(sf::RenderWindow& window) override;

  /** @brief Tilemap total size (width x height)
  *
  *   Getter that gives the total size of the tilemap in tiles number
  *
  *   @return The total size of the tilemap in tiles number
  */
  int get_tilemapSize();

  /** @brief Calculates Manhattan Distance
  *
  *   With two tiles the algorithm calculates the manhattan
  *   distance between them. It uses the theory of the hypotenusa
  *   taking the two points calculating the result by the rednecks
  *   with the map size
  *
  *   @return The distance between two tiles
  */
  int ManhattanDistance(int tile1, int tile2);

  /** @brief Resets Tile
  *
  *   The function takes a tile to reset his values to default
  *
  *   @param The Tile that will be reseted
  */
  void resetTile(Tile& tile);

  /** Cursor of tilemap for execute actions outside other classes */
  Cursor cursor_;
  /** Indicates if debug mode is activated at 1, 0 otherwise */
  uint8_t debugmode_;
  /** Sprite that will take and draw the tilemap texture */
  Sprite* sprite_;
  /** Position at world coordenates of tilemap texture */
  sf::Vector2f map_worldposition_;

private:

  /** The total number of tiles (width x height) */
  int total_grid_size_;
  /** The number of tiles (width x height) */
  sf::Vector2i grid_size_;
  /** List of the tiles for build the tilemap grid */
  MKA::List* grid_list_;
  /** Font that will be assigned to the tile for debug mode */
  sf::Font font_;

};


#endif //!__TILEMAP_H_
