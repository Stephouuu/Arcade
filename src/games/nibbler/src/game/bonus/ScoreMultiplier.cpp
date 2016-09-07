//
// ScoreMultiplier.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Mon Mar 21 10:30:35 2016 stephane galibert
// Last update Mon Mar 21 11:25:38 2016 stephane galibert
//

#include "ScoreMultiplier.hpp"

arcade::ScoreMultiplier::ScoreMultiplier(arcade::Player &player)
  : _duration(10000), _player(player)
{
  _pos = player.getHeadPosition();
  _delta = 0;
  _delta_text = 0;
  _player.setScoreCoef(2);
  _text.type = DrawableType::DRAWABLE_TEXT;
  _text.pos = _pos;
  _text.csize = 30;
  _text.text = "Score x2 !";
  _text.rgba = RGBA(255, 255, 255, 255);
}

arcade::ScoreMultiplier::~ScoreMultiplier(void)
{
  _player.setScoreCoef(1);
}

void arcade::ScoreMultiplier::update(float const delta)
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

bool arcade::ScoreMultiplier::isFinish(void) const
{
  return ((size_t)_delta >= _duration);
}
arcade::Drawable const& arcade::ScoreMultiplier::getCurrentDrawable(void) const
{
  return (_text);
}
