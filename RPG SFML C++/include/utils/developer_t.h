/*
File: developer.h
Author: Alvaro Vazquez
Description: developer tools
*/

#ifndef __DEV_H__
#define __DEV_H__
#define _CRT_SECURE_NO_WARNINGS

#include <stdint.h>
#include <mka_list.h>
#include <sql_management.h>

class Tilemap;
class Scene;
class CharacterManager;
class EnemyManager;

class DeveloperTool{

public:

  DeveloperTool();

  ~DeveloperTool();

  void TilemapTool(Tilemap&, Scene&);

  void CharacterTool(CharacterManager&);
  void EnemyTool(EnemyManager&);

  //void CharacterInstantiate(Tilemap&, Character&);
  void Textures();

private:

  void TilemapT(Tilemap&, Scene&);
  void CharacterStats(MKA::List*);
  void CharacterStatus(CharacterManager&);

  uint8_t active_;
  Database ddbb_;

  static char str0[255];
  MKA::List* mylist_;

};

#endif
