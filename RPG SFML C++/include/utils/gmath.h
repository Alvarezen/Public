/**
  * @file gmath.h
  * @brief math funcs file of the game
  * @details File that is use to math funcs
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */


#ifndef __MATH__H__
#define __MATH__H__

#include <stdint.h>

class Math{

public:

  static int RandomInt(int max, int min = 0);
  static float RandomFloat(int max, int min = 0);
  static void OrderNumbers(int* numbers, int array_size, uint8_t order);

private:

};

#endif //!__MATH__H__
