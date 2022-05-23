/*
File: animation.cc
Author: Saul Vicente Camacho Diaz
Description: animation of sprites
*/

#include <animation.h>

Animation::Animation()
{

}

Animation::~Animation()
{

}

void Animation::selectFrame()
{
  // GUSTAVO: This creates a Memory Leak.
  // sprite is never released nor actually used properly.
  sf::Sprite* sprite = new sf::Sprite();

  sf::IntRect rect((int)texture_.requiredFrame_.x * (int)texture_.framePixelSize_.x,
                   (int)texture_.requiredFrame_.y * (int)texture_.framePixelSize_.y,
                   (int)texture_.framePixelSize_.x, (int)texture_.framePixelSize_.y);

	sprite->setTextureRect(rect);
}

void Animation::animateFrame()
{
	if (texture_.requiredFrame_.x != texture_.nCol - 1)
	{
		texture_.requiredFrame_.x += 1;
	}
	else
	{
		texture_.requiredFrame_.x = 0;
	}

	selectFrame();
}

void Animation::setFrameCol(float frame)
{
	texture_.requiredFrame_.x = frame;
	selectFrame();
}

void Animation::setFrameRow(float frame)
{
	texture_.requiredFrame_.y = frame;
	selectFrame();
}
