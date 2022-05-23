/**
  * @file developer_t.h
  * @brief developer file of the game
  * @details that is use to manage the elements of the game
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#include <developer_t.h>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <texture.h>
#include <sprite.h>
#include <tilemap.h>
#include <character.h>
#include <scene.h>
#include <character_manager.h>
#include <enemy_manager.h>

DeveloperTool::DeveloperTool(){

  active_ = 0;
  mylist_ = nullptr;

}

DeveloperTool::~DeveloperTool(){}

/*void DeveloperTool::CharacterInstantiate(Tilemap& map, Character& chars){

  if (ImGui::TreeNode("Instatiate New Character")){

    static float scale_x = 1.0f;
    static float scale_y = 1.0f;
    static int tilemap_id = 1;
    static int tile = 0;

    ImGui::Text("Scale");
    ImGui::InputFloat("X", &scale_x);
    ImGui::InputFloat("Y", &scale_y);
    ImGui::DragInt("Tilemap ID", &tilemap_id);
    ImGui::DragInt("Tile", &tile);

    if(ImGui::Button("Instantiate")){

      Texture* texture = Texture::CreateTexture();
      texture->set_TextureFromFile((const char*)str0);

      Character* character = new Character();

      character->init({0.0f, 0.0f}, {scale_x, scale_y}, *texture,
                        120.0f, 25.0f, 20.0f, 10.0f, 0.05f, 20,
                        100.0f, 1, 1, 1, Character::kCharactersType_none,
                        1, 1);

      if(map.set_CharacterMapPos(*character, tile)){

        CharacterManager charmanager;

        MKA::List* aux = charmanager.get_characterList();

        MKA::InsertNodeList(&aux, (void*)character);

        charmanager.set_characterList(aux);

      } else {

        printf("Error placing character at tile %d\n", tile);

      }



    }

    ImGui::TreePop();

  }

}
*/
void DeveloperTool::Textures(){

  if (ImGui::TreeNode("Texture List")){

    if(ImGui::Button("Update Texture List")){

      //MKA::EraseList(&mylist_);

      ddbb_.init("../data/sql/game_database.db");
      ddbb_.get_textureData("SELECT FILE_DIR FROM TEXTURES");

      TextureData* textures_ = nullptr;

      if(nullptr !=
        (textures_ = (TextureData*) IndexListInfo(Database::extracted_queries_, 0))){

        for(int i = 0 ; i < MKA::ListSize(Database::extracted_queries_) ; ++i){

          textures_ = (TextureData*) IndexListInfo(Database::extracted_queries_, i);

          const char* dir = textures_->texture_dir;

          MKA::InsertNodeList(&mylist_, (void*)dir);

        }

      }

      ddbb_.endExtractQueries();

    }

    if (ImGui::TreeNode("Texture List")){

      static int selected = -1;
      char buffer[255];
      for (int n = 0; n < MKA::ListSize(mylist_) ; n++){

        const char* texture = (const char*)IndexListInfo(mylist_, n);

          sprintf(buffer, "%s", texture);
          if (ImGui::Selectable(buffer, selected == n)){

            selected = n;

          }

          if(selected == n){

            //strncpy(str0, texture, 255);

          }



      }

      ImGui::TreePop();

    }

    ImGui::TreePop();

  }

}

void DeveloperTool::CharacterStatus(CharacterManager& char_manager){

  const int kMaxchars = 20;
  char state[kMaxchars];
  memset(state, '\0', kMaxchars);

  switch(char_manager.get_characterState()){
    case CharacterManager::kCharacterAction::kCharacterAction_none:
    strncpy(state, "None", sizeof(state));
    break;
    case CharacterManager::kCharacterAction::kCharacterAction_move:
    strncpy(state, "Move", sizeof(state));
    break;
    case CharacterManager::kCharacterAction::kCharacterAction_attack:
    strncpy(state, "Attack", sizeof(state));
    break;
  }

  Character* character = char_manager.get_characterSelected();

  if(nullptr != character){
    ImGui::Text("Character selected: (%d)", character->get_id());
  } else {
    ImGui::Text("Character selected: (NULL)");
  }


  ImGui::Text("Character current status: (%s)", state);
  ImGui::Text("'M' to move");
  ImGui::Text("'A' to move");

}

void DeveloperTool::CharacterStats(MKA::List* char_manager){

  static bool h_borders = true;
  static bool v_borders = true;
  static int columns_count = 4;
  const int lines_count = 3;

  Character* aux_character = nullptr;

  ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
  ImGui::DragInt("##columns_count", &columns_count, 0.1f, 2, 10, "%d columns");
  ImGui::SameLine();
  ImGui::Checkbox("horizontal", &h_borders);
  ImGui::SameLine();
  ImGui::Checkbox("vertical", &v_borders);
  ImGui::Columns(columns_count, NULL, v_borders);

  char buffer[64];

  for (int i = 0; i < MKA::ListSize(char_manager) ; i++)
  {

    aux_character = (Character*)MKA::IndexListInfo(char_manager, i);

      if (h_borders && ImGui::GetColumnIndex() == 0)
          ImGui::Separator();

      ImGui::Text("ID: ");
      sprintf(buffer, "%d", aux_character->get_id());
      ImGui::SameLine(); ImGui::Text((const char*)buffer);
      memset(buffer, 0, sizeof(buffer));

      ImGui::Text("LVL: ");
      sprintf(buffer, "%d", aux_character->getLevel());
      ImGui::SameLine(); ImGui::Text((const char*)buffer);
      memset(buffer, 0, sizeof(buffer));

      ImGui::Text("EXP: ");
      sprintf(buffer, "%d", aux_character->getExperience());
      ImGui::SameLine(); ImGui::Text((const char*)buffer);
      memset(buffer, 0, sizeof(buffer));

      ImGui::Text("HP: ");
      sprintf(buffer, "%.1f", aux_character->getHp());
      ImGui::SameLine(); ImGui::Text((const char*)buffer);
      memset(buffer, 0, sizeof(buffer));

      ImGui::Text("MAX HP: ");
      sprintf(buffer, "%.1f", aux_character->getMaxHp());
      ImGui::SameLine(); ImGui::Text((const char*)buffer);
      memset(buffer, 0, sizeof(buffer));

      ImGui::Text("MANA: ");
      sprintf(buffer, "%.1f", aux_character->getMana());
      ImGui::SameLine(); ImGui::Text((const char*)buffer);
      memset(buffer, 0, sizeof(buffer));

      ImGui::Text("MAX MANA: ");
      sprintf(buffer, "%.1f", aux_character->getMaxMana());
      ImGui::SameLine(); ImGui::Text((const char*)buffer);
      memset(buffer, 0, sizeof(buffer));

      ImGui::Text("ATTACK: ");
      sprintf(buffer, "%.1f", aux_character->getAttack());
      ImGui::SameLine(); ImGui::Text((const char*)buffer);
      memset(buffer, 0, sizeof(buffer));

      ImGui::Text("DEFENSE: ");
      sprintf(buffer, "%.1f", aux_character->getDefense());
      ImGui::SameLine(); ImGui::Text((const char*)buffer);
      memset(buffer, 0, sizeof(buffer));

      ImGui::Text("CRIT_ATTACK: ");
      sprintf(buffer, "%.1f", aux_character->getCriattack());
      ImGui::SameLine(); ImGui::Text((const char*)buffer);
      memset(buffer, 0, sizeof(buffer));

      ImGui::Text("RANGE: ");
      sprintf(buffer, "%d", aux_character->getRange());
      ImGui::SameLine(); ImGui::Text((const char*)buffer);
      memset(buffer, 0, sizeof(buffer));

      ImGui::Text("TURN: ");
      sprintf(buffer, "%d", aux_character->getTurns());
      ImGui::SameLine(); ImGui::Text((const char*)buffer);
      memset(buffer, 0, sizeof(buffer));


      ImGui::NextColumn();
  }
  ImGui::Columns(1);
  if (h_borders)
      ImGui::Separator();

}

void DeveloperTool::CharacterTool(CharacterManager& char_manager){

  ImGui::Begin("CharacterStats_developer_tool");

  CharacterStatus(char_manager);
  CharacterStats(char_manager.get_characterList());

  ImGui::End();

}

void DeveloperTool::EnemyTool(EnemyManager& enemy_manager){

  ImGui::Begin("Enemy_developer_tool");

  CharacterStats(enemy_manager.get_enemyList());


  ImGui::End();

}

void DeveloperTool::TilemapT(Tilemap& map, Scene& scene_map){

  if (ImGui::TreeNode("Tilemap")){

    static int tilemap_id = 1;
    static int tile_size = 32;
    static int texture = 0;
    static char str0[128] = "../data/maps/";
    ImGui::InputText("Texture dir", str0, IM_ARRAYSIZE(str0));

    ImGui::InputInt("Tile Size", &tile_size);
    ImGui::InputInt("Texture", &texture);
    if(ImGui::Button("Show Grid")){ map.debugmode_ = 1; }
    ImGui::SameLine();
    if(ImGui::Button("Hide Grid")){ map.debugmode_ = 0; }
    ImGui::SameLine();
    if(ImGui::Button("Reload Grid")){

      Texture* new_texture_map_ = Texture::CreateTexture();
      new_texture_map_->set_TextureFromFile((const char*)str0);

      map.generateNewGrid(*new_texture_map_, tile_size);
      MKA::List* current_objs = scene_map.get_gameobjectList();
      MKA::InsertNodeList(&current_objs, (void*)&map);

    }
    if(ImGui::Button("Create New Tilemap")
    && MKA::ListSize(scene_map.get_gameobjectList()) == 0){

      Tilemap* newmap = new Tilemap();
      MKA::List* scene_objs = scene_map.get_gameobjectList();
      Texture* new_texture_map_ = Texture::CreateTexture();
      new_texture_map_->set_TextureFromFile((const char*)str0);

      newmap->init("../data/fonts/tilemap.ttf");
      newmap->generateNewGrid(*new_texture_map_, tile_size);
      map = *newmap;
      MKA::InsertNodeList(&scene_objs, (void*)&map);
      scene_map.set_gameobjectList(scene_objs);

    }
    ImGui::SameLine();
    if(ImGui::Button("Delete Actual Tilemap")){

      MKA::List* scene_objs = scene_map.get_gameobjectList();
      MKA::EraseList(&scene_objs);
      scene_map.set_gameobjectList(scene_objs);

    }


    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::DragInt("Tilemap ID", &tilemap_id);

    if(ImGui::Button("Save New Tilemap")){

      Database ddbb;

      ddbb.init("../data/sql/game_database.db");

      map.SaveNewTilemap(ddbb, texture, tile_size, tilemap_id);

    }

    if(ImGui::Button("Load Tilemap")){

      Database ddbb;

      ddbb.init("../data/sql/game_database.db");

      if(!map.LoadTilemap(ddbb, tilemap_id)){

        printf("FAILED LOADING TILEMAP.");

      } else {

        printf("TILEMAP LOADED.");

      }

    }

    if(ImGui::Button("Update Tilemap")){

      Database ddbb;

      ddbb.init("../data/sql/game_database.db");

      map.UpdateTilemap(
        ddbb, tilemap_id, texture, tile_size
      );

    }

    if(ImGui::Button("Remove Tilemap")){

      Database ddbb;

      ddbb.init("../data/sql/game_database.db");

      map.DeleteTilemap(ddbb, tilemap_id);

    }

    if(nullptr != map.sprite_){

      ImGui::DragFloat("X", &(map.map_worldposition_.x), 1.0f);
      ImGui::DragFloat("Y", &(map.map_worldposition_.y), 1.0f);
      map.sprite_->sprite_.setPosition(
        {map.map_worldposition_.x, map.map_worldposition_.y}
      );

    }



    ImGui::TreePop();

  }

}

void DeveloperTool::TilemapTool(Tilemap& scene_map, Scene& scene){

  ImGui::Begin("Tilemap_developer_tool");

  TilemapT(scene_map, scene);
  Textures();

  ImGui::End();

}
