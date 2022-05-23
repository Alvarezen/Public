#include <sounds.h>

Sounds::Sounds(){

}

/*void Sounds::Sounds(const sf::SoundBuffer &buffer){
  sound_ = new sf::Sound(buffer);
}*/

Sounds::~Sounds(){

}

void Sounds::initBuffer(const char* filename){
  if(!buffer_.loadFromFile(filename)){
    printf("error");
  }
}

void Sounds::play(){
  sound_.play();
}

void Sounds::pause(){
  sound_.pause();
}

void Sounds::stop(){
  sound_.stop();
}

void Sounds::setBuffer(sf::SoundBuffer &buffer){
  sound_.setBuffer(buffer);
}

const sf::SoundBuffer *Sounds::getBuffer() const{
  return sound_.getBuffer();
}

void Sounds::setLoop(bool loop){
  sound_.setLoop(loop);
}

bool Sounds::getLoop()const{
  return sound_.getLoop();
}

void Sounds::setPlayingOffset(sf::Time timeOffset){
  sound_.setPlayingOffset(timeOffset);
}

sf::Time Sounds::getPlayingOffset()const{
  return sound_.getPlayingOffset();
}

void Sounds::setVolume (float volume){
  sound_.setVolume(volume);
}

float Sounds::getVolume()const{
  return sound_.getVolume();
}

void Sounds::setPosition(const sf::Vector3f &position){
  sound_.setPosition(position);
}

sf::Vector3f Sounds::getPosition()const{
  return sound_.getPosition();
}
