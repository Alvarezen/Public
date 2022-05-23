/**
  * @file sql_management.h
  * @brief sql_management file of the game
  * @details that is use to manage the sql queries with the code
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __DDBB_H__
#define __DDBB_H__
#define _CRT_SECURE_NO_WARNINGS

#include <sqlite3.h>
#include <mka_list.h>
#include <stdint.h>

/** The window data given by the database */
struct WindowData{
  /** The window id given by the database */
  int id;
  /** The window width given by the database */
  int w_width;
  /** The window height given by the database */
  int w_height;
  /** The window fps given by the database */
  int fps;
  /** The window title given by the database */
  char w_title[255];
  /** The window colors given by the database */
  uint8_t r, g, b, a;
  /** The window fullscreen setting given by the database */
  uint8_t fullscreen;
  /** The imgui config .ini dir given by the database */
  char imgui_ini[255];
};

/** The tile data given by the database */
struct TilesData{
  /** The tile id given by the database */
  int id;
  /** The tile x position given by the database */
  float pos_x;
  /** The tile y position given by the database */
  float pos_y;
  /** The tile x size given by the database */
  float size_x;
  /** The tile y size given by the database */
  float size_y;
  /** If the tile is walkable given by the database */
  uint8_t walkable;
  /** The item id into tilemap given by the database */
  int item_id;
  /** The character id into tilemap given by the database */
  int character_id;
};

/** The tilemap data given by the database */
struct TilemapData{
  /** The tilemap id given by the database */
  int id;
  /** The tilemap texture file dir given by the database */
  char texture_dir[255];
  /** The tilemap x position file dir given by the database */
  float pos_x;
  /** The tilemap y position file dir given by the database */
  float pos_y;
  /** The tile size of a tilemap given by the database */
  int tiles_size;
};

/** The texture data given by the database */
struct TextureData{
  /** The texture id that has database */
  int id;
  /** The texture file dir that has database */
  char texture_dir[255];
  /** The texture tag that has database */
  char tag[255];
};

/** The font data given by the database */
struct FontData{
  /** The font id that has database */
  int id;
  /** The font file dir that has database */
  char font_dir[255];
  /** The font tag that has database */
  char tag[255];
};

/** The character data given by the database */
struct CharacterData{
  /** The character id that has database */
  int id;
  /** The texture file dir that has database */
  char texture_dir[255];
  /** The character pos x that has database */
  float pos_x;
  /** The character pos y that has database */
  float pos_y;
  /** The character scale x that has database */
  float scale_x;
  /** The character scale y that has database */
  float scale_y;
  /** The character health that has database */
  float health;
  /** The character mana that has database */
  float mana;
  /** The character attack that has database */
  float attack;
  /** The character defense that has database */
  float defense;
  /** The character critattack that has database */
  float crit_attack;
  /** The character turns that has database */
  int turns;
  /** The character level that has database */
  int level;
  /** If the character is alive at database */
  uint8_t alive;
  /** The character experience that has database */
  int exp;
  /** The character type that has database */
  int chartype;
  /** The character range that has database */
  int range;
  /** The character sprite column that has database */
  float col;
  /** The character name that has database */
  char name[30];
  /** The character max_experience that has database */
  int max_experience_;

};

/** The spells data given by the database */
struct SpellsData{
  /** The spell id that has database */
  int id;
  /** The spell name that has database */
  char name[255];
  /** The spell mana that has database */
  float mana;
  /** The spell range that has database */
  float range;
  /** The spell damage that has database */
  float damage;
};

/** The rol class data given by the database */
struct ClassData{
  /** The rol class id that has database */
  int id;
  /** The rol class profession that has database */
  char profession[255];
  /** The rol class health that has database */
  int health;
  /** The rol class mana that has database */
  int mana;
  /** The rol class attack that has database */
  int attack;
  /** The rol class defense that has database */
  int defense;
  /** The rol class crit_attack that has database */
  int crit_attack;
  /** The rol class description that has database */
  char description[255];
};

/** The item data given by the database */
struct ItemData{
  /** The item id that has database */
  int id;
  /** The item name that has database */
  char name[255];
  /** The item health that has database */
  int health;
  /** The item defense that has database */
  int defense;
  /** The item attack that has database */
  int attack;
  /** The item mana that has database */
  int mana;
  /** The item cit_attack that has database */
  int crit_attack;
  /** The item legendary_item that has database */
  uint8_t legendary_item;
  /** The item dropped_item that has database */
  uint8_t dropped_item;
  /** @var Use it for the cost of the items`s coins*/
  int item_coins;

};

class Database{

private:

  /** The sqlite3 API pointer that has the reference of the database */
  sqlite3* db_;
  /** The error message that gives the sqlite3 API */
  char* errmsg_;
  /** The path of the .db file at disk */
  const char* path_;

public:

  Database();

  ~Database();

  /** @brief Initialize database
  *
  *   Initializes a database based on the path of the .db file
  *
  *   @param file_path The file path where database file is located
  */
  void init(const char* file_path);

  /** @brief Opens Database
  *
  *   Opens database checking if with the database path given by
  *    user is right else the function prints an error by console
  *
  */
  void open();

  /** @brief Closes Database
  *
  *   Closes database checking if database pointer is nullptr
  *    else the database closes
  *
  */
  void close();

  /** @brief Applies SQL table querie
  *
  *   Applies SQL table opening the database and checking, if there's
  *    any error doing the querie it prints by console and it closes.
  *
  *   @return The sqlite3 API error code
  *   @param sql_q The querie it will be applied to the database
  *
  */
  uint8_t sqlTableQuerie(const char* sql_q);

  /** @brief Applies SQL extraction querie for window data
  *
  *   Applies SQL table opening the database and exporting to
  *    the list queries of extraction
  *
  *   @param sql_q The querie it will be applied to the database
  *
  */
  void get_windowData(const char*);

  /** @brief Applies SQL extraction querie for tiles data
  *
  *   Applies SQL table opening the database and exporting to
  *    the list queries of extraction
  *
  *   @param sql_q The querie it will be applied to the database
  *
  */
  void get_tilesData(const char*);

  /** @brief Applies SQL extraction querie for tilemap data
  *
  *   Applies SQL table opening the database and exporting to
  *    the list queries of extraction
  *
  *   @param sql_q The querie it will be applied to the database
  *
  */
  void get_tilemapData(const char*);

  /** @brief Applies SQL extraction querie for texture data
  *
  *   Applies SQL table opening the database and exporting to
  *    the list queries of extraction
  *
  *   @param sql_q The querie it will be applied to the database
  *
  */
  void get_textureData(const char*);

  /** @brief Applies SQL extraction querie for character data
  *
  *   Applies SQL table opening the database and exporting to
  *    the list queries of extraction
  *
  *   @param sql_q The querie it will be applied to the database
  *
  */
  void get_characterData(const char*);

  /** @brief Applies SQL extraction querie for class data
  *
  *   Applies SQL table opening the database and exporting to
  *    the list queries of extraction
  *
  *   @param sql_q The querie it will be applied to the database
  *
  */
  void get_classData(const char*);

  /** @brief Applies SQL extraction querie for item data
  *
  *   Applies SQL table opening the database and exporting to
  *    the list queries of extraction
  *
  *   @param sql_q The querie it will be applied to the database
  *
  */
  void get_itemsData(const char*);

  /** @brief Applies SQL extraction querie for font data
  *
  *   Applies SQL table opening the database and exporting to
  *    the list queries of extraction
  *
  *   @param sql_q The querie it will be applied to the database
  *
  */
  void get_fontData(const char*);

  /** @brief Applies SQL extraction querie for spell data
  *
  *   Applies SQL table opening the database and exporting to
  *    the list queries of extraction
  *
  *   @param sql_q The querie it will be applied to the database
  *
  */
  void get_spellsData(const char*);

  /** @brief Applies SQL table queries from database
  *
  *   Applies SQL table opening the database and taking the
  *    information of the querie from a txt file
  *
  *   @param sql_q The file where the querie is
  *
  */
  void applyTableQueries(const char*);

  /** @brief Applies SQL extraction queries from database
  *
  *   Applies SQL table opening the database and taking the
  *    information of the querie from a txt file
  *
  *   @param sql_q The file where the querie is
  *   @param type The type of data I will be extracted
  *
  */
  void applyExtractQueries(const char* extract_q_f, const int type);

  /** @brief Ends extraction queries
  *
  *   Erases the queries list to keep it clean for another querie
  *
  *
  */
  void endExtractQueries();

  /** @brief Applies SQL update queries from database
  *
  *   Applies SQL table opening the database and taking the
  *    information of the querie from a txt file
  *
  *   @param sql_q The file where the querie is
  *   @param value The value that will be updated to database
  *
  */
  void applyUpdateQueries(const char* path, const char* value);

  /** Extracted queries from a querie usable anywhere */
  static MKA::List* extracted_queries_;

};

#endif //!__DDBB_H__
