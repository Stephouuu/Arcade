//
// IGraphic.hpp for nibbler in /home/galibe_s/github/nibbler
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Jun 24 19:05:26 2015 stephane galibert
// Last update Sun Mar 27 19:05:50 2016 stephane galibert
//

#ifndef _IGRAPHIC_HPP_
# define _IGRAPHIC_HPP_

# include <iostream>
# include <string>

# include "Protocol.hpp"
# include "Exception.hpp"
# include "Utility.hpp"
# include "FileCache.hpp"
# include "RGBA.hpp"
# include "Input.hpp"

# include "Drawable.hpp"

namespace arcade
{
  class IGraphic
  {
  public:
    virtual ~IGraphic(void) {}
    /* misc */
    virtual void setTitleWindow(std::string const& title) = 0;
    virtual void setWindowSize(Vector2u const& size) = 0;
    virtual bool isOpen(void) const = 0;
    virtual void close(void) = 0;
    /* Input converter */
    virtual InputT checkInput(void) = 0;
    /* screen display */
    virtual void clearScreen(void) = 0;
    virtual void draw(Drawable const& drawable) = 0;
    virtual void display(void) = 0;
  };
}

#endif /* !_IGRAPHIC_HPP_ */
