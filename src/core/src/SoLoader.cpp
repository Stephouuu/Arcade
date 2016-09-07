//
// SoLoader.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Mon Mar 28 18:14:44 2016 stephane galibert
// Last update Mon Mar 28 18:14:55 2016 stephane galibert
//

#include "SoLoader.hpp"

arcade::SoLoader::SoLoader(void)
{
  this->_name = "";
  this->_ld = NULL;
}

arcade::SoLoader::SoLoader(std::string const& name)
{
  this->_name = name;
  this->_ld = NULL;
}

arcade::SoLoader::~SoLoader(void)
{
  if (this->_ld)
    dlclose(this->_ld);
}

void arcade::SoLoader::setLibName(std::string const& lib)
{
  if (this->_ld)
    dlclose(this->_ld);
  this->_name = lib;
}

void arcade::SoLoader::load(void)
{
  this->_ld = dlopen(this->_name.data(), RTLD_NOW);
  if (!this->_ld)
    throw (arcade::UnLoaded(std::string(dlerror())));
}

void *arcade::SoLoader::sym(std::string const& symbol) const
{
  char *error = NULL;
  void *sym = NULL;

  dlerror();
  if (_ld)
    {
      sym = dlsym(this->_ld, symbol.c_str());
      error = dlerror();
      if (error)
	{
	  std::cerr << error << std::endl;
	  throw (arcade::BadSym(symbol));
	}
    }
  return (sym);
}
