//
// OpenGLGraphic.hpp for  in /home/avelin_j/Work/cpp_arcade/src/graphics/opengl
//
// Made by avelin_j
// Login   <avelin_j@epitech.net>
//
// Started on  Sun Mar 27 20:26:32 2016 avelin_j
// Last update Sat Apr  2 22:30:50 2016 stephane galibert
//

#ifndef OPENGLGRAPHIC_HPP_
# define OPENGLGRAPHIC_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/OpenGL.hpp>
# include <GL/glu.h>
# include <GL/gl.h>
# include <GL/glut.h>
# include <utility>

# include "IGraphic.hpp"
# include "Input.hpp"
# include "CacheManager.hpp"

namespace arcade
{
  class OpenGLGraphic : public IGraphic
  {
  public:
    OpenGLGraphic(void);
    virtual ~OpenGLGraphic(void);
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
    CacheManager<std::string, sf::Texture> _cache;
    std::map<InputT, InputT> _input;
    std::map<DrawableType, std::function<void(Drawable const&)> > _drawer;
    void draw_text(Drawable const& drawable);
    void draw_texture(Drawable const& drawable);
    void draw_rgba(Drawable const& drawable);
    double negToNul(const double nb);
  };
}

extern "C"
{
  arcade::IGraphic *Entry(void)
  {
    return (new arcade::OpenGLGraphic);
  }
};


#endif /* !_OPENGLGRAPHIC_HPP_ */
