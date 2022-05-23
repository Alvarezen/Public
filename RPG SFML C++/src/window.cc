/*
File: window.cc
Author: Adam Álvarez Enfedal
Description: window implementation
*/

#include <SFML/Graphics.hpp>
#include "window.h"

Window::Window()
{


}

Window::Window
    (
    sf::VideoMode mode, const sf::String &title,
    sf::Uint32 style, const sf::ContextSettings &settings
    )
{

    window_ = new sf::RenderWindow(mode, title, style, settings);

    window_->create(mode, title, style, settings);

}

Window::~Window()
{

    if(nullptr != window_){
        delete window_;
    }

}

void Window::init
    (
    sf::VideoMode mode, const sf::String &title,
    sf::Uint32 style, const sf::ContextSettings &settings
    )
{

    window_->create(mode, title, style, settings);
}

void Window::setTitle(const sf::String &title)
{

    window_->setTitle(title);

}

void Window::setVerticalSyncEnabled(bool enabled){

    window_->setVerticalSyncEnabled(enabled);

}

void Window::setMouseCursorVisible(bool visible){

    window_->setMouseCursorVisible(visible);
}

void Window::setMouseCursor(const sf::Cursor &cursor){

    window_->setMouseCursor(cursor);
}

void Window::setFramerateLimit(unsigned int limit){

    window_->setFramerateLimit(limit);
}

void Window::display(){

    window_->display();
}

void Window::clear(sf::Color negrote){

    window_->clear(negrote);
}

int Window::windowOpen()
{
    if(window_->isOpen()){
        return 1;
    }
    return 0;
}

void Window::windowClose(){

    window_->close();
}

bool Window::pollEvent(sf::Event& event){

    if(window_->pollEvent(event)){
        return 1;
    }
    return 0;
}
