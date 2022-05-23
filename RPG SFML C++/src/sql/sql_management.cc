/**
  * @file sql_management.h
  * @brief sql_management file of the game
  * @details that is use to manage the sql queries with the code
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#include <sql_management.h>
#include <string>
#include <cstring>

MKA::List* Database::extracted_queries_ = nullptr;

Database::Database(){

  db_ = nullptr;
  errmsg_ = nullptr;

}

Database::~Database(){

  MKA::EraseList(&extracted_queries_);

}

void Database::init(const char* path){

  path_ = path;

}

void Database::open(){

    int rc = sqlite3_open(path_, &db_);

    if(rc != SQLITE_OK){

      printf("\nSQL error: %s\n", sqlite3_errmsg(db_));
      sqlite3_close(db_);

    }

}

void Database::close(){

  if(nullptr != db_){

    sqlite3_close(db_);

  }

}

uint8_t Database::sqlTableQuerie(const char* sql_c){

  open();

  int rc = sqlite3_exec(db_, sql_c, 0, 0, &errmsg_);

  if (rc != SQLITE_OK) {

    printf("\nSQL error: %s\n", errmsg_);

    sqlite3_free(errmsg_);
    sqlite3_close(db_);

  }

  close();

  return (uint8_t)rc;

}

int callbackWindowData(void *notused, int argc, char **argv, char **azcolname){

  int ncolum_not_used = 0;
  const char* colname_notused;
  ncolum_not_used = argc;
  colname_notused = *azcolname;

  WindowData *databack_ = (WindowData *)notused;

  databack_->id = atoi(argv[0]);
  databack_->w_width = atoi(argv[1]);
  databack_->w_height = atoi(argv[2]);
  databack_->fps = atoi(argv[3]);
  databack_->r = (uint8_t)atoi(argv[4]);
  databack_->g = (uint8_t)atoi(argv[5]);
  databack_->b = (uint8_t)atoi(argv[6]);
  databack_->a = (uint8_t)atoi(argv[7]);

  char* straux = argv[8];
  strncpy(databack_->w_title, straux, sizeof(databack_->w_title));

  databack_->fullscreen = (uint8_t)atoi(argv[9]);

  char* straux_2 = argv[10];
  strncpy(databack_->imgui_ini, straux_2, sizeof(databack_->imgui_ini));


  WindowData* newnode = (WindowData*)malloc(sizeof(WindowData));
  *newnode = *databack_;

  MKA::InsertNodeList(&Database::extracted_queries_, (void*)newnode);

  return 0;
}

int callbackTilesData(void *notused, int argc, char **argv, char **azcolname){

  int ncolum_not_used = 0;
  const char* colname_notused;
  ncolum_not_used = argc;
  colname_notused = *azcolname;

  TilesData *databack_ = (TilesData *)notused;

  databack_->id = atoi(argv[0]);
  databack_->pos_x = (float)atof(argv[1]);
  databack_->pos_y = (float)atof(argv[2]);
  databack_->size_x = (float)atof(argv[3]);
  databack_->size_y = (float)atof(argv[4]);
  databack_->walkable = (uint8_t)atoi(argv[5]);
  databack_->item_id = atoi(argv[6]);
  databack_->character_id = atoi(argv[7]);

  TilesData* newnode = (TilesData*)malloc(sizeof(TilesData));
  *newnode = *databack_;

  MKA::InsertNodeList(&Database::extracted_queries_, (void*)newnode);

  return 0;
}

int callbackTilemapData(void *notused, int argc, char **argv, char **azcolname){

  int ncolum_not_used = 0;
  const char* colname_notused;
  ncolum_not_used = argc;
  colname_notused = *azcolname;

  TilemapData *databack_ = (TilemapData *)notused;

  char* straux = argv[0];
  databack_->id = 0;
  strncpy(databack_->texture_dir, straux, sizeof(databack_->texture_dir));
  databack_->pos_x = (float)atof(argv[1]);
  databack_->pos_y = (float)atof(argv[2]);
  databack_->tiles_size = atoi(argv[3]);

  TilemapData* newnode = (TilemapData*)malloc(sizeof(TilemapData));
  *newnode = *databack_;

  MKA::InsertNodeList(&Database::extracted_queries_, (void*)newnode);

  return 0;
}

int callbackTextureData(void *notused, int argc, char **argv, char **azcolname){

  int ncolum_not_used = 0;
  const char* colname_notused;
  ncolum_not_used = argc;
  colname_notused = *azcolname;

  TextureData *databack_ = (TextureData *)notused;


  databack_->id = atoi(argv[0]);
  char* straux = argv[1];
  strncpy(databack_->texture_dir, straux, sizeof(databack_->texture_dir));
  char* straux_2 = argv[2];
  strncpy(databack_->tag, straux_2, sizeof(databack_->tag));

  TextureData* newnode = (TextureData*)malloc(sizeof(TextureData));
  *newnode = *databack_;

  MKA::InsertNodeList(&Database::extracted_queries_, (void*)newnode);

  return 0;
}

int callbackSpellsData(void *notused, int argc, char **argv, char **azcolname){

  int ncolum_not_used = 0;
  const char* colname_notused;
  ncolum_not_used = argc;
  colname_notused = *azcolname;

  SpellsData *databack_ = (SpellsData *)notused;


  databack_->id = atoi(argv[0]);
  char* straux = argv[1];
  strncpy(databack_->name, straux, sizeof(databack_->name));
  databack_->mana = (float)atof(argv[2]);
  databack_->range = (float)atof(argv[3]);
  databack_->damage = (float)atof(argv[4]);


  SpellsData* newnode = (SpellsData*)malloc(sizeof(SpellsData));
  *newnode = *databack_;

  MKA::InsertNodeList(&Database::extracted_queries_, (void*)newnode);

  return 0;
}

int callbackCharacterData(void *notused, int argc, char **argv, char **azcolname){

  int ncolum_not_used = 0;
  const char* colname_notused;
  ncolum_not_used = argc;
  colname_notused = *azcolname;

  CharacterData *databack_ = (CharacterData *)notused;


  databack_->id = atoi(argv[0]);
  char* straux = argv[1];
  strncpy(databack_->texture_dir, straux, sizeof(databack_->texture_dir));
  databack_->pos_x = (float)atof(argv[2]);
  databack_->pos_y = (float)atof(argv[3]);
  databack_->scale_x = (float)atof(argv[4]);
  databack_->scale_y = (float)atof(argv[5]);
  databack_->health = (float)atof(argv[6]);
  databack_->mana = (float)atof(argv[7]);
  databack_->attack = (float)atof(argv[8]);
  databack_->defense = (float)atof(argv[9]);
  databack_->crit_attack = (float)atof(argv[10]);
  databack_->turns = atoi(argv[11]);
  databack_->level = atoi(argv[12]);
  databack_->alive = (uint8_t)atoi(argv[13]);
  databack_->exp = atoi(argv[14]);
  databack_->chartype = atoi(argv[15]);
  databack_->range = atoi(argv[16]);
  databack_->col = (float)atoi(argv[17]);
  char* straux1 = argv[18];
  strncpy(databack_->name, straux1, sizeof(databack_->name));
  databack_->max_experience_ = atoi(argv[19]);

  CharacterData* newnode = (CharacterData*)malloc(sizeof(CharacterData));
  *newnode = *databack_;

  MKA::InsertNodeList(&Database::extracted_queries_, (void*)newnode);

  return 0;
}

int callbackClassData(void *notused, int argc, char **argv, char **azcolname){

  int ncolum_not_used = 0;
  const char* colname_notused;
  ncolum_not_used = argc;
  colname_notused = *azcolname;

  ClassData *databack_ = (ClassData *)notused;


  databack_->id = atoi(argv[0]);
  char* straux_1 = argv[1];
  strncpy(databack_->profession, straux_1, sizeof(databack_->profession));
  databack_->health = atoi(argv[2]);
  databack_->mana = atoi(argv[3]);
  databack_->attack = atoi(argv[4]);
  databack_->defense = atoi(argv[5]);
  databack_->crit_attack = atoi(argv[6]);
  char* straux_2 = argv[7];
  strncpy(databack_->description, straux_2, sizeof(databack_->description));


  ClassData* newnode = (ClassData*)malloc(sizeof(ClassData));
  *newnode = *databack_;

  MKA::InsertNodeList(&Database::extracted_queries_, (void*)newnode);

  return 0;
}

int callbackItemData(void *notused, int argc, char **argv, char **azcolname){

  int ncolum_not_used = 0;
  const char* colname_notused;
  ncolum_not_used = argc;
  colname_notused = *azcolname;

  ItemData *databack_ = (ItemData *)notused;


  databack_->id = atoi(argv[0]);
  char* straux_1 = argv[1];
  strncpy(databack_->name, straux_1, sizeof(databack_->name));
  databack_->health = atoi(argv[2]);
  databack_->defense = atoi(argv[3]);
  databack_->attack = atoi(argv[4]);
  databack_->mana = atoi(argv[5]);
  databack_->crit_attack = atoi(argv[6]);
  databack_->legendary_item = (uint8_t)atoi(argv[7]);
  databack_->dropped_item = (uint8_t)atoi(argv[8]);
  databack_->item_coins = atoi(argv[9]);

  ItemData* newnode = (ItemData*)malloc(sizeof(ItemData));
  *newnode = *databack_;

  MKA::InsertNodeList(&Database::extracted_queries_, (void*)newnode);

  return 0;
}

int callbackFontData(void *notused, int argc, char **argv, char **azcolname){

  int ncolum_not_used = 0;
  const char* colname_notused;
  ncolum_not_used = argc;
  colname_notused = *azcolname;

  FontData *databack_ = (FontData *)notused;

  databack_->id = atoi(argv[0]);
  char* straux = argv[1];
  strncpy(databack_->font_dir, straux, sizeof(databack_->font_dir));
  char* straux_2 = argv[2];
  strncpy(databack_->tag, straux_2, sizeof(databack_->tag));

  FontData* newnode = (FontData*)malloc(sizeof(FontData));
  *newnode = *databack_;

  MKA::InsertNodeList(&Database::extracted_queries_, (void*)newnode);

  return 0;
}

void Database::get_windowData(const char* sql_c){

  WindowData databack_;

  open();

  int rc = sqlite3_exec(db_, sql_c, callbackWindowData, &databack_, &errmsg_);

  if (rc != SQLITE_OK ) {

    printf("\nSQL error: %s\n", errmsg_);

    sqlite3_free(errmsg_);
    sqlite3_close(db_);

  }

  close();

}

void Database::get_tilesData(const char* sql_c){

  TilesData databack_;

  open();

  int rc = sqlite3_exec(db_, sql_c, callbackTilesData, &databack_, &errmsg_);

  if (rc != SQLITE_OK ) {

    printf("\nSQL error: %s\n", errmsg_);

    sqlite3_free(errmsg_);
    sqlite3_close(db_);

  }

  close();

}

void Database::get_tilemapData(const char* sql_c){

  TilemapData databack_;

  open();

  int rc = sqlite3_exec(db_, sql_c, callbackTilemapData, &databack_, &errmsg_);

  if (rc != SQLITE_OK ) {

    printf("\nSQL error: %s\n", errmsg_);

    sqlite3_free(errmsg_);
    sqlite3_close(db_);

  }

  close();

}

void Database::get_textureData(const char* sql_c){

  TextureData databack_;

  open();

  int rc = sqlite3_exec(db_, sql_c, callbackTextureData, &databack_, &errmsg_);

  if (rc != SQLITE_OK ) {

    printf("\nSQL error: %s\n", errmsg_);

    sqlite3_free(errmsg_);
    sqlite3_close(db_);

  }

  close();

}

void Database::get_characterData(const char* sql_c){

  CharacterData databack_;

  open();

  int rc = sqlite3_exec(db_, sql_c, callbackCharacterData, &databack_, &errmsg_);

  if (rc != SQLITE_OK ) {

    printf("\nSQL error: %s\n", errmsg_);

    sqlite3_free(errmsg_);
    sqlite3_close(db_);

  }

  close();

}

void Database::get_spellsData(const char* sql_c){

  SpellsData databack_;

  open();

  int rc = sqlite3_exec(db_, sql_c, callbackSpellsData, &databack_, &errmsg_);

  if (rc != SQLITE_OK ) {

    printf("\nSQL error: %s\n", errmsg_);

    sqlite3_free(errmsg_);
    sqlite3_close(db_);

  }

  close();

}

void Database::get_classData(const char* sql_c){

  ClassData databack_;

  open();

  int rc = sqlite3_exec(db_, sql_c, callbackClassData, &databack_, &errmsg_);

  if (rc != SQLITE_OK ) {

    printf("\nSQL error: %s\n", errmsg_);

    sqlite3_free(errmsg_);
    sqlite3_close(db_);

  }

  close();

}

void Database::get_itemsData(const char* sql_c){

  ItemData databack_;

  open();

  int rc = sqlite3_exec(db_, sql_c, callbackItemData, &databack_, &errmsg_);

  if (rc != SQLITE_OK ) {

    printf("\nSQL error: %s\n", errmsg_);

    sqlite3_free(errmsg_);
    sqlite3_close(db_);

  }

  close();

}

void Database::get_fontData(const char* sql_c){

  FontData databack_;

  open();

  int rc = sqlite3_exec(db_, sql_c, callbackFontData, &databack_, &errmsg_);

  if (rc != SQLITE_OK ) {

    printf("\nSQL error: %s\n", errmsg_);

    sqlite3_free(errmsg_);
    sqlite3_close(db_);

  }

  close();

}

void Database::applyTableQueries(const char* table_q_f){

  FILE *temp_file = fopen(table_q_f, "r");

  if(nullptr != temp_file){

    char character;
    std::string buffer;

    while(fread(&character, sizeof(character), 1, temp_file)){

      if(character != '"' && character != ';'){

        buffer += character;

      } else if (character == ';'){

        sqlTableQuerie(buffer.c_str());
        buffer.erase(buffer.begin(), buffer.end());

      }

    }

    fclose(temp_file);

  }



}

void Database::applyExtractQueries(const char* extract_q_f, const int type){

  FILE *temp_file = fopen(extract_q_f, "r");

  if(nullptr != temp_file){

    //MKA::EraseList(&extracted_queries_);

    char character;
    std::string buffer;

    while(fread(&character, sizeof(character), 1, temp_file)){

      if(character != '"' && character != ';'){

        buffer += character;

      } else if (character == ';'){

        switch(type){

          case 0: get_windowData(buffer.c_str()); break;
          case 1: get_tilesData(buffer.c_str()); break;
          case 2: get_tilemapData(buffer.c_str()); break;
          case 3: get_characterData(buffer.c_str()); break;
          case 4: get_classData(buffer.c_str()); break;
          case 5: get_textureData(buffer.c_str()); break;
          case 6: get_fontData(buffer.c_str()); break;
          case 7: get_itemsData(buffer.c_str()); break;
          case 8: get_spellsData(buffer.c_str()); break;

        }

        buffer.erase(buffer.begin(), buffer.end());

      }

    }

    fclose(temp_file);

  }



}

void Database::applyUpdateQueries(const char* update_q_f,
                                  const char* value){

  FILE *temp_file = fopen(update_q_f, "r");

  if(nullptr != temp_file){

    char character;
    std::string buffer;

    while(fread(&character, sizeof(character), 1, temp_file)){

      if(character != '"' && character != ';'){

        if(character == '.'){

          buffer += value;

        } else {

          buffer += character;

        }

      } else if (character == ';'){

        sqlTableQuerie(buffer.c_str());
        buffer.erase(buffer.begin(), buffer.end());

      }

    }

    fclose(temp_file);

  }



}

void Database::endExtractQueries(){ MKA::EraseList(&extracted_queries_); }
