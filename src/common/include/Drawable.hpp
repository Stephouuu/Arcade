//
// Drawable.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Mar 20 20:58:54 2016 stephane galibert
// Last update Tue Mar 29 20:35:14 2016 stephane galibert
//

#ifndef _DRAWABLE_HPP_
# define _DRAWABLE_HPP_

# include <string>

# include "Utility.hpp"
# include "FileCache.hpp"
# include "RGBA.hpp"

namespace arcade
{
  enum DrawableType
    {
      DRAWABLE_NONE = 0,
      DRAWABLE_TEXTURE,
      DRAWABLE_RGBA,
      DRAWABLE_TEXT
    };

  struct Drawable
  {
    Drawable(void)
    {
      type = DRAWABLE_NONE;
      texture = NULL;
      csize = 0;
      rotation = 0;
    }
    Drawable(Drawable const& d)
    {
      *this = d;
    }
    Drawable &operator=(Drawable const& other)
    {
      type = other.type;
      pos = other.pos;
      size = other.size;
      rgba = other.rgba;
      texture = other.texture;
      text = other.text;
      csize = other.csize;
      return (*this);
    }
    DrawableType type;
    Vector2u pos;
    Vector2u size;
    Vector2u origin;
    Vector2u rpos;
    // RGBA
    RGBA rgba;
    // TEXTURE
    FileCache const * texture;
    int rotation;
    // TEXT
    std::string text;
    size_t csize;
  };
}

#endif /* !_DRAWABLE_HPP_ */
