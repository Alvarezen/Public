/**
  * @file window.h
  * @brief window file of the game
  * @details This is the file which we use for window of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SFML/Graphics.hpp>



class Window{

public:

  Window();

 	Window (
    sf::VideoMode mode, const sf::String &title, 
    sf::Uint32 style, const sf::ContextSettings &settings
  );
 
  Window(sf::WindowHandle handle, const sf::ContextSettings &settings);

  virtual ~Window();

	/** @brief init for windowspells
 	*   Initialization the designer atributes for using in spells class
  *   @return nothing
 	*   @param mode mode of the window
	*   @param title title for window
	*   @param style style for window init 
	*   @param settings settings for init
  */

  void init
    (
    sf::VideoMode mode, const sf::String &title, 
    sf::Uint32 style, const sf::ContextSettings &settings
    );

  void setTitle(const sf::String &title);

  int windowOpen();

  void windowClose();

  void setVerticalSyncEnabled(bool enabled);

  void setMouseCursorVisible(bool visible);

  void setMouseCursor(const sf::Cursor &cursor);

  void setFramerateLimit(unsigned int limit);

  void display();

  void clear(sf::Color negrote);

  bool pollEvent(sf::Event& event);

  sf::RenderWindow* window_;

private:


};

#endif //!__WINDOW_H__