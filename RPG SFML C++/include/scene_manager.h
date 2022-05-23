/**
  * @file scene_manager.h
  * @brief scene_manager file of the game
  * @details This is the file which we use for scene_manager of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __SCENEMAN_H__
#define __SCENEMAN_H__1

#include <SFML/Graphics.hpp>
#include <mka_list.h>
#include "gameobject.h"

class Scene;
class DeveloperTool;

class SceneManager{

public:

  SceneManager();

  ~SceneManager();

  void init();

  void insertSceneList(Scene& scene);

  uint8_t deleteSceneList(const int nscene);

  Scene& get_scene(const int nscene);

  MKA::List *scene_list_;

private:

  DeveloperTool *dev_tool_;


};


#endif //!__SCENEMAN_H__
