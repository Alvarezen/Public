/**
  * @file gamemanager.cc
  * @brief gamemanager file of the game
  * @details File that is use to get de data of the game
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */
#include <gamemanager.h>
#include <character.h>
#include <texture.h>
#include <items.h>
#include <mka_list.h>

uint32_t GameManager::s_windowWidth_ = 0;
uint32_t GameManager::s_windowHeight_ = 0;
int GameManager::max_instances_ = 1;
int GameManager::instances_ = 0;

GameManager::GameManager(){

  instances_++;

}

GameManager::~GameManager(){

  instances_--;
  ddbb_.endExtractQueries();

}

GameManager& GameManager::Instance(){

  GameManager* gm = nullptr;

  if(instances_ <= max_instances_){

    gm = new GameManager();

  }

  return *gm;

}

void GameManager::init(){

  ddbb_.init("../data/sql/game_database.db");

}


Texture* GameManager::get_textureFromDatabaseWithTag(const char* texture_tag){

  ddbb_.applyExtractQueries(
    "../data/sql/queries/textures/ex_queries.txt", 5
  );

  Texture* texture = nullptr;
  TextureData* tex_data = nullptr;

  for(int i = 0 ; i < MKA::ListSize(Database::extracted_queries_) ; ++i){

    tex_data =
    (TextureData*)MKA::IndexListInfo(Database::extracted_queries_, i);

    if(strcmp((const char*)tex_data->tag, texture_tag) == 0){

      texture = Texture::CreateTexture();
      texture->set_TextureFromFile(
        tex_data->texture_dir
      );

    }

  }

  ddbb_.endExtractQueries();

  return texture;

}

sf::Font* GameManager::get_fontFromDatabaseWithTag(const char* font_tag){

  ddbb_.applyExtractQueries(
    "../data/sql/queries/fonts/ex_queries.txt", 6
  );

  sf::Font* font = nullptr;
  FontData* font_data = nullptr;

  for(int i = 0 ; i < MKA::ListSize(Database::extracted_queries_) ; ++i){

    font_data =
    (FontData*)MKA::IndexListInfo(Database::extracted_queries_, i);

    if(strcmp(font_data->tag, font_tag) == 0){

      font = new sf::Font();
      font->loadFromFile(font_data->font_dir);

    }

  }

  ddbb_.endExtractQueries();

  return font;

}


WindowData* GameManager::get_windowDataFromDatabase(){

  ddbb_.init("../data/sql/game_database.db");
  ddbb_.applyTableQueries("../data/sql/queries/tables.txt");
  ddbb_.applyTableQueries("../data/sql/queries/classes.txt");
  ddbb_.applyTableQueries("../data/sql/queries/pre_data.txt");
  ddbb_.applyTableQueries("../data/sql/queries/items.txt");
  ddbb_.applyExtractQueries(
    "../data/sql/queries/window/window_ex_queries.txt", 0
  );

  WindowData* my_wdata = nullptr;

  if(nullptr !=
  (my_wdata =
    (WindowData*)MKA::IndexListInfo(Database::extracted_queries_, 0))){

    return my_wdata;

  } else {

    return nullptr;

  }
}

void GameManager::get_classesDataFromDatabase(){

  ddbb_.init("../data/sql/game_database.db");
  ddbb_.applyExtractQueries(
    "../data/sql/queries/classes/ex_queries.txt", 4
  );


}

MKA::List* GameManager::get_itemsDataFromDatabase(){

  ddbb_.init("../data/sql/game_database.db");
  ddbb_.applyExtractQueries(
    "../data/sql/queries/items/ex_queries.txt", 7
  );

  Item* item = nullptr;
  ItemData* item_data = nullptr;
  MKA::List* item_list = nullptr;

  for(int i = 0 ; i < MKA::ListSize(Database::extracted_queries_) ; ++i){

    if(nullptr !=
    (item_data =
      (ItemData*)MKA::IndexListInfo(Database::extracted_queries_, i))){

        item = new Item();
        // texture = Texture::CreateTexture();
        // texture->set_TextureFromFile(
        //   char_data->texture_dir
        // );

        item->init(item_data->health,
                   item_data->defense,
                   item_data->attack,
                   item_data->mana,
                   item_data->crit_attack,
                   item_data->legendary_item,
                   item_data->dropped_item,
                   item_data->item_coins
        );


        MKA::InsertNodeList(&item_list, (void*)item);

    } else {

      printf("Error loading characters from database.");

    }

  }

  ddbb_.endExtractQueries();

  return item_list;

}

void GameManager::set_charactersFromDatabase(MKA::List** input_list){

  ddbb_.init("../data/sql/game_database.db");
  ddbb_.applyExtractQueries(
    "../data/sql/queries/characters/ex_queries.txt", 3
  );

  Texture *texture = nullptr;
  Character* character = nullptr;
  CharacterData* char_data = nullptr;

  for(int i = 0 ; i < MKA::ListSize(Database::extracted_queries_) ; ++i){

    if(nullptr !=
    (char_data =
      (CharacterData*)MKA::IndexListInfo(Database::extracted_queries_, i))){

        character = new Character();
        texture = Texture::CreateTexture();
        texture->set_TextureFromFile(
          char_data->texture_dir
        );

        character->init(
          {char_data->pos_x, char_data->pos_y},
          {char_data->scale_x, char_data->scale_y},
          *texture, char_data->health,
          char_data->mana, char_data->attack,
          char_data->defense, char_data->crit_attack,
          char_data->level, (uint8_t)char_data->alive,
          (uint8_t)char_data->turns, char_data->exp,
          (Character::kCharactersType)char_data->chartype,
          char_data->range, char_data->col, (const char*)char_data->name,
          char_data->max_experience_
        );


        MKA::InsertNodeList(input_list, (void*)character);

    } else {

      printf("Error loading characters from database.");

    }

  }

  ddbb_.endExtractQueries();

}

void GameManager::set_charactersToDatabase(MKA::List* character_list){

  std::string query;
  Character* character = nullptr;

  for(int i = 0; i<MKA::ListSize(character_list) ; i++){

    character = (Character*)MKA::IndexListInfo(character_list, i);

    query += "INSERT INTO CHARACTERS VALUES('" +std::to_string(i + 1)+ "',";
    query += "'" + std::to_string(8) + "',";
    query += "'" + std::to_string(character->sprite_.sprite_.getPosition().x) + "',";
    query += "'" + std::to_string(character->sprite_.sprite_.getPosition().y) + "',";
    query += "'" + std::to_string(character->sprite_.sprite_.getScale().x) + "',";
    query += "'" + std::to_string(character->sprite_.sprite_.getScale().y) + "',";
    query += "'" + std::to_string(character->getHp()) + "',";
    query += "'" + std::to_string(character->getMana()) + "',";
    query += "'" + std::to_string(character->getAttack()) + "',";
    query += "'" + std::to_string(character->getDefense()) + "',";
    query += "'" + std::to_string(character->getCriattack()) + "',";
    query += "'" + std::to_string(0) + "',";
    query += "'" + std::to_string(character->getLevel()) + "',";
    query += "'" + std::to_string(character->getLife()) + "',";
    query += "'" + std::to_string(character->getExperience()) + "',";
    query += "'" + std::to_string((int)character->getKcharacter()) + "',";
    query += "'" + std::to_string(character->getRange()) + "',";
    query += "'" + std::to_string(2) + "','";
    query += character->getName();
    query += "','" + std::to_string(character->get_maxExp()) + "')";


    if(ddbb_.sqlTableQuerie(query.c_str())){

      printf("Loaded %d\n", i);

    }

    query.erase(query.begin(), query.end());

  }

}



Database& GameManager::get_ddbb(){

  return ddbb_;

}
