//
// BSpeed.cpp for arcae in /home/galibe_s/rendu/cpp_arcade/src/games/nibbler/bonus
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Mar 20 23:42:25 2016 stephane galibert
// Last update Mon Mar 28 20:03:43 2016 stephane galibert
//

#include "BSpeed.hpp"

arcade::BSpeed::BSpeed(arcade::Player &player)
  : _duration(10000), _player(player)
{
  _delta = 0;
  _delta_text = 0;
  _pos = _player.getHeadPosition();
  if (_player.getSpeed() - 30 > 30)
    _player.setSpeed(_player.getSpeed() - 30);
  _text.type = DrawableType::DRAWABLE_TEXT;
  _text.pos = _pos;
  _text.csize = 30;
  _text.text = "Speed up !";
  _text.rgba = RGBA(255, 255, 255, 255);

  _progressBar.type = DrawableType::DRAWABLE_RGBA;
  _progressBar.pos = Vector2u(750, 20);
  _progressBar.size = Vector2u(60, 300);
  _progressBar.rgba = RGBA(255, 80, 80, 255);

  _progressText.type = DrawableType::DRAWABLE_TEXT;
  _progressText.pos = _pos;
  _progressText.csize = 20;
  _progressText.text = "Speed up :";
  _progressText.rgba = RGBA(255, 255, 255, 255);
}

arcade::BSpeed::~BSpeed(void)
{
  if (_player.getSpeed() + 30 <= 150)
    _player.setSpeed(_player.getSpeed() + 30);
}

void arcade::BSpeed::update(float const delta)
{
  _delta += delta;
  if (_delta_text <= 1000)
    {
      _delta_text += delta;
      if (_delta_text <= 300)
	_text.pos.y = _pos.y - ((float)(_delta_text / 300.f) * 50.f);
    }
  else
    _text.type = DrawableType::DRAWABLE_NONE;

}

bool arcade::BSpeed::isFinish(void) const
{
  return ((size_t)_delta >= _duration);
}

arcade::Drawable const& arcade::BSpeed::getCurrentDrawable(void) const
{
  return (_text);
}
