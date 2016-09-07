//
// SuperFood.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/games/nibbler
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Mar 18 20:50:41 2016 stephane galibert
// Last update Sat Apr  2 22:36:34 2016 stephane galibert
//

#include "SuperFood.hpp"

arcade::SuperFood::SuperFood(arcade::Vector2u const& pos,
			     arcade::Drawable const *textureDest)
  : _textureDest(textureDest)
{
  _pos = pos;
  _delta = 0;
  _currentFrame = 0;
}

arcade::SuperFood::~SuperFood(void)
{

}

void arcade::SuperFood::affectPlayer(arcade::Player& player, arcade::Map &map)
{
  player.addBody(map, _textureDest);
  player.addScore(10);
  player.addBuff(new AddScore(player.getHeadPosition(), 10 * player.getScoreCoef()));
}

void arcade::SuperFood::addFrame(arcade::Drawable const *frame)
{
  _frames.push_back(frame);
}

void arcade::SuperFood::update(float const delta)
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

arcade::Drawable const * arcade::SuperFood::getCurrentFrame(void) const
{
  return (_frames[_currentFrame]);
}

arcade::Vector2u const& arcade::SuperFood::getPos(void) const
{
  return (_pos);
}
