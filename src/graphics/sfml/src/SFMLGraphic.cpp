//
// SFMLGraphic.cpp for  in /home/avelin_j/Work/cpp_arcade
//
// Made by avelin_j
// Login   <avelin_j@epitech.net>
//
// Started on  Thu Mar 31 18:28:47 2016 avelin_j
// Last update Sat Apr  2 22:22:47 2016 stephane galibert
//

#include "SFMLGraphic.hpp"

arcade::SFMLGraphic::SFMLGraphic(void)
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 16;

  this->_win.create(sf::VideoMode(900, 900), "Arcade - SFML",
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

  _drawer[DrawableType::DRAWABLE_TEXT] = std::bind(&arcade::SFMLGraphic::draw_text, this,
						   std::placeholders::_1);
  _drawer[DrawableType::DRAWABLE_TEXTURE] = std::bind(&arcade::SFMLGraphic::draw_texture, this,
						      std::placeholders::_1);
  _drawer[DrawableType::DRAWABLE_RGBA] = std::bind(&arcade::SFMLGraphic::draw_rgba, this,
						   std::placeholders::_1);

  if (!_font.loadFromFile("rsrc/ttf/regular.ttf"))
    std::cerr << "Warning: cannot load regular.tff" << std::endl;
}

arcade::SFMLGraphic::~SFMLGraphic(void)
{

}

void arcade::SFMLGraphic::setTitleWindow(std::string const& title)
{
  _win.setTitle("Arcade - SFML - " + title);
}

void arcade::SFMLGraphic::setWindowSize(arcade::Vector2u const& size)
{
  _win.close();
  sf::ContextSettings settings;
  settings.antialiasingLevel = 16;
  this->_win.create(sf::VideoMode(size.x, size.y), "Arcade - SFML",
		    sf::Style::Close | sf::Style::Titlebar, settings);
}

bool arcade::SFMLGraphic::isOpen(void) const
{
  return (this->_win.isOpen());
}

void arcade::SFMLGraphic::close(void)
{
  this->_win.close();
}

arcade::InputT arcade::SFMLGraphic::checkInput(void)
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

void arcade::SFMLGraphic::clearScreen(void)
{
  _win.clear();
}

void arcade::SFMLGraphic::draw(arcade::Drawable const& drawable)
{
  if (_drawer.find(drawable.type) != _drawer.end())
    _drawer[drawable.type](drawable);
}

void arcade::SFMLGraphic::display(void)
{
  _win.display();
}

void arcade::SFMLGraphic::draw_text(arcade::Drawable const& drawable)
{
  sf::Text text(drawable.text, _font);
  text.setPosition(drawable.pos.x, drawable.pos.y);
  text.setCharacterSize(drawable.csize);
  text.setColor(sf::Color(drawable.rgba.r, drawable.rgba.g,
			  drawable.rgba.b, drawable.rgba.a));
  _win.draw(text);
}

void arcade::SFMLGraphic::draw_texture(arcade::Drawable const& dw)
{
  std::string filename;
  if (!dw.texture || !dw.texture->data)
    return;
  filename = dw.texture->filename;
  if (!_cache.find(dw.texture->filename))
    {
      sf::RectangleShape shape;
      sf::Texture texture;
      texture.loadFromMemory(dw.texture->data, dw.texture->size);
      _cache.insert(filename, std::make_pair(shape, texture));
      _cache[filename].first.setTexture(&_cache[filename].second);
    }
  _cache[filename].first.setSize(sf::Vector2f(dw.size.x, dw.size.y));
  _cache[filename].first.setPosition(sf::Vector2f(dw.pos.x, dw.pos.y));
  _cache[filename].first.setOrigin(dw.origin.x, dw.origin.y);
  _cache[filename].first.setRotation(dw.rotation);
  _win.draw(_cache[filename].first);
}

void arcade::SFMLGraphic::draw_rgba(arcade::Drawable const& drawable)
{
  sf::RectangleShape shape;
  shape.setSize(sf::Vector2f(drawable.size.x, drawable.size.y));
  shape.setPosition(sf::Vector2f(drawable.pos.x, drawable.pos.y));
  shape.setFillColor(sf::Color(drawable.rgba.r, drawable.rgba.g,
			       drawable.rgba.b, drawable.rgba.a));
  _win.draw(shape);
}
