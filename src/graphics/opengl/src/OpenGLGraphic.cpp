//
// SFMLGraphic.cpp for nibbler in /home/galibe_s/github/nibbler/include
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Jun 24 19:14:36 2015 stephane galibert
// Last update Sat Apr  2 22:31:02 2016 stephane galibert
//

#include "OpenGLGraphic.hpp"

arcade::OpenGLGraphic::OpenGLGraphic(void)
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 16;

  this->_win.create(sf::VideoMode(900, 900), "Arcade - OpenGL",
		    sf::Style::Close | sf::Style::Titlebar, settings);
  this->_win.setFramerateLimit(20);
  this->_win.setVerticalSyncEnabled(true);
  this->_win.setMouseCursorVisible(false);

  _input.insert(std::make_pair(InputT(sf::Event::KeyPressed, sf::Keyboard::Up, InputT::None),
  			      InputT(InputT::KeyPressed, Input::Up, InputT::None)));
  _input.insert(std::make_pair(InputT(sf::Event::KeyPressed, sf::Keyboard::Down, InputT::None),
			      InputT(InputT::KeyPressed, Input::Down, InputT::None)));
  _input.insert(std::make_pair(InputT(sf::Event::KeyPressed, sf::Keyboard::Right, 0),
			      InputT(InputT::KeyPressed, Input::Right, InputT::None)));
  _input.insert(std::make_pair(InputT(sf::Event::KeyPressed, sf::Keyboard::Left, InputT::None),
			      InputT(InputT::KeyPressed, Input::Left, InputT::None)));
  _input.insert(std::make_pair(InputT(sf::Event::KeyPressed, sf::Keyboard::P, InputT::None),
			      InputT(InputT::KeyPressed, Input::P, InputT::None)));
  _input.insert(std::make_pair(InputT(sf::Event::KeyPressed, sf::Keyboard::Escape, 0),
			      InputT(InputT::KeyPressed, Input::Escape, InputT::None)));
  _input.insert(std::make_pair(InputT(sf::Event::KeyPressed, sf::Keyboard::Return, 0),
			      InputT(InputT::KeyPressed, Input::Enter, InputT::None)));
  _input.insert(std::make_pair(InputT(sf::Event::KeyPressed, sf::Keyboard::Num2, 0),
			      InputT(InputT::KeyPressed, Input::K2, InputT::None)));
  _input.insert(std::make_pair(InputT(sf::Event::KeyPressed, sf::Keyboard::Num3, 0),
			      InputT(InputT::KeyPressed, Input::K3, InputT::None)));
  _input.insert(std::make_pair(InputT(sf::Event::KeyPressed, sf::Keyboard::Num4, 0),
			      InputT(InputT::KeyPressed, Input::K4, InputT::None)));
  _input.insert(std::make_pair(InputT(sf::Event::KeyPressed, sf::Keyboard::Num5, 0),
			      InputT(InputT::KeyPressed, Input::K5, InputT::None)));
  _input.insert(std::make_pair(InputT(sf::Event::KeyPressed, sf::Keyboard::Num8, 0),
			      InputT(InputT::KeyPressed, Input::K8, InputT::None)));
  _input.insert(std::make_pair(InputT(sf::Event::KeyPressed, sf::Keyboard::Num9, 0),
			      InputT(InputT::KeyPressed, Input::K9, InputT::None)));

  _drawer[DrawableType::DRAWABLE_TEXT] = std::bind(&arcade::OpenGLGraphic::draw_text, this,
						   std::placeholders::_1);
  _drawer[DrawableType::DRAWABLE_TEXTURE] = std::bind(&arcade::OpenGLGraphic::draw_texture, this,
						      std::placeholders::_1);
  _drawer[DrawableType::DRAWABLE_RGBA] = std::bind(&arcade::OpenGLGraphic::draw_rgba, this,
						   std::placeholders::_1);

  if (!_font.loadFromFile("rsrc/ttf/regular.ttf"))
    std::cerr << "Warning: cannot load regular.tff" << std::endl;
}

arcade::OpenGLGraphic::~OpenGLGraphic(void)
{

}

void arcade::OpenGLGraphic::setTitleWindow(std::string const& title)
{
  _win.setTitle("Arcade - OpenGL - " + title);
}

void arcade::OpenGLGraphic::setWindowSize(arcade::Vector2u const& size)
{
  _win.close();
  sf::ContextSettings settings;
  settings.antialiasingLevel = 16;
  this->_win.create(sf::VideoMode(size.x, size.y), "Arcade - OpenGL",
		    sf::Style::Close | sf::Style::Titlebar, settings);
}

bool arcade::OpenGLGraphic::isOpen(void) const
{
  return (this->_win.isOpen());
}

void arcade::OpenGLGraphic::close(void)
{
  this->_win.close();
}

arcade::InputT arcade::OpenGLGraphic::checkInput(void)
{
  sf::Event event;

  while (this->_win.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	this->_win.close();
      InputT in((int)event.type, (int)event.key.code, 0);
      if (_input.find(in) != _input.end())
	return (_input.at(in));
      if (event.type == sf::Event::TextEntered)
	{
	  in.type = InputT::TextEntered;
	  in.unicode = (int)event.text.unicode;
	  return (in);
	}
    }
  return (InputT(InputT::None, InputT::None, InputT::None));
}

void arcade::OpenGLGraphic::clearScreen(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void arcade::OpenGLGraphic::draw(arcade::Drawable const& drawable)
{
  if (_drawer.find(drawable.type) != _drawer.end())
    _drawer[drawable.type](drawable);
}

void arcade::OpenGLGraphic::display(void)
{
  _win.display();
}

void arcade::OpenGLGraphic::draw_text(arcade::Drawable const& drawable)
{
  sf::Text text(drawable.text, _font);
  text.setPosition(drawable.pos.x, drawable.pos.y);
  text.setCharacterSize(drawable.csize);
  text.setColor(sf::Color(drawable.rgba.r, drawable.rgba.g,
  			  drawable.rgba.b, drawable.rgba.a));
  _win.pushGLStates();
  _win.draw(text);
  _win.popGLStates();
}

void arcade::OpenGLGraphic::draw_texture(arcade::Drawable const& drawable)
{
  int	width;
  int	height;

  if (drawable.texture && drawable.texture->data)
    {
      if (!_cache.find(drawable.texture->filename))
	{
	  sf::Texture texture;

	  texture.loadFromMemory(drawable.texture->data, drawable.texture->size);
	  _cache.insert(drawable.texture->filename, texture);
	}
      sf::Texture::bind(&_cache[drawable.texture->filename]);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef((drawable.pos.x + drawable.size.x / 2) - drawable.origin.x,
		   (drawable.pos.y + drawable.size.y / 2) - drawable.origin.y,
		   0);
      if (drawable.rotation != 0)
      	glRotatef(drawable.rotation, 0, 0, 1.0);
      width = drawable.size.x;
      height = drawable.size.y;
      glBegin(GL_QUADS);
      glTexCoord2d(0, 0);
      glVertex2d(-width / 2, -height / 2);
      glTexCoord2d(1, 0);
      glVertex2d(width / 2, -height / 2);
      glTexCoord2d(1, 1);
      glVertex2d(width / 2, height / 2);
      glTexCoord2d(0, 1);
      glVertex2d(-width / 2, height / 2);
      glEnd();
    }
}

void arcade::OpenGLGraphic::draw_rgba(arcade::Drawable const& drawable)
{
  sf::RectangleShape shape;
  shape.setSize(sf::Vector2f(drawable.size.x, drawable.size.y));
  shape.setPosition(sf::Vector2f(drawable.pos.x, drawable.pos.y));
  shape.setFillColor(sf::Color(drawable.rgba.r, drawable.rgba.g,
  			       drawable.rgba.b, drawable.rgba.a));
  _win.draw(shape);
}
