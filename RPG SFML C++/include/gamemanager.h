/**
  * @file gamemanager.h
  * @brief gamemanager file of the game
  * @details File that is use to get de data of the game
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include <stdint.h>
#include <sql_management.h>
#include <SFML/Graphics.hpp>

class Texture;

class GameManager{

public:

  ~GameManager();

  static uint32_t s_windowWidth_;
  static uint32_t s_windowHeight_;

  void init();

  WindowData* get_windowDataFromDatabase();
  void get_classesDataFromDatabase();
  MKA::List* get_itemsDataFromDatabase();
  void set_charactersFromDatabase(MKA::List**);
  Texture* get_textureFromDatabaseWithTag(const char*);
  sf::Font* get_fontFromDatabaseWithTag(const char*);
  void set_charactersToDatabase(MKA::List* character_list);
  Database& get_ddbb();

  static GameManager& Instance();

private:

  Database ddbb_;
  static int max_instances_;
  static int instances_;

  GameManager();

};

#endif
