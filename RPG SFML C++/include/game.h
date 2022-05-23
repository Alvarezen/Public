/**
  * @file game.h
  * @brief gameloop file of the game
  * @details File that is use to gameloop
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __GAME_H__
#define __GAME_H__ 1

#include <SFML/Graphics.hpp>
#include <gamemanager.h>
#include <stdint.h>


class SceneManager;
class Scene;

class Game{

public:

  Game();

  ~Game();

  void init();
  void mainLoop();
  void finish();

  void LoadScene(Scene&);

  static uint8_t exit_;
  static int selected_scene_;
  static uint8_t change_scene_;


protected:

  void input();
  void update();
  void draw();

  Scene* current_scene_;
  SceneManager* scene_manager_;

private:

  sf::RenderWindow* window_;
  sf::Color win_color_;
  sf::Event events_;
  sf::Clock deltatime_;

  void events();
  void sceneManagerTool();

};


#endif//!__GAME_H__
