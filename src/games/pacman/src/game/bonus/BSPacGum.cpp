//
// BSPacGum.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/games/pacman/src/game/bonus
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Mar 27 18:21:47 2016 stephane galibert
// Last update Mon Mar 28 21:21:28 2016 stephane galibert
//

#include "BSPacGum.hpp"

arcade::BSPacGum::BSPacGum(arcade::Player &player,
			   std::vector<arcade::Ghost *> &ghosts)
  : _duration(10000), _duration_text(1000), _player(player), _ghosts(ghosts)
{
  _delta = 0;
  _delta_text = _duration_text + 1;
  player.setMode(Player::EAT);
  _scoreCoef = 1;
  for (auto &it : ghosts)
    if (it->hasStarted())
      it->setAfraid(true);
  _text.type = DrawableType::DRAWABLE_TEXT;
  _text.csize = 18;
  _text.rgba = RGBA(255, 255, 255, 255);
}

arcade::BSPacGum::~BSPacGum(void)
{
  _player.setMode(Player::NORMAL);
}

void arcade::BSPacGum::update(float const delta)
{
  _delta += delta;
  for (auto &it : _ghosts)
    if (it->getPositions() == *_player.getPositions().cbegin()
	&& it->isAlive() && it->isAfraid())
      {
	_delta_text = 0;
	it->setAfraid(false);
	it->setAlive(false);
	_pos = _player.getRealPosition();
	_text.pos.x = _pos.x;
	_player.addScore(200 * _scoreCoef);
	_text.text = std::to_string(200 * _scoreCoef);
	++_scoreCoef;
      }
  if (_delta_text <= _duration_text)
    {
      _text.type = DrawableType::DRAWABLE_TEXT;
      _delta_text += delta;
      if (_delta_text <= 300)
	_text.pos.y = _pos.y - ((float)(_delta_text / 300.f) * 50.f);
    }
  else
    _text.type = DrawableType::DRAWABLE_NONE;
}

bool arcade::BSPacGum::isFinish(void) const
{
  return ((size_t)_delta >= _duration);
}

arcade::Drawable const& arcade::BSPacGum::getCurrentDrawable(void) const
{
  return (_text);
}
