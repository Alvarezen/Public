// AUTHOR : ANDRES CARSANA
#ifndef __CS_H__
#define __CS_H__ 1

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "gameobject.h"
#include <mka_list.h>
#include <character.h>
#include <scene.h>
#include <sounds.h>

class Label;
class Texture;
class Sprite;

class Character_selection : public Scene{

public:

  Character_selection();

  virtual ~Character_selection();

  void init() override;

  void input() override;

  void update() override;

  // GUSTAVO: OK, in general, instead of declaring a lot of char* and
  // mallocing them, please declare static buffers like:
  //
  // char hp_[6];
  //
  // or actual strings with:
  //
  // std::string hp_;
  //
  // or
  //
  // sf:String hp_;
  //
  // That way your are not creating some memory fragmentation.
  /** @var char for snprintf of hp float into char for label*/
  char *hp;
  /** @var char for snprintf of mana float into char for label*/
  char *mana;
  /** @var char for snprintf of attack float into char for label*/
  char *attack;
  /** @var char for snprintf of defense float into char for label*/
  char *defense;
  /** @var char for snprintf of criattack float into char for label*/
  char *criattack;

private:
  // GUSTAVO: See above comment for strings and apply to all these
  // pointers to entities.
  /** @var textures for characters sprite*/
  Texture* character_selection_texture_[4];
  /** @var characters sprites*/
  Sprite * character_selection_img_[4];
  /** @var texture for hand cursor*/
  Texture* menu_cursor_texture_;
  /** @var sprite for hand cursor*/
  Sprite * menu_cursor_sprite_;
  /** @var sprite for hand cursor, characters onf left side of screen*/
  Sprite * character_cursor_sprite_;

  /** @var labels we are going to draw*/
  Label *label_[22];
  /** @var = to the label of ID class to print its description*/
  int selected_class_ID_;
  /** @var int to determine which class has beens selected for a character*/
  int selected_class_;//0 == programmer
  /** @var int to determine which character has beeen selected*/
  int selected_character_;

  /** @var */
  int labels_id_[4]; //labels id de lo de description

  /** @var characters created on the labels of left side of screen,
  *their values change depending on class selected
  */
  Character* characters_created_[4];
  /** @var characters created so we can then copy the classes' stats into created_characters_*/
  Character* characters_class_[4];
  /*
 0 progrmmer
 1 artist
 2 designer
 3 tech art
 */

  /** @var 1 if characters_created_0 has its class assigned,
  *we verify if true when player tries to go forward in char selection
  *if the 4 int are true it means every character_created has a class
  */
  // GUSTAVO: Please don't do this. Use arrays or other containers.
  // What happens when the designer changes the number of characters to 5?
  int char0_created_;
  /** @var if characters_created_1 has its class assigned*/
  int char1_created_;
  /** @var if characters_created_2 has its class assigned*/
  int char2_created_;
  /** @var if characters_created_3 has its class assigned*/
  int char3_created_;

  //sf::Music music_;

  Sounds cursor_sound_;


};

#endif
