/*
File: combat.h
Author: Alvaro Vazquez
Description: combat scene implementation
*/

#ifndef __COMBAT_SCENE__
#define __COMBAT_SCENE__

#include <scene.h>
#include <SFML/Graphics.hpp>

class Tilemap;
class Character;
class CharacterManager;
class EnemyManager;
class DeveloperTool;
class Ui;
class Camera;

class Combat : public Scene{

public:

  Combat();

  virtual ~Combat();

  void init() override;

  void input() override;

  void update() override;


private:

  Tilemap* combat_map_;
  CharacterManager* characters;
  EnemyManager* enemies_;
  DeveloperTool* dev_tool_map_;
  Ui* ui_;
  Camera* camera_;

};

#endif //!__COMBAT_SCENE__
