//
// Random.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Mar 19 23:27:27 2016 stephane galibert
// Last update Sat Apr  2 22:36:05 2016 stephane galibert
//

#include "Random.hpp"

arcade::Random::Random(arcade::Vector2u const& pos,
		       arcade::Drawable const * textureDest)
  :  _textureDest(textureDest)
{
  _pos = pos;
  _delta = 0;
  _currentFrame = 0;
}

arcade::Random::~Random(void)
{

}

void arcade::Random::affectPlayer(arcade::Player& player, arcade::Map &map)
{
  size_t n = _generator(2, 4);
  for (size_t i = 0 ; i < n ; ++i)
    {
      player.addBody(map, _textureDest);
      player.addScore(1);
    }
  player.addBuff(new AddScore(player.getHeadPosition(), n * player.getScoreCoef()));
}

void arcade::Random::addFrame(arcade::Drawable const *frame)
{
  _frames.push_back(frame);
}

void arcade::Random::update(float const delta)
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

arcade::Drawable const * arcade::Random::getCurrentFrame(void) const
{
  return (_frames[_currentFrame]);
}

arcade::Vector2u const& arcade::Random::getPos(void) const
{
  return (_pos);
}
