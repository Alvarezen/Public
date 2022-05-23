#ifndef __LAB_H__
#define __LAB_H__ 1

#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include <mka_list.h>
#include <stdint.h>
#include <input.h>



class Label : public GameObject{



public:

  Label();

  void initLabel(const char *string, sf::Vector2f pos, sf::Color tcolor,
              sf::Color olcolor);

  void setLabelString(const char *string);
  void setLabelDescription(const char *string);
  void setLabelStringFloat(float number);

  void setLabelFont(sf::Font font, int fontsize);
  void setDescriptionFont(sf::Font font, int fontsize);

  void centerText(); // call after every init

  void getTextBox();

  void update(sf::RenderWindow &window);

  int isSelected(sf::RenderWindow& window); // 0 == false, 1 == true;
  int isClicked(sf::RenderWindow& window); // 0 == false, 1 == true;

  void drawText(sf::RenderWindow &window);
  void drawBox(sf::RenderWindow &window);

  void draw(sf::RenderWindow& window) override;

  sf::String getDescriptionString();

  ~Label();

  sf::Text text_;
  sf::Text description_;
  sf::RectangleShape box_;
  sf::Font font_;
  Input click_;

protected:

private:

};

#endif
