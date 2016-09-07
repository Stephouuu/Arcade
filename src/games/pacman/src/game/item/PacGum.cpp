//
// PacGum.cpp for arcade in /home/galibe_s/rendu/cpp_arcadeold/src/games/pacman/item
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Mar 24 10:14:15 2016 stephane galibert
// Last update Sun Mar 27 21:16:27 2016 stephane galibert
//

#include "PacGum.hpp"

arcade::PacGum::PacGum(arcade::Vector2u const& pos)
{
  _pos = pos;
  _delta = 0;
  _currentFrame = 0;
}

arcade::PacGum::~PacGum(void)
{

}

void arcade::PacGum::affectPlayer(arcade::Player& player,
				  std::vector<arcade::Ghost *> &ghosts,
				  arcade::Map &map)
{
  (void)map;
  (void)ghosts;
  player.addScore(1);
}

void arcade::PacGum::addFrame(arcade::Drawable const *frame)
{
  _frames.push_back(frame);
}

void arcade::PacGum::update(float const delta)
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

arcade::Drawable const * arcade::PacGum::getCurrentFrame(void) const
{
  return (_frames[_currentFrame]);
}

arcade::Vector2u const& arcade::PacGum::getPos(void) const
{
  return (_pos);
}
