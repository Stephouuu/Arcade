//
// Generator.cpp for nibbler in /home/galibe_s/github/mynibbler
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Tue Jul 14 19:10:05 2015 stephane galibert
// Last update Wed Mar  9 16:56:29 2016 stephane galibert
//

#include "Generator.hpp"

arcade::Generator::Generator(void)
{
  this->_generator = new std::default_random_engine(this->_rd());
}

arcade::Generator::~Generator(void)
{
  delete (this->_generator);
}

int arcade::Generator::operator()(unsigned int const min, unsigned int const max)
{
  std::uniform_int_distribution<unsigned int> distrib(min, max);
  return (distrib(*this->_generator));
}
