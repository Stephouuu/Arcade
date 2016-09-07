//
// AddScore.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Mon Mar 21 02:19:21 2016 stephane galibert
// Last update Mon Mar 21 11:27:28 2016 stephane galibert
//

#include "AddScore.hpp"

arcade::AddScore::AddScore(arcade::Vector2u const& pos, size_t const score)
  : _duration(500)
{
  _pos = pos;
  _delta_text = 0;
  _text.type = DrawableType::DRAWABLE_TEXT;
  _text.pos = _pos;
  _text.text = std::to_string(score);
  _text.csize = 22;
  _text.rgba = RGBA(255, 255, 255, 255);
}

arcade::AddScore::~AddScore(void)
{
  
}

void arcade::AddScore::update(float const delta)
{
  if (_delta_text <= 500)
    {
      _delta_text += delta;
      if (_delta_text <= 300)
	_text.pos.y = _pos.y - ((float)(_delta_text / 300.f) * 50.f);
    }
}
bool arcade::AddScore::isFinish(void) const
{
  return ((size_t)_delta_text >= _duration);
}

arcade::Drawable const& arcade::AddScore::getCurrentDrawable(void) const
{
  return (_text);
}
