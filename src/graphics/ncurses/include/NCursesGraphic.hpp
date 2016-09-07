//
// SFMLGraphic.hpp for nibbler in /home/galibe_s/github/nibbler
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Jun 24 19:07:11 2015 stephane galibert
// Last update Wed Mar 30 00:39:25 2016 stephane galibert
//

#ifndef _NCURSES_HPP_
# define _NCURSES_HPP_

# include <ncurses.h>
# include <utility>
# include <unistd.h>
# include <map>
# include <functional>

# include "IGraphic.hpp"
# include "Input.hpp"

namespace arcade
{
  class NCursesGraphic : public IGraphic
  {
  public:
    NCursesGraphic(void);
    virtual ~NCursesGraphic(void);
    virtual void setTitleWindow(std::string const& title);
    virtual void setWindowSize(Vector2u const& size);
    virtual bool isOpen(void) const;
    virtual void close(void);
    virtual InputT checkInput(void);
    virtual void clearScreen(void);
    virtual void draw(Drawable const& drawable);
    virtual void display(void);
  private:
    void draw_text(Drawable const& dw);
    void draw_texture(Drawable const& dw);
    void draw_rgba(Drawable const& dw);
    std::map<DrawableType, std::function<void(Drawable const&)> > _drawer;

    bool _isOpen;
    std::map<int, InputT> _input;

    Vector2u _max;
    Vector2u _size;
    std::string _chars;
  };
}

extern "C"
{
  arcade::IGraphic *Entry(void)
  {
    return (new arcade::NCursesGraphic);
  }
};


#endif /* !_NCURSES_HPP_ */
