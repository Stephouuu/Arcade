//
// Generator.hpp for nibbler in /home/galibe_s/github/mynibbler
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Tue Jul 14 19:10:19 2015 stephane galibert
// Last update Wed Mar  9 16:52:28 2016 stephane galibert
//

#ifndef _GENERATOR_H_
# define _GENERATOR_H_

# include <random>

namespace arcade
{
  class Generator
  {
  public:
    Generator(void);
    ~Generator(void);
    int operator()(unsigned int const min, unsigned int const max);
  private:
    std::default_random_engine *_generator;
    std::random_device _rd;
  };
}

#endif /* !_GENERATOR_H_ */
