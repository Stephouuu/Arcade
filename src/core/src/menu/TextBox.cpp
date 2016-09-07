//
// TextBox.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Mar 15 18:04:43 2016 stephane galibert
// Last update Wed Mar 30 13:17:28 2016 stephane galibert
//

#include "TextBox.hpp"

arcade::TextBox::TextBox(std::string const& text,
			 arcade::Vector2u const& pos,
			 arcade::Vector2u const& rpos,
			 arcade::Vector2u const& size,
			 arcade::RGBA const& color,
			 arcade::Layout const layout)
{
  _isSelecting = false;
  _isClicking = false;
  _text = text;
  _pos = pos;
  _size = size;
  _color = color;
  _csize = 20;
  _layout = layout;
  _rpos = rpos;
}

arcade::TextBox::~TextBox(void)
{

}

void arcade::TextBox::draw(IGraphic *&graphic, bool const bright)
{
  Drawable dBox;
  Drawable dText;
  size_t x;
  size_t y;

  dBox.type = DrawableType::DRAWABLE_RGBA;
  dBox.pos = _pos;
  dBox.size = _size;
  if (bright)
    dBox.rgba = RGBA(255, 70, 70, _color.a);
  else
    dBox.rgba = _color;

  dText.type = DrawableType::DRAWABLE_TEXT;
  dText.csize = _csize;
  dText.text = _text;
  if (_layout == LAYOUT_MIDDLE)
    {
      x = _pos.x + (_size.x / 2) - ((_csize / 2) * (_text.size() / 2));
      y = _pos.y + (_size.y / 2);
    }
  else
    {
      x = _pos.x + _csize;
      y = _pos.y + _csize;
    }
  dText.pos = Vector2u(x, y);
  dText.rgba = RGBA(255, 255, 255, 255);
  dText.rpos = _rpos;
  graphic->draw(dBox);
  graphic->draw(dText);
}

void arcade::TextBox::setPosition(Vector2u const& pos)
{
  _pos = pos;
}

void arcade::TextBox::setSize(Vector2u const& size)
{
  _size = size;
}

void arcade::TextBox::setCharacterSize(size_t const size)
{
  _csize = size;
}

void arcade::TextBox::setText(std::string const& text)
{
  _text = text;
}

void arcade::TextBox::setColor(arcade::RGBA const& rgba)
{
  _color = rgba;
}

arcade::Vector2u arcade::TextBox::getPosition(void) const
{
  return (_pos);
}

arcade::Vector2u arcade::TextBox::getRPosition(void) const
{
  return (_rpos);
}

arcade::Vector2u arcade::TextBox::getSize(void) const
{
  return (_size);
}

size_t arcade::TextBox::getCharacterSize(void) const
{
  return (_csize);
}

std::string arcade::TextBox::getText(void) const
{
  return (_text);
}

arcade::RGBA arcade::TextBox::getColor(void) const
{
  return (_color);
}

bool arcade::TextBox::isClickable(void) const
{
  return (_clickable);
}

void arcade::TextBox::setClickable(bool const value)
{
  _clickable = value;
}

bool arcade::TextBox::isSelectable(void) const
{
  return (_selectable);
}

void arcade::TextBox::setSelectable(bool const value)
{
  _selectable = value;
}
