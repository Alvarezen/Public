/*
File: tilemap.cc
Author: Alvaro Vazquez
Description: tilemap implementation
*/

#include <tilemap.h>
#include <tile.h>
#include <sql_management.h>
#include <sprite.h>
#include <items.h>
#include <character.h>
#include <character_manager.h>
#include <cursor.h>

Tilemap::Tilemap(){

  grid_size_ = {0, 0};
  grid_list_ = nullptr;
  debugmode_ = 0;
  sprite_ = nullptr;
  map_worldposition_ = {0.0f, 0.0f};
  total_grid_size_ = 0;

}

Tilemap::~Tilemap(){

  MKA::EraseList(&grid_list_);

  if(nullptr != sprite_){
    delete sprite_;
  }

}

void Tilemap::init(const char* f_font){

  if(nullptr != f_font){ font_.loadFromFile(f_font); }

}

void Tilemap::set_cursorFirstMapPos(){

  Tile* tile = nullptr;
  bool found_free_tile_ = false;

  for(int i = 0 ; i < MKA::ListSize(grid_list_) && !found_free_tile_ ; ++i){

    tile = (Tile*)MKA::IndexListInfo(grid_list_, i);

    if(tile->walkable_){

      cursor_.init(tile->pos_);

      found_free_tile_ = true;

    }

  }

}

uint8_t Tilemap::generateNewGrid(Texture& texturemap, int tile_size){

  if(nullptr != sprite_){
    delete sprite_;
  }

  sprite_ = new Sprite();

  sprite_->initSprite(texturemap);

  sprite_->sprite_.setPosition(map_worldposition_);

  int aux_width =
  (int)((sprite_->sprite_.getGlobalBounds().width) / tile_size);
  int aux_height =
  (int)((sprite_->sprite_.getGlobalBounds().height) / tile_size);

  grid_size_ = {aux_width, aux_height};

  total_grid_size_ = (grid_size_.x + 2) * (grid_size_.y + 2);

  MKA::EraseList(&grid_list_);

  Tile* tile = nullptr;

  int tile_id_tile = total_grid_size_ - 1;

  float x_offset = sprite_->sprite_.getPosition().x - (float)tile_size;
  float y_offset = sprite_->sprite_.getPosition().y - (float)tile_size;

  for(int j = 0 ; j < (int)grid_size_.y + 2; j++){

    for(int i = 0 ; i < (int)grid_size_.x + 2; i++){

      tile = new Tile();

      tile->init({x_offset, y_offset}, {(float)tile_size, (float)tile_size},
      tile_id_tile--, font_);

      MKA::InsertNodeList(&grid_list_, (void*)tile);

      x_offset += (float)tile_size;

    }

    x_offset = sprite_->sprite_.getPosition().x - (float)tile_size;
    y_offset += (float)tile_size;

  }

  cursor_.init({(float)tile_size, (float)tile_size});

  return 1;

}

void Tilemap::SaveNewTilemap(Database& ddbb,
  int texture,
  int tile_size,
  int id){

  std::string querie;
  Tile* tile = nullptr;

  std::string querie_tilemap;


  querie_tilemap +=
  "INSERT INTO TILEMAP VALUES('" + std::to_string(id) + "',";
  querie_tilemap += std::to_string(texture);
  querie_tilemap += " ,'" + std::to_string(map_worldposition_.x) + "',";
  querie_tilemap += "'" + std::to_string(map_worldposition_.y) + "',";
  querie_tilemap += "'" + std::to_string(tile_size) + "')";

  ddbb.sqlTableQuerie(querie_tilemap.c_str());

  for(int i = 0 ; i < MKA::ListSize(grid_list_) ; ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

    querie +=
    "INSERT INTO TILES VALUES('" + std::to_string(tile->tile_id_) + "',";
    querie += "'" + std::to_string(id) + "',";
    querie += "'" + std::to_string(tile->pos_.x) + "',";
    querie += "'" + std::to_string(tile->pos_.y) + "',";
    querie += "'" + std::to_string(tile->size_.x) + "',";
    querie += "'" + std::to_string(tile->size_.y) + "',";
    querie += "'" + std::to_string(tile->walkable_) + "',";
    querie += "'" + std::to_string(tile->item_id_) + "',";
    querie += "'" + std::to_string(tile->character_id_) + "')";

    ddbb.sqlTableQuerie(querie.c_str());

    printf("SAVING... TILE: %d\n", tile->tile_id_);

    querie.erase(querie.begin(), querie.end());

  }

    printf("TILEMAP SAVED.");

}

uint8_t Tilemap::LoadTilemap(Database& ddbb, int tilemap_id){

  MKA::EraseList(&grid_list_);

  TilesData* tile_db = nullptr;
  TilemapData* map = nullptr;
  Tile* tile = nullptr;
  uint8_t result = 1;

  std::string tilemap_querie;
  tilemap_querie += "SELECT ";
  tilemap_querie += "TEX.FILE_DIR, ";
  tilemap_querie += "T.POS_X, ";
  tilemap_querie += "T.POS_Y, ";
  tilemap_querie += "T.TILES_SIZE ";
  tilemap_querie += "FROM TILEMAP T, TEXTURES TEX ";
  tilemap_querie += "WHERE T.ID = ";
  tilemap_querie += "'" + std::to_string(tilemap_id) + "' ";
  tilemap_querie += " AND TEX.ID = T.TEXTURE_ID";
/*
  SELECT TEX.FILE_DIR, T.POS_X, T.POS_Y, T.TILES_SIZE
  FROM TILEMAP T, TEXTURES TEX
  WHERE T.ID = 2 AND TEX.ID = T.TEXTURE_ID*/

  ddbb.get_tilemapData(tilemap_querie.c_str());

  if(nullptr !=
    (map = (TilemapData*) IndexListInfo(Database::extracted_queries_, 0))){

    Texture* new_texture_map_ = Texture::CreateTexture();
    new_texture_map_->set_TextureFromFile((const char*)map->texture_dir);

    if(nullptr != sprite_){
      delete sprite_;
    }

    sprite_ = new Sprite();

    sprite_->initSprite(*new_texture_map_);

    sprite_->sprite_.setPosition({map->pos_x, map->pos_y});
    map_worldposition_ = {map->pos_x, map->pos_y};


    ddbb.endExtractQueries();

  } else {

    result = 0;

  }

  std::string tiles_querie;
  tiles_querie += "SELECT ";
  tiles_querie += "TS.ID, ";
  tiles_querie += "TS.POS_X, ";
  tiles_querie += "TS.POS_Y, ";
  tiles_querie += "TS.SIZE_X, ";
  tiles_querie += "TS.SIZE_Y, ";
  tiles_querie += "TS.WALKABLE, ";
  tiles_querie += "TS.ITEM_ID, ";
  tiles_querie += "TS.CHARACTER_ID ";
  tiles_querie += "FROM TILES TS, TILEMAP T ";
  tiles_querie += "WHERE TS.TILEMAP_ID = ";
  tiles_querie += "'" + std::to_string(tilemap_id) + "'";

  ddbb.get_tilesData(tiles_querie.c_str());


  if(nullptr !=
    (tile_db = (TilesData*) IndexListInfo(Database::extracted_queries_, 0))){

      MKA::EraseList(&grid_list_);

    for(int i = 0 ; i < MKA::ListSize(Database::extracted_queries_) ; ++i){

      tile_db = (TilesData*) IndexListInfo(Database::extracted_queries_, i);

      tile = new Tile();

      tile->init({tile_db->pos_x, tile_db->pos_y},
        {tile_db->size_x, tile_db->size_y}, tile_db->id,
        font_, {tile_db->walkable});

      MKA::InsertNodeList(&grid_list_, (void*)tile);

    }

    int aux_width = 0;
    int aux_height = 0;

    if(nullptr != sprite_){

      aux_width =
      (int)((sprite_->sprite_.getGlobalBounds().width) / tile_db->size_x);
      aux_height =
      (int)((sprite_->sprite_.getGlobalBounds().height) / tile_db->size_y);

    }

    grid_size_ = {aux_width, aux_height};

    total_grid_size_ = (grid_size_.x + 2) * (grid_size_.y + 2);

    ddbb.endExtractQueries();

    cursor_.init({(float)tile_db->size_x, (float)tile_db->size_y});

  } else {

    result = 0;

  }

  return result;

}

uint8_t Tilemap::DeleteTilemap(Database& ddbb, int tilemap_id){

  uint8_t success = 0;

  std::string tile_querie;
  tile_querie += "DELETE FROM TILES WHERE TILES.TILEMAP_ID = ";
  tile_querie += "'" + std::to_string(tilemap_id) + "'";

  std::string tilemap_querie;
  tilemap_querie += "DELETE FROM TILEMAP WHERE TILEMAP.ID = ";
  tilemap_querie += "'" + std::to_string(tilemap_id) + "'";

  if(ddbb.sqlTableQuerie(tile_querie.c_str()) == 0){

    success++;

  }

  if(ddbb.sqlTableQuerie(tilemap_querie.c_str()) == 0){

    success++;

  }

  if(success == 2){

    return 1;

  } else {

    return 0;

  }

}

void Tilemap::UpdateTilemap(Database& ddbb,
  int tilemap_id,
  int texture,
  uint32_t tile_size){

  std::string table_querie;
  table_querie += "UPDATE TILEMAP SET ";
  table_querie += "TEXTURE_ID = '" + std::to_string(texture) + "',";
  table_querie += "POS_X = '" + std::to_string(map_worldposition_.x) + "',";
  table_querie += "POS_Y = '" + std::to_string(map_worldposition_.y) + "',";
  table_querie += "TILES_SIZE = '" + std::to_string(tile_size) + "' ";
  table_querie += "WHERE TILEMAP.ID = '" + std::to_string(tilemap_id) + "'";

  ddbb.sqlTableQuerie(table_querie.c_str());

  std::string tiles_querie;
  Tile* tile = nullptr;

  for(int i = 0 ; i < MKA::ListSize(grid_list_) ; ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

    tiles_querie += "UPDATE TILES SET ";
    tiles_querie += "POS_X = '" + std::to_string(tile->pos_.x) + "',";
    tiles_querie += "POS_Y = '" + std::to_string(tile->pos_.y) + "',";
    tiles_querie += "SIZE_X = '" + std::to_string(tile->size_.x) + "',";
    tiles_querie += "SIZE_Y = '" + std::to_string(tile->size_.y) + "',";
    tiles_querie += "WALKABLE = '" + std::to_string(tile->walkable_) + "',";
    tiles_querie += "ITEM_ID = '" + std::to_string(tile->item_id_) + "',";
    tiles_querie +=
    "CHARACTER_ID = '" + std::to_string(tile->character_id_) + "' ";
    tiles_querie += "WHERE TILES.ID = '" + std::to_string(tile->tile_id_) + "'";

    ddbb.sqlTableQuerie(tiles_querie.c_str());

    printf("UPDATING... TILE: %d\n", tile->tile_id_);

    tiles_querie.erase(tiles_querie.begin(), tiles_querie.end());

  }

}



void Tilemap::editGrid(sf::RenderWindow& window){

  Tile* tile = nullptr;
  sf::Vector2f mouseworld;
  sf::FloatRect boundingbox;

  for(int i = 0 ; i < MKA::ListSize(grid_list_) ; ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

    mouseworld = window.mapPixelToCoords(
      sf::Mouse::getPosition(window)
    );

    boundingbox = tile->get_debugTile().getGlobalBounds();

    if(boundingbox.contains(mouseworld)){

      if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

        tile->walkable_ = 1;

      }

      if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){

        tile->walkable_ = 0;
      }
    }
  }
}

void Tilemap::drawGridDebug(sf::RenderWindow& window){

  Tile* tile = nullptr;

  if(debugmode_){

    for(int i = 0 ; i < MKA::ListSize(grid_list_) ; ++i){

      tile = (Tile*)IndexListInfo(grid_list_, i);

      tile->draw(window);

    }

    editGrid(window);

  }

}

void Tilemap::drawRangeCharacter(sf::RenderWindow& window){

  Tile* tile = nullptr;

  for(int i = 0 ; i < MKA::ListSize(grid_list_) ; ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

      if(tile->in_range_){

        tile->drawRange(window);

      }

  }

}

void Tilemap::resetRangeCharacter(){

  Tile* tile = nullptr;

  for(int i = 0 ; i < MKA::ListSize(grid_list_) ; ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

    tile->in_range_ = 0;

  }

}

MKA::List* Tilemap::updateRangeCharacter(Character& anychar, int custom_range){


  Tile* tile = nullptr;
  MKA::List* in_range = nullptr;

  int left_offset = 0;
  int up_offset = 0;
  int right_offset = 0;
  int down_offset = 0;
  int left_pos = get_characterMapPos(anychar) + 1;
  int up_pos = get_characterMapPos(anychar) + (grid_size_.x + 2);
  int right_pos = get_characterMapPos(anychar) - 1;
  int down_pos = get_characterMapPos(anychar) - (grid_size_.x + 2);

  int range = 0;

  if(custom_range == 0){
    range = anychar.getRange();
  } else {
    range = custom_range;
  }



  for(int i = 0 ; i < MKA::ListSize(grid_list_) ; ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

    if(tile->tile_id_ == left_pos + left_offset
      && left_pos + left_offset < left_pos + range
      && tile->walkable_){

      left_offset++;
      tile->in_range_ = 1;
      MKA::InsertNodeList(&in_range, (void*)tile);

    }

    if(tile->tile_id_ == up_pos + up_offset
      && up_pos + up_offset < up_pos + range * (grid_size_.x + 2)
      && tile->walkable_){

      up_offset += (grid_size_.x + 2);
      tile->in_range_ = 1;
      MKA::InsertNodeList(&in_range, (void*)tile);

    }

  }


  for(int i = 0 ; i < MKA::ListSize(grid_list_) ; ++i){

    tile = (Tile*)IndexListInfoReverse(grid_list_, i);

    if(tile->tile_id_ == right_pos - right_offset
      && right_pos + right_offset < right_pos + range
      && tile->walkable_){

      right_offset++;
      tile->in_range_ = 1;
      MKA::InsertNodeList(&in_range, (void*)tile);

    }

    if(tile->tile_id_ == down_pos - down_offset
      && down_pos + down_offset < down_pos + range * (grid_size_.x + 2)
      && tile->walkable_){

      down_offset += (grid_size_.x + 2);
      tile->in_range_ = 1;
      MKA::InsertNodeList(&in_range, (void*)tile);

    }

  }

  return in_range;

}

MKA::List* Tilemap::charactersInRange(){

  Tile* tile = nullptr;
  MKA::List* characters_found_ = nullptr;
  int* id = nullptr;

  for(int i = 0 ; i < MKA::ListSize(grid_list_) ; ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

    if(tile->in_range_ && tile->character_id_ != -1){

      id = (int*)malloc(sizeof(int));

      *id = tile->character_id_;

      MKA::InsertNodeList(&characters_found_, (void*)id);

    }
  }

  return characters_found_;

}

MKA::List* Tilemap::charactersInTiles(){

  Tile* tile = nullptr;
  MKA::List* characters_found_ = nullptr;

  for(int i = 0 ; i < MKA::ListSize(grid_list_) ; ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

    if(tile->character_id_ != -1){

      MKA::InsertNodeList(&characters_found_, (void*)tile);

    }
  }

  return characters_found_;

}

MKA::List* Tilemap::tilesInRange(){

  Tile* tile = nullptr;
  MKA::List* tiles_to_move = nullptr;

  for(int i = 0 ; i < MKA::ListSize(grid_list_) ; ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

    if(tile->in_range_ && tile->character_id_ == -1){

      MKA::InsertNodeList(&tiles_to_move, (void*)tile);

    }
  }

  return tiles_to_move;

}

void Tilemap::draw(sf::RenderWindow& window){

  if(nullptr != sprite_){

    sprite_->draw(window);
    drawGridDebug(window);
    drawRangeCharacter(window);
    cursor_.draw(window);

  }

}

uint8_t Tilemap::set_characterMapPos(Character& anychar,
  const int ntile,
  uint8_t smooth_move){

  Tile* tile = nullptr;
  uint8_t can_execute = 1;

  if(nullptr != (tile = (Tile*)IndexListInfo(grid_list_, ntile))){

    if(tile->character_id_ == -1 && tile->walkable_ == 1){

      tile->character_id_ = anychar.get_id();

      if(!smooth_move){
        anychar.sprite_.sprite_.setPosition(tile->pos_);
      }

      can_execute = 1;

    } else {

      can_execute = 0;

    }

  } else {

    can_execute = 0;

  }

  return can_execute;

}

int Tilemap::get_characterMapPos(Character& character){

  Tile* tile = nullptr;
  bool char_id_found = false;
  int map_pos = -1;

  for(int i = 0 ; i < MKA::ListSize(grid_list_) && !char_id_found; ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

    if(character.get_id() == tile->character_id_){

      map_pos = tile->tile_id_;

      char_id_found = true;

    }

  }

  return map_pos;


}

Tile& Tilemap::get_characterMapPosTile(Character& character){

  Tile* tile = nullptr;
  Tile* tile_to_return = nullptr;
  uint8_t char_id_found = 0;

  for(int i = 0 ; i < MKA::ListSize(grid_list_) && !char_id_found; ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

    if(character.get_id() == tile->character_id_){

      tile_to_return = tile;
      char_id_found = 1;

    }

  }

  return *tile_to_return;


}

uint8_t Tilemap::set_ItemMapPos(Item& anyitem, const int ntile){

  Tile* tile = nullptr;
  uint8_t can_execute = 1;

  if(nullptr != (tile = (Tile*)IndexListInfo(grid_list_, ntile))){

    if(tile->character_id_ == -1 && tile->walkable_ == 1){

      tile->character_id_ = anyitem.get_id();
      //anyitem.sprite_.setPosition(tile->pos_);

      can_execute = 1;

    } else {

      can_execute = 0;

    }

  } else {

    can_execute = 0;

  }

  return can_execute;

}

int Tilemap::selectCharacterCursor(){

  Tile* tile = nullptr;

  int char_id_ = -1;
  uint8_t id_found_ = 0;

  for(int i = 0 ; i < MKA::ListSize(grid_list_) && !id_found_; ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

    if(tile->tile_id_ == cursor_.tile_aiming_ && !id_found_){

      if(tile->character_id_ != -1 && !id_found_){

        char_id_ = tile->character_id_;
        id_found_ = 1;

      }

    }

  }

  return char_id_;

}

int Tilemap::selectTileCursor(){

  Tile* tile = nullptr;

  int tile_id_ = 0;

  for(int i = 0 ; i < MKA::ListSize(grid_list_); ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

    if(tile->tile_id_ == cursor_.tile_aiming_){

      tile_id_ = tile->tile_id_;

    }

  }

  return tile_id_;

}

void Tilemap::gridMovement(Character& charman, const int direction){

  int next_pos = get_characterMapPos(charman);

  moveCharacterAtTile(charman, next_pos + direction, 0);

}

uint8_t Tilemap::moveCharacterAtTile(Character& charman,
  const int ntile,
  uint8_t smooth_move){

  Tile* tile = nullptr;
  uint8_t success = 0;

  for(int j = 0 ; j < MKA::ListSize(grid_list_) ; ++j){

    tile = (Tile*)MKA::IndexListInfo(grid_list_, j);

    if(tile->character_id_ == charman.get_id()){

      if(set_characterMapPos(charman, ntile, smooth_move)){

        tile->character_id_ = -1;
        success = 1;

      }

    }

  }

  return success;

}

int Tilemap::ManhattanDistance(int id1, int id2){

  int aux = 0;
  int rows = 22;

  if(id1 == id2)
  {

    return 0;

  }

  if(id1 < id2)
  {
    aux = id2;
    id2 = id1;
    id1 = aux;
  }

  id1--;
  id2--;

  if( (id1 % rows) < (id2 % rows))
  {

    aux = (id2 % rows) - (id1 % rows);

  }else
  {

    aux = (id1 % rows) - (id2 % rows);

  }

  return ((id1 / rows + 1) - (id2 / rows + 1)) + aux;

}

void Tilemap::input(sf::RenderWindow& window){

  cursor_.input(window);

}

uint8_t Tilemap::inputMovement(Character& chars){

  static int fps = 0;
  uint8_t input_made = 0;
  int fps_limit = 10;
  fps++;

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && fps >= fps_limit){
    gridMovement(chars, -1);
    fps = 0;
    input_made = 1;
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && fps >= fps_limit){
    gridMovement(chars, 1);
    fps = 0;
    input_made = 1;
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && fps >= fps_limit){
    gridMovement(chars, (int)(grid_size_.x + 2));
    fps = 0;
    input_made = 1;
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && fps >= fps_limit){
    gridMovement(chars, -(int)(grid_size_.x + 2));
    fps = 0;
    input_made = 1;
  }

  return input_made;

}

void Tilemap::updateCursor(){

  Tile* tile = nullptr;

  for(int i = 0 ; i < MKA::ListSize(grid_list_) ; ++i){

    tile = (Tile*)IndexListInfo(grid_list_, i);

    cursor_.update(*tile);

  }

}

void Tilemap::update(){

  updateCursor();
  selectCharacterCursor();

}

int Tilemap::get_tilemapSize(){

  return total_grid_size_;

}

void Tilemap::resetTile(Tile& tile){

  tile.item_id_ = -1;
  tile.character_id_ = -1;
  tile.in_range_ = 0;

}
