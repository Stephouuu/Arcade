//
// Score.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Mon Mar 21 11:13:36 2016 stephane galibert
// Last update Sat Apr  2 22:36:13 2016 stephane galibert
//

#include "Score.hpp"

arcade::Score::Score(arcade::Vector2u const& pos)
{
  _pos = pos;
  _delta = 0;
  _currentFrame = 0;
}

arcade::Score::~Score(void)
{

}

void arcade::Score::affectPlayer(arcade::Player &player, arcade::Map &map)
{
  (void)map;
  player.addBuff(new ScoreMultiplier(player));
}

void arcade::Score::addFrame(arcade::Drawable const * frame)
{
  _frames.push_back(frame);
}

void arcade::Score::update(float const delta)
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

arcade::Drawable const * arcade::Score::getCurrentFrame(void) const
{
  return (_frames[_currentFrame]);
}

arcade::Vector2u const& arcade::Score::getPos(void) const
{
  return (_pos);
}
