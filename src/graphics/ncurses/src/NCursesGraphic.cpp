//
// SFMLGraphic.cpp for nibbler in /home/galibe_s/github/nibbler/include
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Jun 24 19:14:36 2015 stephane galibert
// Last update Wed Mar 30 14:22:33 2016 stephane galibert
//

#include "NCursesGraphic.hpp"

arcade::NCursesGraphic::NCursesGraphic(void)
{
  _drawer[DRAWABLE_TEXT] = std::bind(&arcade::NCursesGraphic::draw_text, this,
				     std::placeholders::_1);
  _drawer[DRAWABLE_TEXTURE] = std::bind(&arcade::NCursesGraphic::draw_texture, this,
					std::placeholders::_1);
  _drawer[DRAWABLE_RGBA] = std::bind(&arcade::NCursesGraphic::draw_rgba, this,
				     std::placeholders::_1);
  initscr();
  getmaxyx(stdscr, _max.x, _max.y);
  noecho();
  curs_set(0);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  _chars = "azeruiopqsdfhjklmwxcvn1234567890#$";
  _isOpen = true;

  _input[259] = InputT(InputT::KeyPressed, Input::Up, InputT::None);
  _input[258] = InputT(InputT::KeyPressed, Input::Down, InputT::None);
  _input[261] = InputT(InputT::KeyPressed, Input::Right, InputT::None);
  _input[260] = InputT(InputT::KeyPressed, Input::Left, InputT::None);
  _input[112] = InputT(InputT::KeyPressed, Input::P, InputT::None);
  _input[27] = InputT(InputT::KeyPressed, Input::Escape, InputT::None);
  _input[10] = InputT(InputT::KeyPressed, Input::Enter, InputT::None);
  _input[50] = InputT(InputT::KeyPressed, Input::K2, InputT::None);
  _input[51] = InputT(InputT::KeyPressed, Input::K3, InputT::None);
  _input[52] = InputT(InputT::KeyPressed, Input::K4, InputT::None);
  _input[53] = InputT(InputT::KeyPressed, Input::K5, InputT::None);
  _input[56] = InputT(InputT::KeyPressed, Input::K8, InputT::None);
  _input[57] = InputT(InputT::KeyPressed, Input::K9, InputT::None);
}

arcade::NCursesGraphic::~NCursesGraphic(void)
{
  endwin();
}

void arcade::NCursesGraphic::setTitleWindow(std::string const& title)
{
  (void)title;
}

void arcade::NCursesGraphic::setWindowSize(arcade::Vector2u const& size)
{
  _size = size;
}

bool arcade::NCursesGraphic::isOpen(void) const
{
  return (_isOpen);
}

void arcade::NCursesGraphic::close(void)
{
  endwin();
  _isOpen = false;
}

arcade::InputT arcade::NCursesGraphic::checkInput(void)
{
  int input = getch();
  if (_input.find(input) != _input.end())
    {
      InputT in = _input[input];
      in.type = InputT::TextEntered;
      in.unicode = input;
      return (_input[input]);
    }
  return (InputT(InputT::TextEntered, input, input));
}

void arcade::NCursesGraphic::clearScreen(void)
{
  clear();
}

void arcade::NCursesGraphic::draw(arcade::Drawable const& drawable)
{
  if (_drawer.find(drawable.type) != _drawer.end())
  _drawer[drawable.type](drawable);
}

void arcade::NCursesGraphic::display(void)
{
  usleep(100000);
  refresh();
}

void arcade::NCursesGraphic::draw_text(arcade::Drawable const& dw)
{
  move(dw.rpos.y, dw.rpos.x);
  printw(dw.text.data());
}

void arcade::NCursesGraphic::draw_texture(arcade::Drawable const& dw)
{
  if (dw.texture)
    {
      move(dw.rpos.y, dw.rpos.x);
      addch(_chars[dw.texture->size % _chars.size()]);
    }
}

void arcade::NCursesGraphic::draw_rgba(arcade::Drawable const& dw)
{
  (void)dw;
}
