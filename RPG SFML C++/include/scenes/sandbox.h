/**
  * @file sandbox.h
  * @brief sandbox file of the game
  * @details This is the file which we use for sandbox scene
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __SANDBOX_SCENE__
#define __SANDBOX_SCENE__1

#include <scene.h>
#include <music.h>
#include <SFML/Graphics.hpp>

/** forward declarations */
class Tilemap;
class Character;
class CharacterManager;
class DeveloperTool;
class EnemyManager;
class Ui;
class Camera;
class Doors;
class GameManager;
class Sprite;
class Texture;
class Label;

class Sandbox : public Scene{

public:

  Sandbox();

  virtual ~Sandbox();

  void init() override;

  void input() override;

  void update() override;

  /** @brief Function for load next map
 	*   Initialization the artist atributes for using in spells class
  *   @return nothing
  */

  void LoadNextMap();

  void LoadMap(Doors&, GameManager&);


private:

	/** @var pointer for the class Door forward declaration */
  Doors* doors_[3];
  /** @var pointer for the class CharacterManager forward declaration */
  CharacterManager* characters;
  /** @var pointer for the class EnemyManager forward declaration */
  EnemyManager* enemies_;
	/** @var pointer for the class TileMap forward declaration */
  Tilemap* sandbox_map_;
	/** @var pointer for the class DeveLoperTool forward declaration */
  DeveloperTool* dev_tool_map_;
	/** @var pointer for the class Camera forward declaration */
  Camera* camera_;
	/** @var pointer for the class Character forward declaration */
  Character* free_move_char_;

  /** @var sprite for saving*/
  Texture* texture_mogu_;
  Sprite* mogu_;
  Label* save_;
  Music music_;


};

#endif //!__SANDBOX_SCENE__
