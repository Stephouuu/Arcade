//
// SPacGum.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/games/pacman/src/game/item
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Mar 24 15:28:46 2016 stephane galibert
// Last update Sun Mar 27 21:14:29 2016 stephane galibert
//

#include "SPacGum.hpp"

arcade::SPacGum::SPacGum(arcade::Vector2u const& pos)
{
  _pos = pos;
  _delta = 0;
  _currentFrame = 0;
}

arcade::SPacGum::~SPacGum(void)
{

}

void arcade::SPacGum::affectPlayer(arcade::Player& player,
				   std::vector<arcade::Ghost *> &ghosts,
				   arcade::Map &map)
{
  (void)map;
  player.addBuff(new BSPacGum(player, ghosts));
}

void arcade::SPacGum::addFrame(arcade::Drawable const *frame)
{
  _frames.push_back(frame);
}

void arcade::SPacGum::update(float const delta)
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

arcade::Drawable const * arcade::SPacGum::getCurrentFrame(void) const
{
  return (_frames[_currentFrame]);
}

arcade::Vector2u const& arcade::SPacGum::getPos(void) const
{
  return (_pos);
}
