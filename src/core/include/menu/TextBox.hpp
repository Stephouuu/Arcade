//
// TextBox.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/core/menu
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Mar 15 17:54:07 2016 stephane galibert
// Last update Wed Mar 30 13:17:41 2016 stephane galibert
//

#ifndef _TEXTBOX_HPP_
# define _TEXTBOX_HPP_

# include "IBox.hpp"

namespace arcade
{
  enum Layout
    {
      LAYOUT_NONE = 0,
      LAYOUT_MIDDLE
    };

  class TextBox : public IBox
  {
  public:
    TextBox(std::string const& text, Vector2u const& pos,
	    Vector2u const& rpos,
	    Vector2u const& size,
	    RGBA const& color,
	    Layout const layout);
    virtual ~TextBox(void);
    virtual void draw(IGraphic *&graphic, bool const bright);
    virtual void setPosition(Vector2u const& pos);
    virtual void setSize(Vector2u const& size);
    virtual void setCharacterSize(size_t const size);
    virtual void setText(std::string const& text);
    virtual void setColor(RGBA const& rgba);

    virtual Vector2u getPosition(void) const;
    virtual Vector2u getRPosition(void) const;
    virtual Vector2u getSize(void) const;
    virtual size_t getCharacterSize(void) const;
    virtual std::string getText(void) const;
    virtual RGBA getColor(void) const;

    virtual bool isClickable(void) const;
    virtual void setClickable(bool const value);
    virtual bool isSelectable(void) const;
    virtual void setSelectable(bool const value);
  private:
    bool _selectable;
    bool _clickable;
    bool _isSelecting;
    bool _isClicking;

    std::string _text;
    size_t _csize;
    Vector2u _pos;
    Vector2u _rpos;
    Vector2u _size;
    RGBA _color;
    Layout _layout;
  };
}

#endif /* !_TEXTBOX_HPP_ */
