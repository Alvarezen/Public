/**
  * @file gmath.cc
  * @brief math funcs file of the game
  * @details File that is use to math funcs
  * @author Alvaro Vazquez Carmona <vazquezca@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */


#include <gmath.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

int Math::RandomInt(int max, int min){

  int range = max - min + 1;

  if(range != 0 || min != 0){

    return (rand()% range + min);

  } else {

    return -1;

  }



}

float Math::RandomFloat(int max, int min){

  float scale = (rand() / (float) RAND_MAX);
  return (min + scale * ( max - min ));

}

void Math::OrderNumbers(int* numbers, int array_size, uint8_t order){

  if(order){

    for(int i = 0; i < array_size ; i++){

      for(int j = 0; j < array_size - 1 ; j++){

        if(*(numbers+j) > *(numbers+j+1)){
            int temp = *(numbers+j);
            *(numbers+j) = *(numbers+j+1);
            *(numbers+j+1) = temp;
        }

      }

    }

  } else {

    for(int i = 0; i < array_size ; i++){

      for(int j = 0; j < array_size - 1 ; j++){

        if(*(numbers+j) < *(numbers+j+1)){
            int temp = *(numbers+j);
            *(numbers+j) = *(numbers+j+1);
            *(numbers+j+1) = temp;
        }

      }

    }

  }

}
