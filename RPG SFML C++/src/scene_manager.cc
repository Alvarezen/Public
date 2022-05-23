/*
File: scenemanager.cc
Author: Adam Álvarez Enfedal
Description: scene_manager class implementation
*/

#include <SFML/Graphics.hpp>
#include <scene_manager.h>
#include <string.h>
#include <scene.h>
#include <developer_t.h>
#include <game.h>

SceneManager::SceneManager()
{

  scene_list_ = nullptr;
  dev_tool_ = nullptr;

}

SceneManager::~SceneManager()
{

  MKA::EraseList(&scene_list_);

  if(nullptr != dev_tool_){

    delete dev_tool_;

  }

}

void SceneManager::insertSceneList(Scene& scene)
{

  Scene* sceneptr = &scene;

  MKA::InsertNodeList(&scene_list_, (void*)sceneptr);

}

Scene& SceneManager::get_scene(const int nscene){

  return *(Scene*)MKA::IndexListInfoReverse(scene_list_, nscene);

}

uint8_t SceneManager::deleteSceneList(const int nscene){

  if(MKA::DeleteNodeList(&scene_list_, nscene)){

    return 1;

  } else {

    return 0;

  }

}
