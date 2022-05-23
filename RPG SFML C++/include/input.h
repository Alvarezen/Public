/**
  * @file sounds.h
  * @brief sounds file of the game
  * @details This is the file which we use for sounds of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __INPUT_H__
#define __INPUT_H__ 1

#include <SFML/Graphics.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "gameobject.h"
#include <string.h>

class Input{

public:

	Input();

	~Input();

	/** @brief Detect is mouse is pressed
	*   @return number of the button action
	*   @param button to establish the key
	*/

	static uint8_t isMouseButtonDown(sf::Mouse::Button button);

	/** @brief Detect is mouse is released
	*   @return number of the button action
	*   @param button to establish the key
	*/

	static uint8_t isMouseButtonUp(sf::Mouse::Button button);

	/** @brief getter of the mouse position X
	*   @return position in X axis
	*   @param nothing
	*/

	int getMouseX() const;

	/** @brief getter of the mouse position Y
	*   @return position in Y axis
	*   @param nothing
	*/

	int getMouseY() const;

	/** @brief detect if the button of the controller is pressed
	*   @return number of the button action
	*   @param _button to establish the key
	*   @param joy_id to establish Joystick id
	*/

	uint8_t isJoystickButtonDown(unsigned int joy_id, int _button) const;

	/** @brief detect if the button of the controller is pressed
	*   @return boolean that inform if the joystick is connected
	*   @param nothing
	*/

	bool isJoystickConnected();

	/** @brief stablish the value of the buttons
	*   @return nothing
	*   @param nothing
	*/

	void setButtons();

	/** @brief Used to know the position of the joystick axis X and Y
	*   @return value of X and Y axis
	*   @param joy_id to know the joystick id
	*/

	sf::Vector2f axis(unsigned int joy_id);

	/** @var Used to detect buttons*/
	unsigned int button[3];


private:

};

#endif //!__INPUT_H__
