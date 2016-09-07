//
// Speed.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Mar 20 08:28:39 2016 stephane galibert
// Last update Sat Apr  2 22:36:23 2016 stephane galibert
//

#include "Speed.hpp"

arcade::Speed::Speed(arcade::Vector2u const& pos)
{
  _pos = pos;
  _delta = 0;
  _currentFrame = 0;
}

arcade::Speed::~Speed(void)
{

}

void arcade::Speed::affectPlayer(arcade::Player &player, arcade::Map &map)
{
  (void)map;
  player.addBuff(new BSpeed(player));
}

void arcade::Speed::addFrame(arcade::Drawable const * frame)
{
  _frames.push_back(frame);
}

void arcade::Speed::update(float const delta)
{
  _delta += delta;
  if (_delta >= IItems::DELAY_ANIMATION)
    {
      ++_currentFrame;
      if (_currentFrame == _frames.size())
	_currentFrame = 0;
      _delta = (size_t)delta % IItems::DELAY_ANIMATION;
    }
}

arcade::Drawable const * arcade::Speed::getCurrentFrame(void) const
{
  return (_frames[_currentFrame]);
}

arcade::Vector2u const& arcade::Speed::getPos(void) const
{
  return (_pos);
}
