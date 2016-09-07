//
// SFMLGraphic.hpp for nibbler in /home/galibe_s/github/nibbler
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Jun 24 19:07:11 2015 stephane galibert
// Last update Sat Apr  2 22:26:10 2016 stephane galibert
//

#ifndef _SFMLGRAPHIC_HPP_
# define _SFMLGRAPHIC_HPP_

# include <SFML/Graphics.hpp>
# include <utility>

# include "IGraphic.hpp"
# include "Input.hpp"
# include "CacheManager.hpp"

namespace arcade
{
  class SFMLGraphic : public IGraphic
  {
  public:
    SFMLGraphic(void);
    virtual ~SFMLGraphic(void);
    virtual void setTitleWindow(std::string const& title);
    virtual void setWindowSize(Vector2u const& size);
    virtual bool isOpen(void) const;
    virtual void close(void);
    virtual InputT checkInput(void);

    virtual void clearScreen(void);
    virtual void draw(Drawable const& drawable);
    virtual void display(void);
  private:
    sf::Font _font;
    sf::RenderWindow _win;
    CacheManager<std::string, std::pair<sf::RectangleShape, sf::Texture> > _cache;
    std::map<InputT, InputT> _input;
    std::map<DrawableType, std::function<void(Drawable const&)> > _drawer;
    void draw_text(Drawable const& drawable);
    void draw_texture(Drawable const& drawable);
    void draw_rgba(Drawable const& drawable);
  };
}

extern "C"
{
  arcade::IGraphic *Entry(void)
  {
    return (new arcade::SFMLGraphic);
  }
};


#endif /* !_SFMLGRAPHIC_HPP_ */
