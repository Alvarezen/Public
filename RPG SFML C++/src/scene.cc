/*
File: scene.cc
Author: Adam Álvarez Enfedal
Description: scene class for the game
*/

#include <scene.h>
#include <gameobject.h>

Scene::Scene(){

  gameobject_list_ = nullptr;
  scene_window_ = nullptr;

}

Scene::~Scene(){

  MKA::EraseList(&gameobject_list_);

}

void Scene::get_window(sf::RenderWindow& window){

  scene_window_ = &window;

}

void Scene::reset(){

  MKA::EraseList(&gameobject_list_);

}

MKA::List* Scene::get_gameobjectList(){

  return gameobject_list_;

}

void Scene::set_gameobjectList(MKA::List* newlist){

  gameobject_list_ = newlist;

}

void Scene::init(){



}


void Scene::draw(sf::RenderWindow& window){

  GameObject* scenedraw = nullptr;

  for (int i = 0; i < MKA::ListSize(gameobject_list_); i++){

    scenedraw = (GameObject*)MKA::IndexListInfoReverse(gameobject_list_, i);

    scenedraw->draw(window);

  }

}
