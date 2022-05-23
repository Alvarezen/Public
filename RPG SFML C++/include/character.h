  /**
  * @file character.h
  * @brief character file of the game
  * @details This is the file which we use for character of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */

#ifndef __CHA_H__
#define __CHA_H__ 1

#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include <string.h>
#include <mka_list.h>
#include "sprite.h"

class Tilemap;

class Character : public GameObject{

public:

  enum kCharactersType
  {

    kCharactersType_none = -1,
    kCharactersType_programmer = 0,
    kCharactersType_artist = 1,
    kCharactersType_designer = 2,
    kCharactersType_techartist = 3,
    kCharactersType_enemy = 4

  };

  enum kEnemyState
  {

    kEnemyState_none = -1,
    kEnemyState_patrol = 0,
    kEnemyState_attack = 1,
    kEnemyState_surrounded = 2

  };

  Character();

  Character(const Character& charcopy);

  virtual ~Character();

  Sprite sprite_;

  kCharactersType chartype_;

  /** @var Use it for the coins of which characters can spend in the game items*/
  int distincion_coin_;

  sf::String character_name_;

  /** @brief Initilization the Character attributes
  *
  *   Initialization the Character attributes for using our
  *   playable and non playable characters for the game.
  *   It has the parameters we need to use for the characters.
  *
  *   @return nothing
  *
  *   @param pos The vector2f for initial position on the map
  *   @param scale Establishes the scale of the character on the map
  *   @param texture The texture we need for print the characters
  *   @param hp Establishes the initial health points of this character
  *   @param mana Establishes the initial mana of this character
  *   @param attack Establishes the initial attack points of this character
  *   @param defense Establishes the initial defense of this character
  *   @param criattack Establishes the initial critical attack points of this character
  *   @param level Establishes the initial level of the character
  *   @param move Establishes the move on the map of the character
  *   @param alive Put the character life true on the game. We use uint8 like a char
  *   @param chartype Establishes character enum for another thing of the gam.
  *   for expample items or spells.
  *
  */

  void init(
    const sf::Vector2f pos,
    const sf::Vector2f  scale,
    Texture &texture,
    float hp, float mana,
    float attack, float defense,
    float criattack, int level,
	  uint8_t alive,
  	uint8_t turns, int experience,
    kCharactersType chartype, int range,
    float col, const char* name, int max_experience
  );


  /** @brief Initilization the Character attributes for using in another ui function
  *
  *   Initialization the Character attributes for using it on
  *   another ui function. This use to drawing in real time this atributes
  *
  *   @return nothing

  *   @param hp Establishes the health points of this character
  *   @param mana Establishes the mana of this character
  *   @param attack Establishes the attack points of this character
  *   @param defense Establishes the defense of this character
  *   @param criattack Establishes the critical attack points of this character
  *
  */

  virtual void init(float hp, float mana, float attack,
			      float defense, float criattack);

  /** @brief Control de character life in game
  *
  *   Control if character is alive or dead in our game with this
  *   function which recive this parameter.
  *
  *   @return nothing
  *   @param life This data type using for put character alive or dead.
  *
  */

  void lifeOn(uint8_t life);

  /** @brief Control de character turns of the game
  *
  *   Control character`s turns on the game and allow all the character attack, for example,
  *   in the game loop.
  *   @return nothing
  *   @param turns This data type using for character`s turn and put 0 (false), or 1 (true).
  *
  */

  void usablePjTurn(char turns);

  void update(Tilemap& tilemap);

  void draw(sf::RenderWindow& window) override;

  /** @brief Level up the character levels of the game
  *
  *   This function which use to level up the character and their atributes on the game.
  *   @return nothing
  *
  */

  void levelUp();

  MKA::List* get_CharacterList();

  /** @brief Set the character on the list
  *
  *   This function use to set the character on the list of out character list game.
  *   @return nothing
  */

  void enemyAttack(Character& character);

  /** @brief Ennemy attacck function
  *
  *   This function use to do the basic enemy attack on the game.Basically what the
  *   function does is to subtract life from the player through a collection of the total
  *   damage resulting from the enemy's attack minus the player's defense, subtracting
  *   all of this from his life.
  *
  *   @return nothing
  *   @param character use to instantiate a character data type and use it
  */

  int reciveAttack(Character& character);

  /** @brief Ennemy attacck function
  *
  *   This function use to do the basic player attack on the game.Basically what the
  *   function does is to subtract life from the player through a collection of the total
  *   damage resulting from the enemy's attack minus the player's defense, subtracting
  *   all of this from his life. This function also adds a counter to change the turns
  *   of each character and, when this counter reaches 4, we go to the enemy turn.
  *
  *   @return nothing
  *   @param character use to instantiate a character data type and use it
  */

  void set_CharacterList(MKA::List*);

  void setAttack(float);
  float getAttack() const;

  void setMana(float);
  float getMana() const;

  void setMaxMana(float);
  float getMaxMana() const;

  void setHp(float);
  float getHp() const;

  void setMaxHp(float);
  float getMaxHp() const;

  void setDefense(float);
  float getDefense() const;

  void setCriattack(float);
  float getCriattack() const;

  void setLevel(int);
  int getLevel() const;

  void setTurnspj(uint8_t);
  uint8_t getTurnspj() const;

  void setTurns(uint8_t);
  uint8_t getTurns();

  void setLife(uint8_t);
  uint8_t getLife() const;

  void setExperience(int);
  int getExperience() const;

  void setName(const char*);
  const char* getName() const;

  kCharactersType getKcharacter() const;

  int getRange();

  int get_maxExp();

  void checkHealth();

  Sprite ui_sprite_;
  Texture ui_texture_;

protected:

  /** @var Use it for the health points of the characters*/
  const char* name_;
  /** @var Use it for the health points of the characters*/
  float hp_;
  /** @var Use it for the maximun health points of the characters*/
  float maxhp_;
  /** @var Use it for the mana points of the characters*/
  float mana_;
  /** @var Use it for the maximun mana points of the characters*/
  float maxmana_;
  /** @var Use it for the attack points of the characters*/
  float attack_;
  /** @var Use it for the moving of the characters*/
  float move_;
  /** @var Use it for defensive points of the characters*/
  float defense_;
  /** @var Use it for critical attack points of the characters*/
  float criattack_;
  /** @var Using to stay as true (1) or false (0) the characters`s life on the game*/
  uint8_t alive_;
  /** @var Using to stay as true (1) or false (0) the characters`s turn on the game*/
  uint8_t turns_;
  /** @var Use it to put the level of the characters of the game*/
  int level_;
  /** @var Use it for the experience characters`points of the game*/
  int experience_;
  /** @var Use it for the experience characters`range of the game*/
  int max_experience_;
  /** @var Use it for the experience characters`range of the game*/
  int range_;
  /** @var Use it for the characters`type of the game*/
  uint8_t typeofchar_;

  float col_;



private:

};

#endif //!__CHA_H__
