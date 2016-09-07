//
// Input.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Mar 16 13:58:07 2016 stephane galibert
// Last update Thu Mar 31 15:58:06 2016 stephane galibert
//

#ifndef _INPUT_HPP_
# define _INPUT_HPP_

# include <iostream>
# include <string>

namespace arcade
{
  struct InputT
  {
    static const int None = 0;
    static const int KeyPressed = 1;
    static const int KeyReleased = 2;
    static const int TextEntered = 3;
    InputT(void)
    {
      type = None;
      key = None;
      unicode = None;
    }
    InputT(int const type, int const key, int const unicode)
    {
      this->type = type;
      this->key = key;
      this->unicode = unicode;
    }
    ~InputT(void) {}
    int type;
    int key;
    int unicode;
  };
}

namespace std
{
  template<>
  class less<arcade::InputT>
  {
  public:
    bool operator()(arcade::InputT const& lhs, arcade::InputT const& rhs)
    {
      if (lhs.type != rhs.type)
	return (lhs.type < rhs.type);
      return (lhs.key < rhs.key);
    }
  };
}

#endif /* !_INPUT_HPP_ */
