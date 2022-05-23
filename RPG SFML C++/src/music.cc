#include <music.h>


Music::Music(){

}

void Music::init(const char* filename){
  if(!music_.openFromFile(filename)){
    printf("error");
  }
  music_playing_ = 0;
}

void Music::play(){
  if(music_playing_ == 0){
    music_.play();
    music_playing_= 1;
  }
}

void Music::pause(){
  if(music_playing_ == 1){
    music_.pause();
    music_playing_= 0;
  }
}

void Music::stop(){
  if(music_playing_ == 1){
    music_.stop();
    music_playing_= 0;
  }
}

void Music::setVolume (float volume){
  music_.setVolume(volume);
}

void Music::setLoop(bool condition){
  music_.setLoop(condition);
}

Music::~Music(){

}
