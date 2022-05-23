/**
  * @file game.cc
  * @brief gameloop file of the game
  * @details File that is use to gameloop
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */
#include <game.h>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <scene_manager.h>
#include <menu.h>
#include <character_selection.h>
#include <combat.h>
#include <gamemanager.h>
#include <sql_management.h>
#include <time.h>
#include <stdlib.h>
#include <shop.h>
#include <died.h>
#include <sandbox.h>

uint8_t Game::exit_ = 0;
int Game::selected_scene_ = 0;
uint8_t Game::change_scene_ = 0;

Game::Game(){

  window_ = nullptr;
  current_scene_ = nullptr;
  scene_manager_ = nullptr;
  win_color_ = sf::Color(0, 0, 0, 255);

}

Game::~Game(){

  if(nullptr != window_){

    delete window_;

  }

  if(nullptr != current_scene_){

    delete current_scene_;

  }

  if(nullptr != scene_manager_){

    delete scene_manager_;

  }

}

void Game::events(){

  while(window_->pollEvent(events_)){

    ImGui::SFML::ProcessEvent(events_);

    if(events_.type == sf::Event::Closed){
      window_->close();
    }

  }

}

void Game::sceneManagerTool(){

  ImGui::Begin("Scene_developer_tool");


  ImGui::SliderInt(
    "Scene", &selected_scene_, 0, MKA::ListSize(scene_manager_->scene_list_) - 1
  );

  if(ImGui::Button("Load Scene") || change_scene_){

    LoadScene(
      *(Scene*)MKA::IndexListInfoReverse(
        scene_manager_->scene_list_, selected_scene_
      )
    );

    change_scene_ = 0;
  }

  ImGui::End();

}

void Game::input(){

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){

    exit_ = 1;

  }

  if(nullptr != current_scene_){

    current_scene_->input();
  }

}

void Game::LoadScene(Scene& newscene){
/*
  if(nullptr != current_scene_){
    current_scene_->reset();
  }*/

  current_scene_ = &newscene;
  current_scene_->init();
  current_scene_->get_window(*window_);

}

void Game::update(){

  ImGui::SFML::Update(*window_, deltatime_.restart());

  sceneManagerTool();

  if(nullptr != current_scene_){

    current_scene_->update();

  }

}

void Game::draw(){

  window_->clear(win_color_);

  if(nullptr != current_scene_){

    current_scene_->draw(*window_);

  }

  ImGui::SFML::Render(*window_);

  window_->display();
}

void Game::init(){

  srand((unsigned int)time(NULL));

  GameManager& gm = GameManager::Instance();

  gm.init();

  WindowData* my_wdata = nullptr;
  my_wdata = gm.get_windowDataFromDatabase();

    if(nullptr == window_ && nullptr != my_wdata){

      GameManager::s_windowWidth_ = my_wdata->w_width;
      GameManager::s_windowHeight_ = my_wdata->w_height;
      win_color_ = sf::Color(my_wdata->r,
        my_wdata->g, my_wdata->b, my_wdata->a);

      if(my_wdata->fullscreen){

        window_ = new sf::RenderWindow(
          sf::VideoMode(my_wdata->w_width, my_wdata->w_height),
          my_wdata->w_title, sf::Style::Titlebar | sf::Style::Close |
          sf::Style::Fullscreen
        );

      } else {

        window_ = new sf::RenderWindow(
          sf::VideoMode(my_wdata->w_width, my_wdata->w_height),
          my_wdata->w_title, sf::Style::Titlebar | sf::Style::Close
        );

      }

      if(my_wdata->fps > 0){

        window_->setFramerateLimit(my_wdata->fps);

      } else {

        window_->setVerticalSyncEnabled(true);

      }

      ImGui::SFML::Init(*window_);
      ImGui::LoadIniSettingsFromDisk(my_wdata->imgui_ini);

    } else {

      return;

    }

  scene_manager_ = new SceneManager();

  Menu* mainmenu = new Menu();
  scene_manager_->insertSceneList(*mainmenu);
  Character_selection* character_selection_ = new Character_selection();
  scene_manager_->insertSceneList(*character_selection_);
  Combat* combat = new Combat();
  scene_manager_->insertSceneList(*combat);
  Shop* shop = new Shop();
  scene_manager_->insertSceneList(*shop);
  Died* died = new Died();
  scene_manager_->insertSceneList(*died);
  Sandbox* sandbox = new Sandbox();
  scene_manager_->insertSceneList(*sandbox);
  LoadScene(*mainmenu);

  delete &gm;

}

void Game::mainLoop(){

  while(!exit_ && window_->isOpen()){

    events();
    input();
    update();
    draw();

  }

}

void Game::finish(){

  ImGui::SFML::Shutdown();

}
