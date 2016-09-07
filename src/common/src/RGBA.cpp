//
// RGBA.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/core
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Tue Mar  8 20:25:55 2016 stephane galibert
// Last update Wed Mar  9 17:10:22 2016 stephane galibert
//

#include "RGBA.hpp"

arcade::RGBA::RGBA(void)
{
  r = 255;
  g = 255;
  b = 255;
  a = 255;
}

arcade::RGBA::RGBA(unsigned char const r, unsigned char const g,
		   unsigned char const b, unsigned char const a)
{
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

arcade::RGBA::RGBA(arcade::RGBA const& other)
{
  r = other.r;
  g = other.g;
  b = other.b;
  a = other.a;
}

arcade::RGBA::~RGBA(void)
{

}

arcade::RGBA &arcade::RGBA::operator=(arcade::RGBA const& other)
{
  r = other.r;
  g = other.g;
  b = other.b;
  a = other.a;
  return (*this);
}
