/*
File: camera.cc
Author: Adam Álvarez Enfedal
Description: camera class implementation
*/

#include <SFML/Graphics.hpp>
#include "camera.h"

Camera::Camera()
{

}

Camera::Camera(const sf::FloatRect &rectangle)
{

    camera_ = new sf::View(rectangle);

}

Camera::~Camera()
{
    if(nullptr != camera_)
    delete camera_;

}

void Camera::init(){

    camera_ = new sf::View();

}

void Camera::setCenter(const sf::Vector2f &center){

    camera_->setCenter(center);

}

void Camera::setSize(const sf::Vector2f &size){

    camera_->setSize(size);

}

void Camera::setRotation(float angle){

    camera_->setRotation(angle);

}

void Camera::setViewport(const sf::FloatRect &viewport){


    camera_->setViewport(viewport);

}

void Camera::move(const sf::Vector2f &offset){

    camera_->move(offset);

}

void Camera::rotate(float angle){

    camera_->rotate(angle);

}

void Camera::zoom(float factor){

    camera_->zoom(factor);

}


const sf::Vector2f &Camera::getCenter() const{

    return camera_->getCenter();

}

const sf::Vector2f &Camera::getSize() const{

    return camera_->getSize();

}

float Camera::getRotation() const{

    return camera_->getRotation();
}

const sf::FloatRect &Camera::getViewport() const{

    return camera_->getViewport();
}
