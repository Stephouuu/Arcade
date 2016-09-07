//
// Ghost.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/games/pacman
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Mar 26 10:12:13 2016 stephane galibert
// Last update Mon Mar 28 20:53:20 2016 stephane galibert
//

#include "Ghost.hpp"

arcade::Ghost::Ghost(void)
{
  _textureGhost = NULL;
  _textureAfraid = NULL;
  _dirCurrent = Direction::Dir_None;
  _delta = 0;
  _alive = false;
  _afraid = false;
  _speed = REFRESH_DELAY_MS;
  _previous = TileType::EMPTY;
  _start = false;
}

arcade::Ghost::~Ghost(void)
{
  for (size_t i = 0 ; i < _textures.size() ; ++i)
    {
      delete (_textures[i]->texture);
      delete (_textures[i]);
    }
  if (_textureGhost)
    {
      if (_textureGhost->texture)
	delete (_textureGhost->texture);
      delete (_textureGhost);
    }
  if (_textureAfraid)
    {
      if (_textureAfraid->texture)
	delete (_textureAfraid->texture);
      delete (_textureAfraid);
    }
}

void arcade::Ghost::setAfraid(bool const value)
{
  if (value && !_afraid)
    {
      _delta_afraid = 0;
      _speed = REFRESH_DELAY_MS * 2;
    }
  else
    _speed = REFRESH_DELAY_MS;
  _afraid = value;
}

bool arcade::Ghost::isAfraid(void) const
{
  return (_afraid);
}

bool arcade::Ghost::isAlive(void) const
{
  return (_alive);
}

void arcade::Ghost::setAlive(bool const value)
{
  _alive = value;
}

bool arcade::Ghost::hasStarted(void) const
{
  return (_start);
}

void arcade::Ghost::setStart(bool const value)
{
  _start = value;
}
