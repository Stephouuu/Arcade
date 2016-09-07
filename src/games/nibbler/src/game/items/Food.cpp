//
// Food.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Mar 18 18:42:58 2016 stephane galibert
// Last update Sun Mar 27 19:08:28 2016 stephane galibert
//

#include "Food.hpp"

arcade::Food::Food(arcade::Vector2u const& pos, Drawable const * textureDest)
  : _textureDest(textureDest)
{
  _pos = pos;
  _delta = 0;
  _currentFrame = 0;
}

arcade::Food::~Food(void)
{

}

void arcade::Food::affectPlayer(arcade::Player& player, arcade::Map &map)
{
  player.addBody(map, _textureDest);
  player.addScore(1);
  player.addBuff(new AddScore(player.getHeadPosition(), 1 * player.getScoreCoef()));
}

void arcade::Food::addFrame(arcade::Drawable const *frame)
{
  _frames.push_back(frame);
}

void arcade::Food::update(float const delta)
{
  _delta += delta;
  if (_delta >= IItems::DELAY_ANIMATION)
    {
      ++_currentFrame;
      if (_currentFrame == _frames.size())
	_currentFrame = 0;
      _delta = (size_t)_delta % IItems::DELAY_ANIMATION;
    }
}

arcade::Drawable const * arcade::Food::getCurrentFrame(void) const
{
  return (_frames[_currentFrame]);
}

arcade::Vector2u const& arcade::Food::getPos(void) const
{
  return (_pos);
}
