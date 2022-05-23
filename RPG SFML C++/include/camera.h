/**
  * @file camera.h
  * @brief camera file of the game
  * @details This is the file which we use of camera of the game
  * @author Adam Álvarez Enfedal <alvarezen@esat-alumni.com>
  * @version 1.0
  * @date Dec-2020
  * @copyright ESAT
  */


#ifndef __CAMERA_H__
#define __CAMERA_H__ 1

#include <SFML/Graphics.hpp>



class Camera {

public:

    Camera();

    Camera(const sf::FloatRect &rectangle);

    Camera(const sf::Vector2f &center, const sf::Vector2f &size);

    ~Camera();

   /** @brief init for camera and new view
 	  *   Initialization the artist atributes for using in spells class
  	*   @return nothing
  	*/

    void init();

    void setCenter(const sf::Vector2f &center);

    void setSize(const sf::Vector2f &size);

    void setRotation(float angle);

    void setViewport(const sf::FloatRect &viewport);

    const sf::Vector2f &getCenter() const;

    const sf::Vector2f &getSize() const;

    float getRotation() const;

    const sf::FloatRect &getViewport() const;

    /** @brief Function for moving camera with vector2f
    *
  	*   @return nothing
    *   @param offset Vector2f for moving the camera
  	*/

    void move(const sf::Vector2f &offset);

    /** @brief Function for rotate camera with an angle
    *
  	*   @return nothing
    *   @param angle float for using in angle
  	*/

    void rotate(float angle);

    /** @brief Function for doing zoom with camera class with a float
    *
  	*   @return nothing
    *   @param factor float for using in zoom
  	*/

    void zoom(float factor);

	/** @var camera_ for using in all of my functions which called sfml functions */
    sf::View* camera_;

private:

};

#endif //!__CAMERA_H__
