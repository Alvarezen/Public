// AUTHOR : ANDRES CARSANA

#ifndef __UI_H__
#define __UI_H__ 1

#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "label.h"
#include <mka_list.h>
#include <programmer.h>
#include <spells.h>
#include <sprite.h>
#include <texture.h>
#include <items.h>

class Character;

class Ui : public GameObject{

public:

  Ui();
  ~Ui();

  void init();

  void combatFeedback(Character& dealer, Character& receiver, int);

  void update(sf::RenderWindow&, Character *selected_character);

  void draw(sf::RenderWindow&) override;

  // void initUi(Character &character);
  //
  // void drawUi(sf::RenderWindow &window);
  //
  // void initializeBars(Character &character);
  //
  // void drawBarsUi(sf::RenderWindow &window, Character &character);




  // void initListUi();
  // void drawListUi(sf::RenderWindow *window);

protected:

private:

  // sf::Font pixelfont_;

  Programmer* character;



  Texture* character_texture_[4];
  Sprite * character_sprite_;

  MKA::List *list_;

  sf::Sprite playerSprite_;

  /**@var rectangle for hp bar*/
  sf::RectangleShape* hp_;
  /**@var rectangle for mana bar*/
  sf::RectangleShape* mana_;
  /**@var rectangle for exp bar*/
  sf::RectangleShape* exp_;

  /**@var rectangle for hp background bar*/
  sf::RectangleShape* hp_bg_;
  /**@var rectangle for mana background bar*/
  sf::RectangleShape* mana_bg_;

  // sf::RectangleShape* provisional;

  /**@var we use a getter to get the value from the character to
  * then set size for the hp bar
  */
  float hp_num_;
  /**@var we use a getter to get the value from the character to
  * then set size for the maxhp bar
  */
  float maxhp_num_;
  /*@var *we use a getter to get the value from the character to
  * then set size for the mana bar
  */
  float mana_num_;
  /**@var we use a getter to get the value from the character to
  * then set size for the maxmana bar
  */
  float maxmana_num_;


  /** @var labels to print text */
  // GUSTAVO: If there are fixed numbers of objects, please declare static
  // arrays or containers or lists of actual objects instead of pointers to
  // reduce memory fragmentation. Like:
  //
  // Label label_[22];
  Label* label_[22];
  Label* label_feedback_;
  Label* info_[6];
  char* spell_mana_[4];

  Item* item_[12];

  char *level;
  char *hp;
  char *attack;
  char *defense;
  char *criattack;
  char *feedback;

  int damage_dealed;

};

#endif //!__UI_H__
