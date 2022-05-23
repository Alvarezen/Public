/*
File: input.cc
Author: Adam Álvarez Enfedal
Description: input implementation
*/

#include <input.h>

Input::Input()
{

}

Input::~Input()
{

}

uint8_t Input::isMouseButtonDown(sf::Mouse::Button button){
  static int frames = 0;

  if(sf::Mouse::isButtonPressed(button) && frames < 1){
    frames++;
    return 1;
  }else{
    if(!sf::Mouse::isButtonPressed(button)){
      frames = 0;
    }
    return 0;
  }
}

uint8_t Input::isMouseButtonUp(sf::Mouse::Button button){
  static int frames = 0;

  if(sf::Mouse::isButtonPressed(button) && frames < 1){
    frames++;
    return 0;
  }else{
    if(!sf::Mouse::isButtonPressed(button) && frames > 0){
      frames = 0;
      return 1;
    }
    return 0;
  }
}

bool Input::isJoystickConnected(){
  if(sf::Joystick::isConnected(0)){
    printf("isConnected");
    return true;
  }else{
    printf("isNotConnected");
    return false;
  }
}

void Input::setButtons(){
  button[0] = 0;  //A button
  button[1] = 1;  //B button
  button[2] = 2;  //X button
}

uint8_t Input::isJoystickButtonDown(unsigned int Joy_id, int _button) const
{
  static int frames = 0;

  if(sf::Joystick::isButtonPressed(Joy_id, _button) && frames < 1){
    frames++;
    return 0;
  }else if(!sf::Joystick::isButtonPressed(Joy_id, _button) && frames > 0){
    frames = 0;
    return 1;
  }
  return 0;
}

sf::Vector2f Input::axis(unsigned int joy_id)
{
  sf::Vector2f axisValue_(sf::Joystick::getAxisPosition(joy_id, sf::Joystick::X),
                          sf::Joystick::getAxisPosition(joy_id, sf::Joystick::Y));
  return axisValue_;
}
