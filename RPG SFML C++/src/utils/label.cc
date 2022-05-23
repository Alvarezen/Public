#include "label.h"


Label::Label(){


}

void Label::initLabel(const char *string, sf::Vector2f pos, sf::Color tcolor,
              sf::Color olcolor){

  text_.setPosition(pos);
  text_.setString(string);

  text_.setFillColor(tcolor);
  text_.setOutlineColor(olcolor);

  box_.setPosition(text_.getPosition());
  // box_.setSize(sf::Vector2f(text_.getLocalBounds().width,
  //                       text_.getLocalBounds().height));

}

void Label::setLabelString(const char *string){
  text_.setString(string);
}

sf::String Label::getDescriptionString(){
  return description_.getString();
}


void Label::setLabelDescription(const char *string){
  description_.setString(string);
}

void Label::setLabelFont(sf::Font font, int fontsize){
  font_ = font;
  text_.setFont(font_);
  text_.setCharacterSize(fontsize);
}
void Label::setDescriptionFont(sf::Font font, int fontsize){
  font_ = font;
  description_.setFont(font_);
  description_.setCharacterSize(fontsize);
}

void Label::centerText(){
  text_.setOrigin(text_.getLocalBounds().
                          width*0.5f,text_.getLocalBounds().height*0.5f);
  box_.setOrigin(box_.getLocalBounds().
                      width*0.5f,box_.getLocalBounds().height*0.4f);
}

void Label::getTextBox(){

  box_.setPosition(text_.getPosition());
  box_.setSize(sf::Vector2f(text_.getLocalBounds().width*1.1f,
                        text_.getLocalBounds().height*1.2f));
  box_.setFillColor(sf::Color(255,255,255,50));

}

int Label::isSelected(sf::RenderWindow& window){

  sf::Vector2f mouseworld;
  sf::FloatRect boundingbox;

  mouseworld = window.mapPixelToCoords(
    sf::Mouse::getPosition(window)
  );

  boundingbox = box_.getGlobalBounds();

  if(boundingbox.contains(mouseworld)){
  return 1;
  }else{
    return 0;
  }

}

int Label::isClicked(sf::RenderWindow& window){

  if(Label::isSelected(window) == 1 &&
      click_.isMouseButtonDown(sf::Mouse::Left) == 1){
  return 1;
  }else{
    return 0;
  }

}

//void Label::update(sf::RenderWindow &window){}

void Label::drawText(sf::RenderWindow &window){
      window.draw(text_);
}
void Label::drawBox(sf::RenderWindow &window){
      window.draw(box_);
}

void Label::draw(sf::RenderWindow& window){
  drawText(window);
  //drawBox(window);
}

Label::~Label(){

}
