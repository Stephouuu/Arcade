//
// RGBA.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/core
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Tue Mar  8 20:26:10 2016 stephane galibert
// Last update Wed Mar  9 16:52:41 2016 stephane galibert
//

#ifndef _RGBA_HPP_
# define _RGBA_HPP_

namespace arcade
{
  struct RGBA
  {
    RGBA(void);
    RGBA(unsigned char const r, unsigned char const g,
	 unsigned char const b, unsigned char const a);
    RGBA(RGBA const& other);
    ~RGBA(void);
    RGBA &operator=(RGBA const& other);
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
  };
}

#endif /* !_RGBA_HPP_ */
