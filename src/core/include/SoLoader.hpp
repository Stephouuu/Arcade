//
// SoLoader.hpp for nibbler in /home/galibe_s/github/nibbler/include
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Jun 25 15:41:42 2015 stephane galibert
// Last update Wed Mar  9 16:52:48 2016 stephane galibert
//

#ifndef _SOLOADER_HPP
# define _SOLOADER_HPP

# include <iostream>
# include <string>
# include <dlfcn.h>

# include "Exception.hpp"

namespace arcade
{
  class SoLoader
  {
  public:
    SoLoader(void);
    SoLoader(std::string const& name);
    ~SoLoader(void);
    void setLibName(std::string const& lib);
    void load(void);
    void *sym(std::string const& symbol) const;
  private:
    std::string _name;
    void *_ld;
  };
}

#endif /* !_SOLOADER_HPP */
