#include <game.h>

int main(){

  Game game;

  game.init();
  game.mainLoop();
  game.finish();

  return 0;

}
