/*
File: item_manager.cc
Author: Adam Álvarez Enfedal
Description: item_manager implementation
*/

#include <SFML/Graphics.hpp>
#include <character_manager.h>
#include <string.h>
#include <item_manager.h>
#include <items.h>

ItemManager::ItemManager()
{

    item_list_ = nullptr;

}

ItemManager::~ItemManager()
{

    MKA::EraseList(&item_list_);

}
